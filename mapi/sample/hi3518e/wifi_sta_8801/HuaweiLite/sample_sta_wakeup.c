#include "sys/types.h"
#include "stdio.h"
#include "shell.h"
#include "los_scatter.h"
#include <fcntl.h>

#include "hisoc/uart.h"

#include "wifi_info.h"

#include "hi_type.h"
#include "hi_mapi_comm_define.h"
#include "hi_mapi_vcap_define.h"
#include "hi_mapi_vproc_define.h"
#include "hi_mapi_venc_define.h"
#include "hi_mapi_disp_define.h"
#include "hi_mapi_sys.h"


#include "rtsp_server.h"
#include "cJSON.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <lwip/netdb.h>

static HI_HANDLE s_hSensorHdl = 0;
static HI_HANDLE s_hVCapHdl1 = 0;
static HI_HANDLE s_hVCapHdl2 = 1;
static HI_HANDLE s_hVProcHdl = 0;
static HI_HANDLE s_hVPortHdl = 0;
static HI_HANDLE s_hVencHdl = 0;
static HI_HANDLE s_hVoHdl = 0;

static HI_VENC_CALLBACK_S s_stVencCB;
static HI_S32 s_s32SampleVencFrameRate = 30;
static HI_S32 s_s32SampleVencWidth = 1280;
static HI_S32 s_s32SampleVencHeigth = 720;

static HI_S32 max_con = 10;
static HI_S32 priority = 2;
static rtsp_handle rtsp_hl;
static HI_S32 rtsp_send_err = 0;

void Rtsp_Thead_quit_CB(void)
{
	rtsp_finish(rtsp_hl);

	msleep(100);
	
	rtsp_hl = rtsp_create(max_con, priority, Rtsp_Thead_quit_CB);
	if(NULL == rtsp_hl) {
		printf("create rtsp fial!! \n");
		return HI_FALSE;
	}

	rtsp_send_err = 0;
}

HI_S32 VENC_DataProc(HI_HANDLE VencHdl, HI_VENC_DATA_S* pVStreamData, HI_VOID *pPrivateData)
{
	HI_S32 i = 0;
	struct timeval p_tv;
	HI_U32 s32Ret = HI_SUCCESS;

	if(HI_NULL == pVStreamData || pVStreamData->u32PackCount == 0)
		return HI_FAILURE;
	
	memset(&p_tv, 0, sizeof(struct timeval));
	(void)gettimeofday(&p_tv, NULL);

	for ( i = 0 ; i < pVStreamData->u32PackCount; i++ ) {
		
		HI_U8 *pPackVirtAddr = pVStreamData->astPack[i].pu8Addr[0];
		HI_U32 u32PackLen = pVStreamData->astPack[i].au32Len[0];
		HI_U32 u32PackOffset = pVStreamData->astPack[i].u32Offset;
		
		/* dataaddr = pPackVirtAddr+u32PackOffset, datalen = u32PackLen-u32PackOffset */
		s32Ret = rtp_send_h264(rtsp_hl, pPackVirtAddr+u32PackOffset, u32PackLen-u32PackOffset, &p_tv);
		if (s32Ret < 0)
		{
			printf("rtp_send_h264 err %d\n", s32Ret);
			return s32Ret;
		}
	}
	
    return HI_SUCCESS;
}


