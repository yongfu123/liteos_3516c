/**
 * Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
 * All rights reserved.
 *
 * @file      hi_mapi_aenc_define.h
 * @brief     ENC module header file
 * @author    Hisilicon Hi35xx MPP Team
 * @date      2016.07.11
 */
#ifndef __HI_MAPI_AENC_DEFINE_H__
#define __HI_MAPI_AENC_DEFINE_H__

#define MODULE_NAME   "HI_MAPI_AENC"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_mapi_comm_define.h"

/** \addtogroup     AENC */
/** @{ *//** <!-- [AENC] */

/** Max audio encode channel number*/
#define HI_AENC_MAX_CHN_NUM 32

/** max count of AENC channel register call backs*/
#define AENC_CHN_REGISTER_CALLBACK_MAX_COUNT  5

/**audio encode attribute*/
typedef struct hiMPP_AENC_ATTR_S
{
    HI_MPP_AUDIO_FORMAT_E enAencFormat; /**< audio encode format type*/
//    HI_MPP_AUDIO_BITRATE_E enBitrate; /**< bite rate*/
 //   HI_MPP_AUDIO_SAMPLE_RATE_E enSampleRate;/**<need to set when audio encode format type is AAC*/
//    HI_MPP_AUDIO_SOUND_MODE_E enSoundMode; /**<audio sound mode*/
    HI_U32 u32PtNumPerFrm; /**<sampling point number per frame*/
//    HI_S16 s16BandWidth; /**< 0 means bandwidth is equal enSampleRate/2 */
    HI_VOID             *pValue; /*pointer of Aenc attr*/
    HI_U32 u32Len;		/*Aenc attr struct len*/
} HI_MPP_AENC_ATTR_S;

/**audio encode stream*/
typedef struct hiMPP_AENC_STREAM_S
{
    HI_U8* pu8Addr; /**< the virtual address of stream */
    HI_U32 u32PhyAddr; /**< the physics address of stream */
    HI_U32 u32Len; /**< stream length, by bytes */
    HI_U64 u64TimeStamp; /**< frame time stamp*/
    HI_U32 u32Seq; /**< frame sequels,if stream is not a valid frame,u32Seq is 0*/
} HI_MPP_AENC_STREAM_S;

typedef HI_S32 (*PFN_AENC_DataProc)(HI_HANDLE AencHdl,
        HI_MPP_AENC_STREAM_S* pAStreamData, HI_VOID *pPrivateData);

/**audio encode call backs*/
typedef struct hiAENC_CALLBACK_S
{
    PFN_AENC_DataProc pfnDataCB;
    HI_VOID *pPrivateData;
} HI_AENC_CALLBACK_S;

typedef struct hiMPP_AENC_ENCODER_S
{
    HI_MPP_AUDIO_FORMAT_E  enType;
    HI_U32          u32MaxFrmLen;
    HI_CHAR         aszName[16];    /* encoder type,be used to print proc information */
    HI_S32          (*pfnOpenEncoder)(HI_VOID *pEncoderAttr, HI_VOID **ppEncoder); /* pEncoder is the handle to control the encoder */
    HI_S32          (*pfnEncodeFrm)(HI_VOID *pEncoder, const HI_MPP_AUDIO_FRAME_S *pstData,
                        HI_U8 *pu8Outbuf,HI_U32 *pu32OutLen);
    HI_S32          (*pfnCloseEncoder)(HI_VOID *pEncoder);
} HI_MPP_AENC_ENCODER_S;

/** @}*//** <!-- ==== AENC End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_MAPI_AENC_DEFINE_H__ */
