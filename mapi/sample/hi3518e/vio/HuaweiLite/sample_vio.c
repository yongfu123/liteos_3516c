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

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

static HI_S32 s_s32MemDev = -1;

# define MAP_FAILED ((void *)-1)

#define MEM_DEV_OPEN() \
    do {\
        if (s_s32MemDev <= 0)\
        {\
            s_s32MemDev = open("/dev/mem", O_CREAT|O_RDWR|O_SYNC);\
            if (s_s32MemDev < 0)\
            {\
                perror("Open dev/mem error");\
                return -1;\
            }\
        }\
    }while(0)

#define MEM_DEV_CLOSE() \
    do {\
        HI_S32 s32Ret;\
        if (s_s32MemDev > 0)\
        {\
            s32Ret = close(s_s32MemDev);\
            if(HI_SUCCESS != s32Ret)\
            {\
                perror("Close mem/dev Fail");\
                return s32Ret;\
            }\
            s_s32MemDev = -1;\
        }\
    }while(0)

HI_S32 g_s32RawDataCnt = 0;
#define MAX_FRM_WIDTH   4608 
#if 0
HI_VOID* COMM_SYS_Mmap(HI_U32 u32PhyAddr, HI_U32 u32Size)
{
    HI_U32 u32Diff;
    HI_U32 u32PagePhy;
    HI_U32 u32PageSize;
    HI_U8* pPageAddr;

    /* The mmap address should align with page */
    u32PagePhy = u32PhyAddr & 0xfffff000;
    u32Diff    = u32PhyAddr - u32PagePhy;

    /* The mmap size shuld be mutliples of 1024 */
    u32PageSize = ((u32Size + u32Diff - 1) & 0xfffff000) + 0x1000;
    pPageAddr   = mmap ((void*)0, u32PageSize, PROT_READ | PROT_WRITE,
                        MAP_SHARED, s_s32MemDev, u32PagePhy);
    if (MAP_FAILED == pPageAddr )
    {
        perror("mmap error");
        return NULL;
    }
    return (HI_VOID*) (pPageAddr + u32Diff);
}

HI_S32 COMM_SYS_Munmap(HI_VOID* pVirAddr, HI_U32 u32Size)
{
    HI_U32 u32PageAddr;
    HI_U32 u32PageSize;
    HI_U32 u32Diff;

    u32PageAddr = (((HI_U32)pVirAddr) & 0xfffff000);
    u32Diff     = (HI_U32)pVirAddr - u32PageAddr;
    u32PageSize = ((u32Size + u32Diff - 1) & 0xfffff000) + 0x1000;

    return munmap((HI_VOID*)u32PageAddr, u32PageSize);
}

