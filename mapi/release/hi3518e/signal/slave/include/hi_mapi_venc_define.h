/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_venc_define.h
* @brief     ENC module header file
* @author    Hisilicon Hi35xx MPP Team
* @date      2016.06.29
*/
#ifndef __HI_VENC_DEFINE_H__
#define __HI_VENC_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_mapi_comm_define.h"


/** @addtogroup     ENC */
/** @{ */  /** <!-- [ENC] */

/** max channel count of video encoder*/
#define HI_VENC_MAX_CHN_NUM   16

/** pack number of video encoder*/
#define HI_VENC_PACK_NUM     2

/** max pack count of video encoder frame*/
#define HI_VENC_MAX_FRAME_PACKCOUNT  6

/** limitless count of video encoder frame*/
#define HI_VENC_LIMITLESS_FRAME_COUNT -1

/** max count of VENC channel register call backs*/
#define VENC_CHN_REGISTER_CALLBACK_MAX_COUNT  5

/** max length of VENC head information*/
#define MEDIA_VENC_HEAD_INFO_BUFF_LEN 128

/** the param of video encoder*/
typedef struct hiMPP_VENC_PARAM_REF_S
{
    HI_U32 u32Base;             /**< (0£¬+¡Þ)*/
    HI_U32 u32Enhance;          /**< [0, 255]*/
    HI_BOOL bEnablePred;
} HI_MPP_VENC_PARAM_REF_S;

/** the attribute of H264 video encoder*/
typedef struct hiMPP_VENC_ATTR_H264_S
{
    HI_U32  u32Profile;                      /**< 0: baseline; 1:MP; 2:HP; 3: SVC-T [0,3]; */
    HI_MPP_VENC_PARAM_REF_S stParamRef;
} HI_MPP_VENC_ATTR_H264_S;

/** the attribute of H265 video encoder*/
typedef struct hiMPP_VENC_ATTR_H265_S
{
    HI_U32  u32Profile;                     /**< 0: MP */
    HI_MPP_VENC_PARAM_REF_S stParamRef;
} HI_MPP_VENC_ATTR_H265_S;

/** the attribute of JPEG encoder*/
typedef struct hiMPP_VENC_ATTR_JPEG_S
{
    HI_U32 u32Qfactor;
} HI_MPP_VENC_ATTR_JPEG_S;

/** the attribute of encoder type*/
typedef struct hiMPP_VENC_TYPE_ATTR_S
{
    HI_MPP_PAYLOAD_TYPE_E  enType;
    HI_MPP_RESOLUTION_S stResolution;
    HI_U32 u32BufSize;
    union
    {
        HI_MPP_VENC_ATTR_H264_S  stAttrH264e;
        HI_MPP_VENC_ATTR_H265_S  stAttrH265e;
        HI_MPP_VENC_ATTR_JPEG_S  stAttrJpege;
    };

} HI_VENC_TYPE_ATTR_S;

/** the rate control mode*/
typedef enum hiMPP_VENC_RC_MODE_E
{
    HI_MPP_VENC_RC_MODE_CBR,    /**< constant bit rate*/
    HI_MPP_VENC_RC_MODE_VBR,    /**< variable bit rate*/
    HI_MPP_VENC_RC_MODE_BUTT,
} HI_MPP_VENC_RC_MODE_E;

/** the attribute of constant bit rate*/
typedef struct hiMPP_VENC_ATTR_CBR_S
{
    HI_U32    u32Gop;             /**< I frame interval*/
    HI_U32    u32BitRate;         /**< encode bit rate, with Kbps as a unit*/
} HI_MPP_VENC_ATTR_CBR_S;

/** the attribute of variable bit rate*/
typedef struct hiMPP_VENC_ATTR_VBR_S
{
    HI_U32    u32Gop;             /**< I frame interval*/
    HI_U32    u32MaxBitRate;      /**< encode max bit rate, with Kbps as a unit*/
} HI_MPP_VENC_ATTR_VBR_S;

/** the attribute of rate control*/
typedef struct hiMPP_VENC_RC_ATTR_S
{
    HI_MPP_VENC_RC_MODE_E enRcMode;
    union
    {
        HI_MPP_VENC_ATTR_CBR_S    stAttrCbr;
        HI_MPP_VENC_ATTR_VBR_S    stAttrVbr;
    };
} HI_MPP_VENC_RC_ATTR_S;

