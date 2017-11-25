#if !defined(__IMX117_CMOS_H_)
#define __IMX117_CMOS_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "hi_type.h"
#include "hi_mapi_sns_define.h"
#include "hi_mapi_sns_ctrl_define.h"
#include "hi_mapi_ae_define.h"
#include "hi_mapi_awb_define.h"
#include "hi_mapi_vcap_define.h"

#include "imx117_slave_priv.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define IMX117_ID 117
#define IMX117_FULL_LINES_STD_FPGA_COMP 0


const IMX117_VIDEO_MODE_TBL_S g_astImx117ModeTbl[IMX117_MODE_BUTT] = {
    
    {72000000, 0x3E8, 0x249F00, 2400, 30,  "4K2K_8CH_12BIT_30FPS"  },
    {72000000, 0x339, 0x2746B0, 3120, 28,  "12M_8CH_12BIT_28FPS"   },
    {72000000, 0x23C, 0x24A860, 4200, 30,  "4K2K_8CH_12BIT_30FPS"  },
    {72000000, 0x15E, 0x4950C,  858,  240, "720P_10CH_10BIT_240FPS"},
    {72000000, -1,    -1,       -1,   -1,  "NOT SUPPORT"           },
    {72000000, 0x16c, 0x4950C,  825,  240, "720P_8CH_10BIT_240FPS" },
    {72000000, 0x214, 0x92040,  1120, 120, "1080P_8CH_12BIT_120FPS"},   
};

HI_MPP_ISP_SLAVE_SNS_SYNC_S gstImx117Sync[ISP_MAX_DEV_NUM];


/****************************************************************************
 * extern function reference                                                *
 ****************************************************************************/

extern void imx117_init(ISP_ID IspId);
extern void imx117_exit(ISP_ID IspId);
extern void imx117_standby(ISP_ID IspId);
extern void imx117_restart(ISP_ID IspId);
extern int imx117_write_register(ISP_ID IspId, int addr, int data);
extern int imx117_read_register(ISP_ID IspId, int addr);

ISP_SNS_STATE_S             g_astImx117[ISP_MAX_DEV_NUM] = {{0}};
static ISP_SNS_STATE_S     *g_apstSnsState[ISP_MAX_DEV_NUM] = {&g_astImx117[0], &g_astImx117[1]};
HI_MPP_ISP_SNS_COMMBUS_U g_aunImx117BusInfo[ISP_MAX_DEV_NUM] = {
    [0] = {.s8SspDev = { .bit4SspDev = 0, .bit4SspCs = 0}},
    [1] = {.s8SspDev = { .bit4SspDev = 1, .bit4SspCs = 0}}
}; 

static HI_S32 cmos_get_ae_default(ISP_ID IspId,HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft)
{

    HI_U32 u32Fll, U32MaxFps;
    
    if (HI_NULL == pstAeSnsDft)
    {
        printf("null pointer when get ae default value!\n");
        return -1;
    }
    
    u32Fll = g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32VertiLines;
    U32MaxFps = g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32MaxFps;
	g_apstSnsState[IspId]->u32FLStd = u32Fll;
    pstAeSnsDft->u32LinesPer500ms = (u32Fll * U32MaxFps) >> 1; 
    pstAeSnsDft->u32FullLinesStd = g_apstSnsState[IspId]->u32FLStd;
    pstAeSnsDft->u32FlickerFreq = 0;

    pstAeSnsDft->stIntTimeAccu.enAccuType = HI_MPP_AE_ACCURACY_LINEAR;
    pstAeSnsDft->stIntTimeAccu.f32Accuracy = 1;

    switch(g_apstSnsState[IspId]->u8ImgMode) 
    {
        case IMX117_MODE0:
        case IMX117_MODE0A:
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->u32FLStd - 8;
            pstAeSnsDft->stIntTimeAccu.f32Offset = 0.221;
            break;
        case IMX117_MODE1:
        case IMX117_MODE1D:    
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->u32FLStd - 8;
            pstAeSnsDft->stIntTimeAccu.f32Offset = 0.256;
            break;
        case IMX117_MODE2:           
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->u32FLStd - 8;
            pstAeSnsDft->stIntTimeAccu.f32Offset = 0.262;
        	break;
        case IMX117_MODE11A :
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->u32FLStd - 12;
            pstAeSnsDft->stIntTimeAccu.f32Offset = 0.280;      
            break;
        default:
        	printf("[%s]:[%d] NOT support this mode!\n", __FUNCTION__, __LINE__);
        	break;
    }

    pstAeSnsDft->stAgainAccu.enAccuType = HI_MPP_AE_ACCURACY_TABLE;
    pstAeSnsDft->stAgainAccu.f32Accuracy = 0.3;

    pstAeSnsDft->stDgainAccu.enAccuType = HI_MPP_AE_ACCURACY_TABLE;
    pstAeSnsDft->stDgainAccu.f32Accuracy = 0.3;
    
    pstAeSnsDft->u32ISPDgainShift = 8;
    pstAeSnsDft->u32MinISPDgainTarget = 1 << pstAeSnsDft->u32ISPDgainShift;
    pstAeSnsDft->u32MaxISPDgainTarget = 6 << pstAeSnsDft->u32ISPDgainShift; 
    
    switch(g_apstSnsState[IspId]->enWDRMode)
    {
        default:
        case HI_MPP_WDR_MODE_NONE:  
        {
            pstAeSnsDft->au8HistThresh[0] = 0xd;
            pstAeSnsDft->au8HistThresh[1] = 0x28;
            pstAeSnsDft->au8HistThresh[2] = 0x60;
            pstAeSnsDft->au8HistThresh[3] = 0x80;
            
            pstAeSnsDft->u8AeCompensation = 0x38;             
           
            pstAeSnsDft->u32MinIntTime = 4;
            pstAeSnsDft->u32MaxIntTimeTarget = 65535;
            pstAeSnsDft->u32MinIntTimeTarget = 2;
            
            pstAeSnsDft->u32MaxAgain = 21845;
            pstAeSnsDft->u32MinAgain = 1024;
            pstAeSnsDft->u32MaxAgainTarget = pstAeSnsDft->u32MaxAgain;
            pstAeSnsDft->u32MinAgainTarget = pstAeSnsDft->u32MinAgain;
            
            pstAeSnsDft->u32MaxDgain = 1024;  /* if Dgain enable,please set ispdgain bigger than 1*/
            pstAeSnsDft->u32MinDgain = 1024;
            pstAeSnsDft->u32MaxDgainTarget = pstAeSnsDft->u32MaxDgain;
            pstAeSnsDft->u32MinDgainTarget = pstAeSnsDft->u32MinDgain;
            
            break;  
        }           
    }

    return 0;
}


