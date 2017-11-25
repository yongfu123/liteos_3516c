/******************************************************************************
  A simple program of Hisilicon Hi35xx video input and output implementation.
  Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2016-6 Created
******************************************************************************/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_mapi_comm_define.h"
#include "hi_mapi_acap.h"
#include "hi_mapi_acap_define.h"
#include "hi_mapi_aenc_define.h"
#include "hi_mapi_aenc.h"
#include "hi_mapi_inner_audio_component_define.h"
#include "hi_mapi_audio_component_define.h"
#include "hi_mapi_audio_component.h"
#include "hi_mapi_ao_define.h"
#include "hi_mapi_ao.h"
#include "hi_mapi_audio_component_define.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

static FILE* s_pAudioEncAacFile = HI_NULL;

#define FILE_FULL_PATH_MAX_LENGTH 64
static HI_BOOL gs_bAoVolumeCtrl = HI_TRUE;


HI_BOOL bExit	= HI_FALSE;
static HI_S32 s32Index = 0;

HI_S32 SAMPLE_AUDIO_DataProc(HI_HANDLE AencHdl, HI_MPP_AENC_STREAM_S* pAStreamData, HI_VOID *pPrivateData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR au8TempValueStr[FILE_FULL_PATH_MAX_LENGTH];
    if(HI_NULL == pAStreamData)
        return HI_FAILURE;

    if (s_pAudioEncAacFile == HI_NULL)
    {
        memset(au8TempValueStr, 0, sizeof(HI_CHAR) * FILE_FULL_PATH_MAX_LENGTH);
		//chdir("/sd0p0");
        //snprintf(au8TempValueStr, FILE_FULL_PATH_MAX_LENGTH, "audio_stream_chn%d.%s", AencHdl, "g726");      
		snprintf(au8TempValueStr, FILE_FULL_PATH_MAX_LENGTH, "audio_stream_chn%d_%d.%s", AencHdl, s32Index, "aac");
        s_pAudioEncAacFile = fopen(au8TempValueStr, "a+");
        if (!s_pAudioEncAacFile)
        {
            s_pAudioEncAacFile = fopen(au8TempValueStr, "wb");
            printf("[%s][%d] fopen wb\n",__FUNCTION__,__LINE__);
        }
        if (!s_pAudioEncAacFile)
        {
            printf("open file failed!\n");
        }
    }

    if(HI_NULL != s_pAudioEncAacFile)
    {
        fwrite((const void*)pAStreamData->pu8Addr,1,pAStreamData->u32Len, s_pAudioEncAacFile);
        if (fflush(s_pAudioEncAacFile))
        {
            perror("fflush file");
        }

        if (fclose(s_pAudioEncAacFile))
        {
            perror("close file");
        }
        s_pAudioEncAacFile = HI_NULL;
    }
    return HI_SUCCESS;
}



/******************************************************************************
* function : Ai -> Ao(with fade in/out and volume adjust)
******************************************************************************/
HI_S32  SAMPLE_AUDIO_AiAo()
{
HI_S32 s32Ret = HI_SUCCESS;  
	HI_HANDLE ACapHdl = 0;
	HI_HANDLE AoHdl = 0;
	
	HI_MPP_ACAP_ATTR_S stAcapAttr;
	//HI_MPP_AO_ATTR_S stAoAttr;
	
	HI_MPP_AUDIO_GAIN_S SetAcapVol;
	HI_MPP_AUDIO_GAIN_S GetAcapVol;
	HI_MPP_AUDIO_GAIN_S GetVoVol;
	HI_MPP_AUDIO_GAIN_S SetVoVol;
	
 
	s32Ret = HI_MAPI_Media_Init();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Media_Init fail\n");
    return HI_FAILURE;
    }
    printf("HI_MAPI_Media_Init succes\n");
        
	stAcapAttr.enAudioMode = HI_MPP_AUDIO_MODE_I2S_MASTER;
	stAcapAttr.enBitwidth = HI_MPP_AUDIO_BITWIDTH_16;
	stAcapAttr.enSampleRate = HI_MPP_AUDIO_SAMPLE_RATE_8;
	stAcapAttr.enSoundMode = HI_MPP_AUDIO_SOUND_MODE_STEREO;
	stAcapAttr.u32PtNumPerFrm = 320; 
	
