/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_ae.h
* @brief       ae algorithm function declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_AE_H__
#define __HI_MAPI_AE_H__

#define MODULE_NAME   "AE"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     AE */
/** @{ */  /** <!-- [AE] */

HI_S32 HI_MAPI_AE_SensorRegCallBack(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, SENSOR_ID SensorId,HI_MPP_AE_SENSOR_REGISTER_S *pstRegister);

HI_S32 HI_MAPI_AE_SensorUnRegCallBack(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, SENSOR_ID SensorId);

/** @}*/  /** <!-- ==== AE End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_AE_H__ */


