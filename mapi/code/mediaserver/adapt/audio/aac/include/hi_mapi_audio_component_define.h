#ifndef __AUDIO_COMPONENT_DEFINE_H__
#define __AUDIO_COMPONENT_DEFINE_H__

#include "hi_mapi_comm_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


/*samples per frame for AACLC and aacPlus */
#define AACLC_SAMPLES_PER_FRAME         1024
#define AACPLUS_SAMPLES_PER_FRAME       2048

/*max length of AAC stream by bytes */
#define MAX_AAC_MAINBUF_SIZE    768*2

typedef enum hiAAC_TYPE_E
{
    AAC_TYPE_AACLC      = 0,            /* AAC LC */
    AAC_TYPE_EAAC       = 1,            /* eAAC  (HEAAC or AAC+  or aacPlusV1) */
    AAC_TYPE_EAACPLUS   = 2,            /* eAAC+ (AAC++ or aacPlusV2) */
    AAC_TYPE_BUTT,
} AAC_TYPE_E;

typedef enum hiAAC_BPS_E
{
	AAC_BPS_16K     = 16000,
    AAC_BPS_22K     = 22000,
    AAC_BPS_24K     = 24000,
    AAC_BPS_32K     = 32000,
    AAC_BPS_48K     = 48000,
    AAC_BPS_64K     = 64000,
    AAC_BPS_96K     = 96000,
    AAC_BPS_128K    = 128000,
    AAC_BPS_256K    = 256000,
    AAC_BPS_320K    = 320000,
    AAC_BPS_BUTT
} AAC_BPS_E;

typedef struct hiAAC_FRAME_INFO_S
{
    HI_S32 s32Samplerate;   /* sample rate*/
    HI_S32 s32BitRate;                  /* bitrate */
    HI_S32 s32Profile;                  /* profile*/
    HI_S32 s32TnsUsed;                  /* TNS Tools*/
    HI_S32 s32PnsUsed;                  /* PNS Tools*/
} AAC_FRAME_INFO_S;

/*
    AAC Commendatory Parameter:
    Sampling Rate(HZ)   LC BitRate(Kbit/s)  EAAC BitRate (Kbit/s)   EAAC+ BitRate (Kbit/s)
    48000               128                 48                      32¡¢24
    44100               128                 48                      32¡¢24
    32000               96                  22                      16
    24000               64
    22050               64
    16000               48
*/
typedef enum hiAAC_TRANS_TYPE_E
{
    AAC_TRANS_TYPE_ADTS = 0,
    AAC_TRANS_TYPE_LOAS= 1,
    AAC_TRANS_TYPE_LATM_MCP1 = 2,
    AAC_TRANS_TYPE_BUTT
}AAC_TRANS_TYPE_E;

typedef struct hiAENC_ATTR_AAC_S
{
    AAC_TYPE_E          enAACType;   /* AAC profile type */
    AAC_BPS_E           enBitRate;   /* AAC bitrate (LC:48~128, EAAC:22~48, EAAC+:16~32)*/
    HI_MPP_AUDIO_SAMPLE_RATE_E enSmpRate;   /* AAC sample rate (LC:16~48, EAAC:32~48, EAAC+:32~48)*/
    HI_MPP_AUDIO_BITWIDTH_E   enBitWidth;  /* AAC bit width (only support 16bit)*/
    HI_MPP_AUDIO_SOUND_MODE_E  enSoundType; /* sound type of inferent audio frame */
    AAC_TRANS_TYPE_E    enTransType;
    
    HI_S16              s16BandWidth; /* targeted audio bandwidth in Hz (0 or 1000~enSmpRate/2), the default is 0*/
} AENC_ATTR_AAC_S;

typedef struct hiADEC_ATTR_AAC_S
{
    HI_U32 resv;
} ADEC_ATTR_AAC_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
