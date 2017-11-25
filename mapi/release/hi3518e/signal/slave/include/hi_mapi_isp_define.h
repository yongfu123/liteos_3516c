/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_isp_define.h
* @brief       isp struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_ISP_DEFINE_H__
#define __HI_MAPI_ISP_DEFINE_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/****************************************************************************
 * MACRO DEFINITION                                                         *
 ****************************************************************************/
typedef HI_S32		     SENSOR_ID;

typedef HI_S32		    ISP_ID;

#define RES_WIDTH_MAX               (4608)
#define RES_WIDTH_MIN               (480)
#define RES_HEIGHT_MAX              (4608)
#define RES_HEIGHT_MIN              (240)
#define FRAME_RATE_MAX              (65535.0)

#define VREG_MAX_NUM                (16)

#define AE_ZONE_ROW                 (15)
#define AE_ZONE_COLUMN              (17)
#define AWB_ZONE_ROW                (32)
#define AWB_ZONE_COLUMN             (32)
#define AWB_ZONE_ROW_STITCH         (16)
#define AWB_ZONE_COLUMN_STITCH      (64)
#define AWB_ZONE_NUM                (AWB_ZONE_ROW * AWB_ZONE_COLUMN) 
#define AF_ZONE_ROW                 (15)
#define AF_ZONE_COLUMN              (17)
#define LIGHTSOURCE_NUM             (4)

#define STATIC_DP_COUNT_MAX         (4095)
#define STATIC_DP_CAL_TIME_OUT      (0x640)
#define GAMMA_NODE_NUM              (257)
#define GAMMA_FE0_NODE_NUM          (33)
#define GAMMA_FE1_NODE_NUM          (257)

#define NP_NODE_NUM_MAX             (128)

#define SHADING_NODE_NUM_MAX        (129)
#define ISP_MESH_SHADING_NODE_NUM   (64*64)
#define ISP_MESH_SHADING_PLANE_NUM  (3)
#define ISP_MESH_LS_NUM_MAX         (4)

#define DEFOG_ZONE_ROW       (32)
#define DEFOG_ZONE_COLUMN    (32)
#define DEFOG_ZONE_NUM       (1024)
#define DEFOG_MAX_ZONE_NUM   (1024)
#define DEFOG_ZONE_ROW_STITCH (32)
#define DEFOG_ZONE_COL_STITCH (16)



#define ISP_AUTO_STENGTH_NUM (16)

#define ISP_MAX_SNS_REGS     (32)
#define ISP_MAX_DEV_NUM      (2)

#define ISP_REG_SIZE_BIN        (0x50000)
#define ISP_VREG_SIZE_BIN       (0x3000)
#define ALG_LIB_VREG_SIZE_BIN   (0x1000)

#define AI_MAX_STEP_FNO_NUM  (1024)

#define ISP_BAYER_CHN_NUM   (4)
#define CCM_MATRIX_SIZE     (9)


/* Slave mode sensor sync signal generate module */
typedef struct hiMPP_ISP_SLAVE_SNS_SYNC_S 
{
    union 
    {
        struct 
        {
            HI_U32  bit16HsDlyCyc     :  16;
            HI_U32  bitHInv           :  1;
            HI_U32  bitVInv           :  1;
            HI_U32  bit12Rsv          :  12;
            HI_U32  bitHEnable        :  1;
            HI_U32  bitVEnable        :  1;          
        } stBits;   
        HI_U32 u32Bytes; 
    } unCfg;

    HI_U32  u32VsTime;
    HI_U32  u32HsTime;
    HI_U32  u32VsCyc;
    HI_U32  u32HsCyc;    
}HI_MPP_ISP_SLAVE_SNS_SYNC_S;

/****************** InputFormatter *******************/
#define IF_KNEE_POINT_NUM       (3)
#define IF_SLOPE_NUM            (4)
/***** YUV domin sharpen *****/
#define ISP_YUV_SHPLUMA_NUM  (4)

/* config of statistics structs */
#define HIST_THRESH_NUM     (4)
/* statistics structs */
#define HIST_5_NUM      (5)
#define HIST_1024_NUM   (1024)
#define HIST_256_NUM    (256)
typedef enum hiMPP_ISP_SNS_TYPE_E
{
    HI_MPP_ISP_SNS_I2C_TYPE = 0,
    HI_MPP_ISP_SNS_SSP_TYPE,
    
    HI_MPP_ISP_SNS_TYPE_BUTT,
} HI_MPP_ISP_SNS_TYPE_E;