HI_S32 SAMPLE_VENC_TEST(HI_VOID)
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

	rtsp_hl = rtsp_create(max_con, priority, Rtsp_Thead_quit_CB);
	if(NULL == rtsp_hl) {
		printf("create rtsp fial!! \n");
		return HI_FALSE;
	}
	
	//add vcap sample here
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

	//vpss 0
	HI_VPORT_ATTR_S stVPortAttr;
	stVPortAttr.stResolution.u32Width = s_s32SampleVencWidth;//s_s32SampleVencWidth;
	stVPortAttr.stResolution.u32Height = s_s32SampleVencHeigth;//s_s32SampleVencHeigth;
	stVPortAttr.enPixFormat = HI_MPP_PIXEL_FORMAT_420;
	stVPortAttr.s32FrameRate = 30; // -1 no frame rate control
	s32Ret = HI_MAPI_VProc_Port_SetAttr(s_hVProcHdl, s_hVPortHdl, &stVPortAttr);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VProc_Port_SetAttr fail s32Ret:%d\n",s32Ret);
		return HI_FAILURE;
	}
	
	s32Ret = HI_MAPI_VProc_Port_Start(s_hVProcHdl, s_hVPortHdl);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VProc_Port_Start fail s32Ret:%d\n",s32Ret);
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
	stVencAttr.stVencPloadTypeAttr.stResolution.u32Width = s_s32SampleVencWidth;//s_s32SampleVencWidth;//s_s32SampleVencWidth;
	stVencAttr.stVencPloadTypeAttr.stResolution.u32Height = s_s32SampleVencHeigth;//s_s32SampleVencHeigth;//s_s32SampleVencHeigth;
	stVencAttr.stVencPloadTypeAttr.u32BufSize = s_s32SampleVencWidth * s_s32SampleVencHeigth;
	stVencAttr.stVencPloadTypeAttr.stAttrH264e.u32Profile = 0;
	stVencAttr.stVencPloadTypeAttr.stAttrH264e.stParamRef.u32Base = 1;
	stVencAttr.stVencPloadTypeAttr.stAttrH264e.stParamRef.u32Enhance = 0;
	stVencAttr.stVencPloadTypeAttr.stAttrH264e.stParamRef.bEnablePred = 0;
	stVencAttr.stRcAttr.enRcMode = HI_MPP_VENC_RC_MODE_CBR;
	stVencAttr.stRcAttr.stAttrCbr.u32BitRate = 2*2048;
	stVencAttr.stRcAttr.stAttrCbr.u32Gop = 10;
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
	
	s32Ret = HI_MAPI_VEnc_Bind_VProc(s_hVProcHdl, 0, s_hVencHdl);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VEnc_Bind_VProc fail s32Ret:%x\n",s32Ret);
		return HI_FAILURE;
	}

	printf("please press enter key twice to quit\n");
	getchar();
	getchar();

	s32Ret= HI_MAPI_VCap_Stop(s_hVCapHdl1);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VCap_Stop capture:%d Fail s32Ret:%d\n", s_hVCapHdl1, s32Ret);
		return HI_FAILURE;
	}

	s32Ret= HI_MAPI_VCap_Isp_Stop(s_hVCapHdl1);
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_VCap_Isp_Stop capture:%d Fail s32Ret:%d\n", s_hVCapHdl1, s32Ret);
		return HI_FAILURE;
	}

	s32Ret= HI_MAPI_Media_DeInit();
	if (HI_SUCCESS != s32Ret)
	{
		printf("HI_MAPI_Media_DeInit capture:%d Fail s32Ret:%d\n", s_hVCapHdl1, s32Ret);
		return HI_FAILURE;
	}

	return HI_SUCCESS;
}



void app_main(void)
{
	HI_S32 s32Ret = HI_SUCCESS;
	
    misc_driver_init();

    mcu_uart_proc();


 #if (WIFITYPE==WIFI_6214)
    wifi_pre_proc();
 	//hi_product_wifi_image_proc();
 #endif	

	
	
#ifndef CFG_WIFI_IMAGE
    //User can place business code here.
    misc_driver_post_init();
    osShellInit(TTY_DEVICE);
   
    net_init();
    HI_Product_OpenWifiStaServer();	
	dprintf("------------------start finish------------------ \n");
		
#endif
	
 	s32Ret = SAMPLE_VENC_TEST();
    if(HI_SUCCESS != s32Ret)
    {
        printf("SAMPLE_VENC fail\n");
        return HI_FAILURE;
    }

    while (1)
    {
        sleep(3);
    }

}

