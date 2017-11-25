/******************************************************************************

  Copyright (C), 2016-2022, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_mapi_gyro.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/08/24
  Description   :
  History       :
  1.Date        : 2016/08/24
    Author      : 
    Modification: Created file

******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hi_type.h"
#include "hi_mapi_sys.h"
#include "gyro_dev.h"
#include "hi_mapi_vcap_define.h"


#define FD_INITIALIZATION_VAL -1

#define HAL_GYRO_SCALE 2000
//#define GYRO_SENSITIVTY   (16.4)    //32768/2000
#define GYRO_SENSITIVTY   (131.072)    //32768/250
#define DEC_TO_RAD  (0.01745333)  //PI/180

#define X_BUF_LEN            (1000)
#define GYRO_BUF_LEN         ((4*3*X_BUF_LEN)+8*X_BUF_LEN)
#define PI                   (3.14159)

#define GYTO_DEV "/dev/BMI160"

HI_S32 g_s32GyroDevFd = FD_INITIALIZATION_VAL;
GYRO_ATTR_S  g_stGyroAttr;
HI_U32 phyaddr = 0;
HI_MPP_VCAP_DIS_GYRO_DATA_S g_stMORPHOGyroData;
GYRO_INFO_S g_stDISGyroInfo;
//FILE *fpGyroData = NULL;

static void DC_2I_D32_TRC_WRA_01(   HI_S32    *pDataIn_x,
                                           HI_S32    *pDataOut_x,
                                           HI_S32    *pDataIn_y,
                                           HI_S32    *pDataOut_y,
                                           HI_S32    *pDataIn_z,
                                           HI_S32    *pDataOut_z,
                                           HI_S32      NrSamples)
{
	#if 1
	#define DC_D16_STEP 0.1
    static float GYROX=1,GYROY=1,GYROZ=1;
    HI_S32 Diff;
    HI_S32 j;

   
    for(j=NrSamples-1;j>=0;j--)
    { 
        /* Subtract DC an saturate */
        Diff=*(pDataIn_x++)-(HI_S32)(GYROX + 0.5);
        if (Diff > 32767) {
            Diff = 32767; }
        else if (Diff < -32768) {
            Diff = -32768; }
        *(pDataOut_x++)=(HI_S32)Diff;
        if (Diff < 0) {
            GYROX -= DC_D16_STEP; }
        else {
            GYROX += DC_D16_STEP; }

        /* Subtract DC an saturate */
        Diff=*(pDataIn_y++)-(HI_S32)(GYROY + 0.5);
        if (Diff > 32767) {
            Diff = 32767; }
        else if (Diff < -32768) {
            Diff = -32768; }
        *(pDataOut_y++)=(HI_S32)Diff;
        if (Diff < 0) {
            GYROY -= DC_D16_STEP; }
        else {
            GYROY += DC_D16_STEP; }

        /* Subtract DC an saturate */
        Diff=*(pDataIn_z++)-(HI_S32)(GYROZ + 0.5);
        if (Diff > 32767) {
            Diff = 32767; }
        else if (Diff < -32768) {
            Diff = -32768; }
        *(pDataOut_z++)=(HI_S32)Diff;
        if (Diff < 0) {
            GYROZ -= DC_D16_STEP; }
        else {
            GYROZ += DC_D16_STEP; }

    }
	#endif
}

HI_S32 HI_GYRO_Init(HI_S32 GyroDev, HI_S32 s32HZ)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BufSize = 0;    
    u32BufSize = GYRO_BUF_LEN;

    g_s32GyroDevFd = open(GYTO_DEV, O_RDWR);
    if (g_s32GyroDevFd < 0)
    {
        printf("Error: cannot open %s device.\n",GYTO_DEV);
        return -1;
    }

	s32Ret = HI_MAPI_AllocBuffer(&g_stGyroAttr.u32PhyAddr, &g_stGyroAttr.pVirAddr, u32BufSize, "GyroData");
    if (HI_SUCCESS != s32Ret)
    {
        printf("GYRO Mmz alloc failed!\n");
        return s32Ret;
    }
    memset(g_stGyroAttr.pVirAddr, 0, u32BufSize);

    phyaddr = g_stGyroAttr.u32PhyAddr;
    
    printf("n111111111 u32PhyAddr : %x !!!!!!!!!!\r\n",g_stGyroAttr.u32PhyAddr);
    g_stGyroAttr.u32GyroFreq = 1000;
    g_stGyroAttr.u32Buflen = GYRO_BUF_LEN;

    g_stMORPHOGyroData.pdRotX = (HI_DOUBLE *)malloc(sizeof(HI_DOUBLE) * X_BUF_LEN);
    if(NULL ==g_stMORPHOGyroData.pdRotX  )
    {
    	printf("~~~~~~~~~~~~~~~pdRotX : ~~~~~~~~~~~~~~\n");
    }
    g_stMORPHOGyroData.pdRotY = (HI_DOUBLE *)malloc(sizeof(HI_DOUBLE) * X_BUF_LEN);
        if(NULL ==g_stMORPHOGyroData.pdRotY  )
    {
    	printf("~~~~~~~~~~~~~~~pdRoty : ~~~~~~~~~~~~~~\n");
    }
    g_stMORPHOGyroData.pdRotZ = (HI_DOUBLE *)malloc(sizeof(HI_DOUBLE) * X_BUF_LEN);
        if(NULL ==g_stMORPHOGyroData.pdRotZ  )
    {
    	printf("~~~~~~~~~~~~~~~pdRotz : ~~~~~~~~~~~~~~\n");
    }
    g_stMORPHOGyroData.ps64Time = (HI_S32 *)malloc(sizeof(HI_S64) * X_BUF_LEN);
        if(NULL ==g_stMORPHOGyroData.ps64Time  )
    {
    	printf("~ps32Time : ~~~~~~~~~~~~~~\n");
    }
    g_stMORPHOGyroData.u32Num = 0;

    printf("~1213~~~~~~~~~~~~~~pdRotX : %p  ~~~~~~~~~~~~~~\n",g_stMORPHOGyroData.pdRotX);

    ioctl(g_s32GyroDevFd, IOCTL_CMD_INIT_BUF, &g_stGyroAttr);
    
    return s32Ret;
}

