#include "coap_config.h"
#include <coap.h>

coap_context_t *main_coap_context;

#define TEST_CONTENT "Hello CoAP test!!!\n\n"
struct coap_resource_t *test_resource = NULL;

void 
hnd_get_test(coap_context_t  *ctx, struct coap_resource_t *resource, 
          const coap_endpoint_t* local_if, coap_address_t *peer, 
          coap_pdu_t *request, str *token, coap_pdu_t *response) {
  unsigned char buf[3];
  coap_opt_iterator_t opt_iter;

  response->hdr->code = COAP_RESPONSE_CODE(205);

  if (coap_find_observer(resource, peer, token)) {
    /* FIXME: need to check for resource->dirty? */
    coap_add_option(response, COAP_OPTION_OBSERVE, 
		    coap_encode_var_bytes(buf, ctx->observe), buf);
  }

  coap_add_option(response, COAP_OPTION_CONTENT_TYPE,
	  coap_encode_var_bytes(buf, COAP_MEDIATYPE_TEXT_PLAIN), buf);

  coap_add_option(response, COAP_OPTION_MAXAGE,
	  coap_encode_var_bytes(buf, 0x2ffff), buf);
    
  coap_add_data(response, strlen(TEST_CONTENT), (unsigned char *)TEST_CONTENT);
}

/* changeable clock base (see handle_put_time()) */
static time_t my_clock_base = 0;
static time_t clock_offset;
struct coap_resource_t *time_resource = NULL;

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

void 
hnd_get_time(coap_context_t  *ctx, struct coap_resource_t *resource, 
         const coap_endpoint_t* local_if, coap_address_t *peer, 
         coap_pdu_t *request, str *token, coap_pdu_t *response) {
  coap_opt_iterator_t opt_iter;
  coap_opt_t *option;
  unsigned char buf[40];
  size_t len;
  time_t now;
  coap_tick_t t;

  /* FIXME: return time, e.g. in human-readable by default and ticks
   * when query ?ticks is given. */

  /* if my_clock_base was deleted, we pretend to have no such resource */
  response->hdr->code = 
    my_clock_base ? COAP_RESPONSE_CODE(205) : COAP_RESPONSE_CODE(404);

  if (coap_find_observer(resource, peer, token)) {
    /* FIXME: need to check for resource->dirty? */
    coap_add_option(response, 
                    COAP_OPTION_OBSERVE, 
		            coap_encode_var_bytes(buf, ctx->observe), buf);
  }

  if (my_clock_base)
    coap_add_option(response, 
                    COAP_OPTION_CONTENT_FORMAT,
		            coap_encode_var_bytes(buf, COAP_MEDIATYPE_TEXT_PLAIN), buf);

  coap_add_option(response, 
                  COAP_OPTION_MAXAGE,
	              coap_encode_var_bytes(buf, 0x01), buf);

  if (my_clock_base) {
    /* calculate current time */
    coap_ticks(&t);
    now = my_clock_base + (t / COAP_TICKS_PER_SECOND);

    if (request != NULL
	    && (option = coap_check_option(request, COAP_OPTION_URI_QUERY, &opt_iter))
	    && memcmp(COAP_OPT_VALUE(option), "ticks",
		min(5, COAP_OPT_LENGTH(option))) == 0) {

      /* output ticks */
      len = snprintf((char *)buf, 
	                 min(sizeof(buf), response->max_size - response->length),
		             "%u", (unsigned int)now);
      coap_add_data(response, len, buf);

    } else {			/* output human-readable time */
      struct tm *tmp;
      tmp = gmtime(&now);
      len = strftime((char *)buf, 
		             min(sizeof(buf), response->max_size - response->length),
		             "%b %d %H:%M:%S", tmp);

      coap_add_data(response, len, buf);
    }
  }
}


void
init_coap_resources(coap_context_t *ctx) {
  coap_resource_t *r;

  /* store clock base to use in /time */
  coap_ticks(&my_clock_base);
  r = coap_resource_init((unsigned char *)"time", 4, 0);
  coap_register_handler(r, COAP_REQUEST_GET, hnd_get_time);
  //coap_register_handler(r, COAP_REQUEST_PUT, hnd_put_time);
  //coap_register_handler(r, COAP_REQUEST_DELETE, hnd_delete_time);

  coap_add_attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  coap_add_attr(r, (unsigned char *)"title", 5, (unsigned char *)"\"Internal Clock\"", 16, 0);
  coap_add_attr(r, (unsigned char *)"rt", 2, (unsigned char *)"\"Ticks\"", 7, 0);
  r->observable = 1;
  coap_add_attr(r, (unsigned char *)"if", 2, (unsigned char *)"\"clock\"", 7, 0);

  coap_add_resource(ctx, r);
  time_resource = r;
  
#if 1
  r = coap_resource_init((unsigned char *)"test", 4, 0);
  if (!r)
    goto error;

  r->observable = 1;

  coap_register_handler(r, COAP_REQUEST_GET, hnd_get_test);
#if 0
  coap_register_handler(r, COAP_REQUEST_PUT, hnd_put_time);
  coap_register_handler(r, COAP_REQUEST_DELETE, hnd_delete_time);
#endif
  coap_add_attr(r, (unsigned char *)"ct", 2, (unsigned char *)"0", 1, 0);
  /* coap_add_attr(r, (unsigned char *)"title", 5, (unsigned char *)"\"Internal Clock\"", 16, 0); */
  coap_add_attr(r, (unsigned char *)"rt", 2, (unsigned char *)"\"Text\"", 6, 0);
  coap_add_attr(r, (unsigned char *)"if", 2, (unsigned char *)"\"Test\"", 6, 0);

  coap_add_resource(ctx, r);
  test_resource = r;
#endif

  return;
 error:
  coap_log(LOG_CRIT, "cannot create resource\n");
}

void server_coap_init(void)
{
	coap_address_t listenaddress;

	coap_address_init(&listenaddress);

	/* looks like a server address, but is used as end point for clients too */

    listenaddress.addr = *(IP_ADDR_ANY);
	listenaddress.port = COAP_DEFAULT_PORT;

	main_coap_context = coap_new_context(&listenaddress);

	LWIP_ASSERT("Failed to initialize context", main_coap_context != NULL);

    init_coap_resources(main_coap_context);
}

void server_coap_poll(void)
{
    if (test_resource && test_resource->subscribers)
        test_resource->dirty = 1;
    if (time_resource && time_resource->subscribers)
        time_resource->dirty = 1;
    
	coap_check_notify(main_coap_context);
}


#include <lwip/init.h>
#include <lwip/timers.h>

#include <netif/etharp.h>
//#include <netif/tapif.h>

#include <signal.h>



void server_coap_main(VOID)
{
	/* start applications here */
	server_coap_init();

	printf("printf: CoAP Applications started.\n");

	while (1) {
		/* poll netif, pass packet to lwIP */
		//tapif_select(&netif);

		//sys_check_timeouts();
		os_sleep(2, 0);

		server_coap_poll();
	}

	return 0;
}

UINT32 osShell_coaps(int arg_num, char **argv )
{
  int i;
  UINT32 uwRet;
  UINT32 uwShellTask;
  
  TSK_INIT_PARAM_S stInitParam = {server_coap_main, 11, {0}, 0x6000, "coaps", LOS_TASK_STATUS_DETACHED};
  uwRet = LOS_TaskCreate(&uwShellTask, &stInitParam);
  if(uwRet != LOS_OK)
  {
      return uwRet;
  }
  
  return 0;  
}

