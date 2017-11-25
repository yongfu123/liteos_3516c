/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_vcap_define.h
* @brief       vcap mapi struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/
#ifndef __HI_MAPI_VCAP_DEFINE_H__
#define __HI_MAPI_VCAP_DEFINE_H__

#define MODULE_NAME   "HI_MAPI_VCAP"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     VCAP */
/** @{ */  /** <!-- [VCAP] */

#include "hi_mapi_comm_define.h"

/** Max length of exif description*/
#define HI_SNAP_EXIF_DRSCRIPTION_LENGTH 32
/** Max frame num used to HDR*/
#define HI_SNAP_HDR_MAX_FRAME_NUM    8
/** Max num of osd region*/
#define HI_VCAP_OSD_MAX_NUM	4

#define HI_VCAP_MAX_NUM 1// 2

#define HI_MPP_VCAP_MAX_BRIGHTNESS 100
#define HI_MPP_VCAP_MIN_BRIGHTNESS 0

#define HI_MPP_VCAP_MAX_SATURATION 100
#define HI_MPP_VCAP_MIN_SATURATION 0

#define HI_MPP_VCAP_MAX_SHARPEN_ST 255
#define HI_MPP_VCAP_MIN_SHARPEN_ST 0

#define HI_MPP_VCAP_MAX_COLORTEMP 15000
#define HI_MPP_VCAP_MIN_COLORTEMP 1500

#define HI_MPP_VCAP_MAX_LDC_CENTERX_OFFSET 127
#define HI_MPP_VCAP_MIN_LDC_CENTERX_OFFSET -127

#define HI_MPP_VCAP_MAX_LDC_CENTERY_OFFSET 127
#define HI_MPP_VCAP_MIN_LDC_CENTERY_OFFSET -127

#define HI_MPP_VCAP_MAX_LDC_RATIO 300
#define HI_MPP_VCAP_MIN_LDC_RATIO -300

#define HI_MPP_VCAP_MAX_LDC_MINRATIO 0
#define HI_MPP_VCAP_MIN_LDC_MINRATIO -300

#define HI_MPP_VCAP_MAX_RAWDUMP_DEPTH 8
#define HI_MPP_VCAP_MIN_RAWDUMP_DEPTH 0

/** WDR mode*/
typedef enum hiHI_MPP_WDR_MODE_E
{
	HI_MPP_WDR_MODE_NONE = 0,
	HI_MPP_WDR_MODE_BUILT_IN,
	HI_MPP_WDR_MODE_2To1_LINE,
	HI_MPP_WDR_MODE_2To1_FRAME,
	HI_MPP_WDR_MODE_2To1_FRAME_FULL_RATE,
	HI_MPP_WDR_MODE_3To1_LINE,
	HI_MPP_WDR_MODE_3To1_FRAME,
	HI_MPP_WDR_MODE_3To1_FRAME_FULL_RATE,
	HI_MPP_WDR_MODE_4To1_LINE,
	HI_MPP_WDR_MODE_4To1_FRAME,
	HI_MPP_WDR_MODE_4To1_FRAME_FULL_RATE,
	HI_MPP_WDR_MODE_BUTT
}HI_MPP_WDR_MODE_E;

/** sensor attribute*/
typedef struct hiHI_MPP_SENSOR_ATTR_S
{
    HI_S32 s32FrameRate;
    HI_MPP_RESOLUTION_S stResolution;
	HI_MPP_WDR_MODE_E enWdrMode;
} HI_MPP_SENSOR_ATTR_S;

typedef enum hiHI_MPP_VCAP_TYPE_E
{
	HI_MPP_VCAP_TYPE_VIDEO = 0,
	HI_MPP_VCAP_TYPE_SNAP,
	HI_MPP_VCAP_TYPE_BUTT
}HI_MPP_VCAP_TYPE_E;

