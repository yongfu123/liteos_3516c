/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_vproc_define.h
* @brief       vproc mapi struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/
#ifndef __HI_VPROC_DEFINE_H__
#define __HI_VPROC_DEFINE_H__

#include "hi_mapi_errno.h"
#include "hi_mapi_comm_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     VPROC */
/** @{ */  /** <!-- [VPROC] */

#define HI_MAPI_ERR_VPROC_NULL_PTR        HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NULL_PTR)
#define HI_MAPI_ERR_VPROC_NOTREADY        HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_SYS_NOTREADY)
#define HI_MAPI_ERR_VPROC_INVALID_DEVID   HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_DEVID)
#define HI_MAPI_ERR_VPROC_INVALID_CHNID   HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_CHNID)
#define HI_MAPI_ERR_VPROC_EXIST           HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_EXIST)
#define HI_MAPI_ERR_VPROC_UNEXIST         HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_UNEXIST)
#define HI_MAPI_ERR_VPROC_NOT_SUPPORT     HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_SUPPORT)
#define HI_MAPI_ERR_VPROC_NOT_PERM        HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_PERM)
#define HI_MAPI_ERR_VPROC_NOMEM           HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOMEM)
#define HI_MAPI_ERR_VPROC_NOBUF           HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOBUF)
#define HI_MAPI_ERR_VPROC_ILLEGAL_PARAM   HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_ILLEGAL_PARAM)
#define HI_MAPI_ERR_VPROC_BUSY            HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUSY)
#define HI_MAPI_ERR_VPROC_BUF_EMPTY       HI_DEF_ERR(HI_MPP_MOD_VPROC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUF_EMPTY)

#define VPROC_MAX_NUM 32
#define VPORT_MAX_NUM 4

typedef enum hiVPROC_TYPE_E
{
    VPROC_TYPE_VIDEO = 0,
    VPROC_TYPE_SNAP,
    VPROC_TYPE_BUTT
}HI_VPROC_TYPE_E;

typedef struct hiVPROC_ATTR_S
{
    HI_VPROC_TYPE_E enVProcType;
    HI_U32 u32MaxW;
    HI_U32 u32MaxH;
} HI_VPROC_ATTR_S;

typedef struct hiVPORT_ATTR_S
{
    HI_S32 s32FrameRate;
    HI_MPP_RESOLUTION_S stResolution;
    HI_MPP_PIXEL_FORMAT_E enPixFormat;
} HI_VPORT_ATTR_S;

/** vproc cmd list*/
typedef enum hiVPROC_CMD_E
{
	HI_VPROC_CMD_SetPortMirror,
	HI_VPROC_CMD_GetPortMirror,
	HI_VPROC_CMD_SetPortFlip,
	HI_VPROC_CMD_GetPortFlip,
	HI_VPROC_CMD_SetPortRotate,
	HI_VPROC_CMD_GetPortRotate,
	HI_VPROC_CMD_BUTT
}HI_VPROC_CMD_E;


/** VPROC_CMD_SetPortMirror,VPROC_CMD_GetPortMirror*/
typedef struct hiVPROC_MIRROR_ATTR_S
{
	HI_BOOL bEnable;
}HI_VPROC_MIRROR_ATTR_S;

/** VPROC_CMD_SetPortFlip,VPROC_CMD_GetPortFlip*/
typedef struct hiVPROC_FLIP_ATTR_S
{
	HI_BOOL bEnable;
}HI_VPROC_FLIP_ATTR_S;

/** VPROC_CMD_SetPortRotate,VPROC_CMD_GetPortRotate*/
typedef enum hiMPP_ROTATE_E
{
    HI_ROTATE_NONE = 0,
    HI_ROTATE_90 = 1,
    HI_ROTATE_180 = 2,
    HI_ROTATE_270 = 3,
    HI_ROTATE_BUTT
} HI_MPP_ROTATE_E;

typedef enum hiPHOTO_PROC_TYPE_E
{
    PHOTO_PROC_TYPE_LL = 0,
    PHOTO_PROC_TYPE_HDR,
    PHOTO_PROC_TYPE_BUTT
} HI_PHOTO_PROC_TYPE_E;

typedef struct hiPHOTO_PROC_HDR_ATTR_S
{
    HI_S32 s32NrLuma;          /* noise reduction for luma,   [1, 10], 1=lowest level,10=highest filtering */
    HI_S32 s32NrChroma;        /* noise reduction for chroma  [0, 10], 0=off, 10=highest filtering */
    HI_S32 s32Sharpen;         /* Intelligent edge sharpening [0, 10], 0=off, 10 = largest sharpening */
    HI_S32 s32Saturation;      /* increase color saturation   [0, 10], 0=off, 10 = maximum */
    HI_S32 s32GlobalContrast;  /* global contrast enhancement strength [0, 10] */
    HI_S32 s32LocalContrast;   /* local contrast enhancement strength [0, 10] */

}HI_PHOTO_HDR_ATTR_S;

typedef struct hiPHOTO_PROC_LL_ATTR_S
{
    HI_S32 s32NrLuma;          /* noise reduction for luma,   [1, 10], 1=lowest level, 10=highest filtering*/
    HI_S32 s32NrChroma;        /* noise reduction for chroma  [0, 10], */
    HI_S32 s32Sharpen;         /* Intelligent edge sharpening [0, 10], 0=off, 10 = largest sharpening */
    HI_S32 s32Saturation;      /* increase color saturation   [0, 10], */
    HI_S32 s32Iso;
}HI_PHOTO_LL_ATTR_S;

typedef struct hiPHOTO_PROC_ATTR_S
{
    HI_PHOTO_PROC_TYPE_E enPhotoType;
    union
    {
        HI_PHOTO_HDR_ATTR_S  stHDRAttr;
        HI_PHOTO_LL_ATTR_S   stLLAttr;
    };
}HI_PHOTO_PROC_ATTR_S;


typedef HI_S32 (*PFN_VPROC_YUVDataProc)(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_FRAME_DATA_S* pVPortYUV);


/** @}*/  /** <!-- ==== VPROC End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_VPROC_DEFINE_H__ */
