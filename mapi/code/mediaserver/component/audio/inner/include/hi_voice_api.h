#ifndef __HI_VOICE_ENGINE_H__
#define __HI_VOICE_ENGINE_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"

/********************************Macro Definition********************************/
/** \addtogroup      VOICE */
/** @{ */  /** <!-- 【VOICE】 */

/********************************************************************************
|                                                                               |
|	   HISI VOCIE FRAME Description                                             | 
|	                                                                            |
|	   Paramater 	    bit        Description                                  |
|	   HI_S16 0         15:8       Frame Flag                                   |
|	                               01B  :  normal voice frame                   |
|	                               other:  invalid                              |
|	   HI_S16 0         07:0       reseverd                                     |
|	                                                                            |
|	   HI_S16 1         15:8       Frame Counter                                |
|	                               00 ~ 255                                     |
|	   HI_S16 1         07:0       Raw Frame Data Length(HI_S16)                |
|	                                                                            |
|	   HI_S16 2         15:0       Raw data 0                                   |
|      HI_S16 3         15:0       Raw data 1                                   |
|	     .                                                                      |
|		 .                                                                      |
|		 .                                                                      |
|       HI_S16 2+n       15:0       Raw data n   n==Raw Frame Data Length       |
|                                                                               |
|                                                                               |
********************************************************************************/


#ifndef HI_RESULT
   #define  HI_RESULT int
#endif

#ifndef NULL
   #define NULL   (HI_S32)0x0L
#endif

#ifndef HI_VOICE_API
#ifdef WIN32
	#define HI_VOICE_API     __declspec(dllexport)
#else
	#define HI_VOICE_API
#endif	
#endif

#define HI_VOICE_MAX_FRAME_SIZE       (481)    /**<max decode/encode frame size, 60ms at 8k samperate or 10ms at 48k samplerate*/ /**<CNcomment: voice 最大帧长*/
#define HI_VOICE_ADPCM_MAX_FRAME_SIZE       (1020)    /**<ADPCM max decode/encode frame size, 60ms at 8k samperate or 10ms at 48k samplerate*/ /**<CNcomment: ADPCM 最大帧长*/

#define G711_A                        0x01  /**<64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */ /**<CNcomment: G711 A格式*/
#define G711_U                        0x02  /**<64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */ /**<CNcomment: G711 U格式*/
#define ADPCM_DVI4                    0x03  /**<32kbps ADPCM(DVI4) for RTP; see DVI4 diiffers in three respects from the IMA ADPCM at RFC3551.txt 4.5.1 DVI4 */
											/**<CNcomment: RTP ADPCM DVI4格式*/
#define G726_16KBPS                   0x04  /**<16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */ /**<CNcomment: G726 16kbps格式*/
#define G726_24KBPS                   0x05  /**<24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */ /**<CNcomment: G726 24kbps格式*/
#define G726_32KBPS                   0x06  /**<32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */ /**<CNcomment: G726 32kbps格式*/
#define G726_40KBPS                   0x07  /**<40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */ /**<CNcomment: G726 40kbps格式*/

#define ADPCM_IMA                     0x23  /**<32kbps ADPCM(IMA) */ /**<CNcomment: 32kbps ADPCM IMA格式*/

/**
An example of the packing scheme for G726-32 codewords is as shown, and bit A3 is the least significant bit of the first codeword: 
RTP G726-32:
0                   1
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
|B B B B|A A A A|D D D D|C C C C| ...
|0 1 2 3|0 1 2 3|0 1 2 3|0 1 2 3|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

MEDIA G726-32:
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
|A A A A|B B B B|C C C C|D D D D| ...
|3 2 1 0|3 2 1 0|3 2 1 0|3 2 1 0|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
*/
#define MEDIA_G726_16KBPS             0x24  /**<media G726 16kbps for ASF ... */ /**<CNcomment: 媒体G726 16kbps格式*/
#define MEDIA_G726_24KBPS             0x25  /**<media G726 24kbps for ASF ... */ /**<CNcomment: 媒体G726 24kbps格式*/
#define MEDIA_G726_32KBPS             0x26  /**<media G726 32kbps for ASF ... */ /**<CNcomment: 媒体G726 32kbps格式*/
#define MEDIA_G726_40KBPS             0x27  /**<media G726 40kbps for ASF ... */ /**<CNcomment: 媒体G726 40kbps格式*/