HI_S32 HI_GYRO_DeInit(HI_S32 GyroDev)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BufSize = 0;
    
    s32Ret = ioctl(g_s32GyroDevFd, IOCTL_CMD_DEINIT_BUF);

    s32Ret = HI_MAPI_FreeBuffer(g_stGyroAttr.u32PhyAddr, g_stGyroAttr.pVirAddr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("new dis exit failed!");
    }
    g_stGyroAttr.u32PhyAddr = 0;
    g_stGyroAttr.pVirAddr = NULL;

    free(g_stMORPHOGyroData.pdRotX);
    g_stMORPHOGyroData.pdRotX = NULL;

    free(g_stMORPHOGyroData.pdRotY);
    g_stMORPHOGyroData.pdRotY = NULL;

    free(g_stMORPHOGyroData.pdRotZ);
    g_stMORPHOGyroData.pdRotZ = NULL;

    free(g_stMORPHOGyroData.ps64Time);
    g_stMORPHOGyroData.ps64Time = NULL;

    close(g_s32GyroDevFd);
        
    return s32Ret;
}

HI_S32 HI_GYRO_Start(HI_S32 GyroDev)
{
    if(FD_INITIALIZATION_VAL ==g_s32GyroDevFd)
	{
		return HI_FAILURE;
	}
	
    return ioctl(g_s32GyroDevFd, IOCTL_CMD_START_GYRO, NULL);
}

HI_S32 HI_GYRO_Stop(HI_S32 GyroDev)
{
    if(FD_INITIALIZATION_VAL ==g_s32GyroDevFd)
	{
		return HI_FAILURE;
	}
    return ioctl(g_s32GyroDevFd, IOCTL_CMD_STOP_GYRO, NULL);
}

extern HI_BOOL g_bSaveGyroData;
extern HI_BOOL bRecording;