int RawData_Save(HI_FRAME_DATA_S* pVBuf, HI_U32 u32Nbit, FILE* pfd)
{
    unsigned int w, h;
    HI_U16* pVBufVirt_Y;
    HI_U8  au8Data[MAX_FRM_WIDTH];
    HI_U16 au16Data[MAX_FRM_WIDTH];
    HI_U32 phy_addr, size;
    HI_U8* pUserPageAddr[2];

    size = pVBuf->u32Stride[0]  * (pVBuf->u32Height) * 2;

    phy_addr = pVBuf->u32PhyAddr[0];

    MEM_DEV_OPEN();

    pUserPageAddr[0] = (HI_U8*) COMM_SYS_Mmap(phy_addr, size);
    if (NULL == pUserPageAddr[0])
    {
        MEM_DEV_CLOSE();
        return -1;
    }

    pVBufVirt_Y = (HI_U16*)pUserPageAddr[0];

    /* save Y ----------------------------------------------------------------*/
    fprintf(stderr, "saving......dump data......u32Stride[0]: %d, width: %d\n", pVBuf->u32Stride[0], pVBuf->u32Width);
    fflush(stderr);
    for (h = 0; h < pVBuf->u32Height; h++)
    {
        HI_U16 u16Data;
        for (w = 0; w < pVBuf->u32Width; w++)
        {
            if (8 == u32Nbit)
            {
                au8Data[w] = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 8);
            }
            else if (10 == u32Nbit)
            {
                u16Data = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 6);
                au16Data[w] = u16Data;
            }
            else if (12 == u32Nbit)       
            {
                u16Data = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 4);
                au16Data[w] = u16Data;
            }
            else if (14 == u32Nbit)        
            {
                u16Data = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 2);
                au16Data[w] = u16Data;
            }
            else if (16 == u32Nbit)
            {
                u16Data = pVBufVirt_Y[h * pVBuf->u32Width + w];
                au16Data[w] = u16Data;
            }
            else
            {
                printf("Err! Bayer data can't support %d bits!\n", u32Nbit);
                COMM_SYS_Munmap(pUserPageAddr[0], size);
                MEM_DEV_CLOSE();
                return -1;
            }
        }

        if (8 == u32Nbit)
        {
            fwrite(au8Data, pVBuf->u32Width, 1, pfd);
        }
        else
        {
            fwrite(au16Data, pVBuf->u32Width, 2, pfd);
        }

    }
    fflush(pfd);

    fflush(stderr);

    COMM_SYS_Munmap(pUserPageAddr[0], size);

    MEM_DEV_CLOSE();

    return 0;
}
#endif
int RawData_Save(HI_FRAME_DATA_S* pVBuf, HI_U32 u32Nbit, FILE* pfd)
{
    unsigned int w, h;
    HI_U16* pVBufVirt_Y;
    HI_U8  au8Data[MAX_FRM_WIDTH];
    HI_U16 au16Data[MAX_FRM_WIDTH];
    HI_U8* pUserPageAddr[2];

    pVBufVirt_Y = (HI_U16*)pVBuf->u32PhyAddr[0];

    /* save Y ----------------------------------------------------------------*/
    fprintf(stderr, "saving......dump data......u32Stride[0]: %d, width: %d\n", pVBuf->u32Stride[0], pVBuf->u32Width);
    fflush(stderr);
    for (h = 0; h < pVBuf->u32Height; h++)
    {
        HI_U16 u16Data;
        for (w = 0; w < pVBuf->u32Width; w++)
        {
            if (8 == u32Nbit)
            {
                au8Data[w] = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 8);
            }
            else if (10 == u32Nbit)
            {
                u16Data = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 6);
                au16Data[w] = u16Data;
            }
            else if (12 == u32Nbit)       
            {
                u16Data = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 4);
                au16Data[w] = u16Data;
            }
            else if (14 == u32Nbit)        
            {
                u16Data = (pVBufVirt_Y[h * pVBuf->u32Width + w] >> 2);
                au16Data[w] = u16Data;
            }
            else if (16 == u32Nbit)
            {
                u16Data = pVBufVirt_Y[h * pVBuf->u32Width + w];
                au16Data[w] = u16Data;
            }
            else
            {
                printf("Err! Bayer data can't support %d bits!\n", u32Nbit);
                return -1;
            }
        }

        if (8 == u32Nbit)
        {
            fwrite(au8Data, pVBuf->u32Width, 1, pfd);
        }
        else
        {
            fwrite(au16Data, pVBuf->u32Width, 2, pfd);
        }

    }
    fflush(pfd);

    fflush(stderr);

    return 0;
}

HI_S32 RawData_Dump_Callback(HI_HANDLE VCapHdl, HI_FRAME_DATA_S* pVCapRawData)
{
	FILE* pfd = NULL;
	HI_S32 s32Ret = HI_SUCCESS;
	HI_CHAR szRawDataName[128] = {0};
	printf("begin dump...\n");

	snprintf(szRawDataName, sizrof(szRawDataName)-1, "/home/vcap_%d_%d_%d_%d.raw", VCapHdl,
		pVCapRawData->u32Width,pVCapRawData->u32Height,g_s32RawDataCnt++);
	pfd = fopen(szRawDataName, "wb");
	if(pfd > 0)
	{
		s32Ret = RawData_Save(pVCapRawData,14,pfd);
		if(HI_SUCCESS != s32Ret)
		{
			printf("RawData_Save fail\n");
			fclose(pfd);
			return HI_FAILURE;
		}
	}
	else
	{
		printf("open file fail\n");
	}
	return HI_SUCCESS;
	
}