/* ORIGINE VERSION CODEC */
#define G711_ORG_A                    0x41  /**<original version 64kbps G.711 A */ /**<CNcomment: 原始G711 A格式*/
#define G711_ORG_U                    0x42  /**<original version 64kbps G.711 U */ /**<CNcomment: 原始G711 U格式*/
#define ADPCM_ORG_DVI4                0x43  /**<original version 32kbps ADPCM */ /**<CNcomment: 原始ADPCM DVI4格式*/
#define G726_ORG_16KBPS               0x44  /**<original version(DVS1.0) 16kbps G.726 */ /**<CNcomment: 原始G726 16kbps格式*/


/* TRANSFORM CODE */
#define ORG_G711A_TRANSF2_G711A               0x61  /**<transform original version 64kbps G.711 A to G711_A*/ /**<CNcomment: 传输模式下G711 A格式*/
#define ORG_G711U_TRANSF2_G711U               0x62  /**<transform original version 64kbps G.711 U to G711_U*/ /**<CNcomment: 传世格式下G711 U格式*/
#define ORG_ADPCM_DVI4_TRANSF2_ADPCM_DVI4     0x63  /**<transform original version 32kbps ADPCM to ADPCM_DVI4*/ /**<CNcomment: 传输模式下ADPCM DVI4格式*/
#define ORG_G726_16KBPS_TRANSF2_G726_16KBPS   0x64  /**<transform original version(DVS1.0) 16kbps G.726 to G726_16KBPS*/ /**<CNcomment: 传输模式G726 16kbps格式*/


#define HI_NORMAL_FRAME               0x01 /**<Normal frame flag */ /**<CNcomment: 正常帧标识*/


#define HI_SUCCESS                    0

#define HI_ERR_VOICE_PREFIX           0xA1220000

#define HI_ERR_VOICE_ENC_TYPE         (HI_ERR_VOICE_PREFIX | 0x0001)
#define HI_ERR_VOICE_ENC_FRAMESIZE    (HI_ERR_VOICE_PREFIX | 0x0002)

#define HI_ERR_VOICE_DEC_TYPE         (HI_ERR_VOICE_PREFIX | 0x0011)
#define HI_ERR_VOICE_DEC_FRAMESIZE    (HI_ERR_VOICE_PREFIX | 0x0012)
#define HI_ERR_VOICE_DEC_FRAMETYPE    (HI_ERR_VOICE_PREFIX | 0x0013)


#define HI_ERR_VOICE_INVALID_DEVICE   (HI_ERR_VOICE_PREFIX | 0x0101)
#define HI_ERR_VOICE_INVALID_INBUF    (HI_ERR_VOICE_PREFIX | 0x0102)
#define HI_ERR_VOICE_INVALID_OUTBUF   (HI_ERR_VOICE_PREFIX | 0x0103)

#define HI_ERR_VOICE_TRANS_DEVICE     (HI_ERR_VOICE_PREFIX | 0x1001)
#define HI_ERR_VOICE_TRANS_TYPE       (HI_ERR_VOICE_PREFIX | 0x1002)

/** @} */  /** <!-- ==== Macro Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      HIVQE */
/** @{ */  /** <!-- [HIVQE] */

/**Defines State for G711 encoder and decoder*/
/**CNcomment:定义G711参数*/
typedef struct hiVOICE_G711_STATE{
    HI_S32 G711StateBuf[2];
} hiVOICE_G711_STATE_S;

