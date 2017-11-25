/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : aenc_aac_adp.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/02/26
  Description   :
  History       :
  1.Date        : 2011/02/26
    Author      : n00168968
    Modification: Created file

******************************************************************************/


#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "aacenc.h"
#include "aacdec.h"

#include "hi_mapi_aenc_define.h"
#include "hi_mapi_audio_component.h"
#include "hi_mapi_audio_component_define.h"
#include "hi_mapi_errno.h"

typedef struct hiAENC_AAC_ENCODER_S
{
    AAC_ENCODER_S*       pstAACState;
    AENC_ATTR_AAC_S     stAACAttr;
} AENC_AAC_ENCODER_S;

typedef struct hiADEC_AAC_DECODER_S
{
    HAACDecoder         pstAACState;
    ADEC_ATTR_AAC_S     stAACAttr;
} ADEC_AAC_DECODER_S;

#ifdef HI_TRACE

#define AENV_TRACE(level, enModId, fmt...)\
    do{ \
        HI_TRACE(level, enModId,"[Func]:%s [Line]:%d [Info]:", __FUNCTION__, __LINE__);\
        HI_TRACE(level,enModId,##fmt);\
    }while(0)
#else

#define AENV_TRACE(level, enModId, fmt...)\
    do{ \
        printf("[Func]:%s [Line]:%d [Info]:", __FUNCTION__, __LINE__);\
        printf(level,enModId,##fmt);\
    }while(0)

#endif

pthread_mutex_t m_AencEncoderLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_AdecEncoderLock = PTHREAD_MUTEX_INITIALIZER;

#define AENC_ADAPT_MAGIC 0Xfcfcfcfc

static HI_S32 AencCheckAACAttr(const AENC_ATTR_AAC_S* pstAACAttr)
{
    if (pstAACAttr->enBitWidth != HI_MPP_AUDIO_BITWIDTH_16)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "invalid bitwidth for AAC encoder");
        return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    if (pstAACAttr->enSoundMode >= HI_MPP_AUDIO_SOUND_MODE_BUTT)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "invalid sound mode for AAC encoder");
        return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    if ((pstAACAttr->enAACType == AAC_TYPE_EAACPLUS) && (pstAACAttr->enSoundMode != HI_MPP_AUDIO_SOUND_MODE_STEREO))
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "invalid sound mode for AAC encoder");
        return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    return HI_SUCCESS;
}