/** video capture attribute*/
typedef struct hiHI_MPP_VCAP_ATTR_S
{
    HI_S32 s32FrameRate;
    HI_MPP_RESOLUTION_S stResolution;
    HI_MPP_WDR_MODE_E enWdrMode;
	HI_MPP_PIXEL_FORMAT_E enPixelFormat;
	HI_MPP_VCAP_TYPE_E enVCapType;
} HI_MPP_VCAP_ATTR_S;

typedef struct hiHI_MPP_VCAP_DUMP_ATTR_S
{
	HI_MPP_PIXEL_FORMAT_E enPixelForamt;			/**< [8bit,10bit,12bit,14bit,16bit]*/
	HI_U32 u32Depth;								/**< [0,8]*/
}HI_MPP_VCAP_DUMP_ATTR_S;

/** video capture setting command*/
typedef enum hiHI_MPP_VCAP_CMD_E
{
	HI_MPP_VCAP_CMD_SetExposure,
	HI_MPP_VCAP_CMD_GetExposure,
	HI_MPP_VCAP_CMD_SetWBAttr,
	HI_MPP_VCAP_CMD_GetWBAttr,
	HI_MPP_VCAP_CMD_SetSharpen,
	HI_MPP_VCAP_CMD_GetSharpen,
	HI_MPP_VCAP_CMD_SetBrightness,
	HI_MPP_VCAP_CMD_GetBrightness,
	HI_MPP_VCAP_CMD_SetSaturation,
	HI_MPP_VCAP_CMD_GetSaturation,
	HI_MPP_VCAP_CMD_SetLDC,
	HI_MPP_VCAP_CMD_GetLDC,
	HI_MPP_VCAP_CMD_BUTT
}HI_MPP_VCAP_CMD_E;


/** operation type*/
typedef enum hiHI_MPP_VCAP_OP_TYPE_E
{
    HI_MPP_VCAP_OP_TYPE_AUTO = 0,
    HI_MPP_VCAP_OP_TYPE_MANUAL = 1,
    HI_MPP_VCAP_OP_TYPE_DISABLE = 2,
    HI_MPP_VCAP_OP_TYPE_BUTT
} HI_MPP_VCAP_OP_TYPE_E;

/** manual exposure attribute*/
typedef struct hiHI_MPP_VCAP_EXPOSURE_MANUAL_MODE_S
{
    HI_U32 u32ExposureTime;
    HI_U32 u32Gain;
} HI_MPP_VCAP_EXPOSURE_MANUAL_MODE_S;

typedef struct hiHI_MPP_VCAP_AE_RANGE_S
{
	HI_U32 u32Min;
	HI_U32 u32Max;
}HI_MPP_VCAP_AE_RANGE_S;

typedef struct hiHI_MPP_VCAP_EXPOSURE_AUTO_MODE_S
{
	HI_U32 u32EVBias;			/**< [0,0xFFFF] */
	HI_MPP_VCAP_AE_RANGE_S stSysGainRange;		/**ISO*/
}HI_MPP_VCAP_EXPOSURE_AUTO_MODE_S;

/** exposure attribute.HI_MPP_VCAP_CMD_SetExposure,HI_MPP_VCAP_CMD_GetExposure*/
typedef struct hiHI_MPP_VCAP_EXPOSURE_ATTR_S
{
    HI_MPP_VCAP_OP_TYPE_E enOpType;
    HI_MPP_VCAP_EXPOSURE_MANUAL_MODE_S stMExposureMode;
	HI_MPP_VCAP_EXPOSURE_AUTO_MODE_S stAExposureMode;
} HI_MPP_VCAP_EXPOSURE_ATTR_S;

/** The current exposure info.HI_MPP_VCAP_CMD_QUERY_EXPOSURE_INFO*/
typedef struct hiMPP_VCAP_EXPOSURE_INFO_S
{
	HI_U32 u32ExposureTime;
    HI_U32 u32AGain;
	HI_U32 u32DGain;
	HI_U32 u32IspDGain;
}HI_MPP_VCAP_EXPOSURE_INFO_S;

/** white balance manual mode*/
typedef struct hiHI_MPP_VCAP_WB_MANUAL_MODE_S
{
    HI_U32 u32ColorTemp;				/**< Unit:Kelvin,1500~15000*/
} HI_MPP_VCAP_WB_MANUAL_MODE_S;

