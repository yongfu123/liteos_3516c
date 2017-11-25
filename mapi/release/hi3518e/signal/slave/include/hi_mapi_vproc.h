/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_vproc.h
* @brief       vproc mapi functions declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/
#ifndef __HI_MAPI_VPROC_H__
#define __HI_MAPI_VPROC_H__

#include "hi_mapi_vproc_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     HI_MAPI_VCPROC */
/** @{ */  /** <!-- [HI_MAPI_VCPROC] */

/**
 * @brief Init vproc.
 * @param[in] VProcHdl HI_HANDLE: handle of vproc. It's integer from 0 to 31.
 * @param[in] pstVprocAttr HI_VPROC_ATTR_S: pointer of vproc attribute.Static attribute.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Init(HI_HANDLE VProcHdl, HI_VPROC_ATTR_S* pstVprocAttr);

/**
 * @brief Deinit vproc. It must be init first.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_DeInit(HI_HANDLE VProcHdl);

/**
 * @brief Start vproc. It must be created first.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Start(HI_HANDLE VProcHdl);

/**
 * @brief Stop vproc. It must be created first.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Stop(HI_HANDLE VProcHdl);

/**
 * @brief Bind vcap to vproc.
 * @param[in] VCapHdl HI_HANDLE : handle of vcap.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Bind_VCap(HI_HANDLE VCapHdl, HI_HANDLE VProcHdl);

/**
 * @brief Unbind vcap from vproc.
 * @param[in] VCapHdl HI_HANDLE : handle of vcap.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_UnBind_VCap(HI_HANDLE VCapHdl, HI_HANDLE VProcHdl);

/**
 * @brief Set attribute of a port in vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. It's integer from 0 to 3.
 * @param[in] pstVPortAttr HI_VPORT_ATTR_S: pointer of vport attribute. Dynamic attribute.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Port_SetAttr(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_VPORT_ATTR_S *pstVPortAttr);

/**
 * @brief Get attribute of a port in vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @param[out] pstVPortAttr HI_VPORT_ATTR_S: pointer of vport attribute. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Port_GetAttr(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_VPORT_ATTR_S *pstVPortAttr);

/**
 * @brief Start a port in vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Port_Start(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl);

/**
 * @brief Stop a port in vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_Port_Stop(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl);

/**
 * @brief Set corresponding attributes of a vproc,including mirror, flip, rotate etc.
 * @param[in] VProcHdl HI_HANDLE :handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @param[in] enCMD HI_VPROC_CMD_E : Setting command.
 * @param[in] pAttr HI_VOID:The struct of corresponding attributes.Dynamic attribute.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_SetAttrEx(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_VPROC_CMD_E enCMD, HI_VOID* pAttr);

/**
 * @brief Get corresponding attributes of a vproc,including mirror, flip, rotate etc.
 * @param[in] VProcHdl HI_HANDLE :handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @param[in] enCMD HI_VPROC_CMD_E : Getting command.
 * @param[out] pAttr HI_VOID:The struct of corresponding attributes.
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_GetAttrEx(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_VPROC_CMD_E enCMD, HI_VOID* pAttr);

/**
 * @brief Set attributes of photo process, include HDR, lowlight.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @param[in] pstSnapAttr HI_PHOTO_PROC_ATTR_S: pointer of photo process attribute. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_SetPhotoAttr(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_PHOTO_PROC_ATTR_S* pstSnapAttr);

/**
 * @brief Get attributes of photo process, include HDR, lowlight.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @param[out] pstSnapAttr HI_PHOTO_PROC_ATTR_S: pointer of photo process attribute. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_GetPhotoAttr(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_PHOTO_PROC_ATTR_S* pstSnapAttr);

/**
 * @brief Do photo process. It should be called before HI_MAPI_VCap_Trigger and after HI_MAPI_VProc_SetPhotoAttr,
 *        only if you need process HDR or lowlight photo.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_PhotoProcess(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl);

/**
 * @brief enable dump YUV data form port of vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_EnableDumpYUV(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl);

/**
 * @brief disable dump YUV data form port of vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_DisableDumpYUV(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl);

/**
 * @brief disable dump YUV data form port of vproc.
 * @param[in] VProcHdl HI_HANDLE : handle of vproc.
 * @param[in] VPortHdl HI_HANDLE : handle of port. 
 * @param[out] pfunVProcYUVProc PFN_VPROC_YUVDataProc : The pointer of callback function of dump YUV data. 
 * @return 0  successful.
 * @return non 0  fail.
 */
HI_S32 HI_MAPI_VProc_DumpYUV(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, PFN_VPROC_YUVDataProc pfunVProcYUVProc);

/** @}*/  /** <!-- ==== HI_MAPI_VPROC End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_VPROC_H__ */
