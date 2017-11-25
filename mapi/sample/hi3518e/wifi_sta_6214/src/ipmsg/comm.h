#pragma once
#include "msg_manage.h"

//#define MCAST_ADDR "224.0.0.88"
#define MCAST_ADDR "239.255.255.250"

void ping();
void login();
int ansEntry(PMSGPACK msg);
void logout();