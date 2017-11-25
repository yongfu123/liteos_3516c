/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_sns_ctrl_define.h
* @brief       sensor ctrl struct declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/

#ifndef __HI_MAPI_SNS_CTRL_DEFINE_H__
#define __HI_MAPI_SNS_CTRL_DEFINE_H__

#include "hi_type.h"
#include "hi_mapi_3a_define.h"
#include "hi_mapi_vcap_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


//#define DOUBLE_SENSOR
//#define ISP_MAX_DEV_NUM     2

typedef struct hiISP_SNS_STATE_S
{
    HI_BOOL     bInit;                  /* HI_TRUE: Sensor init */
    HI_BOOL     bSyncInit;              /* HI_TRUE: Sync Reg init */
    HI_BOOL     bYoutSize_1080p;
    HI_U8       u8Hcg;
    HI_U8       u8ImgMode;
    HI_MPP_WDR_MODE_E  enWDRMode;

    HI_MPP_ISP_SNS_REGS_INFO_S astRegsInfo[2]; /* [0]: Sensor reg info of cur-frame; [1]: Sensor reg info of pre-frame ; */

    HI_U32      au32FL[2];              /* [0]: FullLines of cur-frame; [1]: Pre FullLines of pre-frame */
    HI_U32      u32FLStd;               /* FullLines std */
    HI_U32      u32BRL;
    HI_U32      u32DgainVal; 
    HI_U32      u32RHS1_MAX;
    HI_U32      u32RHS1_LocRLimit;
    HI_U32      u32RHS2_MAX;
    HI_U32      au32RHS[2];           /*[0] RHS1 [1] RHS2 */
    HI_U32      au32WDRIntTime[4];
} ISP_SNS_STATE_S;

typedef struct hiISP_SNS_OBJ_S
{
    HI_S32  (*pfnRegisterCallback)(HI_S32 IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib);
    HI_S32  (*pfnUnRegisterCallback)(HI_S32 IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib);
    HI_S32  (*pfnSetBusInfo)(HI_S32 IspId, HI_MPP_ISP_SNS_COMMBUS_U unSNSBusInfo);
    HI_VOID (*pfnStandby)(HI_S32 IspId);
    HI_VOID (*pfnRestart)(HI_S32 IspId);
    HI_S32  (*pfnWriteReg)(HI_S32 IspId, HI_S32 s32Addr, HI_S32 s32Data);
    HI_S32  (*pfnReadReg)(HI_S32 IspId, HI_S32 s32Addr);
} ISP_SNS_OBJ_S;


extern ISP_SNS_OBJ_S stSnsMn34220Obj;
extern ISP_SNS_OBJ_S stSnsMn34220MipiObj;
extern ISP_SNS_OBJ_S stSnsImx117Obj;
extern ISP_SNS_OBJ_S stSnsImx226Obj;
extern ISP_SNS_OBJ_S stSnsImx274Obj;
extern ISP_SNS_OBJ_S stSnsImx290Obj;
extern ISP_SNS_OBJ_S stSnsOv4689SlaveObj;
extern ISP_SNS_OBJ_S stSnsOv9732Obj;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_MAPI_SNS_CTRL_DEFINE_H__ */

