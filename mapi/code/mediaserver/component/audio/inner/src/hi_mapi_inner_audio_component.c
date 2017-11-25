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
#include "hi_voice_api.h"

#include "hi_mapi_aenc_define.h"
#include "hi_mapi_audio_component.h"
#include "hi_mapi_inner_audio_component_define.h"
#include "hi_mapi_errno.h"


typedef struct hiG726_ENCODER_S
{
    HI_S32                  s32Coder;
    hiVOICE_G726_STATE_S    stG726State;
} G726_ENCODER_S;

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
extern HI_S32 OpenG726Encoder(HI_VOID *pEncoderAttr, HI_VOID **ppEncoder);
extern HI_S32 EncodeG726Frm(HI_VOID *pEncoder, const HI_MPP_AUDIO_FRAME_S *pstData,
                    HI_U8 *pu8Outbuf,HI_U32 *pu32OutLen);
extern HI_S32 CloseG726Encoder(HI_VOID *pEncoder);

#if 0
HI_S32 OpenG726Encoder(HI_VOID *pEncoderAttr, HI_VOID **ppEncoder)
{
    G726_ENCODER_S *pstEncoder = NULL;
    AENC_ATTR_G726_S *pstAttr = NULL;

//    HI_ASSERT(pEncoderAttr != NULL); 
//    HI_ASSERT(ppEncoder != NULL);

    /* 检查编码器属性 */
    pstAttr = (AENC_ATTR_G726_S *)pEncoderAttr;
    if (pstAttr->enG726bps >= G726_BUTT)
    {
    	printf("%s, %d, bps:%d of G726 encoder is illegal!\n", __FUNCTION__, __LINE__, pstAttr->enG726bps);
        return HI_FAILURE;
    }

    /* 为编码器状态空间分配内存 */
    pstEncoder = (G726_ENCODER_S *)malloc(sizeof(G726_ENCODER_S));
    if(NULL == pstEncoder)
    {
    	printf("%s, %d, malloc G726 encoder context failed!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
    memset(pstEncoder, 0, sizeof(G726_ENCODER_S));
    *ppEncoder = (HI_VOID *)pstEncoder;

    /* 初始化编码器 */
    switch(pstAttr->enG726bps)
    {
        case G726_16K:
        pstEncoder->s32Coder = G726_16KBPS;
        break;
        case G726_24K:
        pstEncoder->s32Coder = G726_24KBPS;
        break;
        case G726_32K:
        pstEncoder->s32Coder = G726_32KBPS;
        break;
        case G726_40K:
        pstEncoder->s32Coder = G726_40KBPS;
        break;
        case MEDIA_G726_16K:
        pstEncoder->s32Coder = MEDIA_G726_16KBPS;
        break;
        case MEDIA_G726_24K:
        pstEncoder->s32Coder = MEDIA_G726_24KBPS;
        break;
        case MEDIA_G726_32K:
        pstEncoder->s32Coder = MEDIA_G726_32KBPS;
        break;
        case MEDIA_G726_40K:
        pstEncoder->s32Coder = MEDIA_G726_40KBPS;
        break;
        default:
		printf("%s, %d, bps:%d of G726 encoder is not support!\n", __FUNCTION__, __LINE__, pstAttr->enG726bps);	
        return HI_FAILURE;
    }
    
    return HI_VOICE_EncReset(&pstEncoder->stG726State, pstEncoder->s32Coder);
}

HI_S32 EncodeG726Frm(HI_VOID *pEncoder, const HI_MPP_AUDIO_FRAME_S *pstData,
                    HI_U8 *pu8Outbuf,HI_U32 *pu32OutLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    G726_ENCODER_S *pstEncoder = NULL;
    HI_U32 u32PtNums;
    
 /*   HI_ASSERT(pEncoder != NULL);
    HI_ASSERT(pstData != NULL);
    HI_ASSERT(pu8Outbuf != NULL); 
    HI_ASSERT(pu32OutLen != NULL);*/

    pstEncoder = (G726_ENCODER_S *)pEncoder;
    
    /* 计算采样点数目(单声道的) */
    u32PtNums = pstData->u32Len/(pstData->enBitwidth + 1);
    if (u32PtNums != 80 && u32PtNums != 160 && u32PtNums != 240 
        && u32PtNums != 320 && u32PtNums != 480)
    {
    	printf("%s, %d, points:%d of each frame is illegal!\n", __FUNCTION__, __LINE__, u32PtNums);
        return HI_FAILURE;
    }

    s32Ret = HI_VOICE_EncodeFrame(&pstEncoder->stG726State, (HI_S16 *)pstData->pVirAddr[0],
        (HI_S16 *)pu8Outbuf, pstData->u32Len/sizeof(HI_U16)); 
    *pu32OutLen = (2 + ((HI_U16 *)pu8Outbuf)[1])*sizeof(HI_U16);
    
    return s32Ret;
}

HI_S32 CloseG726Encoder(HI_VOID *pEncoder)
{
    G726_ENCODER_S *pstEncoder = NULL;

//    HI_ASSERT(pEncoder != NULL);
    pstEncoder = (G726_ENCODER_S *)pEncoder;

    HI_VOICE_EncReset(&pstEncoder->stG726State, (HI_S16)pstEncoder->s32Coder);

    free(pstEncoder);
    return HI_SUCCESS;
}
#endif

HI_S32 s32Handle_g726 = -1;
pthread_mutex_t m_AencEncoderLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_AdecEncoderLock = PTHREAD_MUTEX_INITIALIZER;

HI_S32 HI_MAPI_AENC_G726Init(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
	HI_MPP_AENC_ENCODER_S stG726;
	if(s32Handle_g726 != -1)
	{
	    printf("[%s][%d] g726 have inited, return successful \n",__FUNCTION__,__LINE__);
	    return HI_SUCCESS;
	}
	printf("+++++++++++++++++++HI_MAPI_AENC_G726Init+++++++++++\n");
	stG726.enType = HI_MPP_AUDIO_FORMAT_G726;
	snprintf(stG726.aszName,  16, "%s", "G726");
	stG726.u32MaxFrmLen = MAX_VOICE_POINT_NUM * MAX_AUDIO_POINT_BYTES / 2;
    stG726.pfnOpenEncoder = OpenG726Encoder;
    stG726.pfnEncodeFrm = EncodeG726Frm;
    stG726.pfnCloseEncoder = CloseG726Encoder;
    s32Ret = HI_MAPI_Register_ExtAudioEncoder(&stG726,&s32Handle_g726);

    if (s32Ret)
    {
        printf("[%s][%d] HI_MAPI_Register_ExtAudioEncoder fail s32Ret:%d \n",__FUNCTION__,__LINE__,s32Ret);
        return s32Ret;
    }
//    s32Handle_aac = -1;

    return HI_SUCCESS;
}

HI_S32 HI_MAPI_AENC_G726DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    if(s32Handle_g726 == -1)
    {
        printf("[%s][%d] aac have Deinited, return successful \n", __FUNCTION__, __LINE__);
        return HI_SUCCESS;
    }

    s32Ret = HI_MAPI_UnRegister_ExtAudioEncoder(s32Handle_g726);

    if (HI_SUCCESS != s32Ret)
    {
        printf("[%s][%d] HI_MAPI_UnRegister_ExtAudioEncoder fail,s32Ret:%d\n", __FUNCTION__, __LINE__, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MAPI_ADEC_G726Init(HI_VOID)
{	
	//TODO
    return HI_SUCCESS;
}

HI_S32 HI_MAPI_ADEC_G726DeInit(HI_VOID)
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
        case HI_MPP_AUDIO_FORMAT_G726:
            s32Ret = HI_MAPI_AENC_G726Init();

            if (HI_SUCCESS != s32Ret)
            {
                AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "HI_MAPI_AENC_G726Init  failed, s32Ret:%x\n",s32Ret);
                pthread_mutex_unlock(&m_AencEncoderLock);
                return s32Ret;
            }

            break;
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
            s32Ret = HI_MAPI_AENC_G726DeInit();

            if (HI_SUCCESS != s32Ret)
            {
                AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "HI_MAPI_AENC_G726DeInit failed, ret:%d\n", s32Ret);
                pthread_mutex_unlock(&m_AencEncoderLock);
                return s32Ret;
            }

            break;

        default:
            AENV_TRACE(MPP_EN_ERR_LEVEL_ERROR, HI_MPP_MOD_AENC, "enAudioFormat:%d not support\n", enAudioFormat);
            pthread_mutex_unlock(&m_AencEncoderLock);
            return HI_FAILURE;
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
