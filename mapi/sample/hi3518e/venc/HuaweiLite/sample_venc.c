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
#include "hi_type.h"
#include "hi_mapi_comm_define.h"
#include "hi_mapi_vcap_define.h"
#include "hi_mapi_vproc_define.h"
#include "hi_mapi_venc_define.h"
#include "hi_mapi_disp_define.h"
#include "hi_mapi_sys.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

static HI_HANDLE s_hSensorHdl = 0;
static HI_HANDLE s_hVCapHdl1 = 0;
//static HI_HANDLE s_hVCapHdl2 = 1;
static HI_HANDLE s_hVProcHdl = 0;
static HI_HANDLE s_hVPortHdl0 = 0;
static HI_HANDLE s_hVPortHdl1 = 1;

static HI_HANDLE s_hVencHdl = 0;
static HI_HANDLE s_hVoHdl = 0;

static HI_VENC_CALLBACK_S s_stVencCB;
static HI_S32 s_s32SampleVencFrameRate = 30;
static HI_S32 s_s32SampleVencWidth = 1280;
static HI_S32 s_s32SampleVencHeigth = 720;


static HI_BOOL issavefile = HI_TRUE;

HI_S32 VENC_DataProc(HI_HANDLE VencHdl, HI_VENC_DATA_S* pVStreamData, HI_VOID *pPrivateData)
	{
		HI_S32 i = 0;
		char filename[30];
		static FILE *pFd = NULL;
	
		if(HI_NULL == pVStreamData || pVStreamData->u32PackCount == 0)
			return HI_FAILURE;
	
		if(issavefile == HI_TRUE) {
	
			if(pFd == NULL) {
				memset(filename, 0, 30);
				sprintf(filename, "stream%d.h264", VencHdl);
				pFd = fopen(filename, "wb");
				if(pFd == NULL) {
					printf("open file fail\n");
					return HI_FALSE;
				}
			}
	
			for ( i = 0 ; i < pVStreamData->u32PackCount; i++ )
			{
				HI_U32 s32Ret = HI_SUCCESS;
				HI_U8 *pPackVirtAddr = pVStreamData->astPack[i].pu8Addr[0];
				HI_U32 u32PackLen = pVStreamData->astPack[i].au32Len[0];
				HI_U32 u32PackOffset = pVStreamData->astPack[i].u32Offset;
				//printf("[%s][%d] VencHdl:%d u32PackLen-u32PackOffset:%u \n", __FUNCTION__,__LINE__, VencHdl, u32PackLen-u32PackOffset);
				//dataaddr = pPackVirtAddr+u32PackOffset, datalen = u32PackLen-u32PackOffset
				s32Ret = fwrite((void *)pPackVirtAddr+u32PackOffset,  u32PackLen-u32PackOffset, 1, pFd);
				if(s32Ret<0)
				{
					printf("fwrite err %d\n", s32Ret);
					return s32Ret;
				}
			}
		}
		else {
			if(pFd) {
				//printf("quit save file, close fd\n");
				fclose(pFd);
			}
		}
	
		return HI_SUCCESS;
	}