HI_S32 HI_GYRO_GetData(HI_S32 GyroDev,HI_U64 u64BeginPts, HI_U64 u64EndPts, HI_MPP_VCAP_DIS_GYRO_DATA_S *pstDISGyroData)
{
    //printf("-------------------------------------HI_HAL_GYRO_GetData,u64BeginPts=%llu,u64EndPts=%llu\n",u64BeginPts,u64EndPts);
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Size1 = 0;
    HI_U32 u32Size2 = 0;
    HI_U32 i = 0;
    HI_S32 *pdRotX1 = 0;
    HI_S32 *pdRotY1 = 0;
    HI_S32 *pdRotZ1 = 0;
    HI_U64 *pu64PTS1 = 0;
    HI_S32 *pdRotX2 = 0;
    HI_S32 *pdRotY2 = 0;
    HI_S32 *pdRotZ2 = 0;
    HI_U64 *pu64PTS2 = 0;
    HI_CHAR aszPts[128];
    HI_CHAR text[256];
    
    if(NULL == pstDISGyroData)
    {
        printf("pstDISGyroData is null\n");
        return HI_FAILURE;
    }
    if(FD_INITIALIZATION_VAL ==g_s32GyroDevFd)
	{
		return HI_FAILURE;
	}

//    double num[1000];

    memset(&g_stDISGyroInfo , 0, sizeof(GYRO_INFO_S));

    g_stDISGyroInfo.u64BeginPts = u64BeginPts;
    g_stDISGyroInfo.u64EndPts = u64EndPts;

    s32Ret =  ioctl(g_s32GyroDevFd, IOCTL_CMD_GET_GYRO_DATA, &g_stDISGyroInfo);
    if (HI_SUCCESS != s32Ret)
    {
        printf("gyrodev %d get gyrodata failed ! s32Ret : 0x%x \r\n", GyroDev, s32Ret);
        return s32Ret;
    }

    //printf( "!!!!!! u32Num 1 : %d , u32Num2  : %d ,buflen : %d ,startpts:%llu,endpts:%llu!!!!!!!!!!!!!!\r\n",g_stDISGyroInfo.stDISGyroData[0].u32Num,g_stDISGyroInfo.stDISGyroData[1].u32Num,X_BUF_LEN,g_stDISGyroInfo.u64BeginPts,g_stDISGyroInfo.u64EndPts);

    g_stMORPHOGyroData.u32Num = g_stDISGyroInfo.stDISGyroData[0].u32Num + g_stDISGyroInfo.stDISGyroData[1].u32Num;

    if (g_stDISGyroInfo.stDISGyroData[0].u32Num > 0)
    {
        u32Size1 = g_stDISGyroInfo.stDISGyroData[0].u32Num * sizeof(HI_S32);
        pdRotX1 = (HI_S32 *)((HI_S32 *)g_stGyroAttr.pVirAddr + ((HI_S32 *)g_stDISGyroInfo.stDISGyroData[0].pdRotX - (HI_S32 *)phyaddr));
        pdRotY1 = (HI_S32 *)((HI_S32 *)g_stGyroAttr.pVirAddr + ((HI_S32 *)g_stDISGyroInfo.stDISGyroData[0].pdRotY - (HI_S32 *)phyaddr));
        pdRotZ1 = (HI_S32 *)((HI_S32 *)g_stGyroAttr.pVirAddr + ((HI_S32 *)g_stDISGyroInfo.stDISGyroData[0].pdRotZ - (HI_S32 *)phyaddr));
        pu64PTS1 = (HI_U64 *)((HI_U64 *)g_stGyroAttr.pVirAddr + ((HI_U64 *)g_stDISGyroInfo.stDISGyroData[0].pu64Time - (HI_U64 *)phyaddr));

        
        DC_2I_D32_TRC_WRA_01(pdRotX1,
        pdRotX1,
        pdRotY1,
        pdRotY1,
        pdRotZ1,
        pdRotZ1,
        g_stDISGyroInfo.stDISGyroData[0].u32Num);

        for (i = 0; i < g_stDISGyroInfo.stDISGyroData[0].u32Num ; i++)
        {
			/*
            if (g_bSaveGyroData && bRecording)
            {
                sprintf(text,"x:%d, y:%d, z:%d, pts:%llu\n", *(pdRotX1 + i), *(pdRotY1 + i), *(pdRotZ1 + i), *(pu64PTS1 + i));
                s32Ret = fwrite(text, strlen(text), 1, fpGyroData);
            }*/
//            	printf("0================x:%d,y:%d,z:%d,pts:%llu\n", *(pdRotX1 + i), *(pdRotY1 + i), *(pdRotZ1 + i), *(pu64PTS1 + i));
//			printf("%d   %d   %d   %llu\n", *(pdRotX1 + i), *(pdRotY1 + i), *(pdRotZ1 + i), *(pu64PTS1 + i));

            *(g_stMORPHOGyroData.pdRotZ + i) = (((HI_DOUBLE) * (pdRotX1 + i) / GYRO_SENSITIVTY) * DEC_TO_RAD)*(-1);
            *(g_stMORPHOGyroData.pdRotX + i) = (((HI_DOUBLE) * (pdRotY1 + i) / GYRO_SENSITIVTY) * DEC_TO_RAD);
            *(g_stMORPHOGyroData.pdRotY + i) = (((HI_DOUBLE) * (pdRotZ1 + i) / GYRO_SENSITIVTY) * DEC_TO_RAD)*(-1);
            *(g_stMORPHOGyroData.ps64Time + i) = (HI_S64)((*(pu64PTS1 + i)));
//            	printf("%10lf ,%10lf ,%10lf , %lld\r\n", *(g_stMORPHOGyroData.pdRotX + i), *(g_stMORPHOGyroData.pdRotY + i), *(g_stMORPHOGyroData.pdRotZ + i), *(g_stMORPHOGyroData.ps64Time + i) );

//            g_x +=*(pdRotX1 + i);
//            g_y +=*(pdRotY1 + i);
//            g_z +=*(pdRotZ1 + i);
//            g_num++;
        }

    }

    if (g_stDISGyroInfo.stDISGyroData[1].u32Num > 0)
    {

        pdRotX2 = (HI_S32 *)((HI_S32 *)g_stGyroAttr.pVirAddr + ((HI_S32 *)g_stDISGyroInfo.stDISGyroData[1].pdRotX - (HI_S32 *)phyaddr));
        pdRotY2 = (HI_S32 *)((HI_S32 *)g_stGyroAttr.pVirAddr + ((HI_S32 *)g_stDISGyroInfo.stDISGyroData[1].pdRotY - (HI_S32 *)phyaddr));
        pdRotZ2 = (HI_S32 *)((HI_S32 *)g_stGyroAttr.pVirAddr + ((HI_S32 *)g_stDISGyroInfo.stDISGyroData[1].pdRotZ - (HI_S32 *)phyaddr));
        pu64PTS2 = (HI_U64 *)((HI_U64 *)g_stGyroAttr.pVirAddr + ((HI_U64 *)g_stDISGyroInfo.stDISGyroData[1].pu64Time - (HI_U64 *)phyaddr));

        DC_2I_D32_TRC_WRA_01(pdRotX2,
        pdRotX2,
        pdRotY2,
        pdRotY2,
        pdRotZ2,
        pdRotZ2,
        g_stDISGyroInfo.stDISGyroData[1].u32Num);
        
        for (i = g_stDISGyroInfo.stDISGyroData[0].u32Num ; i < g_stDISGyroInfo.stDISGyroData[0].u32Num + g_stDISGyroInfo.stDISGyroData[1].u32Num ; i++)
        {
			/*
            if (g_bSaveGyroData && bRecording)
            {
                sprintf(text,"x:%d, y:%d, z:%d, pts:%llu\n", *(pdRotX2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pdRotY2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pdRotZ2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pu64PTS2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num));
                s32Ret = fwrite(text, strlen(text), 1, fpGyroData);
            }*/
//             printf("1================x:%d,y:%d,z:%d,pts:%llu\n",*(pdRotX2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pdRotY2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pdRotZ2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pu64PTS2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num));
//			printf("%d   %d   %d   %llu\n",*(pdRotX2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pdRotY2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pdRotZ2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num), *(pu64PTS2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num));
            *(g_stMORPHOGyroData.pdRotZ + i) = (HI_DOUBLE)((HI_DOUBLE)(*(pdRotX2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num) / GYRO_SENSITIVTY) * DEC_TO_RAD)*(-1);
            *(g_stMORPHOGyroData.pdRotX + i) = (HI_DOUBLE)((HI_DOUBLE)(*(pdRotY2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num) / GYRO_SENSITIVTY) * DEC_TO_RAD);
            *(g_stMORPHOGyroData.pdRotY + i)  = (HI_DOUBLE)((HI_DOUBLE)(*(pdRotZ2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num) / GYRO_SENSITIVTY) * DEC_TO_RAD)*(-1);
            *(g_stMORPHOGyroData.ps64Time + i) = (HI_S64)((*(pu64PTS2 + i - g_stDISGyroInfo.stDISGyroData[0].u32Num)));
//            printf("%10lf ,%10lf ,%10lf , %lld\r\n", *(g_stMORPHOGyroData.pdRotX + i), *(g_stMORPHOGyroData.pdRotY + i), *(g_stMORPHOGyroData.pdRotZ + i), *(g_stMORPHOGyroData.ps64Time + i) );
//            g_x +=*(pdRotX2 + i);
//            g_y +=*(pdRotY2 + i);
//            g_z +=*(pdRotZ2 + i);
//            g_num++;

		}

    }
//    if(g_num >= 20000)
//    {
//        printf("================g_x:%d,g_y:%d,g_z:%d\n",g_x/g_num,g_y/g_num,g_z/g_num);
//    }

    memcpy(pstDISGyroData , &g_stMORPHOGyroData, sizeof(HI_MPP_VCAP_DIS_GYRO_DATA_S));

    //printf("******************offset : x = %d , y = %d ,z = %d  *****************\r\n", (g_xsum/g_num),(g_ysum/g_num),(g_zsum/g_num));
    return s32Ret;
}

HI_S32 HI_GYRO_Release(HI_S32 GyroDev)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if(FD_INITIALIZATION_VAL ==g_s32GyroDevFd)
	{
		return HI_FAILURE;
	}

    memset(g_stMORPHOGyroData.pdRotX, 0 , sizeof(HI_DOUBLE) * X_BUF_LEN);
    memset(g_stMORPHOGyroData.pdRotY, 0 , sizeof(HI_DOUBLE) * X_BUF_LEN);
    memset(g_stMORPHOGyroData.pdRotZ, 0 , sizeof(HI_DOUBLE) * X_BUF_LEN);
    memset(g_stMORPHOGyroData.ps64Time, 0 , sizeof(HI_S64) * X_BUF_LEN);

    return  ioctl(g_s32GyroDevFd, IOCTL_CMD_RELEASE_BUF, &g_stDISGyroInfo);
    
    return HI_SUCCESS;
}