static HI_VOID cmos_fps_set(ISP_ID IspId,HI_FLOAT f32Fps, HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft)
{
    HI_U32 u32maxFps;
    HI_U32 u32Lines;

    u32maxFps = g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32MaxFps;
    u32Lines = g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32VertiLines * u32maxFps / f32Fps;

    /* SHR was 16bit, so limit full_lines as 0xFFFF */
    if (f32Fps > u32maxFps || u32Lines > FULL_LINES_MAX)
    {
        printf("[%s]:[%d] Not support Fps: %f\n", __FUNCTION__, __LINE__, f32Fps);
        return;
    }
    
    gstImx117Sync[IspId].u32VsTime = (g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32InckPerVs) * u32maxFps / f32Fps;
    g_apstSnsState[IspId]->u32FLStd = g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32VertiLines * u32maxFps / f32Fps;
    
    g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.u32SlaveVsTime = gstImx117Sync[IspId].u32VsTime;
    g_apstSnsState[IspId]->u32FLStd = (g_apstSnsState[IspId]->u32FLStd > FULL_LINES_MAX) ? FULL_LINES_MAX : g_apstSnsState[IspId]->u32FLStd;
    
    pstAeSnsDft->f32Fps = f32Fps;
    pstAeSnsDft->u32LinesPer500ms = g_apstSnsState[IspId]->u32FLStd * f32Fps / 2;
	switch(g_apstSnsState[IspId]->u8ImgMode) 
    {
        case IMX117_MODE0:
        case IMX117_MODE0A:
        case IMX117_MODE1:
        case IMX117_MODE1D:            
        case IMX117_MODE2:
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->u32FLStd - 8;
        	break;
        case IMX117_MODE11A :    
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->u32FLStd - 12;
            break;
            
        default:
        	printf("[%s]:[%d] NOT support this mode!\n", __FUNCTION__, __LINE__);
            return;
        	break;
    } 
    pstAeSnsDft->u32FullLinesStd = g_apstSnsState[IspId]->u32FLStd;

    g_apstSnsState[IspId]->au32FL[0]= g_apstSnsState[IspId]->u32FLStd;
    pstAeSnsDft->u32FullLines = g_apstSnsState[IspId]->au32FL[0];
    
    return;
}


static HI_VOID cmos_slow_framerate_set(ISP_ID IspId,HI_U32 u32FullLines,
    HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft)
{
    // current do not support slow shutter
    g_apstSnsState[IspId]->au32FL[0] = (u32FullLines > FULL_LINES_MAX) ? FULL_LINES_MAX : u32FullLines;
	gstImx117Sync[IspId].u32VsTime =  g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32InckPerHs * u32FullLines;
    g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.u32SlaveVsTime = gstImx117Sync[IspId].u32VsTime;
    pstAeSnsDft->u32FullLines = g_apstSnsState[IspId]->au32FL[0];
	switch(g_apstSnsState[IspId]->u8ImgMode) 
    {
        case IMX117_MODE0:
        case IMX117_MODE0A:
        case IMX117_MODE1:
        case IMX117_MODE1D:            
        case IMX117_MODE2:
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->au32FL[0] - 8;
        	break;
        case IMX117_MODE11A :    
            pstAeSnsDft->u32MaxIntTime = g_apstSnsState[IspId]->au32FL[0] - 12;
            break;
            
        default:
        	printf("[%s]:[%d] NOT support this mode!\n", __FUNCTION__, __LINE__);
            return;
        	break;
    } 

    return;
}

/* while isp notify ae to update sensor regs, ae call these funcs. */
static HI_VOID cmos_inttime_update(ISP_ID IspId,HI_U32 u32IntTime)
{
    HI_U32 u32Shr = g_apstSnsState[IspId]->au32FL[0] - u32IntTime;
    
    u32Shr = MIN(u32Shr, 0xffff);
    
    switch(g_apstSnsState[IspId]->u8ImgMode) 
    {
        case IMX117_MODE0:
        case IMX117_MODE0A:
        case IMX117_MODE1D:
        case IMX117_MODE4A:     
            u32Shr = MIN(MAX(u32Shr, 8), g_apstSnsState[IspId]->au32FL[0] - 4);
        	break;
        case IMX117_MODE11A:
            u32Shr = MIN(MAX(u32Shr, 12), g_apstSnsState[IspId]->au32FL[0] - 4);
            break;
        default:
        	printf("[%s]:[%d] NOT support this mode!\n", __FUNCTION__, __LINE__);
        	break;
    }

    // issue a exposure start positon SHR
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[0].u32Data = LOW_8BITS(u32Shr);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[1].u32Data = HIGH_8BITS(u32Shr);  
    
    return;
}



/* Again segmentation = 123 */
static HI_U32 ad_gain_table[123]=
{    
    1024,1032, 1040, 1049, 1057, 1066, 1074, 1083, 1092,1101,1111,1120,1130,1140,1150,1160,1170,1181,1192,
    1202,1214, 1225, 1237, 1248, 1260, 1273, 1285, 1298,1311,1324,1337,1351,1365,1380,1394,1409,1425,1440,
    1456,1473, 1489, 1507, 1524, 1542, 1560, 1579, 1598,1618,1638,1659,1680,1702,1725,1748,1771,1796,1820,
    1846,1872, 1900, 1928, 1956, 1986, 2016, 2048, 2081,2114,2149,2185,2222,2260,2300,2341,2383,2427,2473,
    2521,2570, 2621, 2675, 2731, 2789, 2849, 2913, 2979,3048,3121,3197,3277,3361,3449,3542,3641,3745,3855,
    3972,4096, 4228, 4369, 4520, 4681, 4855, 5041, 5243,5461,5699,5958,6242,6554,6899,7282,7710,8192,8738,
    9362,10082,10923,11916,13107,14564,16384,18725,21845
};

static HI_VOID cmos_again_calc_table(ISP_ID IspId,HI_U32 *pu32AgainLin, HI_U32 *pu32AgainDb)
{   
    int i;

    if((HI_NULL == pu32AgainLin) ||(HI_NULL == pu32AgainDb))
    {
        printf("null pointer when get ae sensor gain info  value!\n");
        return;
    }

    if (*pu32AgainLin >= ad_gain_table[122])
    {
         *pu32AgainLin = ad_gain_table[122];
         *pu32AgainDb = 122;
         goto calc_table_end;
    }
    
    for (i = 1; i < 123; i++)
    {
        if (*pu32AgainLin < ad_gain_table[i])
        {
            *pu32AgainLin = ad_gain_table[i - 1];
            *pu32AgainDb = i - 1;
            goto calc_table_end;;
        }
    }


calc_table_end:

    // downsample require
    *pu32AgainDb <<= 4;

    return;
}

static HI_U32 dgain_table[4]=
{    
    1024,2048,4096,8192
};

static HI_VOID cmos_dgain_calc_table(ISP_ID IspId,HI_U32 *pu32DgainLin, HI_U32 *pu32DgainDb)
{
    int i;

    if((HI_NULL == pu32DgainLin) ||(HI_NULL == pu32DgainDb))
    {
        printf("null pointer when get ae sensor gain info value!\n");
        return;
    }

    if (*pu32DgainLin >= dgain_table[3])
    {
         *pu32DgainLin = dgain_table[3];
         *pu32DgainDb = 3;
         return ;
    }
    
    for (i = 1; i < 4; i++)
    {
        if (*pu32DgainLin < dgain_table[i])
        {
            *pu32DgainLin = dgain_table[i - 1];
            *pu32DgainDb = i - 1;
            break;
        }
    }

    return;
}


