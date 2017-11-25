/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_mapi_comm_define.h
* @brief     define of common struct
* @author    HiMobileCam middleware develop team
* @date      2016.06.08
*/
#ifndef __HI_COMM_DEFINE_H__
#define __HI_COMM_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_mapi_errno.h"

/** \addtogroup     COMM */
/** @{ */  /** <!-- [COMM] */

#define MUTEX_INIT_LOCK(mutex) \
do { \
	(void)pthread_mutex_init(&mutex, NULL); \
}while(0)

#define MUTEX_LOCK(mutex) \
do { \
	(void)pthread_mutex_lock(&mutex); \
}while(0)

#define MUTEX_UNLOCK(mutex) \
do { \
	(void)pthread_mutex_unlock(&mutex); \
}while(0)

#define MUTEX_DESTROY(mutex) \
do { \
	(void)pthread_mutex_destroy(&mutex); \
}while(0)

typedef struct hiMPP_RESOLUTION_S
{
    HI_U32 u32Width;
    HI_U32 u32Height;
} HI_MPP_RESOLUTION_S;

typedef struct hiMPP_RECT_S
{
    HI_U32 u32X;
    HI_U32 u32Y;
    HI_U32 u32Width;
    HI_U32 u32Height;
} HI_MPP_RECT_S;

typedef enum hiHI_MPP_MOD_ID_E
{
    HI_MPP_MOD_SYS = 0,
    HI_MPP_MOD_VCAP,
    HI_MPP_MOD_VPROC,
    HI_MPP_MOD_VENC,
    HI_MPP_MOD_ACAP,
    HI_MPP_MOD_AENC,
    HI_MPP_MOD_ADEC,
    HI_MPP_MOD_AO,
    HI_MPP_MOD_DISP,
    HI_MPP_MOD_VDEC,
    HI_MPP_MOD_BUTT,
} HI_MPP_MOD_ID_E;

typedef enum hiMPP_PIXEL_FORMAT_E
{
    HI_MPP_PIXEL_FORMAT_420 = 0,
    HI_MPP_PIXEL_FORMAT_422,
    HI_MPP_PIXEL_FORMAT_RGB_1555,
    HI_MPP_PIXEL_FORMAT_RGB_8888,
    HI_MPP_PIXEL_FORMAT_RGB_BAYER_8BPP,			/**<Raw 8bit*/
    HI_MPP_PIXEL_FORMAT_RGB_BAYER_10BPP,		/**<Raw 10bit*/
    HI_MPP_PIXEL_FORMAT_RGB_BAYER_12BPP,		/**<Raw 12bit*/
    HI_MPP_PIXEL_FORMAT_RGB_BAYER_14BPP,		/**<Raw 14bit*/
    HI_MPP_PIXEL_FORMAT_RGB_BAYER,				/**<Raw 16bit*/
    HI_MPP_PIXEL_FORMAT_BUTT
} HI_MPP_PIXEL_FORMAT_E;

typedef enum hiHI_MPP_PAYLOAD_TYPE_E
{
    HI_MPP_PAYLOAD_TYPE_H264,
    HI_MPP_PAYLOAD_TYPE_H265,
    HI_MPP_PAYLOAD_TYPE_MJPEG,
    HI_MPP_PAYLOAD_TYPE_JPEG,
    HI_MPP_PAYLOAD_TYPE_AAC,
    HI_MPP_PAYLOAD_TYPE_BUTT
} HI_MPP_PAYLOAD_TYPE_E;

typedef enum hiFRAME_DATA_TYPE_E
{
    HI_FRAME_DATA_TYPE_RAW,
    HI_FRAME_DATA_TYPE_YUV,
    HI_FRAME_DATA_TYPE_BUTT
} HI_FRAME_DATA_TYPE_E;

typedef struct hiFRAME_DATA_S
{
    HI_FRAME_DATA_TYPE_E enFrameDataType;
    HI_U32          u32Width;
    HI_U32          u32Height;
    HI_MPP_PIXEL_FORMAT_E  enPixelFormat;
    HI_U32          u32PhyAddr[3];
    HI_VOID*        pVirAddr[3];
    HI_U32          u32Stride[3];
    HI_U64          u64pts;
} HI_FRAME_DATA_S;


typedef enum hiMPP_AUDIO_SAMPLE_RATE_E
{
    HI_MPP_AUDIO_SAMPLE_RATE_8     = 8000,   /* 8K Sample rate     */
    HI_MPP_AUDIO_SAMPLE_RATE_11025 = 11025,   /* 11.025K Sample rate*/
    HI_MPP_AUDIO_SAMPLE_RATE_16    = 16000,   /* 16K Sample rate    */
    HI_MPP_AUDIO_SAMPLE_RATE_22050 = 22050,   /* 22.050K Sample rate*/
    HI_MPP_AUDIO_SAMPLE_RATE_24    = 24000,   /* 24K Sample rate    */
    HI_MPP_AUDIO_SAMPLE_RATE_32    = 32000,   /* 32K Sample rate    */
    HI_MPP_AUDIO_SAMPLE_RATE_441   = 44100,   /* 44.1K Sample rate  */
    HI_MPP_AUDIO_SAMPLE_RATE_48    = 48000,   /* 48K Sample rate    */
    HI_MPP_AUDIO_SAMPLE_RATE_BUTT
} HI_MPP_AUDIO_SAMPLE_RATE_E;

