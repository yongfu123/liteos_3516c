/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_sns_ctrl.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/01/10
  Description   : 
  History       :
  1.Date        : 2011/01/10
    Author      : x00100808
    Modification: Created file

******************************************************************************/

#ifndef __HI_SNS_CTRL_H__
#define __HI_SNS_CTRL_H__

#include "hi_type.h"
#include "hi_mapi_isp_define.h"
#include "hi_mapi_sns_define.h"
#include "hi_mapi_sns_ctrl_define.h"
#include "hi_mapi_ae_define.h"
#include "hi_mapi_awb_define.h"
#include "hi_mapi_vcap_define.h"
#include "hi_mapi_sns_ctrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

void ov9732_init(ISP_ID IspId);
void ov9732_exit(ISP_ID IspId);
void ov9732_standby(ISP_ID IspId);
void ov9732_restart(ISP_ID IspId);
int  ov9732_write_register(ISP_ID IspId, int addr, int data);
int  ov9732_read_register(ISP_ID IspId, int addr);
int  sensor_register_callback(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib); 
int  sensor_unregister_callback(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib);
int  sensor_set_inifile_path(const HI_CHAR *pcPath);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_SNS_CTRL_H__ */