static HI_VOID cmos_gains_update(ISP_ID IspId,HI_U32 u32Again, HI_U32 u32Dgain)
{   
    HI_U16 u16Agc01 = 0;
    HI_U16 u16Agc02 = 0; 

    switch(g_apstSnsState[IspId]->u8ImgMode) 
    {
        case IMX117_MODE0: 
        case IMX117_MODE0A:
        	u16Agc01 = 0x003d;
        	u16Agc02 = 0x003c;
        	break;  
            
        default:
        	if (u32Again <= 0x146)
            {
        		u16Agc01 = 0x001f;
        		u16Agc02 = 0x001e;
        	} 
            else if (u32Again <= 0x400)
        	{
        		u16Agc01 = 0x0021;
        		u16Agc02 = 0x0020;
        	} 
            else if (u32Again <= 0x52c)
        	{
        		u16Agc01 = 0x0026;
        		u16Agc02 = 0x0025;
        	} 
            else if (u32Again <= 0x696)
        	{
        		u16Agc01 = 0x0028;
        		u16Agc02 = 0x0027;
        	} 
            else if (u32Again <= 0x74b)
        	{
        		u16Agc01 = 0x002c;
        		u16Agc02 = 0x002b;
        	} 
            else if (u32Again <= 0x7a5)
        	{
        		u16Agc01 = 0x0030;
        		u16Agc02 = 0x002f;
        	}
        	break;
    }

    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[2].u32Data = (u32Again & 0xFF);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[3].u32Data = ((u32Again >> 8) & 0x00FF);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[4].u32Data = (u16Agc01 & 0xFF);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[5].u32Data = ((u16Agc01 >> 8) & 0x00FF);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[6].u32Data = (u16Agc02 & 0xFF);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[7].u32Data = ((u16Agc02 >> 8) & 0x00FF);
    g_apstSnsState[IspId]->astRegsInfo[0].astSspData[10].u32Data = (u32Dgain & 0x3);

    return;
}

static HI_S32 cmos_init_ae_exp_function(HI_MPP_AE_SENSOR_EXP_FUNC_S *pstExpFuncs)
{
    memset(pstExpFuncs, 0, sizeof(HI_MPP_AE_SENSOR_EXP_FUNC_S));

    pstExpFuncs->pfn_cmos_get_ae_default    = cmos_get_ae_default;
    pstExpFuncs->pfn_cmos_fps_set           = cmos_fps_set;
    pstExpFuncs->pfn_cmos_slow_framerate_set= cmos_slow_framerate_set;    
    pstExpFuncs->pfn_cmos_inttime_update    = cmos_inttime_update;
    pstExpFuncs->pfn_cmos_gains_update      = cmos_gains_update;
    pstExpFuncs->pfn_cmos_again_calc_table  = cmos_again_calc_table;
    pstExpFuncs->pfn_cmos_dgain_calc_table  = cmos_dgain_calc_table;   

    return 0;
}


#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_R_R 0x01C8
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_R_G 0x80A3
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_R_B 0x8025
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_G_R 0x803F
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_G_G 0x0194
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_G_B 0x8055
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_B_R 0x000D
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_B_G 0x80B9
#define MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_B_B 0x01AC
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_R_R 0x01D6
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_R_G 0x80AD
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_R_B 0x8029
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_G_R 0x8067
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_G_G 0x01B0
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_G_B 0x8049
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_B_R 0x0003
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_B_G 0x80B2
#define MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_B_B 0x01AF
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_R_R 0x01C1 
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_R_G 0x80B2
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_R_B 0x800F
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_G_R 0x8069
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_G_G 0x015F
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_G_B 0x000A
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_B_R 0x801A
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_B_G 0x8292
#define MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_B_B 0x03AC

static HI_MPP_AWB_CCM_S g_stAwbCcm =
{
 
   5120,
   #if 0
   {
      MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_R_R, MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_R_G, MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_R_B,   
      MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_G_R, MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_G_G, MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_G_B,   
      MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_B_R, MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_B_G, MT_ABSOLUTE_LS_H_CALIBRATE_CCM_LINEAR_B_B    
   },
   #else
   {
    //0x01AC, 0x8074, 0x8038,
    //0x8064, 0x01E0, 0x807C,
    //0x0000, 0x80AF, 0x01AF
    0x01B8, 0x809F, 0x8019, 
    0x8051, 0x01B0, 0x805F, 
    0x0003, 0x80AB, 0x01A8
    },
   #endif
   3633,
   {
      MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_R_R, MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_R_G, MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_R_B,   
      MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_G_R, MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_G_G, MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_G_B,   
      MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_B_R, MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_B_G, MT_ABSOLUTE_LS_M_CALIBRATE_CCM_LINEAR_B_B    
   }, 
   
   2465,
   {     
      MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_R_R, MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_R_G, MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_R_B,   
      MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_G_R, MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_G_G, MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_G_B,   
      MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_B_R, MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_B_G, MT_ABSOLUTE_LS_L_CALIBRATE_CCM_LINEAR_B_B   
   }                 
};

static HI_MPP_AWB_AGC_TABLE_S g_stAwbAgcTable =
{
    /* bvalid */
    1,

    /* saturation */ 
    {0x80,0x80,0x78,0x74,0x68,0x60,0x58,0x50,0x48,0x40,0x38,0x38,0x38,0x38,0x38,0x38}
};
#if 0
#define CALIBRATE_STATIC_WB_R_GAIN 0x1AD 
#define CALIBRATE_STATIC_WB_GR_GAIN 0x100 
#define CALIBRATE_STATIC_WB_GB_GAIN 0x100 
#define CALIBRATE_STATIC_WB_B_GAIN 0x19D 
#else
#define CALIBRATE_STATIC_WB_R_GAIN 0x1A6 
#define CALIBRATE_STATIC_WB_GR_GAIN 0x100 
#define CALIBRATE_STATIC_WB_GB_GAIN 0x100 
#define CALIBRATE_STATIC_WB_B_GAIN 0x1A8 
#endif
/* Calibration results for Auto WB Planck */
#define CALIBRATE_AWB_P1 0x002C  
#define CALIBRATE_AWB_P2 0x006B  
#define CALIBRATE_AWB_Q1 -0x0069 
#define CALIBRATE_AWB_A1 0x291D4  
#define CALIBRATE_AWB_B1 0x0080  
#define CALIBRATE_AWB_C1 -0x1D5A8  

static HI_S32 cmos_get_awb_default(ISP_ID IspId,HI_MPP_AWB_SENSOR_DEFAULT_S *pstAwbSnsDft)
{
    if (HI_NULL == pstAwbSnsDft)
    {
        printf("sony imx117 null pointer when get awb default value!\n");
        return -1;
    }

    memset(pstAwbSnsDft, 0, sizeof(HI_MPP_AWB_SENSOR_DEFAULT_S));
    pstAwbSnsDft->u16WbRefTemp = 5120;

    pstAwbSnsDft->au16GainOffset[0] = CALIBRATE_STATIC_WB_R_GAIN;
    pstAwbSnsDft->au16GainOffset[1] = CALIBRATE_STATIC_WB_GR_GAIN;
    pstAwbSnsDft->au16GainOffset[2] = CALIBRATE_STATIC_WB_GB_GAIN;
    pstAwbSnsDft->au16GainOffset[3] = CALIBRATE_STATIC_WB_B_GAIN;

    pstAwbSnsDft->as32WbPara[0] = CALIBRATE_AWB_P1;
    pstAwbSnsDft->as32WbPara[1] = CALIBRATE_AWB_P2;
    pstAwbSnsDft->as32WbPara[2] = CALIBRATE_AWB_Q1;
    pstAwbSnsDft->as32WbPara[3] = CALIBRATE_AWB_A1;
    pstAwbSnsDft->as32WbPara[4] = CALIBRATE_AWB_B1;
    pstAwbSnsDft->as32WbPara[5] = CALIBRATE_AWB_C1;

    memcpy(&pstAwbSnsDft->stCcm, &g_stAwbCcm, sizeof(HI_MPP_AWB_CCM_S));
    memcpy(&pstAwbSnsDft->stAgcTbl, &g_stAwbAgcTable, sizeof(HI_MPP_AWB_AGC_TABLE_S));
    
    return 0;
}


