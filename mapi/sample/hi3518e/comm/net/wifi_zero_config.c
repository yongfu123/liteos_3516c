#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>  
#include <sys/ioctl.h>  
#include <stdarg.h>
#include <errno.h>
#include <lwip/netdb.h>

#include "wifi_zero_config.h"
#include "bcm_wifi.h"

static struct wifi_info zero_wifi_info;

struct wifi_info *wifi_get_wifi_info(void)
{
	return &zero_wifi_info;
}

void wifi_save_wifi_info(void)
{
	hispinor_erase( FLASH_ZEROCFG_ADDR, FLASH_EDI_MIN_SZIE );
	hispinor_write( &zero_wifi_info, FLASH_ZEROCFG_ADDR, sizeof(struct wifi_info) );
}

struct wifi_info * wifi_zero_info_init(void)
{
	memset( &zero_wifi_info, 0, sizeof(struct wifi_info) );
	hispinor_read( &zero_wifi_info, FLASH_ZEROCFG_ADDR, sizeof(struct wifi_info) );

	return &zero_wifi_info;
}

int wifi_wait_zero_cfg(char *destip, char *rand)
{
	int ret = 0;
	char *passwd = NULL;
	mhd_es_ap_info_t apinfo = {0};

	mhd_es_enable_cooee();

	/* it well always stay here until recv zero config info and callback */
	if (mhd_easy_setup_start( &apinfo )) {
		printf("mhd_easy_setup_start failed. \r\n");
	} else {
		printf("mhd_easy_setup_start done. \r\n");
	}

	/* output the recv config info */
	printf ("\n##############################\n") ;
	printf ("SSID : %s\r\n", apinfo.SSID.val);
	printf ("PASSWORD : %.64s\r\n", apinfo.security_key);
	printf ("BSSID : %02x:%02x:%02x:%02x:%02x:%02x\r\n",
	    (unsigned int)apinfo.BSSID.octet[0], (unsigned int)apinfo.BSSID.octet[1],
	    (unsigned int)apinfo.BSSID.octet[2], (unsigned int)apinfo.BSSID.octet[3],
	    (unsigned int)apinfo.BSSID.octet[4], (unsigned int)apinfo.BSSID.octet[5]);
	printf ("AP Channel : %d\r\n", apinfo.channel);
	printf ("AP Security : %s ",
	    apinfo.security == 0 ? "Open" :
	    apinfo.security == 3 ? "WEP-OPEN" :
	    apinfo.security == 4 ? "WEP-SHARED" :
	    apinfo.security == 5 ? "WPA-PSK TKIP" :
	    apinfo.security == 1 ? "WPA-PSK AES" :
	    apinfo.security == 2 ? "WPA2-PSK AES" :
	    apinfo.security == 6 ? "WPA2-PSK TKIP" :
	    apinfo.security == 7 ? "WPA2-PSK Mixed" :
	    "Unknown" );
	printf ("\n##############################\n") ;

	/* get destip and ramdom value */
	if ( NULL != destip && NULL != rand ) {
		int tlen = apinfo.security_key_length;

		tlen -= ZERO_CONF_RANDOM_LEN;
		memcpy(rand, &apinfo.security_key[tlen], ZERO_CONF_RANDOM_LEN);

		tlen -= ZERO_CONF_ADDR_LEN;
		memcpy(destip, &apinfo.security_key[tlen], ZERO_CONF_ADDR_LEN);

		/* add finish for security */
		apinfo.security_key[tlen] = '\0';
	}

	passwd = (char *)apinfo.security_key;

	/* save zero config info */
	memcpy( &zero_wifi_info.zero_cfg, &apinfo, sizeof(apinfo) );
	
	mhd_start_scan();
	ret |= mhd_sta_connect( (char*)apinfo.SSID.val, apinfo.BSSID.octet, (uint8_t)apinfo.security, (char *)apinfo.security_key, apinfo.channel );
	ret |= mhd_sta_network_up( 0, 0, 0 );

	return ret;
}

void wifi_open_zero_cfg(void)
{
	int ret = 0;
	char random[ZERO_CONF_RANDOM_LEN+1] = {0};
	char destip[ZERO_CONF_ADDR_LEN+1] = {0};

	/* first disconnect sta mode, or zero config doesn't work */
	mhd_sta_disconnect( TRUE );

	/* going for zero config and get the destip and random value */
	ret |= wifi_wait_zero_cfg( destip, random );

	if ( ret ) {
		printf("zero config faild. \r\n");
	} else {
		/* save zero config to flash */
		wifi_save_wifi_info();
	}

	/* create one socket to send response */
	wifi_zero_conf_response( destip, random );
}

void wifi_zero_conf_response(char *addr, char *rand)
{
	int ret = 1;
	struct sockaddr_in dest_addr;
	
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.s_addr = htonl(inet_addr(addr));
	dest_addr.sin_port = htons(5600);
	
	printf("%s, %d, addr = %x, random = %s \r\n", __FUNCTION__, __LINE__, dest_addr.sin_addr.s_addr, rand);
	
	/* zero conf send ack message */
	/*
	ret = zero_conf_send_ack( rand, &dest_addr );
	if ( ret < 0 ) {
		printf("%s, %d   send ack result = %d \r\n", __FUNCTION__, __LINE__, ret); 
	}
	*/
}
