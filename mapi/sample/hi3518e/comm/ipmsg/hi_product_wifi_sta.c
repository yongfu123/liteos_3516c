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



extern HI_S32 HI_Product_ShutDown(void);

HI_S32 HI_Product_OpenWifiStaServer()
{
    HI_S32 s32Ret = HI_SUCCESS;
    static int inited = 0;

    if (!inited)
    {
        inited = 1;
        printf("HI_Product_OpenWifiStaServer init call \n");
    }
    else
    {
        printf("HI_Product_OpenWifiStaServer has already been inited \n");
        return HI_SUCCESS;
    }

    s32Ret =  HI_WOL_Init(HI_Product_ShutDown);

    if (HI_SUCCESS != s32Ret)
    {
        printf("----------------HI_WOL_Init failed---------------\r\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}
#endif

