/*****************************************************************************
*             Copyright 2004 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: aacdec.h
* Description:
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01      2006-11-01   z40717    NULL         Create this file.
*
*****************************************************************************/
/**
 * \file
 * \brief Describes the information about AACDEC. CNcomment:提供AACDEC的相关信息 CNend
 */

#ifndef _AACDEC_H
#define _AACDEC_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cpluscplus */
#endif  /* __cpluscplus */

#include "hi_type.h"


/********************************Macro Definition********************************/
/** \addtogroup      AACENC */
/** @{ */  /** <!-- 【AACENC】 */

#ifndef AAC_MAX_NCHANS
#define AAC_MAX_NCHANS      2
#endif
#define AAC_MAX_NSAMPS      1024
#define AAC_MAINBUF_SIZE    (768 * AAC_MAX_NCHANS)  /**<according to spec (13818-7 section 8.2.2, 14496-3 section 4.5.3),6144 bits =  768 bytes per SCE or CCE-I,12288 bits = 1536 bytes per CPE*/
/**<CNcomment: 输入数据长度，根据协议，SCE:768 bytes, CPE:1536*/

#define AAC_NUM_PROFILES    3
#define AAC_PROFILE_MP      0
#define AAC_PROFILE_LC      1
#define AAC_PROFILE_SSR     2

#ifndef HI_SUCCESS
#define HI_SUCCESS          0
#endif
/** @} */  /** <!-- ==== Macro Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      AACDEC */
/** @{ */  /** <!-- [AACDEC] */

/**Defines AACDEC error code*/
/**CNcomment:定义解码错误码*/
enum
{
    ERR_AAC_NONE                          =   0,        /**<no decode error*/ /**<CNcomment: 无解码错误 */
    ERR_AAC_INDATA_UNDERFLOW              =  -1,        /**<not enough input data*/ /**<CNcomment: 输入数据不够*/
    ERR_AAC_NULL_POINTER                  =  -2,        /**<null pointer*/ /**<CNcomment: 检测到非法的输入指针 */
    ERR_AAC_INVALID_ADTS_HEADER           =  -3,        /**<invalid adts header*/ /**<CNcomment: 检测输入码流的ADTS头信息非法 */
    ERR_AAC_INVALID_ADIF_HEADER           =  -4,        /**<invalid adif header*/ /**<CNcomment: 检测到输入码流的ADIF头信息非法 */
    ERR_AAC_INVALID_FRAME                 =  -5,        /**<invalid frame*/ /**<CNcomment: 检测到SetRawBlockParams输入AACDecInfo信息非法 */
    ERR_AAC_MPEG4_UNSUPPORTED             =  -6,        /**<upsupport mpeg4 format*/ /**<CNcomment: 检测到不支持的MPEG4 AAC码流格式 */
    ERR_AAC_CHANNEL_MAP                   =  -7,        /**<channel map error*/ /**<CNcomment: 检测到非法解码声道信息 */
    ERR_AAC_SYNTAX_ELEMENT                =  -8,        /**<element error*/ /**<CNcomment: 检测到输入码流包破损 */
    ERR_AAC_DEQUANT                       =  -9,        /**<dequant error*/ /**<CNcomment: 解码器反量化处理模块出错 */
    ERR_AAC_STEREO_PROCESS                = -10,        /**<stereo process error*/ /**<CNcomment: 解码器立体声处理模块模块出错 */
    ERR_AAC_PNS                           = -11,        /**<pns process error*/ /**<CNcomment: 解码器PNS处理模块模块出错 */
    ERR_AAC_SHORT_BLOCK_DEINT             = -12,        /**<reserved*/ /**<CNcomment: 保留扩展 */
    ERR_AAC_TNS                           = -13,        /**<TNS process error*/ /**<CNcomment: 解码器TNS处理模块模块出错 */
    ERR_AAC_IMDCT                         = -14,        /**<IMDCT process error*/ /**<CNcomment: 解码器IMDCT处理模块模块出错     */
    ERR_AAC_NCHANS_TOO_HIGH               = -15,        /**<unsupport mutil channel*/ /**<CNcomment: 不支撑多声道解码，最多支持两声道解码 */
    ERR_AAC_SBR_INIT                      = -16,        /**<SBR init error*/ /**<CNcomment: 解码器SBR处理模块初始化出错 */
    ERR_AAC_SBR_BITSTREAM                 = -17,        /**<SBR bitstream error*/ /**<CNcomment: 检测到SBR码流信息非法 */
    ERR_AAC_SBR_DATA                      = -18,        /**<SBR data error*/ /**<CNcomment: 解码后的SBR数据非法 */
    ERR_AAC_SBR_PCM_FORMAT                = -19,        /**<SBR pcm data error*/ /**<CNcomment: 解码后的SBR数据的PCM_FORMAT信息非法 */
    ERR_AAC_SBR_NCHANS_TOO_HIGH           = -20,        /**<unsupport SBR multi channel*/ /**<CNcomment: 不支撑SBR多声道解码，最多支持两声道解码 */
    ERR_AAC_SBR_SINGLERATE_UNSUPPORTED    = -21,        /**<SBR invalid samplerate*/ /**<CNcomment: SBR采样频率非法 */
    ERR_AAC_RAWBLOCK_PARAMS               = -22,        /**<invalid RawBlock params*/ /**<CNcomment: 检测到SetRawBlockParams输入参数非法 */
    ERR_AAC_PS_INIT                       = -23,        /**<PS init error*/ /**<CNcomment: 解码器PS处理模块初始化出错 */
    ERR_AAC_CH_MAPPING                    = -24,
    ERR_UNKNOWN               = -9999                   /**<reserved*/ /**<CNcomment: 保留扩展 */
};