/*
	stAoAttr.enSampleRate=stAcapAttr.enAudioMode;
	stAoAttr.enBitwidth=stAcapAttr.enBitwidth;
	stAoAttr.enSampleRate =stAcapAttr.enSampleRate;
	stAoAttr.enSoundMode =stAcapAttr.enSoundMode ;
	stAoAttr.u32PtNumPerFrm =stAcapAttr.u32PtNumPerFrm;
	*/
	
	s32Ret = HI_MAPI_ACap_Init(ACapHdl, &stAcapAttr);
	if(HI_SUCCESS != s32Ret)
	{ 
		printf("HI_MAPI_ACap_Init fail s32Ret:%d\n",s32Ret);
		return HI_FAILURE;
	} 


	s32Ret = HI_MAPI_ACap_Start(ACapHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_Start fail s32Ret:%#x\n",s32Ret);
		return HI_FAILURE;
	}
	
	GetAcapVol.s32Gain=40;
	s32Ret =HI_MAPI_ACap_SetVolume(ACapHdl,&GetAcapVol);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_SetVolume:%#x\n",s32Ret);
		return HI_FAILURE;
	}
	
	 s32Ret =HI_MAPI_ACap_GetVolume(ACapHdl,&GetAcapVol);
	 if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_GetVolume:%#x\n",s32Ret);
		return HI_FAILURE;
	}

	s32Ret = HI_MAPI_AO_Init(AoHdl, &stAcapAttr);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_AO_Start return ERR, %x\n", s32Ret);
		return HI_FAILURE;
	}
	

	s32Ret = HI_MAPI_AO_Start(AoHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_AO_Start return ERR, %x\n", s32Ret);
		return HI_FAILURE;
	}

    s32Ret = HI_MAPI_Ao_BindACap(ACapHdl,AoHdl); 
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_BindACap fail ");
        return HI_FAILURE;
    }
	
	SetVoVol.s32Gain=5;
	s32Ret =HI_MAPI_AO_SetVolume(AoHdl,&SetVoVol); 
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_AO_SetVolume:%#x\n",s32Ret);
		return HI_FAILURE;
	}
		
	s32Ret =HI_MAPI_AO_GetVolume(AoHdl,&GetVoVol);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_AO_GetVolume:%#x\n",s32Ret);
		return HI_FAILURE;
	}



printf("please speak loudly.......\n");

sleep(30);
    printf("press any to stop.......\n");
    getchar();
    getchar();

    s32Ret = HI_MAPI_Ao_UnBindACap(ACapHdl,AoHdl); 
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Ao_UnBindACap fail ");
        return HI_FAILURE;
    }

	s32Ret = HI_MAPI_AO_Stop(ACapHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_AO_Stop return ERR, %x\n", s32Ret);
		return HI_FAILURE;
	}

	s32Ret = HI_MAPI_AO_DeInit(ACapHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_AO_DeInit return ERR, %x\n", s32Ret);
		return HI_FAILURE;
	}		

	s32Ret = HI_MAPI_ACap_Stop(ACapHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_Stop fail s32Ret:%d\n",s32Ret);
		return HI_FAILURE;
	}
	s32Ret = HI_MAPI_ACap_DeInit(ACapHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_DeInit fail s32Ret:%d\n",s32Ret);
		return HI_FAILURE;
	}
	
	s32Ret = HI_MAPI_Media_DeInit();
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Media_Init fail\n");
		return HI_FAILURE;
	}



	return HI_SUCCESS;

}


