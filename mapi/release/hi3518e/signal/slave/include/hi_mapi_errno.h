/**
* Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file      hi_mapi_errno.h
* @brief     define of error
* @author    HiMobileCam middleware develop team
* @date      2016.06.08
*/
#ifndef __HI_MAPI_ERRNO_H__
#define __HI_MAPI_ERRNO_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/** \addtogroup     COMM */
/** @{ */  /** <!-- [COMM] */

#define HI_MPP_ERR_APPID  (0x80000000L + 0x23000000L)

typedef enum hiMPP_ERR_LEVEL_E
{
    MPP_EN_ERR_LEVEL_DEBUG = 0,  /* debug-level                                  */
    MPP_EN_ERR_LEVEL_INFO,       /* informational                                */
    MPP_EN_ERR_LEVEL_NOTICE,     /* normal but significant condition             */
    MPP_EN_ERR_LEVEL_WARNING,    /* warning conditions                           */
    MPP_EN_ERR_LEVEL_ERROR,      /* error conditions                             */
    MPP_EN_ERR_LEVEL_CRIT,       /* critical conditions                          */
    MPP_EN_ERR_LEVEL_ALERT,      /* action must be taken immediately             */
    MPP_EN_ERR_LEVEL_FATAL,      /* just for compatibility with previous version */
    MPP_EN_ERR_LEVEL_BUTT
}MPP_ERR_LEVEL_E;


/******************************************************************************
|----------------------------------------------------------------|
| 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            |
|----------------------------------------------------------------|
|<--><--7bits----><----8bits---><--3bits---><------13bits------->|
******************************************************************************/

#define HI_MPP_DEF_ERR( module, level, errid) \
    ((HI_S32)( (HI_MPP_ERR_APPID) | ((module) << 16 ) | ((level)<<13) | (errid) ))

/* NOTE! the following defined all common error code,
** all module must reserved 0~63 for their common error code
*/
typedef enum hiMPP_EN_ERR_CODE_E
{
    MPP_EN_ERR_INVALID_DEVID = 1, /* invlalid device ID                           */
    MPP_EN_ERR_INVALID_CHNID = 2, /* invlalid channel ID                          */
    MPP_EN_ERR_ILLEGAL_PARAM = 3, /* at lease one parameter is illagal
                               * eg, an illegal enumeration value             */
    MPP_EN_ERR_EXIST         = 4, /* resource exists                              */
    MPP_EN_ERR_UNEXIST       = 5, /* resource unexists                            */
    
    MPP_EN_ERR_NULL_PTR      = 6, /* using a NULL point                           */
    
    MPP_EN_ERR_NOT_CONFIG    = 7, /* try to enable or initialize system, device
                              ** or channel, before configing attribute       */

    MPP_EN_ERR_NOT_SUPPORT   = 8, /* operation or type is not supported by NOW    */
    MPP_EN_ERR_NOT_PERM      = 9, /* operation is not permitted
                              ** eg, try to change static attribute           */

    MPP_EN_ERR_NOMEM         = 12,/* failure caused by malloc memory              */
    MPP_EN_ERR_NOBUF         = 13,/* failure caused by malloc buffer              */

    MPP_EN_ERR_BUF_EMPTY     = 14,/* no data in buffer                            */
    MPP_EN_ERR_BUF_FULL      = 15,/* no buffer for new data                       */

    MPP_EN_ERR_SYS_NOTREADY  = 16,/* System is not ready,maybe not initialed or
                              ** loaded. Returning the error code when opening
                              ** a device file failed.                        */

    MPP_EN_ERR_BADADDR       = 17,/* bad address,
                              ** eg. used for copy_from_user & copy_to_user   */

    MPP_EN_ERR_BUSY          = 18,/* resource is busy,
                              ** eg. destroy a venc chn without unregister it */

    MPP_EN_ERR_BUTT          = 63,/* maxium code, private error code of all modules
                              ** must be greater than it                      */
}MPP_EN_ERR_CODE_E;

// error code for venc
#define HI_ERR_MAPI_VENC_NULL_PTR                      HI_MPP_DEF_ERR(HI_MPP_MOD_VENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_NULL_PTR)
#define HI_ERR_MAPI_VENC_ILLEGAL_PARAM                 HI_MPP_DEF_ERR(HI_MPP_MOD_VENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_ILLEGAL_PARAM)
#define HI_ERR_MAPI_VENC_NOT_INITED                    HI_MPP_DEF_ERR(HI_MPP_MOD_VENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_SYS_NOTREADY)
#define HI_ERR_MAPI_VENC_HANDLE_ILLEGAL                HI_MPP_DEF_ERR(HI_MPP_MOD_VENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_INVALID_CHNID)
#define HI_ERR_MAPI_VENC_PARA_ILLEGAL                  HI_MPP_DEF_ERR(HI_MPP_MOD_VENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_ILLEGAL_PARAM)

// error code for aenc
#define HI_ERR_MAPI_AENC_NULL_PTR                      HI_MPP_DEF_ERR(HI_MPP_MOD_AENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_NULL_PTR)
#define HI_ERR_MAPI_AENC_ILLEGAL_PARAM                 HI_MPP_DEF_ERR(HI_MPP_MOD_AENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_ILLEGAL_PARAM)
#define HI_ERR_MAPI_AENC_NOT_INITED                    HI_MPP_DEF_ERR(HI_MPP_MOD_AENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_SYS_NOTREADY)
#define HI_ERR_MAPI_AENC_HANDLE_ILLEGAL                HI_MPP_DEF_ERR(HI_MPP_MOD_AENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_INVALID_CHNID)
#define HI_ERR_MAPI_AENC_PARA_ILLEGAL                  HI_MPP_DEF_ERR(HI_MPP_MOD_AENC,MPP_EN_ERR_LEVEL_ERROR,MPP_EN_ERR_ILLEGAL_PARAM)
/** @}*/  /** <!-- ==== COMM End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __HI_MAPI_ERRNO_H__ */