/** white balance attribute.VCAP_CMD_SetWBAttr,VCAP_CMD_GetWBAttr*/
typedef struct hiHI_MPP_VCAP_WB_ATTR_S
{
    HI_MPP_VCAP_OP_TYPE_E enOpType;
    HI_MPP_VCAP_WB_MANUAL_MODE_S stWBMode;
} HI_MPP_VCAP_WB_ATTR_S;

typedef struct hiHI_MPP_VCAP_SHARPEN_MANUAL_ATTR_S
{
	HI_S32 s32Sharpness;			/**> [0,255]*/
}HI_MPP_VCAP_SHARPEN_MANUAL_ATTR_S;

/** shapren attribute.HI_MPP_VCAP_CMD_SetSharpen,HI_MPP_VCAP_CMD_GetSharpen*/
typedef struct hiHI_MPP_VCAP_SHARPEN_S
{
	HI_MPP_VCAP_OP_TYPE_E enOpType;
	HI_MPP_VCAP_SHARPEN_MANUAL_ATTR_S stSharpenManualAttr;
}HI_MPP_VCAP_SHARPEN_S;

/** brightness attribute.VCAP_CMD_SetBrightness,VCAP_CMD_GetBrightness*/
typedef struct hiHI_MPP_VCAP_BRIGHTNESS_S
{
	HI_S32 s32Brightness;
}HI_MPP_VCAP_BRIGHTNESS_S;

/** saturation attribute.VCAP_CMD_SetSaturation,VCAP_CMD_GetSaturation*/
typedef struct hiHI_MPP_VCAP_SATURATION_S
{
	HI_S32 s32Saturation;
}HI_MPP_VCAP_SATURATION_S;

typedef enum hiHI_MPP_VCAP_LDC_TYPE_E
{
	HI_MPP_VCAP_LDC_TYPE_ALL = 0,
	HI_MPP_VCAP_LDC_TYPE_CROP,
	HI_MPP_VCAP_LDC_TYPE_BUTT
}HI_MPP_VCAP_LDC_TYPE_E;

/** LDC attribute.HI_MPP_VCAP_CMD_SetLDC,HI_MPP_VCAP_CMD_GetLDC*/
typedef struct hiHI_MPP_VCAP_LDC_ATTR_S
{
	HI_BOOL bEnable;
	HI_MPP_VCAP_LDC_TYPE_E enLDCType;
	HI_S32 s32CenterXOffset;			/**< [-127,127] */
	HI_S32 s32CenterYOffset;			/**< [-127,127] */
	HI_S32 s32Ratio;					/**< [-300,300] */				
	HI_S32 s32MinRatio;					/**< [-300,0],when enLDCType is HI_MPP_VCAP_LDC_TYPE_CROP effective,s32Ratio>=s32MinRatio */
}HI_MPP_VCAP_LDC_ATTR_S;

typedef enum hi_MPP_VCAP_DIS_MOTION_TYPE_E
{
	HI_MPP_VCAP_DIS_MOTION_4DOF_SOFT,
	HI_MPP_VCAP_DIS_MOTION_6DOF_SOFT,   /**< Same as MovieSolid 3.x. */
	HI_MPP_VCAP_DIS_MOTION_6DOF_HYBRID, /**< Same as MovieSolid 3.x. (Hybrid) */
	HI_MPP_VCAP_DIS_MOTION_8DOF_HARD,   /**< Motion detection from gyroscope data only. */
	HI_MPP_VCAP_DIS_MOTION_BUTT
}HI_MPP_VCAP_DIS_MOTION_TYPE_E;

/** dis attribute.HI_MPP_VCAP_CMD_SetDis,HI_MPP_VCAP_CMD_GetDis*/
typedef struct hiHI_MPP_VCAP_DisAttr_S
{
	HI_MPP_VCAP_DIS_MOTION_TYPE_E enDisMotionType;
}HI_MPP_VCAP_DisAttr_S;

