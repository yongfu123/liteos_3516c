/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_ae_define.h
* @brief       ae algorithm struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_AE_DEFINE_H__
#define __HI_MAPI_AE_DEFINE_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/************************** sensor's interface to ae *********************/

/* eg: 0.35db, enAccuType=AE_ACCURACY_DB, f32Accuracy=0.35 
*  and the multiply of 0.35db is power(10, (0.35/20))
*  eg: 1/16, 2/16, 3/16 multiplies, enAccuType=AE_ACCURACY_LINEAR, f32Accuracy=0.0625
*  eg: 1,2,4,8,16 multiplies, enAccuType=AE_ACCURACY_DB, f32Accuracy=6
*/
typedef enum hiMPP_AE_ACCURACY_E
{
    HI_MPP_AE_ACCURACY_DB = 0,
    HI_MPP_AE_ACCURACY_LINEAR,
    HI_MPP_AE_ACCURACY_TABLE,
    
    HI_MPP_AE_ACCURACY_BUTT,
} HI_MPP_AE_ACCURACY_E;

typedef struct hiMPP_AE_ACCURACY_S
{
    HI_MPP_AE_ACCURACY_E enAccuType;
    float   f32Accuracy;
    float   f32Offset;
} HI_MPP_AE_ACCURACY_S;

typedef struct hiMPP_AE_SENSOR_DEFAULT_S
{
    HI_U8   au8HistThresh[HIST_THRESH_NUM];
    HI_U8   u8AeCompensation;

    HI_U32  u32LinesPer500ms;
    HI_U32  u32FlickerFreq;
    HI_FLOAT f32Fps;
    HI_U32  u32InitExposure;
    HI_U32  u32InitAESpeed;
    HI_U32  u32InitAETolerance;
    
    HI_U32  u32FullLinesStd;  
    HI_U32  u32FullLinesMax;
    HI_U32  u32FullLines;  
    HI_U32  u32MaxIntTime;     /* unit is line */
    HI_U32  u32MinIntTime;
    HI_U32  u32MaxIntTimeTarget;
    HI_U32  u32MinIntTimeTarget;
    HI_MPP_AE_ACCURACY_S stIntTimeAccu;
    
    HI_U32  u32MaxAgain;
    HI_U32  u32MinAgain;
    HI_U32  u32MaxAgainTarget;
    HI_U32  u32MinAgainTarget;
    HI_MPP_AE_ACCURACY_S stAgainAccu;

    HI_U32  u32MaxDgain;
    HI_U32  u32MinDgain;
    HI_U32  u32MaxDgainTarget;
    HI_U32  u32MinDgainTarget;
    HI_MPP_AE_ACCURACY_S stDgainAccu;

    HI_U32  u32MaxISPDgainTarget;
    HI_U32  u32MinISPDgainTarget;
    HI_U32  u32ISPDgainShift;

    HI_MPP_ISP_AE_ROUTE_S stAERouteAttr;
    HI_BOOL bAERouteExValid;
    HI_MPP_ISP_AE_ROUTE_EX_S stAERouteAttrEx;

    HI_U16 u16ManRatioEnable;
    HI_U32 au32Ratio[EXP_RATIO_NUM];
	
    HI_MPP_ISP_IRIS_TYPE_E  enIrisType;
    HI_MPP_ISP_PIRIS_ATTR_S stPirisAttr;
    HI_MPP_ISP_IRIS_F_NO_E  enMaxIrisFNO;  /*RW, Range:[F32.0, F1.0], Max F number of Piris's aperture, it's related to the specific iris */
    HI_MPP_ISP_IRIS_F_NO_E  enMinIrisFNO;  /*RW, Range:[F32.0, F1.0], Min F number of Piris's aperture, it's related to the specific iris */

    HI_MPP_ISP_AE_STRATEGY_E enAeExpMode;
	
	HI_U8  u8AERunInterval;
} HI_MPP_AE_SENSOR_DEFAULT_S;

typedef struct hiMPP_AE_FSWDR_ATTR_S
{
    HI_MPP_ISP_FSWDR_MODE_E enFSWDRMode;
} HI_MPP_AE_FSWDR_ATTR_S;

typedef struct hiMPP_AE_SENSOR_EXP_FUNC_S
{
    HI_S32(*pfn_cmos_get_ae_default)(ISP_ID IspId, HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft);

    /* the function of sensor set fps */
    HI_VOID(*pfn_cmos_fps_set)(ISP_ID IspId, HI_FLOAT f32Fps, HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft);
    HI_VOID(*pfn_cmos_slow_framerate_set)(ISP_ID IspId, HI_U32 u32FullLines, HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft);

    /* while isp notify ae to update sensor regs, ae call these funcs. */
    HI_VOID(*pfn_cmos_inttime_update)(ISP_ID IspId, HI_U32 u32IntTime);
    HI_VOID(*pfn_cmos_gains_update)(ISP_ID IspId, HI_U32 u32Again, HI_U32 u32Dgain);

    HI_VOID (*pfn_cmos_again_calc_table)(ISP_ID IspId, HI_U32 *pu32AgainLin, HI_U32 *pu32AgainDb);
    HI_VOID (*pfn_cmos_dgain_calc_table)(ISP_ID IspId, HI_U32 *pu32DgainLin, HI_U32 *pu32DgainDb);

    HI_VOID (*pfn_cmos_get_inttime_max)(ISP_ID IspId, HI_U16 u16ManRatioEnable, HI_U32 *au32Ratio, HI_U32 *au32IntTimeMax, HI_U32 *au32IntTimeMin);

    /* long frame mode set */
    HI_VOID(*pfn_cmos_ae_fswdr_attr_set)(ISP_ID IspId, HI_MPP_AE_FSWDR_ATTR_S *pstAeFSWDRAttr);
    
} HI_MPP_AE_SENSOR_EXP_FUNC_S;

typedef struct hiMPP_AE_SENSOR_REGISTER_S
{
    HI_MPP_AE_SENSOR_EXP_FUNC_S stSnsExp;
} HI_MPP_AE_SENSOR_REGISTER_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