/** the attribute of video encode*/
typedef struct hiMPP_VENC_ATTR_S
{
    HI_VENC_TYPE_ATTR_S 	stVencPloadTypeAttr;
    HI_MPP_VENC_RC_ATTR_S  stRcAttr;
} HI_MPP_VENC_ATTR_S;

/** the NALU type of H264 encode*/
typedef enum hiVENC_DATA_H264E_NALU_TYPE_E
{
    HI_ENC_H264E_NALU_BSLICE = 0,         /**<BSLICE types*/
    HI_ENC_H264E_NALU_PSLICE = 1,         /**<PSLICE types*/
#if (HIARCH==hi3518e)
    HI_ENC_H264E_NALU_ISLICE = 5,         /**<ISLICE types*/
#else
	HI_ENC_H264E_NALU_ISLICE = 2,		  /**<ISLICE types*/
	HI_ENC_H264E_NALU_IDRSLICE = 5, 	  /**<IDRSLICE types*/
#endif
    HI_ENC_H264E_NALU_SEI    = 6,         /**<SEI types*/
    HI_ENC_H264E_NALU_SPS    = 7,         /**<SPS types*/
    HI_ENC_H264E_NALU_PPS    = 8,         /**<PPS types*/
    HI_ENC_H264E_NALU_BUTT
} HI_VENC_DATA_H264E_NALU_TYPE_E;

/** the NALU type of H265 encode*/
typedef enum hiVENC_H265E_NALU_TYPE_E
{
    HI_ENC_H265E_NALU_BSLICE = 0,          /**<B SLICE types*/
    HI_ENC_H265E_NALU_PSLICE = 1,          /**<P SLICE types*/
#if (HIARCH==hi3518e)
	HI_ENC_H265E_NALU_ISLICE = 19,		  /**<ISLICE types*/
#else
	HI_ENC_H265E_NALU_ISLICE = 2,		  /**<ISLICE types*/
	HI_ENC_H265E_NALU_IDRSLICE = 19, 	  /**<IDRSLICE types*/
#endif
    HI_ENC_H265E_NALU_VPS    = 32,         /**<VPS types*/
    HI_ENC_H265E_NALU_SPS    = 33,         /**<SPS types*/
    HI_ENC_H265E_NALU_PPS    = 34,         /**<PPS types*/
    HI_ENC_H265E_NALU_SEI    = 39,         /**<SEI types*/
    HI_ENC_H265E_NALU_BUTT
} HI_VENC_DATA_H265E_NALU_TYPE_E;

/** the pack type of JPEG encode*/
typedef enum hiVENC_DATA_JPEG_PACK_TYPE_E
{
    HI_VENC_JPEGE_PACK_ECS = 5,
    HI_VENC_JPEGE_PACK_APP = 6,
    HI_VENC_JPEGE_PACK_VDO = 7,
    HI_VENC_JPEGE_PACK_PIC = 8,
    HI_VENC_JPEGE_PACK_BUTT
}HI_VENC_DATA_JPEGE_PACK_TYPE_E;

/** the pack type of MJPEG4 encode*/
typedef enum hiVENC_DATA_MPEG4E_PACK_TYPE_E
{
    HI_VENC_DATA_MPEG4E_PACK_VOP_P = 1,
    HI_VENC_DATA_MPEG4E_PACK_VOP_I = 5,
    HI_VENC_DATA_MPEG4E_PACK_VOS = 6,
    HI_VENC_DATA_MPEG4E_PACK_VO = 7,
    HI_VENC_DATA_MPEG4E_PACK_VOL = 8,
    HI_VENC_DATA_MPEG4E_PACK_GVOP = 9,
    HI_VENC_DATA_MPEG4E_PACK_BUTT
} HI_VENC_DATA_MPEG4E_PACK_TYPE_E;

/** the slice type*/
typedef enum hiREFSLICE_TYPE_E
{
    HI_REFSLICE_FOR_1X = 1,
    HI_REFSLICE_FOR_2X = 2,
    HI_REFSLICE_FOR_4X = 5,
    HI_REFSLICE_FOR_BUTT
} HI_REFSLICE_TYPE_E;

typedef enum hiREF_TYPE_E
{
    HI_BASE_IDRSLICE = 0,             /**<the Idr frame at Base layer*/
    HI_BASE_PSLICE_REFTOIDR,          /**<the P frame at Base layer, referenced by other frames at Base layer and reference to Idr frame */
    HI_BASE_PSLICE_REFBYBASE,         /**<the P frame at Base layer, referenced by other frames at Base layer*/
    HI_BASE_PSLICE_REFBYENHANCE,      /**<the P frame at Base layer, referenced by other frames at Enhance layer*/
    HI_ENHANCE_PSLICE_REFBYENHANCE,   /**<the P frame at Enhance layer, referenced by other frames at Enhance layer*/
    HI_ENHANCE_PSLICE_NOTFORREF,      /**<the P frame at Enhance layer ,not referenced*/
    HI_ENHANCE_PSLICE_BUTT
} HI_REF_TYPE_E;

