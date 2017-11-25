/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_isp.h
* @brief       isp function declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_ISP_H__
#define __HI_MAPI_ISP_H__

#define MODULE_NAME   "ISP"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     ISP */
/** @{ */  /** <!-- [ISP] */
HI_S32 HI_MAPI_ISP_SetHvSync(ISP_ID IspId, const HI_MPP_ISP_SLAVE_SNS_SYNC_S *pstSnsSync);

HI_S32 HI_MAPI_ISP_GetHvSync(ISP_ID IspId, HI_MPP_ISP_SLAVE_SNS_SYNC_S *pstSnsSync);

HI_S32 HI_MAPI_ISP_SensorRegCallBack(ISP_ID IspId, SENSOR_ID SensorId, HI_MPP_ISP_SENSOR_REGISTER_S *pstRegister);

HI_S32 HI_MAPI_ISP_SensorUnRegCallBack(ISP_ID IspId, SENSOR_ID SensorId);

/** @}*/  /** <!-- ==== ISP End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_ISP_H__ */