static HI_S32 cmos_init_awb_exp_function(HI_MPP_AWB_SENSOR_EXP_FUNC_S *pstExpFuncs)
{
    memset(pstExpFuncs, 0, sizeof(HI_MPP_AWB_SENSOR_EXP_FUNC_S));

    pstExpFuncs->pfn_cmos_get_awb_default = cmos_get_awb_default;

    return 0;
}


static HI_MPP_ISP_CMOS_AGC_TABLE_S g_stIspAgcTable =
{
    /* bvalid */
    1,

    /* snr_thresh */
    //{0x64,0x64,0x68,0x68,0x68,0x6c,0x6c,0x70,0x70,0x78,0x78,0x78,0x7c,0x7c,0x80,0x80},
    {0x08,0x0c,0x10,0x14,0x18,0x20,0x28,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30},
    /* demosaic_np_offset */
    {0x0,0xa,0x12,0x1a,0x20,0x28,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30},
        
    /* ge_strength */
    {0x55,0x55,0x55,0x55,0x55,0x55,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37}
    
};

static HI_MPP_ISP_CMOS_BAYER_SHARPEN_S g_stIspBayerSharpen = 
{
    /* bvalid */
    1,

    /* ShpAlgSel = 1 is Demosaic SharpenEx, else Demosaic sharpen. */ 
    0,
    
    /* sharpen_alt_d to Sharpen */
    //{0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x40,0x30,0x20,0x10},
    {20, 20, 20, 38, 38, 38, 34, 34, 32, 32, 32, 32, 32, 32, 32, 32},
    /* sharpen_alt_ud to Sharpen */
    //{0x3a,0x36,0x32,0x30,0x2c,0x30,0x30,0x30,0x28,0x24,0x24,0x20,0x20,0x20,0x10,0x10},
    {22, 20, 20, 20, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 16, 16},
    /* demosaic_lum_thresh to Sharpen */
    {0x50,0x50,0x4c,0x42,0x38,0x30,0x28,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20},
        
    /* SharpenHF to SharpenEx */
    {0x30,0x30,0x30,0x30,0x30,0x30,0x2c,0x28,0x20,0x18,0x14,0x10,0x10,0x10,0x10,0x10},
        
    /* SharpenMF to SharpenEx */
    {0x30,0x30,0x30,0x30,0x28,0x20,0x20,0x20,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x10},
        
    /* SharpenLF to SharpenEx */
    {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18},

    /* SadAmplifier to SharpenEx */
    {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10}   

};

static HI_MPP_ISP_CMOS_YUV_SHARPEN_S g_stIspYuvSharpen = 
{
    /* bvalid */
     1,

     /* 100,  200,    400,     800,    1600,    3200,    6400,    12800,    25600,   51200,  102400,  204800,   409600,   819200,   1638400,  3276800 */
    
     /* bEnLowLumaShoot */ 
     {0,     0,     0,     0,     0,     0,     0,     0,     0,     1,     1,     1,     1,     1,     1,     1},
     
     /* TextureSt */
     //{12,   12,    12,    12,    10,    10,    8,     8,     8,     8,     8,     6,     6,     6,     6,     6},
    {30, 28, 25, 20, 20, 26, 24, 24, 22, 20, 20, 18, 18, 12, 12, 12},
     /* EdgeSt */
     //{56,	56,	   56,	  56,	 56,	56,	   50,	  50,	 44,	44,	   38,	  38,	 38,	20,	   20,	  20},      
    {40, 40, 38, 36, 34, 32, 30, 28, 20, 20, 16, 16, 16, 16, 16, 16},
     /* OverShoot */
     //{32,   32,    32,    32,    32,    32,    30,    30,    28,    28,    28,    26,    26,    24,    24,    24},
    {2, 2, 10, 20, 30, 50, 80, 80, 70, 60, 50, 40, 30, 24, 24, 24},
     /* UnderShoot */
     //{32,   32,    32,    32,    32,    32,    30,    30,    28,    28,    28,    26,    26,    24,    24,    24},
    {20, 30, 50, 70, 90, 120, 120, 100, 80, 50, 30, 26, 26, 24, 24, 24},
     /* TextureThd */
     {10,   16,    20,    32,    36,    40,    48,    56,    64,   128,   156,    156,    156,    160,    160,   160},
        
     /* EdgeThd */
     {0,     0,     0,    10,    10,    10,    16,    32,    64,   128,   156,    156,    156,    160,    160,   160},
    
     /* JagCtrl */
     {16,   14,    12,    10,     8,     6,     4,     4,     4,     4,     4,      4,      2,      2,      2,     2},
    
     /* SaltCtrl */
     {50,   50,    50,    90,    90,    90,    90,    90,    90,    90,     90,    90,     90,     50,     50,    50},
    
     /* PepperCtrl */
     {0,     0,      0,     20,     60,     60,     60,     80,    120,    160,    180,     180,   180,     180,    180,   180},
    
     /* DetailCtrl */
     //{140,  140,   135,    135,    130,    130,    130,    130,    120,    120,    120,     120,    100,      50,     50,    50}, 
    {245,  240,   230,    220,    210,    200,    200,    180,    180,    180,    180,     160,    160,      100,     50,    50},
    /* LumaThd */
    {
        {20,    20,     20,     20,     20,     20,     20,     20,     20,     20,     20,     20,     20,     20,     20,     20}, /* LumaThd0 */
        {40,    40,     40,     40,     40,     40,     40,     40,     40,     40,     40,     40,     40,     40,     40,     40}, /* LumaThd1 */
        {65,    65,     65,     65,     65,     65,     65,     65,     65,     65,     65,     65,     65,     65,     65,     65}, /* LumaThd2 */
        {90,    90,     90,     90,     90,     90,     90,     90,     90,     90,     90,     90,     90,     90,     90,     90}  /* LumaThd3 */  
    }, 
    
    /* LumaWgt */
    {
        {160,   160,    160,    150,    140,    130,    120,    110,    100,    100,     90,     90,     80,     80,     80,     80},
        {200,   200,    200,    180,    170,    160,    150,    150,    150,    150,    120,    120,    120,    120,    120,    120},
        {240,   240,    240,    200,    200,    190,    180,    180,    180,    180,    160,    160,    160,    160,    160,    160},
        {255,   255,    255,    255,    255,    255,    255,    255,    255,    255,    255,    255,    255,    255,    255,    255},
    } 

};