typedef struct _AACFrameInfo
{
    int bitRate;
    int nChans;                      /**<channels,range:1,2*/ /**<CNcomment: 1 或 2 */
    int sampRateCore;                /**<inner sample rate*/ /**<CNcomment: 内核解码器采样率，码流信息，不作为输出控制使用 */
    int sampRateOut;                 /**<output samplerate*/ /**<CNcomment: 解码输出采样率 */
    int bitsPerSample;               /**<bitwidth ,range:16*/ /**<CNcomment: 16，目前仅支持16比特位宽输出 */
    int outputSamps;                 /**<output samples*/ /**<CNcomment: nChans*SamplePerFrame */
    int profile;                     /**<profile*/ /**<CNcomment: profile,   码流信息，不作为输出控制使用 */
    int tnsUsed;                     /**<tns tools*/ /**<CNcomment: TNS Tools，码流信息，不作为输出控制使用 */
    int pnsUsed;                     /**<pns tools*/ /**<CNcomment: PNS Tools，码流信息，不作为输出控制使用 */
} AACFrameInfo;

typedef enum
{
    AACDEC_ADTS = 0,
    AACDEC_LOAS = 1,
    AACDEC_LATM_MCP1 = 2,
} AACDECTransportType;
typedef void* HAACDecoder;

typedef struct hiAACDEC_VERSION_S
{
    HI_U8 aVersion[64];
} AACDEC_VERSION_S;


/** @} */  /** <!-- ==== Structure Definition End ==== */

/******************************* API declaration *****************************/
/** \addtogroup      AACDEC */
/** @{ */  /** <!--  【AACDEC】 */

/**
\brief Get version information. CNcomment:获取版本信息 CNend
\attention \n
N/A
\param[in] pVersion       version describe struct CNcomment:版本信息 CNend
\retval ::HI_SUCCESS   : Success       CNcomment:成功 CNend
\retval ::HI_FAILURE          : FAILURE.      CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_AACDEC_GetVersion(AACDEC_VERSION_S* pVersion);

/**
\brief create and initial decoder device. CNcomment:创建解码器 CNend
\attention \n
N/A
\param[in] enTranType    transport type CNcomment:传输格式 CNend
\retval ::HAACDecoder   : Success       CNcomment:成功，返回句柄 CNend
\retval ::HI_FAILURE          : FAILURE.      CNcomment:失败 CNend
\see \n
N/A
*/
HAACDecoder AACInitDecoder(AACDECTransportType enTranType);

/**
\brief destroy AAC-Decoder, free the memory.. CNcomment:销毁解码器 CNend
\attention \n
N/A
\param[in] hAACDecoder    AAC-Decoder handle CNcomment:句柄 CNend
\retval ::HAACDecoder   : Success       CNcomment:成功，返回句柄 CNend
\retval ::HI_FAILURE          : FAILURE.      CNcomment:失败 CNend
\see \n
N/A
*/
HI_VOID AACFreeDecoder(HAACDecoder hAACDecoder);