/** the data type of video encode*/
typedef struct hiHI_VENC_DATA_TYPE_S
{
    HI_MPP_PAYLOAD_TYPE_E enPayloadType;                    /**< H.264/H.265/JPEG/MJPEG*/
    union
    {
        HI_VENC_DATA_H264E_NALU_TYPE_E    enH264EType;      /**<H264E NALU types*/
        HI_VENC_DATA_H265E_NALU_TYPE_E    enH265EType;      /**<H265E NALU types*/
        HI_VENC_DATA_JPEGE_PACK_TYPE_E    enJPEGEType;      /**<JPEGE PACK types*/
        HI_VENC_DATA_MPEG4E_PACK_TYPE_E enMPEG4EType;       /**<MJPEGE PACK types*/
    };

} HI_VENC_DATA_TYPE_S;

/** the data pack of video encode*/
typedef struct hiVENC_DATA_PACK_S
{
    HI_U32           u32PhyAddr[HI_VENC_PACK_NUM];      /*the physics address of stream*/
    HI_U8             *pu8Addr[HI_VENC_PACK_NUM];       /*the virtual address of stream*/
    HI_U32            au32Len[HI_VENC_PACK_NUM];
    HI_U64            u64PTS;
    HI_VENC_DATA_TYPE_S  stDataType;
    HI_U32   u32Offset;
} HI_VENC_DATA_PACK_S;

/** the stream information of video encode*/
typedef struct hiVENC_STREAM_INFO_S
{
    HI_REFSLICE_TYPE_E enRefSliceType;
    HI_REF_TYPE_E enRefType;
    HI_U32 u32StartQp;
}HI_VENC_STREAM_INFO_S;

/** the data of video encode*/
typedef struct hiVENC_DATA_S
{
    HI_VENC_DATA_PACK_S  astPack[HI_VENC_MAX_FRAME_PACKCOUNT];  /**<stream pack attribute*/
    HI_U32            u32PackCount;                             /**<the pack number of one frame stream*/
    HI_U32            u32Seq;                                   /**<the list number of stream*/
    HI_BOOL    	    bEndOfStream;
    HI_VENC_STREAM_INFO_S stStreamInfo;
} HI_VENC_DATA_S;

typedef HI_S32 (*PFN_VENC_DataProc)(HI_HANDLE VencHdl, HI_VENC_DATA_S* pVStreamData, HI_VOID *pPrivateData);

typedef struct hiVENC_CALLBACK_S
{
    PFN_VENC_DataProc pfnDataCB;
    HI_VOID *pPrivateData;
} HI_VENC_CALLBACK_S;

/** the head information type of video encode*/
typedef enum hiVENC_HEAD_INFO_TYPE_E
{
    HI_VENC_HEAD_INFO_TYPE_VPS,                         /**<VPS types*/
    HI_VENC_HEAD_INFO_TYPE_PPS,                         /**<PPS types*/
    HI_VENC_HEAD_INFO_TYPE_SPS,                         /**<SPS types*/
    HI_VENC_HEAD_INFO_TYPE_BUTT
} HI_VENC_HEAD_INFO_TYPE_E;

/** the attribute of snap thumb nail*/
typedef struct hiSNAP_THUMBNAIL_ATTR_S
{
    HI_BOOL bEnable;
}HI_SNAP_THUMBNAIL_ATTR_S;

/** the attribute of snap screen nail*/
typedef struct hiSNAP_SCREENNAIL_ATTR_S
{
    HI_BOOL bEnable;
    HI_MPP_RESOLUTION_S astThumbNailSize;
}HI_SNAP_SCREENNAIL_ATTR_S;

/** the attribute of thumb nail*/
typedef struct hiTHUMBNAIL_ATTR_S
{
    HI_SNAP_THUMBNAIL_ATTR_S stThumbNail;
    HI_SNAP_SCREENNAIL_ATTR_S stScreenNail;
}HI_THUMBNAIL_ATTR_S;

/** @}*/  /** <!-- ==== ENC End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_VENC_DEFINE_H__ */