HI_S32 SAMPLE_VI_Dump()
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 SensorHdl = 0;
    HI_S32 VCapHdl1 = 0;
    HI_S32 VCapHdl2 = 1;
    HI_MPP_SENSOR_ATTR_S stSensorAttr; 
    HI_MPP_VCAP_ATTR_S stVcapAttr1;
    HI_MPP_VCAP_ATTR_S stVcapAttr2;
	
    stSensorAttr.s32FrameRate = 30;
    stSensorAttr.stResolution.u32Width = 1280;
    stSensorAttr.stResolution.u32Height = 720;

    stVcapAttr1.enWdrMode = HI_MPP_WDR_MODE_NONE;
    stVcapAttr1.s32FrameRate = 30;
    stVcapAttr1.stResolution.u32Width = 1280;
    stVcapAttr1.stResolution.u32Height = 720;

    stVcapAttr2.enWdrMode = HI_MPP_WDR_MODE_NONE;
    stVcapAttr2.s32FrameRate = 30;
    stVcapAttr2.stResolution.u32Width = 1280;
    stVcapAttr2.stResolution.u32Height = 720;

    //add vcap sample here
    s32Ret = HI_MAPI_Media_Init();
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_Media_Init fail\n");
	return HI_FAILURE;
    }
    printf("HI_MAPI_Media_Init ok....\n");

    s32Ret = HI_MAPI_Sensor_SetAttr(SensorHdl,&stSensorAttr);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_Sensor_SetAttr fail\n");
	return HI_FAILURE;
    }

    //start cap1
     s32Ret = HI_MAPI_VCap_SetAttr(VCapHdl1,&stVcapAttr1);
     if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_SetAttr fail\n");
	return HI_FAILURE;
    }

     s32Ret = HI_MAPI_VCap_Isp_Start(VCapHdl1);
     if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_Isp_Start fail\n");
	return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VCap_Start(VCapHdl1);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_Start fail\n");
	return HI_FAILURE;
    }
    //start cap2
    s32Ret = HI_MAPI_VCap_SetAttr(VCapHdl2,&stVcapAttr2);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_SetAttr capture:%d fail\n",VCapHdl2);
	return HI_FAILURE;
    }

     s32Ret = HI_MAPI_VCap_Isp_Start(VCapHdl2);
     if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_Isp_Start fail\n");
	return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VCap_Start(VCapHdl2);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_Start fail\n");
	return HI_FAILURE;
    }

    #if 0
    HI_S32 VProcHdl = 0;
    HI_VPROC_ATTR_S stVprocAttr;
    stVprocAttr.enVProcType = VPROC_TYPE_VIDEO;
    stVprocAttr.u32MaxW = 3840;
    stVprocAttr.u32MaxH = 2160;
    s32Ret =HI_MAPI_VProc_Init(VProcHdl,&stVprocAttr);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Creat fail s32Ret:%x\n", s32Ret);
    	return HI_FAILURE;
    }

     s32Ret =HI_MAPI_VProc_Start(VProcHdl);
     if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Start fails 32Ret:%x\n", s32Ret);
    	return HI_FAILURE;
    }

    s32Ret =HI_MAPI_VProc_Bind_VCap(VCapHdl1,VProcHdl);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Bind_VCap fail s32Ret:%x\n", s32Ret);
    	return HI_FAILURE;
    }

    HI_S32 VPortHdl = 0;
    HI_VPORT_ATTR_S stVportAttr;
    stVportAttr.enPixFormat = HI_MPP_PIXEL_FORMAT_420;
    stVportAttr.s32FrameRate = 30;
    stVportAttr.stResolution.u32Width = 3840;
    stVportAttr.stResolution.u32Height = 2160;
    s32Ret= HI_MAPI_VProc_Port_SetAttr(VProcHdl, VPortHdl, &stVportAttr);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Port_SetAttr fail\n");
	return HI_FAILURE;
    }

    s32Ret= HI_MAPI_VProc_Port_Start(VProcHdl, VPortHdl);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Port_Start fail\n");
	return HI_FAILURE;
    }
