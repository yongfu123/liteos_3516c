/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file         hi_mapi_disp.h
* @brief       video display mapi functions declaration
* @author    HiMobileCam middleware develop team
* @date       2016.06.08
*/
#ifndef __HI_MAPI_DISP_H__
#define __HI_MAPI_DISP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     Disp */
/** @{ */  /** <!-- [Disp] */

HI_S32 HI_MAPI_Disp_Init(HI_HANDLE DispHdl, HI_MPP_DISP_ATTR_S* pstDispAttr);

HI_S32 HI_MAPI_Disp_DeInit(HI_HANDLE DispHdl);

HI_S32 HI_MAPI_Disp_Start(HI_HANDLE DispHdl);

HI_S32 HI_MAPI_Disp_Stop(HI_HANDLE DispHdl);

HI_S32 HI_MAPI_Disp_Window_SetAttr(HI_HANDLE DispHdl, HI_HANDLE WndHdl, HI_MPP_DISP_WINDOW_ATTR_S* pstWndAttr);

HI_S32 HI_MAPI_Disp_Window_GetAttr(HI_HANDLE DispHdl, HI_HANDLE WndHdl, HI_MPP_DISP_WINDOW_ATTR_S* pstWndAttr);

HI_S32 HI_MAPI_Disp_Window_Start(HI_HANDLE DispHdl, HI_HANDLE WndHdl);

HI_S32 HI_MAPI_Disp_Window_Stop(HI_HANDLE DispHdl, HI_HANDLE WndHdl);

HI_S32 HI_MAPI_Disp_Bind_VProc(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_HANDLE DispHdl, HI_HANDLE WndHdl);

HI_S32 HI_MAPI_Disp_UnBind_VProc(HI_HANDLE VProcHdl, HI_HANDLE VPortHdl, HI_HANDLE DispHdl, HI_HANDLE WndHdl);

HI_S32 HI_MAPI_Disp_SendFrame(HI_HANDLE DispHdl, HI_HANDLE WndHdl, HI_FRAME_DATA_S *pstFramedata);

HI_S32 HI_MAPI_Disp_SetAttrEx(HI_HANDLE DispHdl,  HI_MPP_DISP_ATTREX_S* pstDispAttrEx);

HI_S32 HI_MAPI_Disp_GetAttrEx(HI_HANDLE DispHdl,  HI_MPP_DISP_ATTREX_S* pstDispAttrEx);

HI_S32 HI_MAPI_Disp_SetReg(HI_U32 u32Addr, HI_U32 u32Value);

HI_S32 HI_MAPI_Disp_GetReg(HI_U32 u32Addr, HI_U32 *pu32Value);


/** @}*/  /** <!-- ==== Disp End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_DISP_H__ */
