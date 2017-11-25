#ifdef CFG_SUPPORT_WIFI_STA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ipmsg.h"

#include "comm.h"

#include "com_pthread.h"

void ping()//zhubo
{
    MSGPACK msg;
    int udpSock = getUdpSock();
    createMsg(&msg, IPMSG_BR_ENTRY, NULL);
    memset(&(msg.address), 0, sizeof(msg.address));
    msg.address.sin_family = AF_INET;
    msg.address.sin_port = htons(IPMSG_DEFAULT_PORT);
    msg.address.sin_addr.s_addr  = inet_addr(MCAST_ADDR);
    sendMsg(udpSock, &msg);
}

void broadcastping()//guangbo
{
    MSGPACK msg;
    int udpSock = getUdpSock();
    createMsg(&msg, IPMSG_BR_ENTRY, NULL);
    memset(&(msg.address), 0, sizeof(msg.address));
    msg.address.sin_family = AF_INET;
    msg.address.sin_port = htons(IPMSG_DEFAULT_PORT);
    msg.address.sin_addr.s_addr  = inet_addr(INADDR_BROADCAST);
    sendMsg(udpSock, &msg);
}

void problematch(char* ip)
{
    MSGPACK msg;
    int udpSock = getUdpSock();
    createMsg(&msg, IPMSG_ANSENTRY, NULL);
    memset(&(msg.address), 0, sizeof(msg.address));
    msg.address.sin_family = AF_INET;
    msg.address.sin_port = htons(IPMSG_DEFAULT_PORT);
    msg.address.sin_addr.s_addr  = inet_addr(ip);
    sendMsg(udpSock, &msg);
}
void mediaready()
{
    MSGPACK msg;
    int udpSock = getUdpSock();
    createMsg(&msg, IPMSG_MEDIA_SERVER_READY, NULL);
    memset(&(msg.address), 0, sizeof(msg.address));
    msg.address.sin_family = AF_INET;
    msg.address.sin_port = htons(IPMSG_DEFAULT_PORT);
    msg.address.sin_addr.s_addr  = inet_addr(INADDR_BROADCAST);
    sendMsg(udpSock, &msg);
    printf("+++++++++++++++++++++++++++++Media server is ready\n");
    sendMsg(udpSock, &msg);
    sendMsg(udpSock, &msg);
}
#endif
