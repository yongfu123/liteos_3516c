/******************************************************************************

  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : IMX117_slave_priv.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/06/18
  Description   : this file was private for IMX117 slave mode sensor
  History       :
  1.Date        : 
    Author      : 
    Modification: Created file
******************************************************************************/
#ifndef __IMX117_SLAVE_PRIV_H_
#define __IMX117_SLAVE_PRIV_H_

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

// usefull macro
#define HIGH_8BITS(x) ((x & 0xff00) >> 8)
#define LOW_8BITS(x)  (x & 0x00ff)
#ifndef MAX
#define MAX(a, b) (((a) < (b)) ?  (b) : (a))
#endif

#ifndef MIN
#define MIN(a, b) (((a) > (b)) ?  (b) : (a))
#endif

#define IMX117_RES_IS_4K(w, h)     (w == 4096 && h == 2160)
#define IMX117_RES_IS_4K2K(w, h)   (w == 3840 && h == 2160)
#define IMX117_RES_IS_12M(w, h)    (w == 4000 && h == 3000)
#define IMX117_RES_IS_2K(w, h)     (w == 2048 && h == 1080)
#define IMX117_RES_IS_1080P(w, h)  (w == 1920 && h == 1080)
#define IMX117_RES_IS_720P(w, h)   (w == 1280 && h == 720 )

#define CHECK_RET(express)\
do{\
    HI_S32 s32Ret;\
    s32Ret = express;\
    if (HI_SUCCESS != s32Ret)\
    {\
        printf("Failed at %s: LINE: %d with %#x!\n", __FUNCTION__, __LINE__, s32Ret);\
    }\
}while(0)

/*
--------------------------------------------------------------------------------
- Structure For Slave Mode Sensor Using
--------------------------------------------------------------------------------
*/
#define     FULL_LINES_MAX              (0xFFFF)                                                                                   
// registers to control exposure            
#define     IMX117_SHR_L                (0x000b)
#define     IMX117_SHR_H                (0x000c)
#define     IMX117_PGC_L                (0x0009)
#define     IMX117_PGC_H                (0x000a)
#define     IMX117_APGC01_L             (0x0352)
#define     IMX117_APGC01_H             (0x0353)
#define     IMX117_APGC02_L             (0x0356)
#define     IMX117_APGC02_H             (0x0357)
#define     IMX117_SVR_L                (0x000d)
#define     IMX117_SVR_H                (0x000e)
#define     IMX117_DGAIN                (0x0011)

#define     NA                          (0xFFFF)

typedef struct hiIMX117_SENSOR_REG_S{

    HI_U16 u16Addr;
    HI_U8  u8Data;
} IMX117_SENSOR_REG_S;

typedef enum {
    IMX117_MODE0 = 0,
    IMX117_MODE0A,       
    IMX117_MODE1,  
    IMX117_MODE1D,
    IMX117_MODE2,       
    IMX117_MODE4A,
    IMX117_MODE11A,

    IMX117_MODE_BUTT
    
} IMX117_RES_MODE_E;

typedef struct hiIMX117_VIDEO_MODE_TBL_S 
{
    HI_U32  u32Inck;
    HI_U32  u32InckPerHs;
    HI_U32  u32InckPerVs;
    HI_U32  u32VertiLines;
    
    HI_U32  u32MaxFps;
    const char *pszModeName;
    
} IMX117_VIDEO_MODE_TBL_S;



#endif /* __IMX117_SLAVE_PRIV_H_ */
