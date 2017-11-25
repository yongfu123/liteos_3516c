/******************************************************************************

  Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_mapi_disp_define.h
  Version       : Initial Draft
  Author        : Hisilicon Hi35xx MPP Team
  Created       : 2016/06/08
  Last Modified :
  Description   : disp mapi struct declaration
  Function List :
  History       :
******************************************************************************/
#ifndef __HI_MAPI_DISP_DEFINE_H__
#define __HI_MAPI_DISP_DEFINE_H__

#include "hi_mapi_comm_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     DISP */
/** @{ */  /** <!-- [DISP] */

#define HI_MAPI_ERR_DISP_NULL_PTR        HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NULL_PTR)
#define HI_MAPI_ERR_DISP_NOTREADY        HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_SYS_NOTREADY)
#define HI_MAPI_ERR_DISP_INVALID_DEVID   HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_DEVID)
#define HI_MAPI_ERR_DISP_INVALID_CHNID   HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_CHNID)
#define HI_MAPI_ERR_DISP_EXIST           HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_EXIST)
#define HI_MAPI_ERR_DISP_UNEXIST         HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_UNEXIST)
#define HI_MAPI_ERR_DISP_NOT_SUPPORT     HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_SUPPORT)
#define HI_MAPI_ERR_DISP_NOT_PERM        HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_PERM)
#define HI_MAPI_ERR_DISP_NOMEM           HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOMEM)
#define HI_MAPI_ERR_DISP_NOBUF           HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOBUF)
#define HI_MAPI_ERR_DISP_ILLEGAL_PARAM   HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_ILLEGAL_PARAM)
#define HI_MAPI_ERR_DISP_BUSY            HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUSY)
#define HI_MAPI_ERR_DISP_BUF_EMPTY       HI_DEF_ERR(HI_MPP_MOD_DISP, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUF_EMPTY)


typedef HI_S32 HI_MPP_DISP_INTF_TYPE_E;
#define DISP_INTF_CVBS        (0x01L<<0)
#define DISP_INTF_BT656       (0x01L<<3)
#define DISP_INTF_BT1120      (0x01L<<4)
#define DISP_INTF_HDMI        (0x01L<<5)
#define DISP_INTF_LCD_6BIT    (0x01L<<9)
#define DISP_INTF_LCD_8BIT    (0x01L<<10)
#define DISP_INTF_LCD_16BIT   (0x01L<<11)
#define DISP_INTF_LCD_24BIT   (0x01L<<12)


typedef enum HiMPP_DISP_INTF_SYNC_E
{
    DISP_SYNC_PAL = 0,
    DISP_SYNC_NTSC,
    
    DISP_SYNC_1080P24,
    DISP_SYNC_1080P25,
    DISP_SYNC_1080P30,
    
    DISP_SYNC_720P50, 
    DISP_SYNC_720P60,   
    DISP_SYNC_1080I50,
    DISP_SYNC_1080I60,    
    DISP_SYNC_1080P50,
    DISP_SYNC_1080P60,            

    DISP_SYNC_576P50,
    DISP_SYNC_480P60,

    DISP_SYNC_800x600_60,            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
    DISP_SYNC_1024x768_60,           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
    DISP_SYNC_1280x1024_60,          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
    DISP_SYNC_1366x768_60,           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
    DISP_SYNC_1440x900_60,           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
    DISP_SYNC_1280x800_60,           /* 1280*800@60Hz VGA@60Hz*/
    DISP_SYNC_1600x1200_60,          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
    DISP_SYNC_1680x1050_60,          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
    DISP_SYNC_1920x1200_60,          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking)*/
    DISP_SYNC_640x480_60,            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
    DISP_SYNC_960H_PAL,              /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced)*/
    DISP_SYNC_960H_NTSC,             /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced)*/
    DISP_SYNC_320X240_60,            /* For ota5182 at 60 Hz (8bit) */
    DISP_SYNC_320X240_50,            /* For ili9342 at 50 Hz (6bit) */
    DISP_SYNC_240X320_50,            /* For ili9341 at 50 Hz (6bit) */
    DISP_SYNC_240X320_60,            /* For ili9341 at 60 Hz (16bit) */
    DISP_SYNC_800X600_50,            /* For LCD at 50 Hz (24bit) */
    DISP_SYNC_USER,
    DISP_SYNC_BUTT
    
} HI_MPP_DISP_INTF_SYNC_E;