HI_S32  SAMPLE_AUDIO_AiAenc()
{
	HI_S32 s32Ret = HI_SUCCESS;
	HI_HANDLE ACapHdl = 0;
	HI_HANDLE AEncHdl = 0;
	HI_MPP_ACAP_ATTR_S stAcapAttr;
	

    
	s32Ret = HI_MAPI_Media_Init();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Media_Init fail 11\n");
    return HI_FAILURE;
    } 
        
	stAcapAttr.enAudioMode = HI_MPP_AUDIO_MODE_I2S_MASTER;
	stAcapAttr.enBitwidth = HI_MPP_AUDIO_BITWIDTH_16;
	stAcapAttr.enSampleRate = HI_MPP_AUDIO_SAMPLE_RATE_8;
	stAcapAttr.enSoundMode = HI_MPP_AUDIO_SOUND_MODE_STEREO;//HI_MPP_AUDIO_SOUND_MODE_STEREO
	stAcapAttr.u32PtNumPerFrm = 1024;
	s32Ret = HI_MAPI_ACap_Init(ACapHdl, &stAcapAttr);
	if(HI_SUCCESS != s32Ret)   
	{
		printf("HI_MAPI_ACap_Init fail s32Ret:%d\n",s32Ret); 
		return HI_FAILURE;
	}    


	s32Ret = HI_MAPI_ACap_Start(ACapHdl); 
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_Start fail s32Ret:%#x\n",s32Ret);
		return HI_FAILURE;
	}

	HI_MPP_AUDIO_GAIN_S stAudioGain;
	stAudioGain.s32Gain = 40;
	s32Ret = HI_MAPI_ACap_SetVolume(ACapHdl, &stAudioGain);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_SetVolume fail s32Ret:%d\n",s32Ret);
		return HI_FAILURE;
	}


	HI_MPP_AUDIO_GAIN_S stGetAudioGain;
	s32Ret = HI_MAPI_ACap_GetVolume(ACapHdl,&stGetAudioGain);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_ACap_GetVolume fail s32Ret:%d\n",s32Ret);
		return HI_FAILURE;
	}
	
    s32Ret = HI_MAPI_Register_AudioEncoder(HI_MPP_AUDIO_FORMAT_AAC);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Register_AudioEncoder fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }

    HI_HANDLE hAEncHdl = 0;
    HI_MPP_AENC_ATTR_S stAencAttr;
    AENC_ATTR_AAC_S stAacAencAttr;
    stAacAencAttr.enAACType = AAC_TYPE_AACLC;
    stAacAencAttr.enBitRate = AAC_BPS_48K;
    stAacAencAttr.enBitWidth = HI_MPP_AUDIO_BITWIDTH_16;
    stAacAencAttr.enSmpRate = HI_MPP_AUDIO_SAMPLE_RATE_8;
    stAacAencAttr.enSoundType = HI_MPP_AUDIO_SOUND_TYPE_STEREO;//HI_MPP_AUDIO_SOUND_TYPE_STEREO
    stAacAencAttr.enTransType = AAC_TRANS_TYPE_ADTS;
    stAacAencAttr.s16BandWidth = 0;
    stAencAttr.enAencFormat = HI_MPP_AUDIO_FORMAT_AAC;
    stAencAttr.u32PtNumPerFrm = 1024;
    stAencAttr.pValue = &stAacAencAttr;
    stAencAttr.u32Len = sizeof(stAacAencAttr);

	s32Ret = HI_MAPI_AEnc_Init(hAEncHdl,&stAencAttr);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_Init fail s32Ret:%d\n", s32Ret);
        return HI_FAILURE;
    } 
    HI_AENC_CALLBACK_S stAencCB;
    stAencCB.pfnDataCB = SAMPLE_AUDIO_DataProc;
    stAencCB.pPrivateData = HI_NULL;
    s32Ret = HI_MAPI_AEnc_RegisterCallback(hAEncHdl, &stAencCB);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_RegisterCallback fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
    s32Ret = HI_MAPI_AEnc_Start(hAEncHdl); 
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_Start fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	
    s32Ret = HI_MAPI_AEnc_BindACap(ACapHdl,AEncHdl); 
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_BindACap fail ");
        return HI_FAILURE;
    }
	

	printf("audio recording.......\n");

	sleep(60);
    printf("press any to stop.......\n");   
    getchar();
    getchar();

	

	s32Ret = HI_MAPI_AEnc_UnBindACap(ACapHdl,AEncHdl); 
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_UnBindACap fail\n ");
        return HI_FAILURE;
    }
	
    s32Ret = HI_MAPI_AEnc_Stop(hAEncHdl);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_Stop fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_MAPI_AEnc_UnRegisterCallback(hAEncHdl, &stAencCB);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_UnRegisterCallback fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_MAPI_AEnc_DeInit(hAEncHdl);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_AEnc_DeInit fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }

	s32Ret = HI_MAPI_ACap_Stop(ACapHdl);
	if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_ACap_Stop fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	s32Ret = HI_MAPI_ACap_DeInit(ACapHdl);
	if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_ACap_DeInit fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	s32Ret = HI_MAPI_Media_DeInit();
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Media_Init fail\n");
    	return HI_FAILURE;
    }

	return HI_SUCCESS;
}


HI_VOID SAMPLE_AUDIO_Usage()
{
    printf("Usage : \n");
	printf("\t 0) ai->ao(G726:SampleRate:8k).\n");
    printf("\t 1) ai->aenc(AAC:SampleRate:8k).\n");
    return;
}


/******************************************************************************
* function    : main()
* Description : audio sample
******************************************************************************/
int app_main()
{

   // sleep(3600*24);  
   // return HI_SUCCESS;

   	HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR ch;
	s32Ret = HI_MAPI_Sys_Init();
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Sys_Init fail s32Ret:%x\n", s32Ret);
		return HI_FAILURE;
	}
	

	while (1)
     {
	 	SAMPLE_AUDIO_Usage();
        ch = (char)getchar();
		getchar();
        switch (ch)
        {

		    case '0':
		    {
			 	s32Ret = SAMPLE_AUDIO_AiAo();
			 	printf("Input anyKey to stop sample audio\n");
				getchar();
				break;
		     }

		    case '1':
		    {
			 	s32Ret = SAMPLE_AUDIO_AiAenc();
			 	printf("Input anyKey to stop sample audio\n");
				getchar();
				break;
		     }
						
            case 'q':
            case 'Q':
            {
                bExit = HI_TRUE;
                break;
            }
            default :
            {
                printf("input invaild! please try again.\n");
                break;
            }
        }

	 	if (bExit)
        {
            break;
        }	
	}
	return s32Ret;

	
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