/** exif info*/
typedef struct hiHI_MPP_SNAP_EXIF_INFO_S
{
    HI_U8 au8ImageDescription[HI_SNAP_EXIF_DRSCRIPTION_LENGTH]; 		/**<Describes image*/
    HI_U8 au8Make[HI_SNAP_EXIF_DRSCRIPTION_LENGTH]; 				/**<Shows manufacturer of digital cameras*/
    HI_U8 au8Model[HI_SNAP_EXIF_DRSCRIPTION_LENGTH]; 				/**<Shows model number of digital cameras*/
    HI_U8 au8Software[HI_SNAP_EXIF_DRSCRIPTION_LENGTH]; 			/**<Shows firmware (internal software of digital cameras) version number*/
} HI_MPP_SNAP_EXIF_INFO_S;


/** osd display attribute.dynamic attribute*/
typedef struct hiHI_MPP_OSD_DISPATTR_S
{
    HI_BOOL                     bShow; 
    HI_U32                      u32Color;
    HI_U32                      u32Alpha;
    HI_S32                      s32RegionX;
    HI_S32                      s32RegionY;
} HI_MPP_OSD_DISPATTR_S;

/** bitmap attribute.static attribute*/
typedef struct hiHI_MPP_OSD_BITMAP_ATTR_S
{
    HI_MPP_PIXEL_FORMAT_E   enPixelFormat;
    HI_U32                      u32Width;
    HI_U32                      u32Height;
    HI_VOID*                    pData;
} HI_MPP_OSD_BITMAP_ATTR_S;

/** osd attribute*/
typedef struct hiHI_MPP_OSD_ATTR_S
{
    HI_MPP_OSD_BITMAP_ATTR_S stBitmapAttr;							/**<static attribute*/
    HI_MPP_OSD_DISPATTR_S stOsdDisplayAttr;							/**<dynamic attribute*/
} HI_MPP_OSD_ATTR_S;

/** snap mode*/
typedef enum hiHI_MPP_SNAP_MODE_E
{
    HI_MPP_SNAP_MODE_NONE = 0,									/**<non snap mode*/
    HI_MPP_SNAP_MODE_NORMAL,									/**<single snap,burst snap,continues snap and lapse snap choose this mode*/
    HI_MPP_SNAP_MODE_HDR,										/**<HDR mode*/
    HI_MPP_SNAP_MODE_LOWLIGHT,								/**<lowlight mode*/
    HI_MPP_SNAP_MODE_BUTT
} HI_MPP_SNAP_MODE_E;

/** snap normal attribute*/
typedef struct hiHI_MPP_SNAP_NORMAL_ATTR_S
{
	HI_U32 u32FrameRate;											/**<snap framerate*/
	HI_U32 u32FrameCnt;												/**<total frame count for snap*/
}HI_MPP_SNAP_NORMAL_ATTR_S;

typedef enum hiHI_MPP_VCAP_HDR_OP_TYPE_E
{
    HI_MPP_VCAP_HDR_OP_TYPE_AUTO = 0,
    HI_MPP_VCAP_HDR_OP_TYPE_MANUAL = 1,
    HI_MPP_VCAP_HDR_OP_TYPE_BUTT
} HI_MPP_VCAP_HDR_OP_TYPE_E;

typedef struct hiHI_MPP_VCAP_HDR_MANUAL_ATTR_S
{
	HI_U32 au32ManExpTime[HI_SNAP_HDR_MAX_FRAME_NUM];/*RW,  sensor exposure time (unit: us ), Range: [0x0, 0xFFFFFFFF], it's related to the specific sensor */
    HI_U32 au32ManSysgain[HI_SNAP_HDR_MAX_FRAME_NUM];/*RW,  system gain (unit: times, 10bit precision), Range : [0x400, 0xFFFFFFFF], it's related to the specific sensor and ISP Dgain range */
}HI_MPP_VCAP_HDR_MANUAL_ATTR_S;

