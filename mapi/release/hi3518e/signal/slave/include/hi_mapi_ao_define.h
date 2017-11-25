/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_ao_define.h
* @brief       vcap mapi struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.07.11
*/
#ifndef __HI_MAPI_AO_DEFINE_H__
#define __HI_MAPI_AO_DEFINE_H__

#include "hi_mapi_comm_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     AO */
/** @{ */  /** <!-- [AO] */

/* invlalid device ID */
#define HI_MAPI_ERR_AO_INVALID_DEVID     HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_DEVID)
/* invlalid channel ID */
#define HI_MAPI_ERR_AO_INVALID_CHNID     HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_CHNID)
/* at lease one parameter is illagal ,eg, an illegal enumeration value  */
#define HI_MAPI_ERR_AO_ILLEGAL_PARAM     HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_ILLEGAL_PARAM)
/* using a NULL point */
#define HI_MAPI_ERR_AO_NULL_PTR          HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NULL_PTR)
/* try to enable or initialize system,device or channel, before configing attribute */
#define HI_MAPI_ERR_AO_NOT_CONFIG        HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_CONFIG)
/* operation is not supported by NOW */
#define HI_MAPI_ERR_AO_NOT_SUPPORT       HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_SUPPORT)
/* operation is not permitted ,eg, try to change stati attribute */
#define HI_MAPI_ERR_AO_NOT_PERM          HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_PERM)
/* the devide is not enabled  */
#define HI_MAPI_ERR_AO_NOT_ENABLED       HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_UNEXIST)
/* failure caused by malloc memory */
#define HI_MAPI_ERR_AO_NOMEM             HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOMEM)
/* failure caused by malloc buffer */
#define HI_MAPI_ERR_AO_NOBUF             HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOBUF)
/* no data in buffer */
#define HI_MAPI_ERR_AO_BUF_EMPTY         HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUF_EMPTY)
/* no buffer for new data */
#define HI_MAPI_ERR_AO_BUF_FULL          HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUF_FULL)
/* system is not ready,had not initialed or loaded*/
#define HI_MAPI_ERR_AO_SYS_NOTREADY      HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_SYS_NOTREADY)

#define HI_MAPI_ERR_AO_BUSY              HI_MPP_DEF_ERR(HI_MPP_MOD_AO, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUSY)


typedef enum hiMPP_AO_INTF_TYPE_E
{
    HI_MPP_AO_INTF_TYPE_HDMI = 0,
    HI_MPP_AO_INTF_TYPE_ACODEC = 1,
    HI_MPP_AO_INTF_TYPE_BUTT
}HI_MPP_AO_INTF_TYPE_E;

typedef struct hiMPP_AO_ATTR_S
{
    HI_MPP_AUDIO_SAMPLE_RATE_E  enSampleRate;           /*音频采样率，单位赫兹*/
    HI_MPP_AUDIO_BITWIDTH_E     enBitwidth;             /*音频位宽*/
    HI_MPP_AUDIO_SOUND_MODE_E   enSoundMode;      /*音频声道数*/
    HI_MPP_AUDIO_MODE_E enAudioMode;			
    HI_U32                  u32PtNumPerFrm;         /*每帧采样点数*/
    HI_MPP_AO_INTF_TYPE_E enAoIntfType;
} HI_MPP_AO_ATTR_S;

/** @}*/  /** <!-- ==== AO End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_MAPI_AO_DEFINE_H__ */