/* sensor communication bus */
typedef union hiMPP_ISP_SNS_COMMBUS_U 
{
    HI_S8   s8I2cDev;
    struct 
    {
        HI_S8  bit4SspDev       : 4;
        HI_S8  bit4SspCs        : 4;  
    }s8SspDev;
} HI_MPP_ISP_SNS_COMMBUS_U; 

typedef struct hiMPP_ISP_I2C_DATA_S
{
    HI_BOOL bUpdate;
    HI_U8   u8DelayFrmNum;
    HI_U8   u8IntPos;
    
    HI_U8   u8DevAddr;
    HI_U32  u32RegAddr;
    HI_U32  u32AddrByteNum;
    HI_U32  u32Data;
    HI_U32  u32DataByteNum;
} HI_MPP_ISP_I2C_DATA_S;

typedef struct hiMPP_ISP_SSP_DATA_S
{
    HI_BOOL bUpdate;
    HI_U8   u8DelayFrmNum;
    HI_U8   u8IntPos;
    
    HI_U32  u32DevAddr;
    HI_U32  u32DevAddrByteNum;
    HI_U32  u32RegAddr;
    HI_U32  u32RegAddrByteNum;
    HI_U32  u32Data;
    HI_U32  u32DataByteNum;
} HI_MPP_ISP_SSP_DATA_S;

typedef struct hiMPP_ISP_SNS_REGS_INFO_S
{
    HI_MPP_ISP_SNS_TYPE_E enSnsType;
    HI_U32  u32RegNum;
    HI_U8   u8Cfg2ValidDelayMax;
    HI_MPP_ISP_SNS_COMMBUS_U  unComBus;
    union
    {
        HI_MPP_ISP_I2C_DATA_S astI2cData[ISP_MAX_SNS_REGS];
        HI_MPP_ISP_SSP_DATA_S astSspData[ISP_MAX_SNS_REGS];
    };

   struct 
   {  
       HI_BOOL bUpdate;
       HI_U8   u8DelayFrmNum;
       HI_U32  u32SlaveVsTime;      /* time of vsync. Unit: inck clock cycle */             
    } stSlvSync;  

   	HI_BOOL bConfig;
} HI_MPP_ISP_SNS_REGS_INFO_S;

typedef enum hiMPP_ISP_IRIS_TYPE_E
{
    HI_MPP_ISP_IRIS_DC_TYPE = 0,
    HI_MPP_ISP_IRIS_P_TYPE,
    
    HI_MPP_ISP_IRIS_TYPE_BUTT,
} HI_MPP_ISP_IRIS_TYPE_E;

typedef enum hiMPP_ISP_IRIS_F_NO_E
{
    HI_MPP_ISP_IRIS_F_NO_32_0 = 0,
    HI_MPP_ISP_IRIS_F_NO_22_0,
    HI_MPP_ISP_IRIS_F_NO_16_0,
    HI_MPP_ISP_IRIS_F_NO_11_0,
    HI_MPP_ISP_IRIS_F_NO_8_0,
    HI_MPP_ISP_IRIS_F_NO_5_6,
    HI_MPP_ISP_IRIS_F_NO_4_0,
    HI_MPP_ISP_IRIS_F_NO_2_8,
    HI_MPP_ISP_IRIS_F_NO_2_0,
    HI_MPP_ISP_IRIS_F_NO_1_4,
    HI_MPP_ISP_IRIS_F_NO_1_0,    
    
    HI_MPP_ISP_IRIS_F_NO_BUTT,
} HI_MPP_ISP_IRIS_F_NO_E;

typedef struct hiMPP_ISP_PIRIS_ATTR_S
{
    HI_BOOL bStepFNOTableChange;    /*WO, Step-F number mapping table change or not */
    HI_BOOL bZeroIsMax;             /*RW, Step 0 corresponds to max aperture or not, it's related to the specific iris */
    HI_U16 u16TotalStep;            /*RW, Range:[1, 1024], Total steps of  Piris's aperture, it's related to the specific iris */
    HI_U16 u16StepCount;            /*RW, Range:[1, 1024], Used steps of Piris's aperture. when Piris's aperture is too small, the F number precision is not enough, 
                                          so not all the steps can be used. It's related to the specific iris*/
    HI_U16 au16StepFNOTable[AI_MAX_STEP_FNO_NUM];   /*RW, Range:[0, 1024], Step-F number mapping table. F1.0 is expressed as 1024, F32 is expressed as 1, it's related to the specific iris*/
    HI_MPP_ISP_IRIS_F_NO_E  enMaxIrisFNOTarget;  /*RW, Range:[F32.0, F1.0], Max F number of Piris's aperture, it's related to the specific iris */
    HI_MPP_ISP_IRIS_F_NO_E  enMinIrisFNOTarget;  /*RW, Range:[F32.0, F1.0], Min F number of Piris's aperture, it's related to the specific iris */
} HI_MPP_ISP_PIRIS_ATTR_S;