static HI_MPP_ISP_CMOS_NOISE_TABLE_S g_stIspNoiseTable =
{
    /* bvalid */
    1,

    /* nosie_profile_weight_lut */
    {
    0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x3,  0xC,  0x11, 0x15, 0x17, 0x1A, 0x1B, 0x1D, 0x1E, 0x1F, 
    0x21, 0x22, 0x23, 0x23, 0x24, 0x25, 0x26, 0x26, 0x27, 0x27, 0x28, 0x29, 0x29, 0x2A, 0x2A, 0x2A, 
    0x2B, 0x2B, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x2E, 0x2E, 0x2E, 0x2E, 0x2F, 0x2F, 0x2F, 0x30, 0x30, 
    0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x32, 0x32, 0x32, 0x32, 0x33, 0x33, 0x33, 0x33, 0x33, 0x34, 
    0x34, 0x34, 0x34, 0x34, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
    0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x39, 0x39,
    0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3B, 0x3B, 
    0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 
    },

    /* demosaic_weight_lut */
    {
    0x3,  0xC,  0x11, 0x15, 0x17, 0x1A, 0x1B, 0x1D, 0x1E, 0x1F, 0x21, 0x22, 0x23, 0x23, 0x24, 0x25, 
    0x26, 0x26, 0x27, 0x27, 0x28, 0x29, 0x29, 0x2A, 0x2A, 0x2A, 0x2B, 0x2B, 0x2C, 0x2C, 0x2C, 0x2D, 
    0x2D, 0x2E, 0x2E, 0x2E, 0x2E, 0x2F, 0x2F, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 
    0x32, 0x32, 0x32, 0x32, 0x33, 0x33, 0x33, 0x33, 0x33, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x35, 
    0x35, 0x35, 0x35, 0x35, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 
    0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 
    0x3B, 0x3B, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 
    }
    
};

static HI_MPP_ISP_CMOS_DEMOSAIC_S g_stIspDemosaic =
{
    /* bvalid */
    1,
    
    /*vh_slope*/
    0xac,

    /*aa_slope*/
    0xa3,

    /*va_slope*/
    0xa0,

    /*uu_slope*/
    //0x5a,
    140,

    /*sat_slope*/
    0x5d,

    /*ac_slope*/
    0xa0,
    
    /*fc_slope*/
    0x80,

    /*vh_thresh*/
    0x0,

    /*aa_thresh*/
    0x00,

    /*va_thresh*/
    0x00,

    /*uu_thresh*/
    0x08,

    /*sat_thresh*/
    0x00,

    /*ac_thresh*/
    0x1b3
};    

static HI_MPP_ISP_CMOS_GAMMA_S g_stIspGamma =
{
    /* bvalid */
    1,

#if 0
    {
        0, 180, 320, 426, 516, 590, 660, 730, 786, 844, 896, 946, 994, 1040, 1090, 1130, 1170, 1210, 1248,
        1296, 1336, 1372, 1416, 1452, 1486, 1516, 1546, 1580, 1616, 1652, 1678, 1714, 1742, 1776, 1798, 1830,
        1862, 1886, 1912, 1940, 1968, 1992, 2010, 2038, 2062, 2090, 2114, 2134, 2158, 2178, 2202, 2222, 2246,
        2266, 2282, 2300, 2324, 2344, 2360, 2372, 2390, 2406, 2422, 2438, 2458, 2478, 2494, 2510, 2526, 2546,
        2562, 2582, 2598, 2614, 2630, 2648, 2660, 2670, 2682, 2698, 2710, 2724, 2736, 2752, 2764, 2780, 2792,
        2808, 2820, 2836, 2848, 2864, 2876, 2888, 2896, 2908, 2920, 2928, 2940, 2948, 2960, 2972, 2984, 2992,
        3004, 3014, 3028, 3036, 3048, 3056, 3068, 3080, 3088, 3100, 3110, 3120, 3128, 3140, 3148, 3160, 3168,
        3174, 3182, 3190, 3202, 3210, 3218, 3228, 3240, 3256, 3266, 3276, 3288, 3300, 3306, 3318, 3326, 3334,
        3342, 3350, 3360, 3370, 3378, 3386, 3394, 3398, 3406, 3414, 3422, 3426, 3436, 3444, 3454, 3466, 3476,
        3486, 3498, 3502, 3510, 3518, 3526, 3530, 3538, 3546, 3554, 3558, 3564, 3570, 3574, 3582, 3590, 3598,
        3604, 3610, 3618, 3628, 3634, 3640, 3644, 3652, 3656, 3664, 3670, 3678, 3688, 3696, 3700, 3708, 3712,
        3716, 3722, 3730, 3736, 3740, 3748, 3752, 3756, 3760, 3766, 3774, 3778, 3786, 3790, 3800, 3808, 3812,
        3816, 3824, 3830, 3832, 3842, 3846, 3850, 3854, 3858, 3862, 3864, 3870, 3874, 3878, 3882, 3888, 3894,
        3900, 3908, 3912, 3918, 3924, 3928, 3934, 3940, 3946, 3952, 3958, 3966, 3974, 3978, 3982, 3986, 3990,
        3994, 4002, 4006, 4010, 4018, 4022, 4032, 4038, 4046, 4050, 4056, 4062, 4072, 4076, 4084, 4090, 4095
    }
#else
/*
{0,   20 ,  68 ,  116 , 164 , 212 , 260 , 308 , 356 , 403 , 451 , 498 ,545 ,  591 , 638 ,684 , 730 ,  775 ,820 ,864 ,908 ,952 ,
 995 ,1038 ,1080 ,1121 ,1162 ,1203 ,1243 ,1283 ,1321 ,1360 ,1397 ,1435 ,1471 ,1507 ,1542 ,1577 ,1611 ,1645 ,
 1678 ,1710 ,1742 ,1773 ,1803 ,1833 ,1862 ,1891 ,1919 ,1947 ,1974 ,2000 ,2026 ,2051 ,2076 ,2100 ,2123 ,2146 ,
 2169 ,2191 ,2212 ,2233 ,2253 ,2273 ,2293 ,2312 ,2330 ,2348 ,2366 ,2383 ,2400 ,2416 ,2432 ,2448 ,2463 ,2478 ,
 2493 ,2507 ,2521 ,2534 ,2547 ,2560 ,2573 ,2585 ,2597 ,2609 ,2620 ,2632 ,2643 ,2654 ,2664 ,2675 ,2685 ,2695 ,
 2705 ,2715 ,2724 ,2734 ,2743 ,2752 ,2761 ,2770 ,2779 ,2788 ,2797 ,2805 ,2814 ,2822 ,2831 ,2839 ,2847 ,2856 ,
 2864 ,2872 ,2880 ,2889 ,2897 ,2905 ,2913 ,2921 ,2930 ,2938 ,2946 ,2954 ,2962 ,2971 ,2979 ,2987 ,2996 ,3004 ,
 3012 ,3021 ,3029 ,3037 ,3046 ,3054 ,3063 ,3071 ,3080 ,3089 ,3097 ,3106 ,3114 ,3123 ,3132 ,3140 ,3149 ,3158 ,
 3166 ,3175 ,3184 ,3192 ,3201 ,3209 ,3218 ,3226 ,3235 ,3243 ,3252 ,3260 ,3268 ,3277 ,3285 ,3293 ,3301 ,3309 ,
 3317 ,3324 ,3332 ,3340 ,3347 ,3354 ,3362 ,3369 ,3376 ,3382 ,3389 ,3396 ,3402 ,3408 ,3414 ,3420 ,3426 ,3435 ,
 3444 ,3453 ,3462 ,3472 ,3481 ,3490 ,3499 ,3508 ,3517 ,3527 ,3536 ,3545 ,3554 ,3563 ,3573 ,3582 ,3591 ,3600 ,
 3609 ,3618 ,3628 ,3637 ,3646 ,3655 ,3664 ,3674 ,3683 ,3692 ,3701 ,3710 ,3720 ,3729 ,3738 ,3747 ,3756 ,3765 ,
 3775 ,3784 ,3793 ,3802 ,3811 ,3821 ,3830 ,3839 ,3848 ,3857 ,3866 ,3876 ,3885 ,3894 ,3903 ,3912 ,3922 ,3931 ,
 3940 ,3949 ,3958 ,3967 ,3977 ,3986 ,3995 ,4004 ,4013 ,4023 ,4032 ,4041 ,4050 ,4059 ,4068 ,4078 ,4087 ,4094 ,
 4095 }*/
{
    0,76,151,224,281,335,425,465,509,559,612,668,725,783,842,899,954,988,1023,1058,1093,
                1128,1164,1200,1235,1271,1306,1340,1374,1408,1440,1472,1503,1533,1562,1591,1620,1648,
                1675,1702,1728,1755,1780,1805,1830,1855,1879,1902,1925,1948,1970,1992,2014,2035,2056,
                2077,2097,2116,2136,2155,2174,2192,2210,2228,2246,2263,2280,2296,2313,2329,2344,2360,
                2375,2390,2405,2420,2434,2448,2462,2475,2489,2502,2515,2528,2541,2553,2566,2578,2590,
                2602,2614,2625,2637,2648,2659,2670,2681,2692,2703,2714,2724,2735,2745,2756,2766,2776,
                2786,2796,2806,2816,2826,2836,2846,2856,2865,2875,2885,2894,2904,2914,2923,2933,2942,
                2952,2961,2971,2980,2990,2999,3009,3018,3028,3037,3046,3056,3065,3074,3084,3093,3103,
                3112,3121,3130,3140,3149,3158,3168,3177,3186,3195,3204,3214,3223,3232,3241,3250,3259,
                3268,3277,3285,3294,3303,3312,3320,3329,3338,3346,3355,3363,3371,3380,3388,3396,3404,
                3412,3420,3427,3435,3443,3450,3458,3465,3472,3481,3490,3499,3508,3517,3525,3534,3543,
                3552,3561,3570,3578,3587,3596,3605,3613,3622,3631,3640,3648,3657,3666,3674,3683,3692,
                3700,3709,3718,3726,3735,3743,3752,3761,3769,3778,3786,3795,3803,3812,3820,3829,3837,
                3846,3854,3863,3871,3879,3888,3896,3905,3913,3921,3930,3938,3947,3955,3963,3972,3980,
                3988,3996,4005,4013,4021,4030,4038,4046,4054,4063,4071,4079,4087,4094,4095
}

#endif
};

