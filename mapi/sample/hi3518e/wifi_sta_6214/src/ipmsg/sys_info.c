
#ifdef CFG_SUPPORT_WIFI_STA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sys_info.h"

static SYSINFO sysInfo;

void initSystem(const char* name, const char* machine)
{
    memset(&sysInfo, 0, sizeof(sysInfo));

    if (name)
    {
        sysInfo.name = (char*)malloc(strlen(name) + 1);
        strcpy(sysInfo.name, name);
    }

    if (machine)
    {
        sysInfo.machine = (char*)malloc(strlen(machine) + 1);
        strcpy(sysInfo.machine, machine);
    }

    sysInfo.udpSock = -1;
}

void setSystemName(const char* name, const char* machine)
{
    if (sysInfo.name)
    { free(sysInfo.name); }

    sysInfo.name = (char*)malloc(strlen(name) + 1);
    strcpy(sysInfo.name, name);

    if (sysInfo.machine)
    { free(sysInfo.machine); }

    sysInfo.machine = (char*)malloc(strlen(name) + 1);
    strcpy(sysInfo.machine, machine);
}

void setSysSock(int udpSock)
{
    sysInfo.udpSock = udpSock;
}

int getUdpSock(void)
{
    return sysInfo.udpSock;
}

char* getSelfName(void)
{
    return sysInfo.name;
}

char* getSelfMachine(void)
{
    return sysInfo.machine;
}

#endif

