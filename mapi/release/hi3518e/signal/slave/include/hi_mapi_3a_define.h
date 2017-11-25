/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_3a_define.h
* @brief       3A algorithm struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_3A_DEFINE_H__
#define __HI_MAPI_3A_DEFINE_H__

#include "hi_type.h"
#include "hi_mapi_isp_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define ALG_LIB_NAME_SIZE_MAX   (20)
typedef struct hiMPP_ALG_LIB_S
{
    HI_S32  s32Id;
    HI_CHAR acLibName[ALG_LIB_NAME_SIZE_MAX];
} HI_MPP_ALG_LIB_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__HI_MAPI_3A_DEFINE_H__ */