typedef enum hiMPP_ISP_AE_STRATEGY_E
{
    HI_MPP_AE_EXP_HIGHLIGHT_PRIOR = 0,
    HI_MPP_AE_EXP_LOWLIGHT_PRIOR  = 1,
    HI_MPP_AE_STRATEGY_MODE_BUTT
} HI_MPP_ISP_AE_STRATEGY_E;

typedef enum hiMPP_ISP_FSWDR_MODE_E
{
    /* Normal FSWDR mode */
    HI_MPP_ISP_FSWDR_NORMAL_MODE = 0x0,

    /* Long frame mode, only effective in LINE_WDR, when running in this mode FSWDR module only output the long frame data */
    HI_MPP_ISP_FSWDR_LONG_FRAME_MODE = 0x1,

    HI_MPP_ISP_FSWDR_MODE_BUTT
}HI_MPP_ISP_FSWDR_MODE_E;

#define EXP_RATIO_NUM       (3)
#define ISP_AE_ROUTE_MAX_NODES (16)
typedef struct hiMPP_ISP_AE_ROUTE_NODE_S
{
    HI_U32  u32IntTime;     /*RW,  sensor exposure time (unit: us ), Range: (0x0, 0xFFFFFFFF], it's related to the specific sensor */
    HI_U32  u32SysGain;     /*RW,  system gain (unit: times, 10bit precision), Range : [0x400, 0xFFFFFFFF], it's related to the specific sensor and ISP Dgain range */
    HI_MPP_ISP_IRIS_F_NO_E  enIrisFNO;  /*RW, the F number of the iris's aperture, Range:[F32.0, F1.0], only support for Piris */
} HI_MPP_ISP_AE_ROUTE_NODE_S;

typedef struct hiMPP_ISP_AE_ROUTE_S
{
    HI_U32 u32TotalNum;     /*RW,  Range: [0x0, 0x10], total node number of AE route */ 
    HI_MPP_ISP_AE_ROUTE_NODE_S astRouteNode[ISP_AE_ROUTE_MAX_NODES];
} HI_MPP_ISP_AE_ROUTE_S;


#define ISP_AE_ROUTE_EX_MAX_NODES (16)
typedef struct hiMPP_ISP_AE_ROUTE_EX_NODE_S
{
    HI_U32  u32IntTime;     /*RW,  sensor exposure time (unit: us ), Range: (0x0, 0xFFFFFFFF], it's related to the specific sensor */
    HI_U32  u32Again;       /*RW,  sensor analog gain (unit: times, 10bit precision), Range : [0x400, 0x1FFFFFFF], it's related to the specific sensor*/
    HI_U32  u32Dgain;       /*RW,  sensor digital gain (unit: times, 10bit precision), Range : [0x400, 0x1FFFFFFF], it's related to the specific sensor*/
    HI_U32  u32IspDgain;    /*RW,  ISP digital gain (unit: times, 10bit precision), Range : [0x400, 0x1FFFFFFF] */
    HI_MPP_ISP_IRIS_F_NO_E  enIrisFNO;  /*RW, the F number of the iris's aperture, Range:[F32.0, F1.0], only support for Piris */
} HI_MPP_ISP_AE_ROUTE_EX_NODE_S;

typedef struct hiMPP_ISP_AE_ROUTE_EX_S
{
    HI_U32 u32TotalNum;       /*RW,  Range: [0x0, 0x10], total node number of extend AE route */ 
    HI_MPP_ISP_AE_ROUTE_EX_NODE_S astRouteExNode[ISP_AE_ROUTE_EX_MAX_NODES];
} HI_MPP_ISP_AE_ROUTE_EX_S;
#define AWB_CURVE_PARA_NUM  (6)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_MAPI_ISP_DEFINE_H__ */