typedef struct HiMPP_DISP_SYNC_INFO_S
{
	HI_BOOL bSynm;
	HI_BOOL bIop;
	HI_U8 u8Intfb;
	HI_U16 u16Vact ;
	HI_U16 u16Vbb;
	HI_U16 u16Vfb;
	HI_U16 u16Hact;
	HI_U16 u16Hbb;
	HI_U16 u16Hfb;
	HI_U16 u16Hmid;
	HI_U16 u16Bvact;
	HI_U16 u16Bvbb;
	HI_U16 u16Bvfb;
	HI_U16 u16Hpw;
	HI_U16 u16Vpw;
	HI_BOOL bIdv;
	HI_BOOL bIhs;
	HI_BOOL bIvs;
} HI_MPP_DISP_SYNC_INFO_S;

typedef enum hiMPP_DISP_ROTATE_E
{
    HI_MPP_ROTATE_NONE = 0,
    HI_MPP_ROTATE_90   = 1,
    HI_MPP_ROTATE_180  = 2,
    HI_MPP_ROTATE_270  = 3,
    HI_MPP_ROTATE_BUTT
} HI_MPP_DISP_ROTATE_E;

typedef struct hiMPP_DISP_ATTR_S
{
    HI_U32 u32BgColor;
    HI_MPP_DISP_INTF_TYPE_E enIntfType;
    HI_MPP_DISP_INTF_SYNC_E enIntfSync;
    HI_MPP_DISP_SYNC_INFO_S stSyncInfo;
    HI_MPP_DISP_ROTATE_E enDispRorate;
} HI_MPP_DISP_ATTR_S;

typedef enum hiMPP_CSC_MATRIX_E
{
    HI_MPP_CSC_MATRIX_IDENTITY = 0,
    
    HI_MPP_CSC_MATRIX_BT601_TO_BT709,
    HI_MPP_CSC_MATRIX_BT709_TO_BT601,

    HI_MPP_CSC_MATRIX_BT601_TO_RGB_PC,
    HI_MPP_CSC_MATRIX_BT709_TO_RGB_PC,

    HI_MPP_CSC_MATRIX_RGB_TO_BT601_PC,
    HI_MPP_CSC_MATRIX_RGB_TO_BT709_PC,

    HI_MPP_CSC_MATRIX_BUTT
} HI_MPP_CSC_MATRIX_E;

typedef struct hiMPP_CSC_S
{
    HI_MPP_CSC_MATRIX_E enCscMatrix;
    HI_U32 u32Luma;                     /* luminance:   0 ~ 100 default: 50 */
    HI_U32 u32Contrast;                 /* contrast :   0 ~ 100 default: 50 */
    HI_U32 u32Hue;                      /* hue      :   0 ~ 100 default: 50 */
    HI_U32 u32Satuature;                /* satuature:   0 ~ 100 default: 50 */
} HI_MPP_CSC_S;

typedef struct hiMPP_DISP_CSCATTREX_S
{
    HI_MPP_CSC_S stVideoCSC;
} HI_MPP_DISP_CSCATTREX_S;

typedef struct hiMPP_DISP_ROTATEATTREX_S
{
    HI_MPP_DISP_ROTATE_E enDispRorate;
} HI_MPP_DISP_ROTATEATTREX_S;

typedef enum hiMPP_DISP_CMD_E
{
    HI_MPP_DISP_CMD_SETCSC,       /**< HI_MPP_DISP_ATTREX_S*/
    HI_MPP_DISP_CMD_GETCSC,       /**< HI_MPP_DISP_ATTREX_S*/
    HI_MPP_DISP_CMD_SETROTATE,  /**< HI_MPP_DISP_ROTATE_E*/
    HI_MPP_DISP_CMD_GETROTATE,  /**< HI_MPP_DISP_ROTATE_E*/
    HI_MPP_DISP_CMD_BUTT
}HI_MPP_DISP_CMD_E;

typedef struct hiMPP_DISP_WINDOW_ATTR_S
{
    HI_MPP_RECT_S stRect;
    HI_U32 u32Priority;
} HI_MPP_DISP_WINDOW_ATTR_S;

/** @}*/  /** <!-- ==== DISP End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_MAPI_DISP_DEFINE_H__ */