/**State for ADPCM encoder and decoder */
/**CNcomment:定义ADPCM参数*/
typedef struct hiVOICE_ADPCM_STATE{
    HI_S32 AdpcmStateBuf[4];
} hiVOICE_ADPCM_STATE_S;

/**State for G726 encoder and decoder */
/**CNcomment:定义G726参数*/
typedef struct hiVOICE_G726_STATE
{
    HI_S32 G726StateBuf[32];
} hiVOICE_G726_STATE_S;

/**State for TransCode */
/**CNcomment:定义Transcode参数*/
typedef struct hiVOICE_TRANSCODE_STATE
{
    HI_S32 TransStateBuf[0x400];
} hiVOICE_TRANSCODE_STATE_S;

/**Defines AMRENC version*/
/**CNcomment:定义版本信息*/
typedef struct hiVOICE_VERSION_S
{
    HI_S8 aVersion[64];
}VOICE_VERSION_S;

/** @} */  /** <!-- ==== Structure Definition End ==== */

/******************************* API declaration *****************************/
/** \addtogroup      VOICE */
/** @{ */  /** <!--  【VOICE】 */

/**
\brief get version. CNcomment:获取版本信息 CNend
\attention \n
N/A
\param[in] pVersion    version describe struct CNcomment:版本信息结构体 CNend
\retval ::HI_SUCCESS    : Success       CNcomment:成功 CNend
\retval ::HI_FAILURE    : FAILURE.      CNcomment:失败 CNend
\see \n
N/A
*/
HI_VOICE_API HI_S32 HI_VOICE_GetVersion(VOICE_VERSION_S *pVersion);

/**
\brief create and initial encoder device. CNcomment:初始化编码器 CNend
\attention \n
N/A
\param[in] pEncState    encoder device handle CNcomment:句柄 CNend
\param[in] nCoder    encoder typeption   CNcomment:编码类型 CNend
\retval ::HI_SUCCESS   : Success       CNcomment:成功，返回句柄 CNend
\retval ::HI_ERR_VOICE_INVALID_DEVICE          :invalid encoder device handle.      CNcomment:失败 CNend
\retval ::HI_ERR_VOICE_ENC_TYPE          :invalid encoder typeption .      CNcomment:失败 CNend
\see \n
N/A
*/ 
HI_VOICE_API HI_RESULT  HI_VOICE_EncReset(HI_VOID *pEncState, HI_S16 nCoder);

/**
\brief create and initial decoder device. CNcomment:初始化解码器 CNend
\attention \n
N/A
\param[in] pDecState    decoder device handle CNcomment:句柄 CNend
\param[in] nCoder    decoder typeption   CNcomment:解码类型 CNend
\retval ::HI_SUCCESS   : Success       CNcomment:成功，返回句柄 CNend
\retval ::HI_ERR_VOICE_INVALID_DEVICE          :invalid encoder device handle.      CNcomment:失败 CNend
\retval ::HI_ERR_VOICE_DEC_TYPE          :invalid decoder typeption .      CNcomment:失败 CNend
\see \n
N/A
*/ 
HI_VOICE_API HI_RESULT  HI_VOICE_DecReset(HI_VOID *pDecState, HI_S16 nCoder);

/**
\brief create and initial encoder device. CNcomment:初始化编码器 CNend
\attention \n
N/A
\param[in] pEncState    decoder device handle CNcomment:句柄 CNend
\param[in] pInputBuf     input speech data addr CNcomment:输入数据小端模式首地址 CNend
\param[in] pOutputBuf    output addr of compressed speech data buffer CNcomment:输出数据缓存 CNend
\param[in] len    nput speech data count(unit: HI_S16)   CNcomment:输入数据长度，ADPCM为10ms整数倍 + 1,其他为10ms整数倍 CNend
\retval :: HI_SUCCESS : Success CNcomment:成功 CNend
\retval :: HI_ERR_VOICE_INVALID_DEVICE :invalid decoder device handle CNcomment:非法设备 CNend
\retval :: HI_ERR_VOICE_INVALID_INBUF :invalid input serial data addr CNcomment:非法输入缓存CNend
\retval :: HI_ERR_VOICE_INVALID_OUTBUF :invalid output addr CNcomment:非法输出缓存 CNend
\retval :: HI_ERR_VOICE_ENC_FRAMESIZE :invalid encoder FrameSize  CNcomment:无效帧长 CNend
\retval :: HI_ERR_VOICE_ENC_TYPE :invalid encoder typeption  CNcomment:编码错误 CNend
\see \n
N/A
*/ 
HI_VOICE_API HI_RESULT  HI_VOICE_EncodeFrame(HI_VOID *pEncState, HI_S16 *pInputBuf, HI_S16 *pOutputBuf, HI_S16 len);

