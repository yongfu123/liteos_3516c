/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_vcap.h
* @brief       vcap mapi functions declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/
#ifndef __HI_MAPI_VCAP_H__
#define __HI_MAPI_VCAP_H__

#define MODULE_NAME   "HI_MAPI_VCAP"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_mapi_vcap_define.h"

/** \addtogroup     VCAP */
/** @{ */  /** <!-- [VCAP] */

/**
 * @brief Set sensor mode.
 *        Sensor mode must be choose from all modes of a sensor.
 *        Sensors and their modes are defined by configure file,a configure template will be available.
 * @param[in] SensorHdl HI_HANDLE:handle of sensor.In hi3559,a sensor be supported.
 * @param[in] pstSensorMode HI_MPP_SENSOR_ATTR_S*: pointer of sensor mode.
 * @return 0  Set sensor mode successful.
 * @return non 0  Set sensor mode fail.
 */
HI_S32 HI_MAPI_Sensor_SetAttr(HI_HANDLE SensorHdl, HI_MPP_SENSOR_ATTR_S* pstSensorMode);

/**
 * @brief Get the current mode of a sensor.
 * @param[in] SensorHdl HI_HANDLE:handle of sensor.In hi3559,a sensor be supported.
 * @param[out] pstSensorMode HI_MPP_SENSOR_ATTR_S*:pointer of sensor mode.
 * @return 0  Get sensor mode successful.
 * @return non 0  Get sensor mode fail.
 */
HI_S32 HI_MAPI_Sensor_GetAttr(HI_HANDLE SensorHdl, HI_MPP_SENSOR_ATTR_S* pstSensorMode);

/**
 * @brief Set attribute of a capture.It must be called after HI_MAPI_Sensor_SetAttr.
 *        We must set the attributes of two captures when record and snap at the same or only snap.
 *        If we only need to record or preview,Setting attribute of capture1 is enough.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] pstVCapAttr HI_MPP_VCAP_ATTR_S *: pointer of capture attribute.Dynamic attribute.
 * @return 0  Set attribute of capture successful.
 * @return non 0  Set attribute of capture fail.
 */
HI_S32 HI_MAPI_VCap_SetAttr(HI_HANDLE VCapHdl, HI_MPP_VCAP_ATTR_S *pstVCapAttr);

/**
 * @brief Get attribute of a capture.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[out] pstVCapAttr HI_MPP_VCAP_ATTR_S *: pointer of capture attribute.
 * @return 0  Get attribute of a capture successful.
 * @return non 0  Get attribute of a capture fail.
 */
HI_S32 HI_MAPI_VCap_GetAttr(HI_HANDLE VCapHdl, HI_MPP_VCAP_ATTR_S *pstVCapAttr);

/**
 * @brief Start a capture.It must be called after HI_MAPI_VCap_SetAttr.
 *        We must start capture0 and capture1 when record and snap at the same or only snap.
 *        If we only need to record or preview,starting capture1 is enough.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Start a capture successful.
 * @return non 0  Start a capture fail.
 */
HI_S32 HI_MAPI_VCap_Start(HI_HANDLE VCapHdl);

/**
 * @brief Stop a capture.It must be called after HI_MAPI_VCap_Start.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Stop a capture successful.
 * @return non 0  Stop capture fail.
 */
HI_S32 HI_MAPI_VCap_Stop(HI_HANDLE VCapHdl);

/**
 * @brief Start isp of capture with VCapHdl.It must be called after HI_MAPI_VCap_SetAttr.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Start isp successful.
 * @return non 0  Start is fail.
 */
HI_S32 HI_MAPI_VCap_Isp_Start(HI_HANDLE VCapHdl);

/**
 * @brief Stop isp of capture with VCapHdl.It must be called after HI_MAPI_VCap_Isp_Start.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Stop isp successful.
 * @return non 0  Stop isp fail.
 */
HI_S32 HI_MAPI_VCap_Isp_Stop(HI_HANDLE VCapHdl);

/**
 * @brief Set corresponding attributes of a capture,including exposure,WB,Sharpen,Brightness,Saturation etc.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] enCMD HI_MPP_VCAP_CMD_E: Setting command.
 * @param[in] pAttr HI_VOID:The struct of corresponding.Dynamic attribute.
 * @return 0  Set corresponding attributes successful.
 * @return non 0  Set corresponding attributes fail.
 */
HI_S32 HI_MAPI_VCap_SetAttrEx(HI_HANDLE VCapHdl, HI_MPP_VCAP_CMD_E enCMD, HI_VOID* pAttr);

/**
 * @brief Get corresponding attributes of capture,including exposure,WB,Sharpen,Brightness,Saturation etc.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] enCMD HI_MPP_VCAP_CMD_E: Getting command.
 * @param[out] pAttr HI_VOID:The struct of corresponding
 * @return 0  Get corresponding attributes of capture success.
 * @return Non 0  Get corresponding attributes of capture fail.
 */
HI_S32 HI_MAPI_VCap_GetAttrEx(HI_HANDLE VCapHdl, HI_MPP_VCAP_CMD_E enCMD, HI_VOID* pAttr);

/**
 * @brief Enable dump raw.Resources for dump will be created.It must be called after HI_MAPI_VCap_Start and HI_MAPI_VCap_Isp_Start.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Enable dump raw successful.
 * @return non 0  Enable dump raw  fail.
 */
HI_S32 HI_MAPI_VCap_EnableDumpRaw(HI_HANDLE VCapHdl);

