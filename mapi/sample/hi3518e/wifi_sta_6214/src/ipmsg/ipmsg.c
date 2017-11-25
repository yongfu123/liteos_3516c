
#define H18E9732

#ifdef CFG_SUPPORT_WIFI_STA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <stdarg.h>
#include <errno.h>
#include <lwip/netdb.h>

#include "debug.h"

#include "ipmsg.h"
#include "comm.h"

#include "hi_wol.h"

#include "sys/prctl.h"

static pthread_t wol_tid;
Standby_Callback Hi_Standby_CB = NULL;

char sta_on_flag = 0;

void* pingThread(void* arg)
{
    (HI_VOID)prctl(PR_SET_NAME, (unsigned long)"pingThread", 0, 0, 0);
    pthread_detach(pthread_self());

    while (1)
    {
        if (sta_on_flag)
        {
            ping();
			broadcastping();
        }

        if (hi_getmsclock() < 2000)
        {
            usleep(300 * 1000);
        }
        else
        {
            usleep(1200 * 1000);
        }
    }

    return NULL;
}

int createSrv()
{
    struct sockaddr_in udpAddr;
    int err;
    int on = 1;
    size_t len = sizeof(on);
    int udpSock;

    udpSock = socket(AF_INET, SOCK_DGRAM, 0);

    udpAddr.sin_family = AF_INET;
    udpAddr.sin_port = htons(IPMSG_DEFAULT_PORT);
    udpAddr.sin_addr.s_addr = htonl(INADDR_ANY);


    int loop = 1;
    err = setsockopt(udpSock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));

    if (err < 0)
    {
        perror("setsockopt():IP_MULTICAST_LOOP");
        close(udpSock);
        return -1;
    }

    struct ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_ADDR);

    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    err = setsockopt(udpSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    if (err < 0)
    {
        perror("setsockopt():IP_ADD_MEMBERSHIP");
        close(udpSock);
        return -1;
    }

    int bBroadcast = 1;
    err = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST, &bBroadcast, sizeof(bBroadcast));

    if (err < 0)
    {
        perror("setsockopt():IP_MULTICAST_LOOP");
        close(udpSock);
        return -1;
    }

    if (bind(udpSock, (struct sockaddr*)&udpAddr, sizeof(udpAddr)) < 0)
    {
        F_PERROR("Udp socket bind error.");
        close(udpSock);
        return -1;
    }

    setSysSock(udpSock);
    pthread_t tid;
    pthread_attr_t attr;
    memset(&attr, 0, sizeof(attr));
    attr.schedparam.sched_priority = 9;

    return 0;
}

pthread_t ping_thread_pid;
void* hi_wol_thread(void* arg)
{
    int err, ret, sock;
    int port = 9528;
    char* machine = "hisilicon";

printf(">>>> %s ,%d \n",__FUNCTION__,__LINE__);
    //pthread_t httper;
#ifdef H18E9732
    initSystem("18E_OV9732", machine);
#else
    initSystem("dv_board", machine);
#endif
    initMsg();
    (HI_VOID)prctl(PR_SET_NAME, (unsigned long)"hi_wol_thread", 0, 0, 0);


    for (;;)
    {
        err = createSrv();

        if (err == 0)
        { break; }

        sleep(1);
    }

    sta_on_flag = 1;

    pthread_attr_t attr;
    memset(&attr, 0, sizeof(attr));
    attr.schedparam.sched_priority = 9;
    pthread_create(&ping_thread_pid, &attr, &pingThread, NULL);

    //pthread_join(httper,NULL);

    ret = createWolServer(NULL, port);

    if (ret )
    {
        printf("create tcp 9528 fail ------------\n");
    }

    return NULL;
}

HI_S32 HI_WOL_Init(Standby_Callback pStandbyCB)
{
    Hi_Standby_CB = pStandbyCB;
    pthread_create(&wol_tid, NULL, hi_wol_thread, NULL);
    //pthread_join(wol_tid,NULL);
    return HI_SUCCESS;
}
#endif