/**
\brief create and initial decoder device. CNcomment:初始化解码器 CNend
\attention \n
N/A
\param[in] pDecState    decoder device handle CNcomment:句柄 CNend
\param[in] pInputBuf     input speech data addr CNcomment:输入数据小端模式首地址 CNend
\param[in] pOutputBuf    output addr of compressed speech data buffer CNcomment:输出数据缓存 CNend
\param[in] pLen    output speech data count(unit: HI_S16)   CNcomment:输出数据长度 CNend
\retval :: HI_SUCCESS : Success CNcomment:成功 CNend
\retval :: HI_ERR_VOICE_INVALID_DEVICE :invalid decoder device handle CNcomment:非法设备 CNend
\retval :: HI_ERR_VOICE_INVALID_INBUF :invalid input serial data addr CNcomment:非法输入缓存CNend
\retval :: HI_ERR_VOICE_INVALID_OUTBUF :invalid output addr CNcomment:非法输出缓存 CNend
\retval :: HI_ERR_VOICE_ENC_FRAMESIZE :invalid encoder FrameSize  CNcomment:无效帧长 CNend
\retval :: HI_ERR_VOICE_DEC_FRAMETYPE :invalid frame of compress speech data  CNcomment:输入码流错误 CNend
\see \n
N/A
*/ 
HI_VOICE_API HI_RESULT  HI_VOICE_DecodeFrame(HI_VOID *pDecState, HI_S16 *pInputBuf,  HI_S16 *pOutputBuf, HI_S16 *pLen);

/**
\brief create and initial transcode device. CNcomment:初始化转码器 CNend
\attention \n
N/A
\param[in] pTransState    transform device handle CNcomment:句柄 CNend
\param[in] nCoder   transform typeption  CNcomment:传输类型 CNend
\retval :: HI_SUCCESS : Success CNcomment:成功 CNend
\retval :: HI_ERR_VOICE_TRANS_DEVICE :invalid decoder device handle CNcomment:非法设备 CNend
\retval :: HI_ERR_VOICE_TRANS_TYPE :invalid transform type  CNcomment:非法传输类型 CNend
\see \n
N/A
*/ 
HI_VOICE_API HI_RESULT  HI_VOICE_TransCodeReset(HI_VOID *pTransState, HI_S16 nCoder);

/**
\brief transform frame. CNcomment:转码 CNend
\attention \n
N/A
\param[in] pTransState    transform device handle CNcomment:句柄 CNend
\param[in] pInputBuf   input addr of origion frame compress speech data buffer  CNcomment:输入数据缓存 CNend
\retval :: HI_SUCCESS : Success CNcomment:成功 CNend
\retval :: HI_ERR_VOICE_TRANS_DEVICE :invalid decoder device handle CNcomment:非法设备 CNend
 \retval :: HI_ERR_VOICE_INVALID_INBUF :invalid input addr of one frame compress speech data buffer  CNcomment:非法输入数据 CNend
\retval :: HI_ERR_VOICE_TRANS_TYPE :invalid transform type  CNcomment:非法传输类型 CNend
\see \n
N/A
*/ 
HI_VOICE_API HI_RESULT  HI_VOICE_TransCodeFrame(HI_VOID *pTransState,HI_S16 *pInputBuf);

/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif 
