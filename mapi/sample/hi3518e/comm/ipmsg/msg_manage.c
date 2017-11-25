
#ifdef CFG_SUPPORT_WIFI_STA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msg_manage.h"


// msg list queue
static PMSGPACK msgList = NULL;
// for msg list operation
static pthread_mutex_t msgMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t msgSendMutex = PTHREAD_MUTEX_INITIALIZER;
static sem_t waitMsgNonEmpty;

#define LOCK_MSGLIST(a)                                         \
    pthread_mutex_lock(&msgMutex);                              \
    {                                                           \
        a;                                                      \
    }                                                           \
    pthread_mutex_unlock(&msgMutex);

#define LOCK_SENDMSG(a)                                         \
    pthread_mutex_lock(&msgSendMutex);                          \
    {                                                           \
        a;                                                      \
    }                                                           \
    pthread_mutex_unlock(&msgSendMutex);

void delMsgEx(PMSGPACK msg)
{
    if (msg->name)
    { free(msg->name); }

    if (msg->machine)
    { free(msg->machine); }

    if (msg->addon)
    {
        if (msg->addon->data)
        { free(msg->addon->data); }

        free(msg->addon);
    }

    free(msg);
}

static void destroyMsgList(void)
{
    PMSGPACK tmpNod;
    LOCK_MSGLIST(
        tmpNod = msgList;

        while (tmpNod)
{
    PMSGPACK tmp = tmpNod->next;
    del_node(&msgList, tmpNod);
        delMsgEx(tmpNod);
        tmpNod = tmp;
    }
    );
}

void initMsg(void)
{
    sem_init(&waitMsgNonEmpty, 0, 0);

    if (msgList != NULL)
    {
        destroyMsgList();
    }
}

int addMsg(PMSGPACK msg)
{
    LOCK_MSGLIST(
        add_node(&msgList, msg);
    );
    sem_post(&waitMsgNonEmpty);
    return 0;
}

PMSGPACK getMsg(void)
{
    PMSGPACK msg = NULL;

    if (sem_wait(&waitMsgNonEmpty) != 0)
    { return NULL; }

    LOCK_MSGLIST(
        msg = msgList;
        del_node(&msgList, msgList);
    );
    return msg;
}

int sendMsg(int sockfd, PMSGPACK msg)
{
    int NumofSend = 0;
    int totSize;
    char tmpString[1024];
    totSize = 10 + 1 + 10 + 1;
    sprintf(tmpString, "%d:%ld:%s:%s:%ld:",
            msg->version, msg->packageNo,
            msg->name, msg->machine, msg->cmd);
    totSize = strlen(tmpString) + 1;

    if (msg->addon)
    {
        totSize += msg->addon->len;
        memcpy(&tmpString[strlen(tmpString)], msg->addon->data, msg->addon->len);
        tmpString[totSize - 1] = '\0';
    }

    LOCK_SENDMSG(
        NumofSend = sendto(sockfd, tmpString, totSize, 0, (struct sockaddr*) & (msg->address), sizeof(msg->address));

        if (NumofSend <= 0)
{
    printf("thy's  func:%s line:%d LOCK_SENDMSG err NumofSend = %d tmpString = %s,totSize =%d \r\n  ", __FUNCTION__, __LINE__, NumofSend, tmpString, totSize);
        perror("Sendto error!");

    }
    );
    return 0;
}

int parseRawMsg(char* raw, int size, PMSGPACK msg)
{
    //版本号(1):包编号:发送者姓名:发送者主机名:命令字:附加信息
    int curMember = 0;
    char* p = raw;

    while ((curMember < 5) && p)
    {
        char* sec = strchr(p, ':');

        if (sec != NULL)
        { *sec++ = '\0'; }

        switch (curMember)
        {
            case 0:
                msg->version = atoi(p);
                break;

            case 1:
                msg->packageNo = atoi(p);
                break;

            case 2:
                if (strlen(p) > 0)
                {
                    msg->name = (char*)malloc(strlen(p) + 1);
                    strcpy(msg->name, p);
                }
                else
                { msg->name = NULL; }

                break;

            case 3:
                if (strlen(p) > 0)
                {
                    msg->machine = (char*)malloc(strlen(p) + 1);
                    strcpy(msg->machine, p);
                }
                else
                { msg->machine = NULL; }

                break;

            case 4:
                msg->cmd = atoi(p);
        }

        curMember++;
        size -= (sec - p);
        p = sec;
    }

    if (p && (size > 0))
    {
        msg->addon = (PMSG_ADDON)malloc(sizeof(MSG_ADDON));
        msg->addon->data = (char*)malloc(size + 1);
        memcpy(msg->addon->data, p, size);
        msg->addon->len = size;
        msg->addon->data[size] = '\0';
    }
    else
    { msg->addon = NULL; }

    return 0;
}

PMSGPACK createMsg(PMSGPACK msg, unsigned long cmd, PMSG_ADDON addon)
{
    msg->version = 1;
    msg->packageNo = time(NULL);
    msg->name = getSelfName();
    msg->machine = getSelfMachine();
    msg->cmd = cmd;
    msg->addon = addon;
    return msg;
}

PMSGPACK createMsgWithPackNo(PMSGPACK msg, unsigned long cmd, unsigned long packageNo, PMSG_ADDON addon)
{
    msg->version = 1;
    msg->packageNo = packageNo;
    msg->name = getSelfName();
    msg->machine = getSelfMachine();
    msg->cmd = cmd;
    msg->addon = addon;
    return msg;
}

#endif
