/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_adec_define.h
* @brief       vcap mapi struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.07.11
*/
#ifndef __HI_MAPI_ADEC_DEFINE_H__
#define __HI_MAPI_ADEC_DEFINE_H__

#define MODULE_NAME   "HI_MAPI_ADEC"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     ADEC */
/** @{ */  /** <!-- [ADEC] */

#define HI_MAPI_ERR_ADEC_NULL_PTR        HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NULL_PTR)
#define HI_MAPI_ERR_ADEC_NOTREADY        HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_SYS_NOTREADY)
#define HI_MAPI_ERR_ADEC_INVALID_DEVID   HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_DEVID)
#define HI_MAPI_ERR_ADEC_INVALID_CHNID   HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_INVALID_CHNID)
#define HI_MAPI_ERR_ADEC_EXIST           HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_EXIST)
#define HI_MAPI_ERR_ADEC_UNEXIST         HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_UNEXIST)
#define HI_MAPI_ERR_ADEC_NOT_SUPPORT     HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_SUPPORT)
#define HI_MAPI_ERR_ADEC_NOT_PERM        HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOT_PERM)
#define HI_MAPI_ERR_ADEC_NOMEM           HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOMEM)
#define HI_MAPI_ERR_ADEC_NOBUF           HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_NOBUF)
#define HI_MAPI_ERR_ADEC_ILLEGAL_PARAM   HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_ILLEGAL_PARAM)
#define HI_MAPI_ERR_ADEC_BUSY            HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUSY)
#define HI_MAPI_ERR_ADEC_BUF_EMPTY       HI_MPP_DEF_ERR(HI_MPP_MOD_ADEC, MPP_EN_ERR_LEVEL_ERROR, MPP_EN_ERR_BUF_EMPTY)

typedef struct hiMPP_ADEC_ATTR_S
{
    HI_MPP_AUDIO_FORMAT_E           enAdecFormat;          /*音频解码格式*/
    HI_MPP_AUDIO_BITRATE_E          enBitrate;             /*比特率*/
} HI_MPP_ADEC_ATTR_S;

/*音频解码数据 */
typedef struct hiMPP_ADEC_STREAM_S
{
    HI_U64           u64TimeStamp;   /* Time stamp                      */
    HI_U32           u32Len;         /* Encode data length              */
    HI_S16*          ps16Addr;       /* Encode data buffer address      */
    HI_U32           u32Seq;         /* frame seq */
} HI_MPP_ADEC_STREAM_S  ;

typedef struct hiMPP_ADEC_DECODER_S
{
    HI_MPP_AUDIO_FORMAT_E  enType;
    HI_CHAR         aszName[16];
    HI_S32          (*pfnOpenDecoder)(HI_VOID *pDecoderAttr, HI_VOID **ppDecoder); /*struct ppDecoder is packed by user,user malloc and free memory for this struct */
    HI_S32          (*pfnDecodeFrm)(HI_VOID *pDecoder, HI_U8 **pu8Inbuf,HI_S32 *ps32LeftByte,
                        HI_U16 *pu16Outbuf,HI_U32 *pu32OutLen,HI_U32 *pu32Chns);
    HI_S32          (*pfnGetFrmInfo)(HI_VOID *pDecoder, HI_VOID *pInfo);
    HI_S32          (*pfnCloseDecoder)(HI_VOID *pDecoder); 
    HI_S32          (*pfnResetDecoder)(HI_VOID *pDecoder);
} HI_MPP_ADEC_DECODER_S;

/** @}*/  /** <!-- ==== ADEC End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_MAPI_ADEC_DEFINE_H__ */