HI_S32 SAMPLE_VENC(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_MPP_SENSOR_ATTR_S stSensorAttr;
    HI_MPP_VCAP_ATTR_S stVcapAttr1;
	HI_MPP_DISP_ATTR_S vo_attr = {0};

    stSensorAttr.s32FrameRate = s_s32SampleVencFrameRate;
    stSensorAttr.stResolution.u32Width = s_s32SampleVencWidth;
    stSensorAttr.stResolution.u32Height = s_s32SampleVencHeigth;
	stSensorAttr.enWdrMode = HI_MPP_WDR_MODE_NONE;
	
	stVcapAttr1.enWdrMode = HI_MPP_WDR_MODE_NONE;
    stVcapAttr1.s32FrameRate = 30;
    stVcapAttr1.stResolution.u32Width = 1280;
    stVcapAttr1.stResolution.u32Height = 720;
	stVcapAttr1.enPixelFormat = HI_MPP_PIXEL_FORMAT_420;
	
    
    s32Ret = HI_MAPI_Media_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Media_Init fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
    s32Ret = HI_MAPI_Sensor_SetAttr(s_hSensorHdl, &stSensorAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Sensor_SetAttr fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	
    //start cap1
    s32Ret = HI_MAPI_VCap_SetAttr(s_hVCapHdl1, &stVcapAttr1);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VCap_SetAttr fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
    s32Ret = HI_MAPI_VCap_Isp_Start(s_hVCapHdl1);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VCap_Isp_Start fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VCap_Start(s_hVCapHdl1);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VCap_Start capture:%d Fail s32Ret:%d\n", s_hVCapHdl1, s32Ret);
        return HI_FAILURE;
    }

    HI_VPROC_ATTR_S stVprocAttr;
    stVprocAttr.enVProcType = VPROC_TYPE_VIDEO;
    stVprocAttr.u32MaxW = s_s32SampleVencWidth;
    stVprocAttr.u32MaxH = s_s32SampleVencHeigth;
    s32Ret = HI_MAPI_VProc_Init(s_hVProcHdl, &stVprocAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VProc_Init fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }

	s32Ret = HI_MAPI_VProc_Start(s_hVProcHdl);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VProc_Start fail s32Ret:%x\n",s32Ret);
        return HI_FAILURE;
    }

	//vproc 0
    HI_VPORT_ATTR_S stVPortAttr;
    stVPortAttr.stResolution.u32Width = s_s32SampleVencWidth;
    stVPortAttr.stResolution.u32Height = s_s32SampleVencHeigth;
    stVPortAttr.enPixFormat = HI_MPP_PIXEL_FORMAT_420;
    stVPortAttr.s32FrameRate = 30;
    s32Ret = HI_MAPI_VProc_Port_SetAttr(s_hVProcHdl, s_hVPortHdl0, &stVPortAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VProc_Port_SetAttr fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	
	s32Ret = HI_MAPI_VProc_Port_Start(s_hVProcHdl, s_hVPortHdl0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VProc_Port_Start fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	
	//vproc 1
	stVPortAttr.stResolution.u32Width = 640;
	stVPortAttr.stResolution.u32Height = 480;
	stVPortAttr.enPixFormat = HI_MPP_PIXEL_FORMAT_420;
	stVPortAttr.s32FrameRate = 30; 
	s32Ret = HI_MAPI_VProc_Port_SetAttr(s_hVProcHdl, s_hVPortHdl1, &stVPortAttr);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VProc_Port_SetAttr fail s32Ret:%x\n",s32Ret);
		return HI_FAILURE;
	}
	
	s32Ret = HI_MAPI_VProc_Port_Start(s_hVProcHdl, s_hVPortHdl1);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VProc_Port_Start fail s32Ret:%x\n",s32Ret);
		return HI_FAILURE;
	}
	

    //start vpss and vi bind
    s32Ret = HI_MAPI_VProc_Bind_VCap(s_hVCapHdl1, s_hVProcHdl);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VProc_Bind_VCap fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }	

    //start venc
    HI_MPP_VENC_ATTR_S stVencAttr;
    stVencAttr.stVencPloadTypeAttr.enType = HI_MPP_PAYLOAD_TYPE_H264;
	stVencAttr.stVencPloadTypeAttr.stResolution.u32Width = s_s32SampleVencWidth;
	stVencAttr.stVencPloadTypeAttr.stResolution.u32Height = s_s32SampleVencHeigth;
	stVencAttr.stVencPloadTypeAttr.u32BufSize = s_s32SampleVencWidth * s_s32SampleVencHeigth;
    stVencAttr.stVencPloadTypeAttr.stAttrH264e.u32Profile = 0;
    stVencAttr.stVencPloadTypeAttr.stAttrH264e.stParamRef.u32Base = 1;
    stVencAttr.stVencPloadTypeAttr.stAttrH264e.stParamRef.u32Enhance = 0;
    stVencAttr.stVencPloadTypeAttr.stAttrH264e.stParamRef.bEnablePred = 0;
    stVencAttr.stRcAttr.enRcMode = HI_MPP_VENC_RC_MODE_CBR;
    stVencAttr.stRcAttr.stAttrCbr.u32BitRate = 2048;
    stVencAttr.stRcAttr.stAttrCbr.u32Gop = 30;
    s32Ret = HI_MAPI_VEnc_Init(s_hVencHdl, &stVencAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VEnc_Creat fail s32Ret:%x\n",s32Ret);
        return HI_FAILURE;
    }

    s_stVencCB.pfnDataCB = VENC_DataProc;
    s_stVencCB.pPrivateData = HI_NULL;
    s32Ret = HI_MAPI_VEnc_RegisterCallback(s_hVencHdl, &s_stVencCB);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VEnc_RegisterCallback fail s32Ret:%x\n",s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VEnc_Start(s_hVencHdl, HI_VENC_LIMITLESS_FRAME_COUNT);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VEnc_Start fail s32Ret:%x\n",s32Ret);
        return HI_FAILURE;
    }
	
    s32Ret = HI_MAPI_VEnc_Bind_VProc(s_hVProcHdl, s_hVPortHdl0, s_hVencHdl);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_VEnc_Bind_VProc fail s32Ret:%x\n",s32Ret);
        return HI_FAILURE;
    }
	
	
	//start vo
		HI_MPP_DISP_CSCATTREX_S stCSC= {0};
		
		stCSC.stVideoCSC.enCscMatrix = HI_MPP_CSC_MATRIX_BT709_TO_RGB_PC;
    stCSC.stVideoCSC.u32Contrast = 50;
    stCSC.stVideoCSC.u32Hue = 50;
    stCSC.stVideoCSC.u32Luma = 50;
    stCSC.stVideoCSC.u32Satuature = 50;
			
    HI_MAPI_Disp_SetAttrEx(s_hVoHdl,&stCSC);


	vo_attr.u32BgColor = 0x00;
		vo_attr.enIntfType = DISP_INTF_LCD_8BIT;
		vo_attr.enIntfSync = DISP_SYNC_USER;

	vo_attr.stSyncInfo.bSynm=1;
	vo_attr.stSyncInfo.bIop=1;
	vo_attr.stSyncInfo.u8Intfb=16;

	vo_attr.stSyncInfo.u16Vact=272;
	vo_attr.stSyncInfo.u16Vbb=8;
	vo_attr.stSyncInfo.u16Vfb=8;

	vo_attr.stSyncInfo.u16Hact=480;
	vo_attr.stSyncInfo.u16Hbb=40;
	vo_attr.stSyncInfo.u16Hfb=56;
	vo_attr.stSyncInfo.u16Hmid=1;
	
	vo_attr.stSyncInfo.u16Bvact=272;
	vo_attr.stSyncInfo.u16Bvbb=8;
	vo_attr.stSyncInfo.u16Bvfb=8;

	vo_attr.stSyncInfo.u16Hpw=1;
	vo_attr.stSyncInfo.u16Vpw=1;
	
	vo_attr.stSyncInfo.bIdv=0;
	vo_attr.stSyncInfo.bIhs=1;
	vo_attr.stSyncInfo.bIvs=1;

	
	s32Ret = HI_MAPI_Disp_Init(s_hVoHdl, &vo_attr);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Disp_Init fail, 0x%x\n", s32Ret);
		return HI_FALSE;
	}
	
	s32Ret = HI_MAPI_Disp_Start(s_hVoHdl);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Disp_Start fail, 0x%x\n", s32Ret);
		return HI_FALSE;
	}

	HI_MPP_DISP_WINDOW_ATTR_S vo_window_attr;
	vo_window_attr.stRect.u32X = 0;
	vo_window_attr.stRect.u32Y = 0;
	vo_window_attr.stRect.u32Width = 480;
	vo_window_attr.stRect.u32Height = 272;

	vo_window_attr.u32Priority = 0;
	
	s32Ret = HI_MAPI_Disp_Window_SetAttr(s_hVoHdl, 0, &vo_window_attr);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Disp_Window_SetAttr fail, 0x%x\n", s32Ret);
		return HI_FALSE;
	}

	s32Ret = HI_MAPI_Disp_Window_Start(s_hVoHdl, 0);
	if(HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Disp_Window_Start fail, 0x%x\n", s32Ret);
		return HI_FALSE;
	}

	lcd_register();
	
	 s32Ret = HI_MAPI_Disp_Bind_VProc(s_hVProcHdl, s_hVPortHdl1, s_hVoHdl, 0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MAPI_Disp_Bind_VProc fail s32Ret:%d\n",s32Ret);
        return HI_FAILURE;
    }
	
	printf("video recording...........\n");
	
	sleep(10);
	issavefile = HI_FAILURE;
	printf("please press enter key twice to quit\n");
	getchar();
	getchar();
	
	issavefile = HI_FAILURE;

    return HI_SUCCESS;
}
/******************************************************************************
* function    : main()
* Description : video preview sample
******************************************************************************/
typedef struct hiVREG_ARGS_S
{
	HI_U32	u32Size;
	HI_U32	u32BaseAddr;
	HI_U32	u32PhyAddr;
} VREG_ARGS_S;
#define VREG_DRV_INIT           _IOW('I', 20, VREG_ARGS_S)

static HI_S32 s32VregFd = -1;
static inline HI_S32 VREG_CHECK_OPEN(HI_VOID)
{
	if (s32VregFd <= 0)
	{
		s32VregFd = open("/dev/isp_dev", O_RDONLY);
		if (s32VregFd <= 0)
		{
			perror("open isp device error!\n");
			return HI_FAILURE;
		}
	}
	return HI_SUCCESS;
}

int app_main(int argc, char *argv[])
{
    HI_S32 s32Ret = HI_SUCCESS;
	
    s32Ret = SAMPLE_VENC();
    if(HI_SUCCESS != s32Ret)
    {
        printf("SAMPLE_VENC fail\n");
        return HI_FAILURE;
    }
    sleep(3600*24);
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
