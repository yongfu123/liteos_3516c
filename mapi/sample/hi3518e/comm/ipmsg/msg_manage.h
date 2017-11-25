#pragma once
#include "lnklst.h"
#include "com_pthread.h"
#include "com_ether.h"
#include "lwip/sockets.h"

typedef struct msg_addon_t
{
    char* data;
    int len;
} MSG_ADDON, *PMSG_ADDON;

typedef struct msg_info_t
{
    struct msg_info_t* next;
    int version;
    unsigned long int packageNo;
    char* name;
    char* machine;
    unsigned long int cmd;
    PMSG_ADDON addon;
    struct sockaddr_in address;
    void* priv;
} MSGPACK, *PMSGPACK;

void initMsg(void);
int addMsg(PMSGPACK msg);
PMSGPACK getMsg(void);
int sendMsg(int sockfd, PMSGPACK msg);
int parseRawMsg(char* raw, int size, PMSGPACK msg);
PMSGPACK createMsg(PMSGPACK msg, unsigned long cmd, PMSG_ADDON addon);
PMSGPACK createMsgWithPackNo(PMSGPACK msg, unsigned long cmd, unsigned long packageNo, PMSG_ADDON addon);
void delMsgEx(PMSGPACK msg);