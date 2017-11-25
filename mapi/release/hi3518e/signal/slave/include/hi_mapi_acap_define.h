/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_acap_define.h
* @brief       vcap mapi struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.07.11
*/
#ifndef __HI_MAPI_ACAP_DEFINE_H__
#define __HI_MAPI_ACAP_DEFINE_H__

#include "hi_mapi_comm_define.h"

#define MODULE_NAME   "HI_MAPI_ACAP"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     ACAP */
/** @{ */  /** <!-- [ACAP] */
#define HI_ACAP_MAX_NUM 1
#define HI_MPP_ACAP_MIN_GAIN -78
#define HI_MPP_ACAP_MAX_GAIN 80

typedef struct hiMPP_ACAP_ATTR_S
{
    HI_MPP_AUDIO_SAMPLE_RATE_E  enSampleRate;           /*音频采样率，单位赫兹*/
    HI_MPP_AUDIO_BITWIDTH_E     enBitwidth;             /*音频位宽*/
    HI_MPP_AUDIO_SOUND_MODE_E   enSoundMode;      /*音频声道数*/
    HI_MPP_AUDIO_MODE_E enAudioMode;			
    HI_U32                  u32PtNumPerFrm;         /*每帧采样点数*/
} HI_MPP_ACAP_ATTR_S;

typedef enum hiEN_ACAP_ERR_CODE_E
{
    EN_ACAP_INVALID_FD = 0x40, 
    EN_ACAP_IOCTL_FAIL = 0x41,
    EN_ACAP_OVERRANGE = 0x42,
    EN_ACAP_NOT_INITED = 0x43,
    EN_ACAP_NOT_STARTED = 0x44
}EN_ACAP_ERR_CODE_E;

/** Null pointer error for acap*/
#define HI_ERR_MAPI_ACAP_NULL_PTR                              		HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ERR_NULL_PTR)
/** illegal parameter error for acap*/
#define HI_ERR_MAPI_ACAP_ILLEGAL_PARA                              HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ERR_ILLEGAL_PARAM)
/** invalid fd error for acap*/
#define HI_ERR_MAPI_ACAP_INVALID_FD					HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ACAP_INVALID_FD)
/** ioctl fail error for acap*/
#define HI_ERR_MAPI_ACAP_IOCTL_FAIL					HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ACAP_IOCTL_FAIL)
/** not support error for acap*/
#define HI_ERR_MAPI_ACAP_NOTSUPPORT					HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ERR_NOT_SUPPORT)
/** overrange error for acap*/
#define HI_ERR_MAPI_ACAP_OVERRANGE					HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ACAP_OVERRANGE)
/** not inited error for acap*/
#define HI_ERR_MAPI_ACAP_NOT_INITED					HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ACAP_NOT_INITED)
/** not start error for acap*/
#define HI_ERR_MAPI_ACAP_NOT_STARTED					HI_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ACAP_NOT_STARTED)

#define HI_ERR_MAPI_ACAP_NOT_PREM                   HI_MPP_DEF_ERR(HI_MPP_MOD_ACAP,EN_ERR_LEVEL_ERROR,EN_ERR_NOT_PERM)

/** @}*/  /** <!-- ==== ACAP End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_MAPI_ACAP_DEFINE_H__ */