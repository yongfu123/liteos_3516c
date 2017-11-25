#pragma once

typedef struct sys_info_t
{
    char* name;
    char* machine;
    int udpSock;
} SYSINFO, *PSYSINFO;

void initSystem(const char* name, const char* machine);
void setSystemName(const char* name, const char* machine);
void setSysSock(int udpSock);
int getUdpSock(void);
char* getSelfName(void);
char* getSelfMachine(void);