/**
\brief set RawMode before decode Raw Format aac bitstream. CNcomment:设置raw模式 CNend
\attention \n
N/A
\param[in] hAACDecoder   AAC-Decoder handle CNcomment:句柄 CNend
\param[in] nChans    inout channels CNcomment:输入声道数 CNend
\param[in] sampRate    input sampelrate CNcomment:输入采样率CNend
\retval ::HAACDecoder   : Success       CNcomment:成功，返回句柄 CNend
\retval ::ERROR_CODE          : FAILURE.      CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32  AACSetRawMode(HAACDecoder hAACDecoder, HI_S32 nChans, HI_S32 sampRate);

/**
\brief look for valid AAC sync header. CNcomment:找帧同步字 CNend
\attention \n
N/A
\param[in] hAACDecoder   AAC-Decoder handle CNcomment:句柄 CNend
\param[in] ppInbufPtr    address of the pointer of start-point of the bitstream CNcomment:输入数据缓存 CNend
\param[in] pBytesLeft    pointer to BytesLeft that indicates bitstream numbers at input buffer CNcomment:输入数据长度 CNend
\retval ::<0    : ERR_AAC_INDATA_UNDERFLOW     CNcomment:失败 CNend
\retval ::other : Success, return number bytes of current frame.      CNcomment:成功，返回帧长CNend
\see \n
N/A
*/
HI_S32 AACDecodeFindSyncHeader(HAACDecoder hAACDecoder, HI_U8** ppInbufPtr, HI_S32* pBytesLeft);

/**
\brief decoding AAC frame and output 1024(LC) OR 2048(HEAAC/eAAC/eAAC+) 16bit PCM samples per channel. CNcomment:AAC解码 CNend
\attention \n
\param[in] hAACDecoder    AAC-Decoder handle CNcomment:AAC句柄 CNend
\param[in] ppInbufPtr     address of the pointer of start-point of the bitstream CNcomment:输入数据小端模式首地址 CNend
\param[in] pBytesLeft     pointer to BytesLeft that indicates bitstream numbers at input buffer，indicates the left bytes CNcomment:输入数据剩余数据长度 CNend
\param[in] pOutPcm        the address of the out pcm buffer,pcm data in noninterlaced fotmat: L/L/L/... R/R/R/... CNcomment:输出数据小端模式首地址，非交织模式输出 CNend
\param[in] nReserved      reserved CNcomment:保留 CNend
\retval :: SUCCESS : Success CNcomment:成功 CNend
\retval :: ERROR_CODE :FAILURE CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32  AACDecodeFrame(HAACDecoder hAACDecoder, HI_U8** ppInbufPtr, HI_S32* pBytesLeft, HI_S16* pOutPcm);

/**
\brief get the frame information. CNcomment:获取解码后帧信息 CNend
\attention \n
\param[in] hAACDecoder    AAC-Decoder handle CNcomment:AAC句柄 CNend
\param[out] aacFrameInfo  frame information CNcomment:输出结构体信息 CNend
\retval \n
\see \n
N/A
*/
HI_VOID AACGetLastFrameInfo(HAACDecoder hAACDecoder, AACFrameInfo* aacFrameInfo);

/**
\brief set eosflag. CNcomment:设置结束标志 CNend
\attention \n
\param[in] hAACDecoder    AAC-Decoder handle CNcomment:AAC句柄 CNend
\param[out] s32Eosflag  end flag CNcomment:结束标志 CNend
\retval :: SUCCESS : Success CNcomment:成功 CNend
\retval :: ERROR_CODE :FAILURE CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 AACDecoderSetEosFlag(HAACDecoder hAACDecoder, HI_S32 s32Eosflag);

/**
\brief flush internal codec state (after seeking, for example). CNcomment:刷新解码器 CNend
\attention \n
\param[in] hAACDecoder    AAC-Decoder handle CNcomment:AAC句柄 CNend
\retval :: SUCCESS : Success CNcomment:成功 CNend
\retval :: ERROR_CODE :FAILURE CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32  AACFlushCodec(HAACDecoder hAACDecoder);

/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cpluscplus */
#endif  /* __cpluscplus */

#endif  /* _AACDEC_H */