/**
 * @brief Disable dump raw.Resources for dump will be destroyed.It must be called after HI_MAPI_VCap_EnableDumpRaw.
 *		  It must be called if you don't want to dump any more. 	
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Disable dump raw success.
 * @return non 0  Disable dump raw fail.
 */
HI_S32 HI_MAPI_VCap_DisableDumpRaw(HI_HANDLE VCapHdl);

/**
 * @brief Start dump raw.It must be called after HI_MAPI_VCap_EnableDumpRaw.non-blocking interface.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] u32Cunt HI_U32: number of raw data need to dump
 * @param[in] pfunVCapRawProc PFN_VCAP_RawDataProc:The pointer of raw data callback function.
 * @return 0  Start dump raw success.
 * @return Non 0  Start dump raw fail.
 */
HI_S32 HI_MAPI_VCap_DumpRaw(HI_HANDLE VCapHdl, HI_U32 u32Cunt, PFN_VCAP_RawDataProc pfunVCapRawProc);

/**
 * @brief Set exif info.It must be called after HI_MAPI_VCap_Start and HI_MAPI_VCap_Isp_Start.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] pstExifInfo HI_MPP_SNAP_EXIF_INFO_S:exif info.Dynamic attribute.
 * @return 0  Set exif info success.
 * @return Non 0  Set exif info fail.
 */
HI_S32 HI_MAPI_VCap_SetExifInfo(HI_HANDLE VCapHdl,HI_MPP_SNAP_EXIF_INFO_S* pstExifInfo);

/**
 * @brief Get exif info.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[out] pstExifInfo HI_MPP_SNAP_EXIF_INFO_S*:pointer of exif info
 * @return 0  Get exif info success.
 * @return Non 0  Get exif info fail.
 */
HI_S32 HI_MAPI_VCap_GetExifInfo(HI_HANDLE VCapHdl,HI_MPP_SNAP_EXIF_INFO_S* pstExifInfo);

/**
 * @brief Set snap attribute,including snap mode and attribute in different mode.
 *        Snap capture will be enabled by calling this API after start snap capture and record capture.
 *        It must be called after snap capture and record capture both started.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] pstSnapAttr HI_MPP_SNAP_ATTR_S:snap attribute.dynamic attribute.
 * @return 0  Set snap attribute success.
 * @return Non 0  Set snap attribute fail.
 */
HI_S32 HI_MAPI_VCap_SetSnapAttr(HI_HANDLE VCapHdl,HI_MPP_SNAP_ATTR_S* pstSnapAttr);

/**
 * @brief Get snap attribute.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] pstSnapAttr HI_MPP_SNAP_ATTR_S*:snap attribute.
 * @return 0  Get snap attribute success.
 * @return Non 0  Get snap attribute fail.
 */
HI_S32 HI_MAPI_VCap_GetSnapAttr(HI_HANDLE VCapHdl,HI_MPP_SNAP_ATTR_S* pstSnapAttr);

/**
 * @brief Trigger snapshot
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Trigger success.
 * @return Non 0  Trigger fail.
 */
HI_S32 HI_MAPI_VCap_Trigger(HI_HANDLE VCapHdl);

/**
 * @brief Stop trigger in continues snap mode when not get s32FrameCnt pictures. 
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @return 0  Stop trigger success.
 * @return Non 0  Stop trigger fail.
 */
HI_S32 HI_MAPI_VCap_StopTrigger(HI_HANDLE VCapHdl);

/**
 * @brief Set osd attribute.It must be called after HI_MAPI_VCap_Start and HI_MAPI_VCap_Isp_Start.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] VOsdHdl HI_HANDLE:handle of osd region.0~3.
 * @param[in] pstOsdAttr HI_MPP_OSD_ATTR_S:Osd attribute.Some of them are dynamic.Details are described in HI_MPP_OSD_ATTR_S.
 * @return 0  Set osd attribute success.
 * @return Non 0  Set osd attribute fail.
 */
HI_S32 HI_MAPI_VCap_OSD_SetAttr(HI_HANDLE VCapHdl, HI_HANDLE VOsdHdl, HI_MPP_OSD_ATTR_S* pstOsdAttr);

/**
 * @brief Get osd attribute.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] VOsdHdl HI_HANDLE:handle of osd region.0~3.
 * @param[out] pstOsdAttr HI_MPP_OSD_ATTR_S*:pointer of Osd attribute
 * @return 0  Get osd attribute success.
 * @return Non 0  Get osd attribute fail.
 */
HI_S32 HI_MAPI_VCap_OSD_GetAttr(HI_HANDLE VCapHdl, HI_HANDLE VOsdHdl, HI_MPP_OSD_ATTR_S *pstOsdAttr);

/**
 * @brief Start osd instance.Osd region will be created in capture.It must be called after HI_MAPI_VCap_OSD_SetAttr.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] OsdHdl HI_HANDLE:handle of osd region.0~3.
 * @return 0  Start osd success.
 * @return Non 0  Start osd fail.
 */
HI_S32 HI_MAPI_VCap_OSD_Start(HI_HANDLE VCapHdl, HI_HANDLE OsdHdl);

/**
 * @brief Stop osd instance.Osd region will be destroyed from capture.
 * @param[in] VCapHdl HI_HANDLE:handle of video capture.In hi3559,0 indicates snap capture,1 indicates record capture.
 * @param[in] OsdHdl HI_HANDLE:handle of osd region.0~3.
 * @return 0  Stop osd success.
 * @return Non 0  Stop osd fail. 
 */
HI_S32 HI_MAPI_VCap_OSD_Stop(HI_HANDLE VCapHdl, HI_HANDLE OsdHdl);
/** @}*/  /** <!-- ==== VCAP End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_VCAP_H__ */
