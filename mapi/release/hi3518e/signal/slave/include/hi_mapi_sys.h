/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_mapi_sys.h
* @brief     define of common struct
* @author    HiMobileCam middleware develop team
* @date      2016.06.08
*/
#ifndef __HI_MAPI_SYS_H__
#define __HI_MAPI_SYS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** \addtogroup     COMM */
/** @{ */  /** <!-- [COMM] */

/**
 * @brief Sys initialization,including message initialization for communicating between HuaweiLite and Linux. 
 *        It must be called by both HuaweiLite's app and Linux's app.It must be called the very first.
 * @return 0  Sys initialize success.
 * @return non 0  Sys initialize fail.
 */
HI_S32 HI_MAPI_Sys_Init();

/**
 * @brief Sys de-initialize.
 * @return 0  Sys de-initialize success.
 * @return non 0  Sys de-initialize fail.
 */
HI_S32 HI_MAPI_Sys_DeInit();

/**
 * @brief Media initialization.
 *        It must be called before other media MAPI,such as HI_MAPI_VCap_XXX,HI_MAPI_VProc_XXX,HI_MAPI_VEnc_XXX,HI_MAPI_Vo_XXX.etc.
 * @return 0  Media initialize success.
 * @return non 0  Media initialize fail.
 */
HI_S32 HI_MAPI_Media_Init();

/**
 * @brief Media de-initialize.
 * @return 0  Media de-initialize success.
 * @return non 0  Media de-initialize fail.
 */
HI_S32 HI_MAPI_Media_DeInit();
/**
 * @brief Allocate buffer from MMZ. 
 * @param[out] pu32PhyAddr HI_U32*:The physical address of buffer.
 * @param[out] ppVitAddr HI_VOID **:The virtual address of buffer.
 * @param[in] u32Len HI_U32:The length of buffer.
 * @param[in] pstrName HI_CHAR*:The name of buffer.
 * @return 0  Allocate buffer successful.
 * @return non 0  Allocate buffer fail.
 */
HI_S32 HI_MAPI_AllocBuffer(HI_U32 *pu32PhyAddr, HI_VOID **ppVitAddr, HI_U32 u32Len, const HI_CHAR *pstrName);

/**
 * @brief Free buffer from MMZ. 
 * @param[in] pu32PhyAddr HI_U32*:The physical address of buffer.
 * @param[in] ppVitAddr HI_VOID **:The virtual address of buffer.
 * @return 0  Free buffer successful.
 * @return non 0  Free buffer fail.
 */
HI_S32 HI_MAPI_FreeBuffer(HI_U32 u32PhyAddr, HI_VOID *pVirtAddr);

/** @}*/  /** <!-- ==== COMM End ====*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_VIDEO_BASIC_H__ */