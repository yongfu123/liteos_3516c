/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_awb_define.h
* @brief       awb algorithm struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_AWB_DEFINE_H__
#define __HI_MAPI_AWB_DEFINE_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/************************** sensor's interface to awb *********************/
typedef struct hiMPP_AWB_CCM_S
{    
    HI_U16 u16HighColorTemp;    /* D50 lighting source is  recommended */
    HI_U16 au16HighCCM[CCM_MATRIX_SIZE];
    HI_U16 u16MidColorTemp;     /* D32 lighting source is  recommended */
    HI_U16 au16MidCCM[CCM_MATRIX_SIZE];       
    HI_U16 u16LowColorTemp;     /* A lighting source is  recommended */
    HI_U16 au16LowCCM[CCM_MATRIX_SIZE];
}HI_MPP_AWB_CCM_S;

typedef struct hiMPP_AWB_AGC_TABLE_S
{
    HI_BOOL bValid;
    
    HI_U8   au8Saturation[ISP_AUTO_STENGTH_NUM];   /* adjust saturation, different iso with different saturation */
} HI_MPP_AWB_AGC_TABLE_S;

typedef struct hiMPP_AWB_SENSOR_DEFAULT_S
{
    HI_U16  u16WbRefTemp;       /* reference color temperature for WB  */    
    HI_U16  au16GainOffset[ISP_BAYER_CHN_NUM];  /* gain offset for white balance */
    HI_S32  as32WbPara[AWB_CURVE_PARA_NUM];      /* parameter for wb curve,p1,p2,q1,a1,b1,c1 */

    HI_MPP_AWB_AGC_TABLE_S stAgcTbl;
    HI_MPP_AWB_CCM_S stCcm;
} HI_MPP_AWB_SENSOR_DEFAULT_S;

typedef struct hiMPP_AWB_SENSOR_EXP_FUNC_S
{
    HI_S32(*pfn_cmos_get_awb_default)(ISP_ID IspId, HI_MPP_AWB_SENSOR_DEFAULT_S *pstAwbSnsDft);
} HI_MPP_AWB_SENSOR_EXP_FUNC_S;

typedef struct hiMPP_AWB_SENSOR_REGISTER_S
{
    HI_MPP_AWB_SENSOR_EXP_FUNC_S stSnsExp;
} HI_MPP_AWB_SENSOR_REGISTER_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
