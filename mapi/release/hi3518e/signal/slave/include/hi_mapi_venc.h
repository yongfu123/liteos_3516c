/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_mapi_venc.h
* @brief     ENC module header file
* @author    Hisilicon Hi35xx MPP Team
* @date      2016.06.29
*/
#ifndef __HI_MAPI_VENC_H__
#define __HI_MAPI_VENC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
#include "hi_mapi_venc_define.h"
/**
 * @brief create video ENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] pstVencAttr HI_MPP_VENC_ATTR_S: the attribute of VENC instance
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_Init(HI_HANDLE hVencHdl, const HI_MPP_VENC_ATTR_S *pstVencAttr);

/**
 * @brief destroy video ENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_DeInit(HI_HANDLE hVencHdl);

/**
 * @brief register call back for VENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] pstVencCB HI_VENC_CALLBACK_S: call back function of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_RegisterCallback(HI_HANDLE hVencHdl, HI_VENC_CALLBACK_S *pstVencCB);

/**
 * @brief unregister call back for VENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] pstVencCB HI_VENC_CALLBACK_S: call back function of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_UnRegisterCallback(HI_HANDLE hVencHdl, HI_VENC_CALLBACK_S *pstVencCB);

/**
 * @brief start video ENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] HI_S32 HI_MPP_VENC_ATTR_S: the frame count of VENC will to do; -1 :VENC Will not automatically stop
 * 			N( N > 0) :VENC will automatically stop after encode N frame data.
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_Start(HI_HANDLE hVencHdl, HI_S32 s32FrameCnt);

/**
 * @brief stop video ENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_Stop(HI_HANDLE hVencHdl);

/**
 * @brief VENC bind video video port
 * @param[in] hVProcHdl HI_HANDLE: handle of video processor
 * @param[in] hVPortHdl HI_HANDLE: handle of video port
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_Bind_VProc(HI_HANDLE hVProcHdl, HI_HANDLE hVPortHdl, HI_HANDLE hVencHdl);

/**
 * @brief VENC unbind video video port
 * @param[in] hVProcHdl HI_HANDLE: handle of video processor
 * @param[in] hVPortHdl HI_HANDLE: handle of video port
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_UnBind_VProc(HI_HANDLE hVProcHdl, HI_HANDLE hVPortHdl, HI_HANDLE hVencHdl);

/**
 * @brief set video ENC attribute
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] pstStreamAttr HI_MPP_VENC_ATTR_S: the attribute of VENC instance
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_SetAttr(HI_HANDLE hVencHdl, HI_MPP_VENC_ATTR_S *pstStreamAttr);

/**
 * @brief get video ENC attribute
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[out] pstStreamAttr HI_MPP_VENC_ATTR_S: the attribute of VENC instance
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_GetAttr(HI_HANDLE hVencHdl, HI_MPP_VENC_ATTR_S *pstStreamAttr);

/**
 * @brief request IDR frame
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_RequestIDR(HI_HANDLE hVencHdl);

/**
 * @brief get stream head information
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] enType HI_VENC_HEAD_INFO_TYPE_E: the type of head information
 * @param[out] pcHeadInfo HI_CHAR: the point of head information
 * @param[in/out] pu32HeadInfoLength HI_U32:length of pcHeadInfo
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_GetStreamHeadInfo(HI_HANDLE hVencHdl, HI_VENC_HEAD_INFO_TYPE_E enType,
             HI_CHAR *pcHeadInfo, HI_U32 *pu32HeadInfoLength);

/**
 * @brief set thumb nail attribute
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[in] pstThumbNailAttr HI_THUMBNAIL_ATTR_S: the attribute of thum nail
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_SetThumbNailAttr(HI_HANDLE hVencHdl,HI_THUMBNAIL_ATTR_S *pstThumbNailAttr);

/**
 * @brief create video ENC instance
 * @param[in] hVencHdl HI_HANDLE: handle of VENC
 * @param[out] pstThumbNailAttr HI_THUMBNAIL_ATTR_S: the attribute of thum nail
 * @return -1 indicate create failed
 * @return  0 indicate success
 */
HI_S32 HI_MAPI_VEnc_GetThumbNailAttr(HI_HANDLE hVencHdl,HI_THUMBNAIL_ATTR_S* pstThumbNailAttr);
/** @}*/  /** <!-- ==== ENC End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_VENC_H__ */
