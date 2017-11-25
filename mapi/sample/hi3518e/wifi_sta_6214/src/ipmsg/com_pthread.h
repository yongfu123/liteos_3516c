#pragma once
#ifdef _WIN32
#include "pthread.h"
#include "semaphore.h"
#define sleep(s)	Sleep((s) * 1000)
#else
#include <pthread.h>
#include <semaphore.h>
#endif
