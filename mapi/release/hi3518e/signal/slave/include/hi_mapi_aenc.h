/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_mapi_aenc.h
* @brief     ENC module header file
* @author    Hisilicon Hi35xx MPP Team
* @date      2016.07.11
*/
#ifndef __HI_MAPI_AENC_H__
#define __HI_MAPI_AENC_H__

#define MODULE_NAME   "HI_MAPI_AENC"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_mapi_aenc_define.h"

/** \addtogroup     AENC */
/** @{ */  /** <!-- [AENC] */

HI_S32 HI_MAPI_AEnc_Init(HI_HANDLE AEncHdl,HI_MPP_AENC_ATTR_S* pstAencAttr);

HI_S32 HI_MAPI_AEnc_DeInit(HI_HANDLE AEncHdl);

HI_S32 HI_MAPI_AEnc_Start(HI_HANDLE AEncHdl);

HI_S32 HI_MAPI_AEnc_Stop(HI_HANDLE AEncHdl);

HI_S32 HI_MAPI_AEnc_RegisterCallback(HI_HANDLE AEncHdl, HI_AENC_CALLBACK_S *pstAencCB);

HI_S32 HI_MAPI_AEnc_UnRegisterCallback(HI_HANDLE AEncHdl, HI_AENC_CALLBACK_S *pstAencCB);

HI_S32 HI_MAPI_AEnc_BindACap(HI_HANDLE ACapHdl,HI_HANDLE AEncHdl);

HI_S32 HI_MAPI_AEnc_UnBindACap(HI_HANDLE ACapHdl,HI_HANDLE AEncHdl);

HI_S32 HI_MAPI_Register_ExtAudioEncoder(HI_MPP_AENC_ENCODER_S* pstAencEncoder,HI_HANDLE* ps32AEncoderHdl);

HI_S32 HI_MAPI_UnRegister_ExtAudioEncoder(HI_HANDLE s32AEncoderHdl);


/** @}*/  /** <!-- ==== AENC End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_AENC_H__ */

