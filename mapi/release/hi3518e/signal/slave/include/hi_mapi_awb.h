/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_awb.h
* @brief       awb algorithm function declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_AWB_H__
#define __HI_MAPI_AWB_H__

#define MODULE_NAME   "AWB"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     AWB */
/** @{ */  /** <!-- [AWB] */
HI_S32 HI_MAPI_AWB_SensorRegCallBack(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAwbLib, SENSOR_ID SensorId,HI_MPP_AWB_SENSOR_REGISTER_S *pstRegister);

HI_S32 HI_MAPI_AWB_SensorUnRegCallBack(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAwbLib, SENSOR_ID SensorId);
/** @}*/  /** <!-- ==== AWB End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_AWB_H__ */