static HI_U32 cmos_get_isp_default(ISP_ID IspId,HI_MPP_ISP_CMOS_DEFAULT_S *pstDef)
{
    if (HI_NULL == pstDef)
    {
        printf("null pointer when get isp default value!\n");
        return -1;
    }

    memset(pstDef, 0, sizeof(HI_MPP_ISP_CMOS_DEFAULT_S));

    switch (g_apstSnsState[IspId]->enWDRMode)
    {
        default:
        case HI_MPP_WDR_MODE_NONE:
            pstDef->stDrc.bEnable               = HI_FALSE;
            pstDef->stDrc.u32BlackLevel         = 0x00;
            pstDef->stDrc.u32WhiteLevel         = 0xD0000; 
            pstDef->stDrc.u32SlopeMax           = 0x30;
            pstDef->stDrc.u32SlopeMin           = 0x00;
            pstDef->stDrc.u32VarianceSpace      = 0x04;
            pstDef->stDrc.u32VarianceIntensity  = 0x01;
            pstDef->stDrc.u32Asymmetry          = 0x08;
            pstDef->stDrc.u32BrightEnhance      = 0xE6;
            pstDef->stDrc.bFilterMux            = 0x1;
            pstDef->stDrc.u32Svariance          = 0x8;
            pstDef->stDrc.u32BrightPr           = 0xB0;
            pstDef->stDrc.u32Contrast           = 0xB0;
            pstDef->stDrc.u32DarkEnhance        = 0x8000;
            
            memcpy(&pstDef->stAgcTbl, &g_stIspAgcTable, sizeof(HI_MPP_ISP_CMOS_AGC_TABLE_S));
            memcpy(&pstDef->stNoiseTbl, &g_stIspNoiseTable, sizeof(HI_MPP_ISP_CMOS_NOISE_TABLE_S));            
            memcpy(&pstDef->stDemosaic, &g_stIspDemosaic, sizeof(HI_MPP_ISP_CMOS_DEMOSAIC_S));
            memcpy(&pstDef->stGamma, &g_stIspGamma, sizeof(HI_MPP_ISP_CMOS_GAMMA_S));
            memcpy(&pstDef->stBayerSharpen, &g_stIspBayerSharpen, sizeof(HI_MPP_ISP_CMOS_BAYER_SHARPEN_S));
            memcpy(&pstDef->stYuvSharpen, &g_stIspYuvSharpen, sizeof(HI_MPP_ISP_CMOS_YUV_SHARPEN_S));
        break;
    }

    pstDef->stSensorMaxResolution.u32MaxWidth  = 4096;
    pstDef->stSensorMaxResolution.u32MaxHeight = 3000;

    return 0;
}


static HI_U32 cmos_get_isp_black_level(ISP_ID IspId,HI_MPP_ISP_CMOS_BLACK_LEVEL_S *pstBlackLevel)
{
    HI_S32  i;
    
    if (HI_NULL == pstBlackLevel)
    {
        printf("null pointer when get isp black level value!\n");
        return -1;
    }

    /* Don't need to update black level when iso change */
    pstBlackLevel->bUpdate = HI_FALSE;

    for (i=0; i<4; i++)
    {
        pstBlackLevel->au16BlackLevel[i] = 0xc8;/*10bit : 0x3c*/
    }

    return 0;    
}

