/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_mapi_aenc.h
* @brief     ENC module header file
* @author    Hisilicon Hi35xx MPP Team
* @date      2016.07.11
*/
#ifndef __HI_MAPI_ADEC_H__
#define __HI_MAPI_ADEC_H__

#define MODULE_NAME   "HI_MAPI_ADEC"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     ADEC */
/** @{ */  /** <!-- [ADEC] */

HI_S32 HI_MAPI_ADEC_Init(HI_HANDLE AdecHdl,HI_MPP_ADEC_ATTR_S* pstAdecAttr);

HI_S32 HI_MAPI_ADEC_DeInit(HI_HANDLE AdecHdl);

HI_S32 HI_MAPI_ADEC_SendStream(HI_HANDLE AdecHdl,HI_MPP_ADEC_STREAM_S* pstAdecStream,HI_U32 u32Timeout);

HI_S32 HI_MAPI_ADEC_GetFrame(HI_HANDLE AdecHdl,HI_MPP_AUDIO_FRAME_INFO_S* pstAudioFrameInfo,HI_U32 u32Timeout);

HI_S32 HI_MAPI_ADEC_ReleaseFrame(HI_HANDLE AdecHdl,HI_MPP_AUDIO_FRAME_INFO_S* pstAudioFrameInfo);

HI_S32 HI_MAPI_ADEC_Flush(HI_HANDLE AdecHdl);

HI_S32 HI_MAPI_Register_ExtAudioDecoder(HI_MPP_ADEC_DECODER_S enADecoder,HI_HANDLE* ps32ADecoderHdl);

HI_S32 HI_MAPI_UnRegister_ExtAudioDecoder(HI_HANDLE* ps32ADecoderHdl);
/** @}*/  /** <!-- ==== ADEC End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_ADEC_H__ */