#endif

#if 0
    printf("-----------enable dump\n");
    s32Ret = HI_MAPI_VCap_EnableDumpRaw(VCapHdl1);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_EnableDumpRaw fail\n");
	return HI_FAILURE;
    }

    printf("-----------dump raw\n");
    g_s32RawDataCnt = 0;
    VCapHdl1 = HI_MAPI_VCap_DumpRaw(VCapHdl1,1, RawData_Dump_Callback);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_DumpRaw fail\n");
	return HI_FAILURE;
    }

    #endif
    return HI_SUCCESS;
}

HI_S32 SAMPLE_VI_vpss()
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 SensorHdl = 0;
    HI_S32 VCapHdl = 0;
    HI_MPP_SENSOR_ATTR_S stSensorAttr; 
    HI_MPP_VCAP_ATTR_S stVcapAttr;
	
    stSensorAttr.s32FrameRate = 30;
    stSensorAttr.stResolution.u32Width = 1280;
    stSensorAttr.stResolution.u32Height = 720;

    stVcapAttr.enWdrMode = HI_MPP_WDR_MODE_NONE;
    stVcapAttr.s32FrameRate = 30;
    stVcapAttr.stResolution.u32Width = 1280;
    stVcapAttr.stResolution.u32Height = 720;

    //add vcap sample here
    s32Ret = HI_MAPI_Media_Init();
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_Media_Init fail\n");
	return HI_FAILURE;
    }

    s32Ret = HI_MAPI_Sensor_SetAttr(SensorHdl,&stSensorAttr);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_Sensor_SetAttr fail\n");
	return HI_FAILURE;
    }
	

     s32Ret = HI_MAPI_VCap_SetAttr(VCapHdl,&stVcapAttr);
     if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_SetAttr fail\n");
	return HI_FAILURE;
    }

     s32Ret = HI_MAPI_VCap_Isp_Start(VCapHdl);
     if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_Isp_Start fail\n");
	return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VCap_Start(VCapHdl);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VCap_Start fail\n");
	return HI_FAILURE;
    }

    HI_HANDLE VProcHdl = 0;
    HI_VPROC_ATTR_S stVprocAttr;
    stVprocAttr.enVProcType = VPROC_TYPE_VIDEO;
    stVprocAttr.u32MaxW = 1280;
    stVprocAttr.u32MaxH = 720;
    s32Ret = HI_MAPI_VProc_Init(VProcHdl, &stVprocAttr);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Init fail\n");
	return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VProc_Bind_VCap(VCapHdl, VProcHdl);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Bind_VCap fail\n");
	return HI_FAILURE;
    }

    HI_HANDLE VPortHdl = 1;
    HI_VPORT_ATTR_S stVPortAttr;
    stVPortAttr.stResolution.u32Width = 1280;
    stVPortAttr.stResolution.u32Height = 720;
    stVPortAttr.enPixFormat = HI_MPP_PIXEL_FORMAT_420;
    stVPortAttr.s32FrameRate = -1;
    s32Ret = HI_MAPI_VProc_Port_SetAttr(VProcHdl, VPortHdl, &stVPortAttr);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Port_SetAttr fail\n");
	return HI_FAILURE;
    }
    
    s32Ret = HI_MAPI_VProc_Port_Start(VProcHdl, VPortHdl);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Port_Start fail\n");
	return HI_FAILURE;
    }

    s32Ret = HI_MAPI_VProc_Start(VProcHdl);
    if(HI_SUCCESS != s32Ret)
    {
    	printf("HI_MAPI_VProc_Start fail\n");
	return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}


/******************************************************************************
* function    : main()
* Description : video preview sample
******************************************************************************/
/*#ifdef __HuaweiLite__
int app_main(int argc, char *argv[])
#else
int main(int argc, char* argv[])
#endif*/
int app_main(int argc, char *argv[])
{

	HI_S32 s32Ret = HI_SUCCESS;
	s32Ret = SAMPLE_VI_vpss();
	if(HI_SUCCESS != s32Ret)
	{
		printf("SAMPLE_VI_vpss fail\n");
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