typedef struct hiHI_MPP_VCAP_HDR_AUTO_ATTR_S
{
	HI_U16 au16HDRExpStep[HI_SNAP_HDR_MAX_FRAME_NUM]; 			/*RW, HDR exposure step (unit: times, 8bit precision), Range:[0x0, 0xFFFF]*/
}HI_MPP_VCAP_HDR_AUTO_ATTR_S;

/** snap HDR attribute*/
typedef struct hiHI_MPP_SNAP_HDR_ATTR_S
{
	HI_MPP_VCAP_HDR_OP_TYPE_E enHdrOpType;
    HI_U32 u32HDRFrameNum; 											/**<frame count for HDR*/
	HI_MPP_VCAP_HDR_MANUAL_ATTR_S stHdrManualAttr; 
	HI_MPP_VCAP_HDR_AUTO_ATTR_S stHdrAutoAttr;
} HI_MPP_SNAP_HDR_ATTR_S;

/** lowlight attribute.reserve*/
typedef struct hiHI_MPP_SNAP_LL_ATTR_S
{
    HI_U32 u32LLFrameNum; 											/**<frame count for LL*/
} HI_MPP_SNAP_LL_ATTR_S;

/** snap attribute*/
typedef struct hiHI_MPP_SNAP_ATTR_S
{
    HI_MPP_SNAP_MODE_E enSnapMode;
    union
    {
        HI_MPP_SNAP_NORMAL_ATTR_S stNormalAttr;
        HI_MPP_SNAP_HDR_ATTR_S stHDRAttr;
        HI_MPP_SNAP_LL_ATTR_S stLLAttr;
    };
} HI_MPP_SNAP_ATTR_S;

typedef struct hiMPP_VCAP_DIS_GYRO_DATA_S
{
	HI_DOUBLE     *pdRotX;		/**< Pointer to the x-axis angler velocity array */
	HI_DOUBLE     *pdRotY;		/**< Pointer to the y-axis angler velocity array */
	HI_DOUBLE     *pdRotZ;		/**< Pointer to the z-axis angler velocity array */
	HI_S64    	  *ps64Time;	/* Pointer to the time stamp array */
	HI_U32    	   u32Num;		/**< Number of valid data */
}HI_MPP_VCAP_DIS_GYRO_DATA_S;

typedef enum hiEN_VCAP_ERR_CODE_E
{
    EN_VCAP_INVALID_FD = 0x40, 
    EN_VCAP_IOCTL_FAIL = 0x41,
    EN_VCAP_OVERRANGE = 0x42,
    EN_VCAP_NOT_INITED = 0x43,
    EN_VCAP_NOT_STARTED = 0x44
}EN_VCAP_ERR_CODE_E;

/** Null pointer error for vcap*/
#define HI_ERR_MAPI_VCAP_NULL_PTR                              		HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_ERR_NULL_PTR)
/** illegal parameter error for vcap*/
#define HI_ERR_MAPI_VCAP_ILLEGAL_PARA                              HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_ERR_ILLEGAL_PARAM)
/** invalid fd error for vcap*/
#define HI_ERR_MAPI_VCAP_INVALID_FD					HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_VCAP_INVALID_FD)
/** ioctl fail error for vcap*/
#define HI_ERR_MAPI_VCAP_IOCTL_FAIL					HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_VCAP_IOCTL_FAIL)
/** not support error for vcap*/
#define HI_ERR_MAPI_VCAP_NOTSUPPORT					HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_ERR_NOT_SUPPORT)
/** overrange error for vcap*/
#define HI_ERR_MAPI_VCAP_OVERRANGE					HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_VCAP_OVERRANGE)
/** not inited error for vcap*/
#define HI_ERR_MAPI_VCAP_NOT_INITED					HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_VCAP_NOT_INITED)
/** not start error for vcap*/
#define HI_ERR_MAPI_VCAP_NOT_STARTED					HI_DEF_ERR(HI_MPP_MOD_VCAP,EN_ERR_LEVEL_ERROR,EN_VCAP_NOT_STARTED)
/** @}*/  /** <!-- ==== VCAP End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_MAPI_VCAP_DEFINE_H__ */
