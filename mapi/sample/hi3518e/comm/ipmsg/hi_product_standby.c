#ifdef CFG_SUPPORT_WIFI_STA

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "sys/prctl.h"

#include "hi_wol.h"



#define I2C_SLAVE_FORCE			0x0706
#define I2C_16BIT_REG			0x0709  /* 16BIT REG WIDTH */
#define I2C_16BIT_DATA			0x070a  /* 16BIT DATA WIDTH */

#define WLC_GET_VERSION			1
#define WLC_GET_REVINFO			98
#define WIFI_INTERFACE			"wlan0"

#define WLC_IOCTL_MAXLEN		8192
#define WLC_GET_VAR				262
#define WLC_SET_VAR				263
#define WLC_SET_PM     86

#define PROP_VALUE_MAX			92
#define SIOCDEVPRIVATE			0x89F0

#define pr_debug printf
#define pr_error printf
#define pr_info  printf

#ifndef TCP_REPAIR
#define TCP_REPAIR		    19
#define TCP_REPAIR_QUEUE	20
#define TCP_QUEUE_SEQ		21
#define TCP_REPAIR_OPTIONS	22
#endif

typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned int	uint32;

extern Standby_Callback Hi_Standby_CB;

#define IPV4_ADDR_LEN 4


extern char sta_on_flag;
static void* standby_thread(void* arg)
{
    char buf[100];
    uint8 mac[6] = {0};
    int len, ret, aux = 1;
    int sock = *(int*)arg;
    printf("sock is %d \n", sock);
    //(HI_VOID)prctl(PR_SET_NAME, (unsigned long)"standby_thread", 0, 0, 0);
	//pthread_detach(pthread_self());

    for (;;)
    {
        len = recv(sock, buf, 100, 0);

		if(len <= 0)
		{
			printf("recv return :%d \n", len);
			close(sock);
			return NULL;
		}

        buf[len] = '\0';

        printf("	standby_thread recv msg: %s  len: %d\n", buf, len);

        if (strncmp(buf, "standby", strlen("standby")) == 0)
        {
            sscanf(buf, "standby%02X:%02X:%02X:%02X:%02X:%02X", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
            printf("	standby buf: %s  buf: 0x%x\n", buf, buf);
            break;
        }
    }
	printf(">>>> %s ,%d \n",__FUNCTION__,__LINE__);

    sta_on_flag = 0;
    Hi_Standby_CB();

    close(sock);

    return NULL;
}





int createWolServer(char* ip, int port)
{
    int ret;
    int tcpSock;
    int wolSock;
    socklen_t len;

    pthread_t wolserver;

    struct sockaddr_in client, local;


    tcpSock = socket(AF_INET, SOCK_STREAM, 0);

    if (tcpSock == -1)
    {
        perror("create socket failed!\n");
        return -1;
    }

    memset(&local, 0, sizeof(struct sockaddr_in));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = htons(port);
    len = sizeof(struct sockaddr);

    ret = bind(tcpSock, (struct sockaddr*)&local, sizeof(struct sockaddr));

    if (ret == -1)
    {
        perror("bind socket failed!\n");
        close(tcpSock);
        return -1;
    }

    ret = listen(tcpSock, 10);

    if (ret == -1)
    {
        perror("listen socket failed!\n");
        close(tcpSock);
        return -1;
    }

    for (;;)
    {
        printf("	accept connection ...\n");
        wolSock = accept(tcpSock, (struct sockaddr*)&client, &len);

        if (wolSock < 0)
        {
            perror("accept socket failed!\n");
            continue;
        }

        printf("	accept new sock: %d\n", wolSock);

#if 1

        standby_thread((void*)&wolSock);
#else
        pthread_create(&wolserver, NULL, &standby_thread, (void*)&wolSock);

        //pthread_join(wolserver,NULL);

#endif
    }

    return 0;
}
#endif