HI_S32 AencAACCheckConfig(AACENC_CONFIG* pconfig)
{
    if (NULL == pconfig)
    {
        return HI_ERR_MAPI_AENC_NULL_PTR;
    }

    if (pconfig->coderFormat != AACLC && pconfig->coderFormat != EAAC && pconfig->coderFormat != EAACPLUS)
    {
        printf("aacenc coderFormat(%d) invalid\n", pconfig->coderFormat);
    }


    if (pconfig->quality != AU_QualityExcellent && pconfig->quality != AU_QualityHigh && pconfig->quality != AU_QualityMedium && pconfig->quality != AU_QualityLow)
    {
        printf("aacenc quality(%d) invalid\n", pconfig->quality);
    }

    if (pconfig->bitsPerSample != 16)
    {
        printf("aacenc bitsPerSample(%d) should be 16\n", pconfig->bitsPerSample);
    }

    if (pconfig->coderFormat == AACLC)
    {
        if (pconfig->nChannelsOut != pconfig->nChannelsIn)
        {
            printf("AACLC nChannelsOut(%d) in not equal to nChannelsIn(%d)\n", pconfig->nChannelsOut, pconfig->nChannelsIn);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }

        if (pconfig->sampleRate == 32000)
        {
            if (pconfig->bitRate < 24000 ||  pconfig->bitRate > 256000)
            {
                printf("AACLC 32000 Hz bitRate(%d) should be 24000 ~ 256000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 44100)
        {
            if (pconfig->bitRate < 32000 ||  pconfig->bitRate > 320000)
            {
                printf("AACLC 44100 Hz bitRate(%d) should be 32000 ~ 320000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 48000)
        {
            if (pconfig->bitRate < 32000 ||  pconfig->bitRate > 320000)
            {
                printf("AACLC 48000 Hz bitRate(%d) should be 48000 ~ 320000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 16000)
        {
            if (pconfig->bitRate < 16000 ||  pconfig->bitRate > 96000)
            {
                printf("AACLC 16000 Hz bitRate(%d) should be 16000 ~ 96000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 8000)
        {
            if (pconfig->bitRate < 8000 ||  pconfig->bitRate > 96000)
            {
                printf("AACLC 8000 Hz bitRate(%d) should be 8000 ~ 96000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 24000)
        {
            if (pconfig->bitRate < 20000 ||  pconfig->bitRate > 128000)
            {
                printf("AACLC 24000 Hz bitRate(%d) should be 20000 ~ 128000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 22050)
        {
            if (pconfig->bitRate < 16000 ||  pconfig->bitRate > 128000)
            {
                printf("AACLC 22025 Hz bitRate(%d) should be 16000 ~ 128000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else
        {
            printf("AACLC invalid samplerate(%d) should be 8000~48000\n", pconfig->sampleRate);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }
    }
    else if (pconfig->coderFormat == EAAC)
    {
        if (pconfig->nChannelsOut != pconfig->nChannelsIn)
        {
            printf("EAAC nChannelsOut(%d) is not equal to nChannelsIn(%d)\n", pconfig->nChannelsOut, pconfig->nChannelsIn);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }

        if (pconfig->sampleRate == 32000)
        {
            if (pconfig->bitRate < 18000 ||  pconfig->bitRate > 23000)
            {
                printf("EAAC 32000 Hz bitRate(%d) should be 18000 ~ 23000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 44100)
        {
            if (pconfig->bitRate < 24000 ||  pconfig->bitRate > 51000)
            {
                printf("EAAC 44100 Hz bitRate(%d) should be 24000 ~ 51000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 48000)
        {
            if (pconfig->bitRate < 24000 || pconfig->bitRate > 51000)
            {
                printf("EAAC 48000 Hz bitRate(%d) should be 24000 ~ 51000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else
        {
            printf("EAAC invalid samplerate(%d) should be 32000/44100/48000\n", pconfig->sampleRate);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }
    }
    else if (pconfig->coderFormat == EAACPLUS)
    {
        if (pconfig->nChannelsOut != 2 || pconfig->nChannelsIn != 2)
        {
            printf("EAACPLUS nChannelsOut(%d) and nChannelsIn(%d) should be 2\n", pconfig->nChannelsOut, pconfig->nChannelsIn);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }

        if (pconfig->sampleRate == 32000)
        {
            if (pconfig->bitRate < 10000 ||  pconfig->bitRate > 17000)
            {
                printf("EAACPLUS 32000 Hz bitRate(%d) should  be 10000 ~ 17000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 44100)
        {
            if (pconfig->bitRate < 12000 ||  pconfig->bitRate > 35000)
            {
                printf("EAACPLUS 44100 Hz bitRate(%d) should  be 12000 ~ 35000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else if (pconfig->sampleRate == 48000)
        {
            if (pconfig->bitRate < 12000 ||  pconfig->bitRate > 35000)
            {
                printf("EAACPLUS 48000 Hz bitRate(%d) should  be 12000 ~ 35000\n", pconfig->bitRate);
                return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
            }
        }
        else
        {
            printf("EAACPLUS invalid samplerate(%d) should be 32000/44100/48000\n", pconfig->sampleRate);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }

    }

    return 0;
}

HI_S32 OpenAACEncoder(HI_VOID* pEncoderAttr, HI_VOID** ppEncoder)
{
    AENC_AAC_ENCODER_S* pstEncoder = NULL;
    AENC_ATTR_AAC_S* pstAttr = NULL;
    HI_S32 s32Ret;
    AACENC_CONFIG  config;

    if(pEncoderAttr == NULL)
    {
	printf("pEncoderAttr is null pointer\n");
	return HI_FAILURE;
    }
    if(ppEncoder == NULL)
    {
	printf("ppEncoder is null pointer\n");
	return HI_FAILURE;
    }

    /* 检查编码器属性 */
    pstAttr = (AENC_ATTR_AAC_S*)pEncoderAttr;
    s32Ret = AencCheckAACAttr(pstAttr);

    if (s32Ret)
    {
        return s32Ret;
    }

    /* 为编码器状态空间分配内存 */
    pstEncoder = (AENC_AAC_ENCODER_S*)malloc(sizeof(AENC_AAC_ENCODER_S));

    if (NULL == pstEncoder)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "no memory");
        return HI_FAILURE;
    }

    memset(pstEncoder, 0, sizeof(AENC_AAC_ENCODER_S));
    *ppEncoder = (HI_VOID*)pstEncoder;

    /* 为编码器设定默认配置 */
    s32Ret = AACInitDefaultConfig(&config);

    if (s32Ret)
    {
        return s32Ret;
    }

    switch (pstAttr->enAACType)
    {
        case AAC_TYPE_AACLC:
            config.coderFormat = AACLC;
            break;

        case AAC_TYPE_EAAC:
            config.coderFormat = EAAC;
            break;

        case AAC_TYPE_EAACPLUS:
            config.coderFormat = EAACPLUS;
            break;

        default:
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    config.bitRate       = pstAttr->enBitRate;
    config.bitsPerSample = 8 * (1 << (pstAttr->enBitWidth));
    config.sampleRate    = pstAttr->enSmpRate;

    if (pstAttr->s16BandWidth == 0)
    {
        config.bandWidth = config.sampleRate / 2;
    }
    else
    {
        config.bandWidth = pstAttr->s16BandWidth;
    }

    if ((HI_MPP_AUDIO_SOUND_MODE_LEFT == pstAttr->enSoundMode || HI_MPP_AUDIO_SOUND_MODE_RIGHT == pstAttr->enSoundMode) 
		&& AAC_TYPE_EAACPLUS != pstAttr->enAACType)
    {
        config.nChannelsIn   = 1;
        config.nChannelsOut  = 1;
    }
    else
    {
        config.nChannelsIn   = 2;
        config.nChannelsOut  = 2;
    }

    config.quality       = AU_QualityHigh;

    s32Ret = AencAACCheckConfig(&config);

    if (s32Ret)
    {
        return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    /* 创建编码器 */
    s32Ret = AACEncoderOpen(&pstEncoder->pstAACState, &config);

    if (s32Ret)
    {
        return s32Ret;
    }

    memcpy(&pstEncoder->stAACAttr, pstAttr, sizeof(AENC_ATTR_AAC_S));

    return HI_SUCCESS;
}

HI_S32 EncodeAACFrm(HI_VOID* pEncoder, const HI_MPP_AUDIO_FRAME_S* pstData,
                    HI_U8* pu8Outbuf, HI_U32* pu32OutLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AENC_AAC_ENCODER_S* pstEncoder = NULL;
    HI_U32 u32PtNums;
    HI_S32 i;
    HI_S16 aData[AACENC_BLOCKSIZE * 2 * MAX_CHANNELS];
    HI_S16 s16Len = 0;
    static HI_S8 aAACFrmBuf0[2048 * 4 * 2] = {0};
    static HI_S8 aAACFrmBuf1[2048 * 4 * 2] = {0};
    static HI_U32 u32WriteIdx0 = 0;
    static HI_U32 u32WriteIdx1 = 0;
    static HI_U32 u32WaterLine;
    HI_U32 u32count = 0;
		
    if(pEncoder == NULL)
    {
	printf("pEncoder is null\n");
	return HI_FAILURE;
    }
    if(pstData == NULL)
    {
	printf("pstData is null\n");
	return HI_FAILURE;
    }
    if(pu8Outbuf == NULL)
    {
	printf("pu8Outbuf is null\n");
	return HI_FAILURE;
    }
    if(pu32OutLen == NULL)
    {
	printf("pu32OutLen is null\n");
	return HI_FAILURE;
    }

    pstEncoder = (AENC_AAC_ENCODER_S*)pEncoder;

    if (HI_MPP_AUDIO_SOUND_MODE_STEREO == pstEncoder->stAACAttr.enSoundMode)
    {
        /* 检查数据是否为立体声模式 */
        if (HI_MPP_AUDIO_SOUND_MODE_STEREO != pstData->enSoundmode)
        {
            printf("[Func]:%s [Line]:%d [Info]:%s\n",
                   __FUNCTION__, __LINE__, "AAC encode receive a frame which not match its Soundmode");
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
        }
    }

    /*水线大小，等于各协议要求的帧长*/
    if (pstEncoder->stAACAttr.enAACType == AAC_TYPE_AACLC)
    {
        u32WaterLine = AACLC_SAMPLES_PER_FRAME;
    }
    else if (pstEncoder->stAACAttr.enAACType == AAC_TYPE_EAAC
             || pstEncoder->stAACAttr.enAACType == AAC_TYPE_EAACPLUS)
    {
        u32WaterLine = AACPLUS_SAMPLES_PER_FRAME;
    }
    else
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__,
               "invalid AAC coder type");
        return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;;
    }

    /* 计算采样点数目(单声道的) */
    u32PtNums = pstData->u32Len / (pstData->enBitwidth + 1);

    /*如果传入数据的帧长大于协议要求帧长，非法，不接收，否则可能造成buffer爆掉*/
    if (u32PtNums != u32WaterLine)
    {
        printf("[Func]:%s [Line]:%d [Info]:invalid u32PtNums%d for AAC_TYPE_AACLC\n",
               __FUNCTION__, __LINE__, u32PtNums);
        return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    memcpy(aAACFrmBuf0 + u32WriteIdx0, pstData->pVirAddr[0], pstData->u32Len);
    u32WriteIdx0 += pstData->u32Len;

    if (HI_MPP_AUDIO_SOUND_MODE_STEREO == pstEncoder->stAACAttr.enSoundMode)
    {
        memcpy(aAACFrmBuf1 + u32WriteIdx1, pstData->pVirAddr[1], pstData->u32Len);
        u32WriteIdx1 += pstData->u32Len;
    }

    u32count = u32WaterLine * (pstData->enBitwidth + 1);

    /*此时应该返回一个特殊值，使上层调用者可以辨认此情况:
      因为帧长不够，而暂时缓存，并未启动编码，但调用者应该明白稍后此帧会被送到编码器，不要重复发送。*/
    if (u32WriteIdx0 < u32count)
    {
        return AENC_ADAPT_MAGIC;
    }

    /* AAC encoder need interleaved data,here change LLLRRR to LRLRLR.
       AACLC will encode 1024*2 point, and AACplus encode 2048*2 point*/
    if (HI_MPP_AUDIO_SOUND_MODE_STEREO == pstEncoder->stAACAttr.enSoundMode)
    {
        s16Len = u32WaterLine;

        for (i = s16Len - 1; i >= 0 ; i--)
        {
            aData[2 * i] = *((HI_S16*)aAACFrmBuf0 + i);
            aData[2 * i + 1] = *((HI_S16*)aAACFrmBuf1 + i);
        }

        u32WriteIdx0 -= u32count;
        u32WriteIdx1 -= u32count;
        memcpy(aAACFrmBuf0, aAACFrmBuf0 + u32count, u32WriteIdx0);
        memcpy(aAACFrmBuf1, aAACFrmBuf1 + u32count, u32WriteIdx1);
    }
    else/* if inbuf is momo, copy left to right */
    {
        HI_S16* temp = (HI_S16*)aAACFrmBuf0;

        s16Len = u32WaterLine;

        for (i = s16Len - 1; i >= 0 ; i--)
        {
            aData[i] = *(temp + i);
        }

        u32WriteIdx0 -= u32count;
        memcpy(aAACFrmBuf0, aAACFrmBuf0 + u32count, u32WriteIdx0);
    }

    s32Ret = AACEncoderFrame(pstEncoder->pstAACState, aData, pu8Outbuf, (HI_S32*)pu32OutLen);

    if (HI_SUCCESS != s32Ret)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "AAC encode failed");
    }

    return s32Ret;
}

HI_S32 CloseAACEncoder(HI_VOID* pEncoder)
{
    AENC_AAC_ENCODER_S* pstEncoder = NULL;

    if(pEncoder == NULL)
    {
	printf("pEncoder is null\n");
	return HI_FAILURE;
    }
    pstEncoder = (AENC_AAC_ENCODER_S*)pEncoder;

    AACEncoderClose(pstEncoder->pstAACState);

    free(pstEncoder);
    return HI_SUCCESS;
}

HI_S32 OpenAACDecoder(HI_VOID* pDecoderAttr, HI_VOID** ppDecoder)
{
    ADEC_AAC_DECODER_S* pstDecoder = NULL;
    ADEC_ATTR_AAC_S* pstAttr = NULL;

	if(pDecoderAttr == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pDecoderAttr is null\n");
        return HI_FAILURE;
	}
	if(ppDecoder == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "ppDecoder is null\n");
        return HI_FAILURE;
	}

    pstAttr = (ADEC_ATTR_AAC_S*)pDecoderAttr;

    /* 为编码器状态空间分配内存 */
    pstDecoder = (ADEC_AAC_DECODER_S*)malloc(sizeof(ADEC_AAC_DECODER_S));

    if (NULL == pstDecoder)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "no memory");
        return HI_FAILURE;
    }

    memset(pstDecoder, 0, sizeof(ADEC_AAC_DECODER_S));
    *ppDecoder = (HI_VOID*)pstDecoder;

    /* 创建编码器 */
    pstDecoder->pstAACState = AACInitDecoder(AACDEC_ADTS);

    if (!pstDecoder->pstAACState)
    {

        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "AACInitDecoder failed");
        return HI_FAILURE;
    }

    memcpy(&pstDecoder->stAACAttr, pstAttr, sizeof(ADEC_ATTR_AAC_S));

    return HI_SUCCESS;
}

HI_S32 DecodeAACFrm(HI_VOID* pDecoder, HI_U8** pu8Inbuf, HI_S32* ps32LeftByte,
                    HI_U16* pu16Outbuf, HI_U32* pu32OutLen, HI_U32* pu32Chns)
{
    HI_S32 s32Ret = HI_SUCCESS;
    ADEC_AAC_DECODER_S* pstDecoder = NULL;
    HI_S32 s32Samples, s32FrmLen, s32SampleBytes;
    AACFrameInfo aacFrameInfo;
	
	if(pDecoder == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pDecoder is null\n");
        return HI_FAILURE;
	}
	if(pu8Inbuf == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pu8Inbuf is null\n");
        return HI_FAILURE;
	}
	if(ps32LeftByte == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "ps32LeftByte is null\n");
        return HI_FAILURE;
	}
	if(pu16Outbuf == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pu16Outbuf is null\n");
        return HI_FAILURE;
	}
	if(pu32OutLen == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pu32OutLen is null\n");
        return HI_FAILURE;
	}
	if(pu32Chns == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pu32Chns is null\n");
        return HI_FAILURE;
	}

    *pu32Chns = 1;/*voice encoder only one channle */

    pstDecoder = (ADEC_AAC_DECODER_S*)pDecoder;

    s32FrmLen = AACDecodeFindSyncHeader(pstDecoder->pstAACState, pu8Inbuf, ps32LeftByte);

    if (s32FrmLen < 0)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n",
               __FUNCTION__, __LINE__, "AAC decoder can't find sync header");
        return HI_FAILURE;
    }

    /*Notes: pInbuf will updated*/
    s32Ret = AACDecodeFrame(pstDecoder->pstAACState, pu8Inbuf, ps32LeftByte, (HI_S16*)pu16Outbuf);

    if (s32Ret)
    {
        //        printf("------------[Func]:%s [Line]:%d  [Ret]:%x  [Inbuf]:0x%x  [LeftByte]:%d->%d [Info]:%s\n",
        //            __FUNCTION__, __LINE__, s32Ret, pu8Inbuf,s32LefteByte, *ps32LeftByte, "AAC decode failed");
        return s32Ret;
    }

#if 0
    else
    {
        //printf("------------[Func]:%s [Line]:%d  [Ret]:%x  [Inbuf]:0x%x  [LeftByte]:%d->%d [Info]:%s\n",
        //    __FUNCTION__, __LINE__, s32Ret, pu8Inbuf,s32LefteByte, *ps32LeftByte, "AAC decode failed");

    }

#endif
    AACGetLastFrameInfo(pstDecoder->pstAACState, &aacFrameInfo);

    /* samples per frame of one sound track*/
    s32Samples = aacFrameInfo.outputSamps / aacFrameInfo.nChans;
    HI_ASSERT(s32Samples == AACLC_SAMPLES_PER_FRAME || s32Samples == AACPLUS_SAMPLES_PER_FRAME);

    s32SampleBytes = s32Samples * sizeof(HI_U16);
    *pu32Chns = aacFrameInfo.nChans;
    *pu32OutLen = s32SampleBytes;

    /* NOTICE: our audio frame format is same as AAC decoder L/L/L/... R/R/R/...*/
#if 0

    /*change data format of AAC encoder to our AUDIO_FRAME format */
    if (MAX_AUDIO_FRAME_LEN != s32SampleBytes)
    {
        /* after decoder, 1024 left samples , then 1024 right samples*/
        memmove((HI_U8*)pOutbuf + MAX_AUDIO_FRAME_LEN,
                (HI_U8*)pOutbuf + s32SampleBytes, s32SampleBytes);
    }

#endif

    return s32Ret;
}

HI_S32 GetAACFrmInfo(HI_VOID* pDecoder, HI_VOID* pInfo)
{
    ADEC_AAC_DECODER_S* pstDecoder = NULL;
    AACFrameInfo aacFrameInfo;
    AAC_FRAME_INFO_S* pstAacFrm = NULL;

	if(pDecoder == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pDecoder is null\n");
        return HI_FAILURE;
	}
	if(pInfo == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pInfo is null\n");
        return HI_FAILURE;
	}

    pstDecoder = (ADEC_AAC_DECODER_S*)pDecoder;
    pstAacFrm = (AAC_FRAME_INFO_S*)pInfo;

    AACGetLastFrameInfo(pstDecoder->pstAACState, &aacFrameInfo);

    pstAacFrm->s32Samplerate = aacFrameInfo.sampRateOut;
    pstAacFrm->s32BitRate = aacFrameInfo.bitRate;
    pstAacFrm->s32Profile = aacFrameInfo.profile;
    pstAacFrm->s32TnsUsed = aacFrameInfo.tnsUsed;
    pstAacFrm->s32PnsUsed = aacFrameInfo.pnsUsed;

    return HI_SUCCESS;
}


HI_S32 CloseAACDecoder(HI_VOID* pDecoder)
{
    ADEC_AAC_DECODER_S* pstDecoder = NULL;

	if(pDecoder == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pDecoder is null\n");
        return HI_FAILURE;
	}
	
    pstDecoder = (ADEC_AAC_DECODER_S*)pDecoder;

    AACFreeDecoder(pstDecoder->pstAACState);

    free(pstDecoder);
    return HI_SUCCESS;
}


HI_S32 ResetAACDecoder(HI_VOID* pDecoder)
{
    ADEC_AAC_DECODER_S* pstDecoder = NULL;

	if(pDecoder == NULL)
	{
		printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "pDecoder is null\n");
        return HI_FAILURE;
	}
    pstDecoder = (ADEC_AAC_DECODER_S*)pDecoder;

    AACFreeDecoder(pstDecoder->pstAACState);

    /* 创建编码器 */
    pstDecoder->pstAACState = AACInitDecoder(AACDEC_ADTS);

    if (!pstDecoder->pstAACState)
    {
        printf("[Func]:%s [Line]:%d [Info]:%s\n", __FUNCTION__, __LINE__, "AACResetDecoder failed");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
HI_S32 s32Handle_aac = -1;
HI_S32 s32Handle_aaclc = -1;
HI_S32 s32Handle_DecAac = -1;
HI_S32 s32Handle_DecAaclc = -1;


HI_S32 HI_MAPI_AENC_AacInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
	HI_MPP_AENC_ENCODER_S stAac;
	if(s32Handle_aac != -1)
	{
	    printf("[%s][%d] aac have inited, return successful \n",__FUNCTION__,__LINE__);
	    return HI_SUCCESS;
	}
	printf("+++++++++++++++++++HI_MAPI_AENC_AacInit+++++++++++\n");
	stAac.enType = HI_MPP_AUDIO_FORMAT_AAC;
	snprintf(stAac.aszName, 3, "Aac");
	stAac.u32MaxFrmLen = MAX_AAC_MAINBUF_SIZE;
    stAac.pfnOpenEncoder = OpenAACEncoder;
    stAac.pfnEncodeFrm = EncodeAACFrm;
    stAac.pfnCloseEncoder = CloseAACEncoder;
    s32Ret = HI_MAPI_Register_ExtAudioEncoder(&stAac,&s32Handle_aac);

    if (s32Ret)
    {
        printf("[%s][%d] HI_MAPI_Register_ExtAudioEncoder fail s32Ret:%d \n",__FUNCTION__,__LINE__,s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MAPI_AENC_AacDeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    if(s32Handle_aac == -1)
    {
        printf("[%s][%d] aac have Deinited, return successful \n", __FUNCTION__, __LINE__);
        return HI_SUCCESS;
    }

    s32Ret = HI_MAPI_UnRegister_ExtAudioEncoder(s32Handle_aac);

    if (HI_SUCCESS != s32Ret)
    {
        printf("[%s][%d] HI_MAPI_UnRegister_ExtAudioEncoder fail,s32Ret:%d\n", __FUNCTION__, __LINE__, s32Ret);
        return s32Ret;
    }
    s32Handle_aac = -1;

    return HI_SUCCESS;
}

HI_S32 HI_MAPI_ADEC_AacInit(HI_VOID)
{	
	//TODO
    return HI_SUCCESS;
}

HI_S32 HI_MAPI_ADEC_AacDeInit(HI_VOID)
{
	//TODO
    return HI_SUCCESS;
}
HI_S32 HI_MAPI_Register_AudioEncoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat)
{
    HI_S32 s32Ret = HI_SUCCESS;
    pthread_mutex_lock(&m_AencEncoderLock);

	printf("+++++++++++++++++++HI_MAPI_Register_AudioEncoder++++++++++1\n");
    switch (enAudioFormat)
    {
        case HI_MPP_AUDIO_FORMAT_AAC:
            s32Ret = HI_MAPI_AENC_AacInit();

            if (HI_SUCCESS != s32Ret)
            {
                AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "HI_MAPI_AENC_AacInit  failed, s32Ret:%x\n",s32Ret);
                pthread_mutex_unlock(&m_AencEncoderLock);
                return s32Ret;
            }

            break;

        default:
            AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "enAudioFormat:%d not support\n", enAudioFormat);
            pthread_mutex_unlock(&m_AencEncoderLock);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    pthread_mutex_unlock(&m_AencEncoderLock);
    return HI_SUCCESS;
}

HI_S32 HI_MAPI_UnRegister_AudioEncoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat)
{
    HI_S32 s32Ret = HI_SUCCESS;
    pthread_mutex_lock(&m_AencEncoderLock);

    switch (enAudioFormat)
    {
        case HI_MPP_AUDIO_FORMAT_AAC:
            s32Ret = HI_MAPI_AENC_AacDeInit();

            if (HI_SUCCESS != s32Ret)
            {
                AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "HI_MAPI_AENC_AacDeInit failed, ret:%d\n", s32Ret);
                pthread_mutex_unlock(&m_AencEncoderLock);
                return s32Ret;
            }

            break;

        default:
            AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "enAudioFormat:%d not support\n", enAudioFormat);
            pthread_mutex_unlock(&m_AencEncoderLock);
            return HI_ERR_MAPI_AENC_ILLEGAL_PARAM;
    }

    pthread_mutex_unlock(&m_AencEncoderLock);
    return HI_SUCCESS;
}

HI_S32 HI_MAPI_Register_AudioDecoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat)
{
	//TODO
    return HI_SUCCESS;
}

HI_S32 HI_MAPI_UnRegister_AudioDecoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat)
{
	//TODO
    return HI_SUCCESS;
}