static HI_VOID cmos_set_pixel_detect(ISP_ID IspId,HI_BOOL bEnable)
{
    /* Detect set 5fps */
    CHECK_RET(HI_MAPI_ISP_GetHvSync(IspId, &gstImx117Sync[IspId]));
    
    if (bEnable)
    {
        switch(g_apstSnsState[IspId]->u8ImgMode) 
        {
            case IMX117_MODE0:
                gstImx117Sync[IspId].u32VsTime = (g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32InckPerVs) * 30/5;
                imx117_write_register (IspId,IMX117_APGC01_L, 0x3D);                 
                imx117_write_register (IspId,IMX117_APGC01_H, 0x0);
                imx117_write_register (IspId,IMX117_APGC02_L, 0x3C);                 
                imx117_write_register (IspId,IMX117_APGC02_H, 0x0); 
                break;
            case IMX117_MODE1:
                gstImx117Sync[IspId].u32VsTime = (g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32InckPerVs) * 6;
                imx117_write_register (IspId,IMX117_APGC01_L, 0x3D);                 
                imx117_write_register (IspId,IMX117_APGC01_H, 0x0);
                imx117_write_register (IspId,IMX117_APGC02_L, 0x3C);                 
                imx117_write_register (IspId,IMX117_APGC02_H, 0x0);
                break;            
            case IMX117_MODE2:
                gstImx117Sync[IspId].u32VsTime = (g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32InckPerVs) * 6;
                imx117_write_register (IspId,IMX117_APGC01_L, 0x1F);                 
                imx117_write_register (IspId,IMX117_APGC01_H, 0x0);
                imx117_write_register (IspId,IMX117_APGC02_L, 0x1E);                 
                imx117_write_register (IspId,IMX117_APGC02_H, 0x0);
                break;  
            default:
            	printf("NOT support this mode for PixDetect!\n");
            	break;
        } 
        
        /* Analog and Digital gains both must be programmed for their minimum values */
        imx117_write_register (IspId,IMX117_PGC_L, 0x0);                 
        imx117_write_register (IspId,IMX117_PGC_H, 0x0);      
    }
    else /* setup for ISP 'normal mode' */
    {
        gstImx117Sync[IspId].u32VsTime = (g_astImx117ModeTbl[g_apstSnsState[IspId]->u8ImgMode].u32InckPerVs);
        g_apstSnsState[IspId]->bSyncInit= HI_FALSE;
    }
    
    CHECK_RET(HI_MPI_ISP_SetHvSync(IspId, &gstImx117Sync[IspId]));

    return;
}

static HI_VOID cmos_set_wdr_mode(ISP_ID IspId,HI_U8 u8Mode)
{
    g_apstSnsState[IspId]->bSyncInit = HI_FALSE;
    
    switch(u8Mode)
    {
        case HI_MPP_WDR_MODE_NONE:
            g_apstSnsState[IspId]->u32FLStd = 2400+IMX117_FULL_LINES_STD_FPGA_COMP;
            g_apstSnsState[IspId]->enWDRMode = HI_MPP_WDR_MODE_NONE;
            printf("linear mode\n");
        break;
        
        default:
            printf("[%s]:[%d] NOT support this mode!\n", __FUNCTION__, __LINE__);
            return;
        break;
    }
    return;
}

static HI_U32 cmos_get_sns_regs_info(ISP_ID IspId,HI_MPP_ISP_SNS_REGS_INFO_S *pstSnsRegsInfo)
{
    HI_S32 i;

    if (HI_NULL == pstSnsRegsInfo)
    {
        printf("null pointer when get sns reg info!\n");
        return -1;
    }
    if ((HI_FALSE == g_apstSnsState[IspId]->bSyncInit) || (HI_FALSE == pstSnsRegsInfo->bConfig))
    {
        g_apstSnsState[IspId]->astRegsInfo[0].enSnsType = HI_MPP_ISP_SNS_SSP_TYPE;
        g_apstSnsState[IspId]->astRegsInfo[0].unComBus.s8SspDev.bit4SspDev = g_aunImx117BusInfo[IspId].s8SspDev.bit4SspDev;        
        g_apstSnsState[IspId]->astRegsInfo[0].unComBus.s8SspDev.bit4SspCs = g_aunImx117BusInfo[IspId].s8SspDev.bit4SspCs;
        g_apstSnsState[IspId]->astRegsInfo[0].u8Cfg2ValidDelayMax = 2;        
        g_apstSnsState[IspId]->astRegsInfo[0].u32RegNum = 11;        

        for (i=0; i<g_apstSnsState[IspId]->astRegsInfo[0].u32RegNum; i++)
        {
            g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].bUpdate = HI_TRUE;
            g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].u32DevAddr = 0x81;
            g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].u32DevAddrByteNum = 1;
            g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].u32RegAddrByteNum = 2;
            g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].u32DataByteNum = 1;
        }        
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[0].u8DelayFrmNum = 0;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[0].u32RegAddr = IMX117_SHR_L;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[1].u8DelayFrmNum = 0;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[1].u32RegAddr = IMX117_SHR_H;

        // gain related
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[2].u32RegAddr = IMX117_PGC_L;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[2].u8DelayFrmNum = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[3].u32RegAddr = IMX117_PGC_H;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[3].u8DelayFrmNum = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[4].u32RegAddr = IMX117_APGC01_L;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[4].u8DelayFrmNum = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[5].u32RegAddr = IMX117_APGC01_H;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[5].u8DelayFrmNum = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[6].u32RegAddr = IMX117_APGC02_L;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[6].u8DelayFrmNum = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[7].u32RegAddr = IMX117_APGC02_H;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[7].u8DelayFrmNum = 1;
        
        //svr registers
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[8].u32RegAddr = IMX117_SVR_L;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[8].u32Data = 0;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[8].u8DelayFrmNum = 0;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[9].u32RegAddr = IMX117_SVR_H;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[9].u8DelayFrmNum = 0;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[9].u32Data = 0;
        
        /* Dgain cfg */
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[10].u32RegAddr = IMX117_DGAIN;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[10].u8DelayFrmNum = 1;        

        /* Slave Sensor VsTime cfg */
        g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.bUpdate = HI_TRUE;
        g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.u8DelayFrmNum = 1;

        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[2].u8IntPos = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[3].u8IntPos = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[4].u8IntPos = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[5].u8IntPos = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[6].u8IntPos = 1;
        g_apstSnsState[IspId]->astRegsInfo[0].astSspData[7].u8IntPos = 1;
        
        g_apstSnsState[IspId]->bSyncInit = HI_TRUE;
    }
    else
    {
        for (i=0; i<g_apstSnsState[IspId]->astRegsInfo[0].u32RegNum; i++)
        {
            if (g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].u32Data == g_apstSnsState[IspId]->astRegsInfo[1].astSspData[i].u32Data)
            {
                g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].bUpdate = HI_FALSE;
            }
            else
            {
                g_apstSnsState[IspId]->astRegsInfo[0].astSspData[i].bUpdate = HI_TRUE;
            }
        }

        if (g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.u32SlaveVsTime == g_apstSnsState[IspId]->astRegsInfo[1].stSlvSync.u32SlaveVsTime)
        {
            g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.bUpdate = HI_FALSE;
        }
        else
        {
            g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.bUpdate = HI_TRUE;
        }        
    }

//	printf("imx117 u32SlaveVsTime %d\n", g_apstSnsState[IspId]->astRegsInfo[0].stSlvSync.u32SlaveVsTime);
    pstSnsRegsInfo->bConfig = HI_FALSE;

    memcpy(pstSnsRegsInfo, &g_apstSnsState[IspId]->astRegsInfo[0],sizeof(HI_MPP_ISP_SNS_REGS_INFO_S)); 
    memcpy(&g_apstSnsState[IspId]->astRegsInfo[1], &g_apstSnsState[IspId]->astRegsInfo[0], sizeof(HI_MPP_ISP_SNS_REGS_INFO_S)); 

    return 0;
}

