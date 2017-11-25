/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_acap.h
* @brief       acap mapi functions declaration
* @author    HiMobileCam middleware develop team
* @date       2016.07.11
*/
#ifndef __HI_MAPI_ACAP_H__
#define __HI_MAPI_ACAP_H__

#include "hi_mapi_acap_define.h"

#define MODULE_NAME   "HI_MAPI_ACAP"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     ACAP */
/** @{ */  /** <!-- [ACAP] */

HI_S32 HI_MAPI_ACap_Init(HI_HANDLE ACapHdl, HI_MPP_ACAP_ATTR_S* pstACapAttr);

HI_S32 HI_MAPI_ACap_DeInit(HI_HANDLE ACapHdl);

HI_S32 HI_MAPI_ACap_Start(HI_HANDLE ACapHdl);

HI_S32 HI_MAPI_ACap_Stop(HI_HANDLE ACapHdl);

HI_S32 HI_MAPI_ACap_SetVolume(HI_HANDLE ACapHdl,HI_MPP_AUDIO_GAIN_S* pstVol);

HI_S32 HI_MAPI_ACap_GetVolume(HI_HANDLE ACapHdl,HI_MPP_AUDIO_GAIN_S* pstVol);

HI_S32 HI_MAPI_ACap_Mute(HI_HANDLE ACapHdl);

HI_S32 HI_MAPI_ACap_UnMute(HI_HANDLE ACapHdl);
/** @}*/  /** <!-- ==== ACAP End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_ACAP_H__ */