typedef enum hiMPP_AUDIO_MODE_E
{
    HI_MPP_AUDIO_MODE_I2S_MASTER  = 0,   /* AIO I2S master mode */
    HI_MPP_AUDIO_MODE_I2S_SLAVE,         /* AIO I2S slave mode */
    HI_MPP_AUDIO_MODE_PCM_SLAVE_STD,     /* AIO PCM slave standard mode */
    HI_MPP_AUDIO_MODE_PCM_SLAVE_NSTD,    /* AIO PCM slave non-standard mode */
    HI_MPP_AUDIO_MODE_PCM_MASTER_STD,    /* AIO PCM master standard mode */
    HI_MPP_AUDIO_MODE_PCM_MASTER_NSTD,   /* AIO PCM master non-standard mode */
    HI_MPP_AUDIO_MODE_BUTT    
} HI_MPP_AUDIO_MODE_E;


typedef enum hiMPP_AUDIO_BITWIDTH_E
{
    HI_MPP_AUDIO_BITWIDTH_8   = 0,   /* Bit width is 8 bits   */
    HI_MPP_AUDIO_BITWIDTH_16  = 1,   /* Bit width is 16 bits  */
    HI_MPP_AUDIO_BITWIDTH_24  = 2,   /* Bit width is 24 bits  */
    HI_MPP_AUDIO_BITWIDTH_BUTT
} HI_MPP_AUDIO_BITWIDTH_E;

typedef enum hiMPP_AUDIO_SOUND_MODE_E
{
    HI_MPP_AUDIO_SOUND_MODE_LEFT = 0,
    HI_MPP_AUDIO_SOUND_MODE_RIGHT = 1,
    HI_MPP_AUDIO_SOUND_MODE_STEREO = 2,
    HI_MPP_AUDIO_SOUND_MODE_BUTT
} HI_MPP_AUDIO_SOUND_MODE_E;

typedef enum hiMPP_AUDIO_SOUND_TYPE_E
{
	HI_MPP_AUDIO_SOUND_TYPE_MONO = 0,
	HI_MPP_AUDIO_SOUND_TYPE_STEREO = 1,
	HI_MPP_AUDIO_SOUND_TYPE_BUTT
}HI_MPP_AUDIO_SOUND_TYPE_E;


typedef struct hiMPP_AUDIO_GAIN_S
{
    HI_S32 s32Gain;					/*Gain,-78~80,recommend 19~50*/
}HI_MPP_AUDIO_GAIN_S;


/*音频编码格式*/
typedef enum hiMPP_AUDIO_FORMAT_E
{
    HI_MPP_AUDIO_FORMAT_G711A   = 1,   /* G.711 A            */
    HI_MPP_AUDIO_FORMAT_G711Mu  = 2,   /* G.711 Mu           */
    HI_MPP_AUDIO_FORMAT_ADPCM   = 3,   /* ADPCM              */
    HI_MPP_AUDIO_FORMAT_G726    = 4,   /* G.726              */
    HI_MPP_AUDIO_FORMAT_AMR     = 5,   /* AMR encoder format */
    HI_MPP_AUDIO_FORMAT_AMRDTX  = 6,   /* AMR encoder formant and VAD1 enable */
    HI_MPP_AUDIO_FORMAT_AAC     = 7,   /* AAC encoder        */
    HI_MPP_AUDIO_FORMAT_WAV     = 8,   /* WAV encoder        */
    HI_MPP_AUDIO_FORMAT_MP3     = 9,   /* MP3 encoder */
    HI_MPP_AUDIO_FORMAT_BUTT
}HI_MPP_AUDIO_FORMAT_E;

typedef enum hiMPP_AUDIO_BITRATE_E
{
    HI_MPP_AUDIO_BITRATE_16K = 0,
    HI_MPP_AUDIO_BITRATE_24K,
    HI_MPP_AUDIO_BITRATE_32K,
    HI_MPP_AUDIO_BITRATE_40K,
    HI_MPP_AUDIO_BITRATE_48K,
    HI_MPP_AUDIO_BITRATE_96K,
    HI_MPP_AUDIO_BITRATE_BUTT
} HI_MPP_AUDIO_BITRATE_E;

typedef struct hiMPP_AUDIO_FRAME_S
{
    HI_MPP_AUDIO_BITWIDTH_E enBitwidth; /*audio frame bitwidth*/
    HI_MPP_AUDIO_SOUND_MODE_E enSoundType; /*audio frame momo or stereo mode*/
    HI_VOID *pVirAddr[2];
    HI_U32 u32PhyAddr[2];
    HI_U64 u64TimeStamp;/*audio frame timestamp*/
    HI_U32 u32Seq; /*audio frame seq*/
    HI_U32 u32Len; /*data lenth per channel in frame*/
}HI_MPP_AUDIO_FRAME_S;


typedef struct hiMPP_AUDIO_FRAME_INFO_S
{
    HI_MPP_AUDIO_FRAME_S *pstFrame;
    HI_U32 u32Id;			//音频帧索引，释放数据时用于唯一标示，直接透传即可
} HI_MPP_AUDIO_FRAME_INFO_S;

typedef HI_S32 (*PFN_VCAP_RawDataProc)(HI_HANDLE VCapHdl, HI_FRAME_DATA_S* pVCapRawData);
extern PFN_VCAP_RawDataProc dump_test_for_vi;

/** @}*/  /** <!-- ==== COMM End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_COMM_DEFINE_H__ */