static HI_S32 cmos_set_image_mode(ISP_ID IspId,HI_MPP_ISP_CMOS_SENSOR_IMAGE_MODE_S *pstSensorImageMode)
{
    HI_U8 u8SensorImageMode = g_apstSnsState[IspId]->u8ImgMode;
    HI_U32 u32W, u32H;
    
    g_apstSnsState[IspId]->bSyncInit= HI_FALSE;    

        
    if (HI_NULL == pstSensorImageMode )
    {
        printf("null pointer when set image mode\n");
        return -1;
    }

    u32H = pstSensorImageMode->u16Height;
    u32W = pstSensorImageMode->u16Width;
  
    if (IMX117_RES_IS_4K(u32W, u32H) || IMX117_RES_IS_4K2K(u32W, u32H))
    {
        u8SensorImageMode = IMX117_MODE0;
    }
    else if (IMX117_RES_IS_12M(u32W, u32H))
    {
        u8SensorImageMode = IMX117_MODE0A;
    } 
    else if (IMX117_RES_IS_1080P(u32W, u32H))
    {
        u8SensorImageMode = IMX117_MODE11A;
    }
    else if ( IMX117_RES_IS_720P(u32W, u32H))
    {
        u8SensorImageMode = IMX117_MODE1D;//IMX117_MODE4A;          // mode4a: wide fov, mode1d: narrow fov, a sensor crop mode
    }
    else
    {
        u8SensorImageMode = IMX117_MODE0;
        return -1;
    }

    /* Sensor first init */
    if (HI_FALSE == g_apstSnsState[IspId]->bInit)
    {
        g_apstSnsState[IspId]->u8ImgMode = u8SensorImageMode;
        
        return 0;
    }

    /* Switch SensorImageMode */
    
    if (u8SensorImageMode == g_apstSnsState[IspId]->u8ImgMode)
    {
        /* Don't need to switch SensorImageMode */
        return -1;
    }
    
    g_apstSnsState[IspId]->u8ImgMode = u8SensorImageMode;

    return 0;
}

static HI_VOID sensor_global_init(ISP_ID IspId)
{
    g_apstSnsState[IspId]->enWDRMode = HI_MPP_WDR_MODE_NONE;
    g_apstSnsState[IspId]->bInit = HI_FALSE;
    g_apstSnsState[IspId]->bSyncInit= HI_FALSE;

    g_apstSnsState[IspId]->u32FLStd= 2400+IMX117_FULL_LINES_STD_FPGA_COMP;
    g_apstSnsState[IspId]->u8ImgMode = IMX117_MODE0;
    
    memset(&g_apstSnsState[IspId]->astRegsInfo[0], 0, sizeof(HI_MPP_ISP_SNS_REGS_INFO_S));
    memset(&g_apstSnsState[IspId]->astRegsInfo[1], 0, sizeof(HI_MPP_ISP_SNS_REGS_INFO_S));
}

static HI_S32 cmos_init_sensor_exp_function(HI_MPP_ISP_SENSOR_EXP_FUNC_S *pstSensorExpFunc)
{
    memset(pstSensorExpFunc, 0, sizeof(HI_MPP_ISP_SENSOR_EXP_FUNC_S));

    pstSensorExpFunc->pfn_cmos_sensor_init                  = imx117_init;
    pstSensorExpFunc->pfn_cmos_sensor_exit                  = imx117_exit;
    pstSensorExpFunc->pfn_cmos_sensor_global_init           = sensor_global_init;
    pstSensorExpFunc->pfn_cmos_set_image_mode               = cmos_set_image_mode;
    pstSensorExpFunc->pfn_cmos_set_wdr_mode                 = cmos_set_wdr_mode;
    pstSensorExpFunc->pfn_cmos_get_isp_default              = cmos_get_isp_default;
    pstSensorExpFunc->pfn_cmos_get_isp_black_level          = cmos_get_isp_black_level;
    pstSensorExpFunc->pfn_cmos_set_pixel_detect             = cmos_set_pixel_detect;
    pstSensorExpFunc->pfn_cmos_get_sns_reg_info             = cmos_get_sns_regs_info;

    return 0;
}

static int imx117_set_bus_info(ISP_ID IspId, HI_MPP_ISP_SNS_COMMBUS_U unSNSBusInfo)
{
    g_aunImx117BusInfo[IspId].s8SspDev.bit4SspDev = unSNSBusInfo.s8SspDev.bit4SspDev;
    g_aunImx117BusInfo[IspId].s8SspDev.bit4SspCs  = unSNSBusInfo.s8SspDev.bit4SspCs;

    return 0;
}

/****************************************************************************
 * callback structure                                                       *
 ****************************************************************************/

static int sensor_register_callback(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib)
{
    HI_S32 s32Ret;
    HI_MPP_ISP_SENSOR_REGISTER_S stIspRegister;
    HI_MPP_AE_SENSOR_REGISTER_S  stAeRegister;
    HI_MPP_AWB_SENSOR_REGISTER_S stAwbRegister;

    cmos_init_sensor_exp_function(&stIspRegister.stSnsExp);
    s32Ret = HI_MAPI_ISP_SensorRegCallBack(IspId, IMX117_ID, &stIspRegister);
    if (s32Ret)
    {
        printf("sensor register callback function failed!\n");
        return s32Ret;
    }
    
    cmos_init_ae_exp_function(&stAeRegister.stSnsExp);
    s32Ret = HI_MAPI_AE_SensorRegCallBack(IspId, pstAeLib, IMX117_ID, &stAeRegister);
    if (s32Ret)
    {
        printf("sensor register callback function to ae lib failed!\n");
        return s32Ret;
    }

    cmos_init_awb_exp_function(&stAwbRegister.stSnsExp);
    s32Ret = HI_MAPI_AWB_SensorRegCallBack(IspId, pstAwbLib, IMX117_ID, &stAwbRegister);
    if (s32Ret)
    {
        printf("sensor register callback function to awb lib failed!\n");
        return s32Ret;
    }
    
    return 0;
}

static int sensor_unregister_callback(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib)
{
    HI_S32 s32Ret;

    s32Ret = HI_MAPI_ISP_SensorUnRegCallBack(IspId, IMX117_ID);
    if (s32Ret)
    {
        printf("sensor unregister callback function failed!\n");
        return s32Ret;
    }
    
    s32Ret = HI_MAPI_AE_SensorUnRegCallBack(IspId, pstAeLib, IMX117_ID);
    if (s32Ret)
    {
        printf("sensor unregister callback function to ae lib failed!\n");
        return s32Ret;
    }

    s32Ret = HI_MAPI_AWB_SensorUnRegCallBack(IspId, pstAwbLib, IMX117_ID);
    if (s32Ret)
    {
        printf("sensor unregister callback function to awb lib failed!\n");
        return s32Ret;
    }
    
    return 0;
}

ISP_SNS_OBJ_S stSnsImx117Obj = 
{
    .pfnRegisterCallback    = sensor_register_callback,
    .pfnUnRegisterCallback  = sensor_unregister_callback,
    .pfnStandby             = imx117_standby,
    .pfnRestart             = imx117_restart,
    .pfnWriteReg            = imx117_write_register,
    .pfnReadReg             = imx117_read_register,
    .pfnSetBusInfo          = imx117_set_bus_info
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif 


