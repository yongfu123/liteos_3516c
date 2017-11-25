#if !defined(__OV9732_CMOS_H_)
#define __OV9732_CMOS_H_

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
#include "hi_mapi_sns_ctrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define HI_AE_LIB_NAME "hisi_ae_lib"
#define HI_AWB_LIB_NAME "hisi_awb_lib"
#define HI_AF_LIB_NAME "hisi_af_lib"

#define OV9732_ID 9732

#ifdef INIFILE_CONFIG_MODE

extern HI_MPP_AE_SENSOR_DEFAULT_S  g_AeDft[];
extern HI_MPP_AWB_SENSOR_DEFAULT_S g_AwbDft[];
extern HI_MPP_ISP_CMOS_DEFAULT_S   g_IspDft[];
extern HI_S32 Cmos_LoadINIPara(const HI_CHAR *pcName);
#else

#endif


/****************************************************************************
 * local variables                                                            *
 ****************************************************************************/

extern const unsigned int sensor_i2c_addr;
extern unsigned int sensor_addr_byte;
extern unsigned int sensor_data_byte;

#define SENSOR_720P_30FPS_MODE (1)

#define VMAX_OV9732_720P30_LINEAR     (812)
#define FULL_LINES_MAX  (0xFFFF)


HI_U8 gu8SensorImageMode = SENSOR_720P_30FPS_MODE;
HI_MPP_WDR_MODE_E genSensorMode = HI_MPP_WDR_MODE_NONE;

static HI_U32 gu32FullLinesStd = VMAX_OV9732_720P30_LINEAR;
static HI_U32 gu32FullLines = VMAX_OV9732_720P30_LINEAR;

static HI_BOOL bInit = HI_FALSE;
HI_BOOL bSensorInit = HI_FALSE;
HI_MPP_ISP_SNS_REGS_INFO_S g_stSnsRegsInfo = {0};
HI_MPP_ISP_SNS_REGS_INFO_S g_stPreSnsRegsInfo = {0};

/* Piris attr */
static HI_MPP_ISP_PIRIS_ATTR_S gstPirisAttr=
{
    0,      // bStepFNOTableChange
    1,      // bZeroIsMax
    94,     // u16TotalStep
    62,     // u16StepCount
    /* Step-F number mapping table. Must be from small to large. F1.0 is 1024 and F32.0 is 1 */
    {30,35,40,45,50,56,61,67,73,79,85,92,98,105,112,120,127,135,143,150,158,166,174,183,191,200,208,217,225,234,243,252,261,270,279,289,298,307,316,325,335,344,353,362,372,381,390,399,408,417,426,435,444,453,462,470,478,486,493,500,506,512},
    HI_MPP_ISP_IRIS_F_NO_1_4, // enMaxIrisFNOTarget
    HI_MPP_ISP_IRIS_F_NO_5_6  // enMinIrisFNOTarget
};


#define PATHLEN_MAX 256
#define CMOS_CFG_INI "ov9732_cfg.ini"
static char pcName[PATHLEN_MAX] = "configs/ov9732_cfg.ini";


/* AE default parameter and function */
static HI_S32 cmos_get_ae_default(ISP_ID IspId,HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft)
{
    if (HI_NULL == pstAeSnsDft)
    {
        printf("null pointer when get ae default value!\n");
        return -1;
    }

    pstAeSnsDft->u32LinesPer500ms = VMAX_OV9732_720P30_LINEAR * 30 / 2;
    pstAeSnsDft->u32FullLinesStd = gu32FullLinesStd;
    pstAeSnsDft->u32FlickerFreq = 0;

    pstAeSnsDft->au8HistThresh[0] = 0xd;
    pstAeSnsDft->au8HistThresh[1] = 0x28;
    pstAeSnsDft->au8HistThresh[2] = 0x60;
    pstAeSnsDft->au8HistThresh[3] = 0x80;
            
    pstAeSnsDft->u8AeCompensation = 0x38;

    pstAeSnsDft->stIntTimeAccu.enAccuType = HI_MPP_AE_ACCURACY_LINEAR;
    pstAeSnsDft->stIntTimeAccu.f32Accuracy = 1;
    pstAeSnsDft->stIntTimeAccu.f32Offset = 0;
    pstAeSnsDft->u32MaxIntTime = gu32FullLinesStd - 4;
    pstAeSnsDft->u32MinIntTime = 4;
    pstAeSnsDft->u32MaxIntTimeTarget = 65535;
    pstAeSnsDft->u32MinIntTimeTarget = 2;


    pstAeSnsDft->stAgainAccu.enAccuType = HI_MPP_AE_ACCURACY_TABLE;
    pstAeSnsDft->stAgainAccu.f32Accuracy = 1;
    pstAeSnsDft->u32MaxAgain = 16229;
    pstAeSnsDft->u32MinAgain = 1024;
    pstAeSnsDft->u32MaxAgainTarget = pstAeSnsDft->u32MaxAgain;
    pstAeSnsDft->u32MinAgainTarget = pstAeSnsDft->u32MinAgain;
        


    pstAeSnsDft->stDgainAccu.enAccuType = HI_MPP_AE_ACCURACY_LINEAR;
    pstAeSnsDft->stDgainAccu.f32Accuracy = 1.0/256;
    pstAeSnsDft->u32MaxDgain = 256;
    pstAeSnsDft->u32MinDgain = 256;
    pstAeSnsDft->u32MaxDgainTarget = 256;  
    pstAeSnsDft->u32MinDgainTarget = 256; 
    

    
    pstAeSnsDft->u32ISPDgainShift = 8;
    pstAeSnsDft->u32MinISPDgainTarget = 1 << pstAeSnsDft->u32ISPDgainShift;
    pstAeSnsDft->u32MaxISPDgainTarget = 16 << pstAeSnsDft->u32ISPDgainShift;


	
    pstAeSnsDft->u32LinesPer500ms = gu32FullLinesStd*30/2;

    pstAeSnsDft->enIrisType = HI_MPP_ISP_IRIS_DC_TYPE;
    memcpy(&pstAeSnsDft->stPirisAttr, &gstPirisAttr, sizeof(HI_MPP_ISP_PIRIS_ATTR_S));
    pstAeSnsDft->enMaxIrisFNO = HI_MPP_ISP_IRIS_F_NO_1_4;
    pstAeSnsDft->enMinIrisFNO = HI_MPP_ISP_IRIS_F_NO_5_6;

    /*For some OV sensors, AERunInterval needs to be set more than 1*/
    pstAeSnsDft->u8AERunInterval = 2;
    
    return 0;
}

/* the function of sensor set fps */
static HI_VOID cmos_fps_set(ISP_ID IspId,HI_FLOAT f32Fps, HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft)
{
    if ((f32Fps <= 30) && (f32Fps >= 0.5))
    {
        if(SENSOR_720P_30FPS_MODE == gu8SensorImageMode)
        {
            gu32FullLinesStd = VMAX_OV9732_720P30_LINEAR * 30 / f32Fps;

            g_stSnsRegsInfo.astI2cData[10].u32Data = (gu32FullLinesStd >> 8) & 0xff;
            g_stSnsRegsInfo.astI2cData[11].u32Data = gu32FullLinesStd & 0xff;

            pstAeSnsDft->f32Fps = f32Fps;
            pstAeSnsDft->u32MaxIntTime = gu32FullLinesStd - 4;
            pstAeSnsDft->u32FullLinesStd = gu32FullLinesStd;
            pstAeSnsDft->u32LinesPer500ms = gu32FullLinesStd * f32Fps/2;
            gu32FullLines = gu32FullLinesStd;
            pstAeSnsDft->u32FullLines = gu32FullLines;
        }
    }
    else
    {
        printf("Not support Fps: %f\n", f32Fps);
        return;
    }
  
    return;
}

static HI_VOID cmos_slow_framerate_set(HI_U32 u32FullLines,
    HI_MPP_AE_SENSOR_DEFAULT_S *pstAeSnsDft)
{
    u32FullLines = (u32FullLines > FULL_LINES_MAX) ? FULL_LINES_MAX : u32FullLines;

    gu32FullLines = u32FullLines;
    
    g_stSnsRegsInfo.astI2cData[10].u32Data = (gu32FullLines >> 8) & 0xff;
    g_stSnsRegsInfo.astI2cData[11].u32Data = gu32FullLines & 0xff;

    pstAeSnsDft->u32FullLines = gu32FullLines;
    pstAeSnsDft->u32MaxIntTime = gu32FullLines - 4;
    
    return;
}

/* while isp notify ae to update sensor regs, ae call these funcs. */
static HI_VOID cmos_inttime_update(ISP_ID IspId,HI_U32 u32IntTime)
{


    g_stSnsRegsInfo.astI2cData[0].u32Data = (u32IntTime >> 12) & 0xF;
    g_stSnsRegsInfo.astI2cData[1].u32Data = (u32IntTime >> 4) & 0xFF;
    g_stSnsRegsInfo.astI2cData[2].u32Data = (u32IntTime & 0xF) << 4;

	
    return;
}

static HI_U32 analog_gain_table[64] =
{
    1024, 1088, 1152, 1216, 1280, 1344, 1408, 1472, 1536, 1600, 1664, 1728, 1792, 1856, 1920, 1984, 2048,
    2176, 2304, 2432, 2560, 2688, 2816, 2944, 3072, 3200, 3328, 3456, 3584, 3712, 3840, 3968, 4096, 4352,
    4608, 4864, 5120, 5376, 5632, 5888, 6144, 6400, 6656, 6912, 7168, 7424, 7680, 7936, 8192, 8704, 9216,
    9728, 10240, 10752, 11264, 11776, 12288, 12800, 13312, 13824, 14336, 14848, 15360, 15872
};

static HI_U32 analog_gain_reg_table[64] =
{     
    0x010, 0x011, 0x012, 0x013, 0x014, 0x015, 0x016, 0x017, 0x018, 0x019, 0x01A, 0x01B, 0x01C, 0x01D,
    0x01E, 0x01F, 0x020, 0x022, 0x024, 0x026, 0x028, 0x02A, 0x02C, 0x02E, 0x030, 0x032, 0x034, 0x036,
    0x038, 0x03A, 0x03C, 0x03E, 0x040, 0x044, 0x048, 0x04C, 0x050, 0x054, 0x058, 0x05C, 0x060, 0x064,
    0x068, 0x06C, 0x070, 0x074, 0x078, 0x07C, 0x080, 0x088, 0x090, 0x098, 0x0A0, 0x0A8, 0x0B0, 0x0B8,
    0x0C0, 0x0C8, 0x0D0, 0x0D8, 0x0E0, 0x0E8, 0x0F0, 0x0F8
};


static HI_VOID cmos_again_calc_table(ISP_ID IspId, HI_U32 *pu32AgainLin, HI_U32 *pu32AgainDb)
{
    int i;

    if (*pu32AgainLin >= analog_gain_table[63])
    {
         *pu32AgainLin = analog_gain_table[63];
         *pu32AgainDb = 63;
         return ;
    }
    
    for (i = 1; i < 64; i++)
    {
        if (*pu32AgainLin < analog_gain_table[i])
        {
            *pu32AgainLin = analog_gain_table[i - 1];
            *pu32AgainDb = i - 1;
            break;
        }
    }

    return;

}

static HI_VOID cmos_gains_update(ISP_ID IspId, HI_U32 u32Again, HI_U32 u32Dgain)
{  
    g_stSnsRegsInfo.astI2cData[3].u32Data = analog_gain_reg_table[u32Again];

    g_stSnsRegsInfo.astI2cData[4].u32Data = (u32Dgain >> 8 ) & 0xF;
    g_stSnsRegsInfo.astI2cData[5].u32Data = u32Dgain & 0xFF;
    g_stSnsRegsInfo.astI2cData[6].u32Data = g_stSnsRegsInfo.astI2cData[4].u32Data;
    g_stSnsRegsInfo.astI2cData[7].u32Data = g_stSnsRegsInfo.astI2cData[5].u32Data ;
    g_stSnsRegsInfo.astI2cData[8].u32Data = g_stSnsRegsInfo.astI2cData[4].u32Data;
    g_stSnsRegsInfo.astI2cData[9].u32Data = g_stSnsRegsInfo.astI2cData[5].u32Data;

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
    pstExpFuncs->pfn_cmos_dgain_calc_table  = NULL;

    return 0;
}


/* AWB default parameter and function */
static HI_MPP_AWB_CCM_S g_stAwbCcm =
{  
#if 0
    5120,    
    {       
        0x01c8,  0x809b,  0x802d,
        0x8058,  0x01a3,  0x804b,       
        0x800b,  0x80fb,  0x0206    
    },  
    
    3633,    
    {       
        0x01b7,  0x8083,  0x8034,       
        0x805f,  0x018b,  0x802c,       
        0x8016,  0x812f,  0x0245    
    },
    
    2465,    
    {            
        0x0212,  0x80d6,  0x803c,        
        0x806d,  0x017c,  0x800f,       
        0x8027,  0x8164,  0x028b    
    }
#endif
//#if 1
    5120,    
    {       
        0x0270,  0x812b,  0x8045,
        0x8048,  0x01c5,  0x807d,       
        0x0011,  0x818e,  0x027d    
    },  
    
    3633,    
    {       
        0x01cf,  0x8089,  0x8046,       
        0x8059,  0x018e,  0x8035,       
        0x8016,  0x812f,  0x0245    
    },
    
    2465,    
    {            
        0x0205,  0x80a2,  0x8063,        
        0x8058,  0x0189,  0x8031,       
        0x802e,  0x8175,  0x02a3    
    }
//#endif
};

static HI_MPP_AWB_AGC_TABLE_S g_stAwbAgcTable =
{
    /* bvalid */
    1,\
    {0x80,0x78,0x70,0x68,0x60,0x55,0x4b,0x40,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38}

};

static HI_MPP_ISP_CMOS_DEMOSAIC_S g_stIspDemosaic =
{
    /* bvalid */
    1,
    
    /*vh_slope*/
    0x30,

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
};

static HI_S32 cmos_get_awb_default(ISP_ID IspId,HI_MPP_AWB_SENSOR_DEFAULT_S *pstAwbSnsDft)
{
    if (HI_NULL == pstAwbSnsDft)
    {
        printf("ov9732 null pointer when get awb default value!\n");
        return -1;
    }

    memset(pstAwbSnsDft, 0, sizeof(HI_MPP_AWB_SENSOR_DEFAULT_S));

    pstAwbSnsDft->u16WbRefTemp = 5200;
    pstAwbSnsDft->au16GainOffset[0] = 0x1eb;//0X1C2    
    pstAwbSnsDft->au16GainOffset[1] = 0x100;    
    pstAwbSnsDft->au16GainOffset[2] = 0x100;    
    pstAwbSnsDft->au16GainOffset[3] = 0x18b;//0X1C0    
    pstAwbSnsDft->as32WbPara[0] = 72;    //128
    pstAwbSnsDft->as32WbPara[1] = 75;    //-26
    pstAwbSnsDft->as32WbPara[2] = -109;    //-154
    pstAwbSnsDft->as32WbPara[3] = 216868;    //233501
    pstAwbSnsDft->as32WbPara[4] = 128;    
    pstAwbSnsDft->as32WbPara[5] = -168656; //-184710
    
    memcpy(&pstAwbSnsDft->stCcm, &g_stAwbCcm, sizeof(HI_MPP_AWB_CCM_S));
    memcpy(&pstAwbSnsDft->stAgcTbl, &g_stAwbAgcTable, sizeof(HI_MPP_AWB_AGC_TABLE_S));
    
    return 0;
}

HI_S32 cmos_init_awb_exp_function(HI_MPP_AWB_SENSOR_EXP_FUNC_S *pstExpFuncs)
{
    memset(pstExpFuncs, 0, sizeof(HI_MPP_AWB_SENSOR_EXP_FUNC_S));

    pstExpFuncs->pfn_cmos_get_awb_default = cmos_get_awb_default;

    return 0;
}

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

static HI_U32 cmos_get_isp_default(ISP_ID IspId, HI_MPP_ISP_CMOS_DEFAULT_S *pstDef)
{
    if (HI_NULL == pstDef)
    {
        printf("ov9732 null pointer when get isp default value!\n");
        return -1;
    }
	
    memset(pstDef, 0, sizeof(HI_MPP_ISP_CMOS_DEFAULT_S));

	pstDef->stDrc.bEnable				= HI_FALSE;
    pstDef->stDrc.u32BlackLevel		   = 0x00;
    pstDef->stDrc.u32WhiteLevel		   = 0xD0000; 
    pstDef->stDrc.u32SlopeMax		   = 0x30;
    pstDef->stDrc.u32SlopeMin		   = 0x00;
    pstDef->stDrc.u32VarianceSpace	   = 0x04;
    pstDef->stDrc.u32VarianceIntensity  = 0x01;
    pstDef->stDrc.u32Asymmetry		   = 0x08;
    pstDef->stDrc.u32BrightEnhance	   = 0xE6;
    pstDef->stDrc.bFilterMux 		   = 0x1;
    pstDef->stDrc.u32Svariance		   = 0x8;
    pstDef->stDrc.u32BrightPr		   = 0xB0;
    pstDef->stDrc.u32Contrast		   = 0xB0;
    pstDef->stDrc.u32DarkEnhance 	   = 0x8000;
	
	memcpy(&pstDef->stAgcTbl, &g_stIspAgcTable, sizeof(HI_MPP_ISP_CMOS_AGC_TABLE_S));
	memcpy(&pstDef->stNoiseTbl, &g_stIspNoiseTable, sizeof(HI_MPP_ISP_CMOS_NOISE_TABLE_S)); 		   
	memcpy(&pstDef->stDemosaic, &g_stIspDemosaic, sizeof(HI_MPP_ISP_CMOS_DEMOSAIC_S));
	memcpy(&pstDef->stGamma, &g_stIspGamma, sizeof(HI_MPP_ISP_CMOS_GAMMA_S));
	memcpy(&pstDef->stBayerSharpen, &g_stIspBayerSharpen, sizeof(HI_MPP_ISP_CMOS_BAYER_SHARPEN_S));
	memcpy(&pstDef->stYuvSharpen, &g_stIspYuvSharpen, sizeof(HI_MPP_ISP_CMOS_YUV_SHARPEN_S));

    pstDef->stSensorMaxResolution.u32MaxWidth  = 1280;
    pstDef->stSensorMaxResolution.u32MaxHeight = 720;

    return 0;
}

static HI_U32 cmos_get_isp_black_level(ISP_ID IspId,HI_MPP_ISP_CMOS_BLACK_LEVEL_S *pstBlackLevel)
{
    if (HI_NULL == pstBlackLevel)
    {
        printf("null pointer when get isp black level value!\n");
        return -1;
    }

    /* Don't need to update black level when iso change */
    pstBlackLevel->bUpdate = HI_FALSE;
          
    pstBlackLevel->au16BlackLevel[0] = 64;
    pstBlackLevel->au16BlackLevel[1] = 58;
    pstBlackLevel->au16BlackLevel[2] = 58;
    pstBlackLevel->au16BlackLevel[3] = 64;
    

    return 0;  
    
}

static HI_VOID cmos_set_pixel_detect(ISP_ID IspId,HI_BOOL bEnable)
{
    HI_U32 u32FullLines_5Fps = 0; 
    HI_U32 u32MaxIntTime_5Fps = 0;

    if (SENSOR_720P_30FPS_MODE == gu8SensorImageMode)
    {
        u32FullLines_5Fps = (VMAX_OV9732_720P30_LINEAR * 30) / 5;
    }
    else
    {
        return;
    }

    u32FullLines_5Fps = (u32FullLines_5Fps > FULL_LINES_MAX) ? FULL_LINES_MAX : u32FullLines_5Fps;
    u32MaxIntTime_5Fps = u32FullLines_5Fps - 2;

    if (bEnable) /* setup for ISP pixel calibration mode */
    {
        ov9732_write_register(IspId, 0x380e, (u32FullLines_5Fps & 0xFF00) >> 8);  /* 5fps */
        ov9732_write_register(IspId, 0x380f, u32FullLines_5Fps & 0xFF);           /* 5fps */
        ov9732_write_register(IspId, 0x3500, (u32MaxIntTime_5Fps >> 12));               /* max exposure lines */
        ov9732_write_register(IspId, 0x3500+1, ((u32MaxIntTime_5Fps & 0xFFF)>>4));     /* max exposure lines */
        ov9732_write_register(IspId, 0x3500+2, ((u32MaxIntTime_5Fps & 0xF)<<4));       /* max exposure lines */
        ov9732_write_register(IspId, 0x350a, 0x00);                                    /* min AG */
        ov9732_write_register(IspId, 0x350a+1, 0x10);                                    /* min AG */
    }
    else /* setup for ISP 'normal mode' */
    {
        ov9732_write_register(IspId, 0x380e, (gu32FullLinesStd & 0xFF00) >> 8);
        ov9732_write_register(IspId, 0x380f, gu32FullLinesStd & 0xFF);
        
        bInit = HI_FALSE;
    }

    return;
}

HI_VOID cmos_set_wdr_mode(ISP_ID IspId,HI_U8 u8Mode)
{
    bInit = HI_FALSE;
    
    switch(u8Mode)
    {
        case HI_MPP_WDR_MODE_NONE:
            if (SENSOR_720P_30FPS_MODE == gu8SensorImageMode)
            {
                gu32FullLinesStd = VMAX_OV9732_720P30_LINEAR;
            }
            genSensorMode = HI_MPP_WDR_MODE_NONE;
            printf("linear mode\n");
        break;
        default:
            printf("NOT support this mode!\n");
            return;
        break;
    }
    
    return;
}

static HI_U32 cmos_get_sns_regs_info(ISP_ID IspId,HI_MPP_ISP_SNS_REGS_INFO_S *pstSnsRegsInfo)
{
    HI_S32 i;

    if (HI_FALSE == bInit)
    {
        g_stSnsRegsInfo.enSnsType = HI_MPP_ISP_SNS_I2C_TYPE;
        g_stSnsRegsInfo.u8Cfg2ValidDelayMax = 2;		
        g_stSnsRegsInfo.u32RegNum = 12;
	
        for (i=0; i<g_stSnsRegsInfo.u32RegNum; i++)
        {	
            g_stSnsRegsInfo.astI2cData[i].bUpdate = HI_TRUE;
            g_stSnsRegsInfo.astI2cData[i].u8DevAddr = sensor_i2c_addr;
            g_stSnsRegsInfo.astI2cData[i].u32AddrByteNum = sensor_addr_byte;
            g_stSnsRegsInfo.astI2cData[i].u32DataByteNum = sensor_data_byte;
        }

        g_stSnsRegsInfo.astI2cData[0].u8DelayFrmNum = 0;         //exposure time: astI2cData[0:2]
        g_stSnsRegsInfo.astI2cData[0].u32RegAddr = 0x3500;
        g_stSnsRegsInfo.astI2cData[1].u8DelayFrmNum = 0;
        g_stSnsRegsInfo.astI2cData[1].u32RegAddr = 0x3501;
        g_stSnsRegsInfo.astI2cData[2].u8DelayFrmNum = 0;
        g_stSnsRegsInfo.astI2cData[2].u32RegAddr = 0x3502;

        g_stSnsRegsInfo.astI2cData[3].u8DelayFrmNum = 0;       //gain
        g_stSnsRegsInfo.astI2cData[3].u32RegAddr = 0x350b;
 
        /* digital gain */
        g_stSnsRegsInfo.astI2cData[4].u8DelayFrmNum = 1;         //gain
        g_stSnsRegsInfo.astI2cData[4].u32RegAddr = 0x5180;
        g_stSnsRegsInfo.astI2cData[5].u8DelayFrmNum = 1;
        g_stSnsRegsInfo.astI2cData[5].u32RegAddr = 0x5181;

        g_stSnsRegsInfo.astI2cData[6].u8DelayFrmNum = 1;         //gain
        g_stSnsRegsInfo.astI2cData[6].u32RegAddr = 0x5182;
        g_stSnsRegsInfo.astI2cData[7].u8DelayFrmNum = 1;
        g_stSnsRegsInfo.astI2cData[7].u32RegAddr = 0x5183;

        g_stSnsRegsInfo.astI2cData[8].u8DelayFrmNum = 1;         //gain
        g_stSnsRegsInfo.astI2cData[8].u32RegAddr = 0x5184;
        g_stSnsRegsInfo.astI2cData[9].u8DelayFrmNum = 1;
        g_stSnsRegsInfo.astI2cData[9].u32RegAddr = 0x5185;

        g_stSnsRegsInfo.astI2cData[10].u8DelayFrmNum = 0;       //VTS
        g_stSnsRegsInfo.astI2cData[10].u32RegAddr = 0x380e;
        g_stSnsRegsInfo.astI2cData[11].u8DelayFrmNum = 0;       
        g_stSnsRegsInfo.astI2cData[11].u32RegAddr = 0x380f;

        bInit = HI_TRUE;
    }
    else    
    {        
        for (i = 0; i < g_stSnsRegsInfo.u32RegNum; i++)        
        {            
            if (g_stSnsRegsInfo.astI2cData[i].u32Data == g_stPreSnsRegsInfo.astI2cData[i].u32Data)            
            {                
                g_stSnsRegsInfo.astI2cData[i].bUpdate = HI_FALSE;
            }            
            else            
            {                
                g_stSnsRegsInfo.astI2cData[i].bUpdate = HI_TRUE;
            }        
        }    
    }

    if (HI_NULL == pstSnsRegsInfo)
    {
        printf("null pointer when get sns reg info!\n");
        return -1;
    }

    memcpy(pstSnsRegsInfo, &g_stSnsRegsInfo, sizeof(HI_MPP_ISP_SNS_REGS_INFO_S)); 
    memcpy(&g_stPreSnsRegsInfo, &g_stSnsRegsInfo, sizeof(HI_MPP_ISP_SNS_REGS_INFO_S)); 

    return 0;
}


int  sensor_set_inifile_path(const char *pcPath)
{
    memset(pcName, 0, sizeof(pcName));
        
    if (HI_NULL == pcPath)
    {        
        strncat(pcName, "configs/", strlen("configs/"));
        strncat(pcName, CMOS_CFG_INI, sizeof(CMOS_CFG_INI));
    }
    else
    {
		if(strlen(pcPath) > (PATHLEN_MAX - 30))
		{
			printf("Set inifile path is larger PATHLEN_MAX!\n");
			return -1;        
		}
        strncat(pcName, pcPath, strlen(pcPath));
        strncat(pcName, CMOS_CFG_INI, sizeof(CMOS_CFG_INI));
    }
    
    return 0;

}

static HI_S32 cmos_set_image_mode(ISP_ID IspId,HI_MPP_ISP_CMOS_SENSOR_IMAGE_MODE_S *pstSensorImageMode)
{
    HI_U8 u8SensorImageMode = gu8SensorImageMode;

    bInit = HI_FALSE;
    
    if (HI_NULL == pstSensorImageMode )
    {
        printf("null pointer when set image mode\n");
        return -1;
    }

    if ((pstSensorImageMode->u16Width <= 1280) && (pstSensorImageMode->u16Height <= 720))
    {
        if (HI_MPP_WDR_MODE_NONE == genSensorMode)
        {
            if (pstSensorImageMode->f32Fps <= 30)
            {
                u8SensorImageMode = SENSOR_720P_30FPS_MODE;
            }
            else
            {
                printf("Not support! Width:%d, Height:%d, Fps:%f, WDRMode:%d\n", 
                    pstSensorImageMode->u16Width, 
                    pstSensorImageMode->u16Height,
                    pstSensorImageMode->f32Fps,
                    genSensorMode);

                return -1;
            }
        }
        else
        {
            printf("Not support! Width:%d, Height:%d, Fps:%f, WDRMode:%d\n", 
                pstSensorImageMode->u16Width, 
                pstSensorImageMode->u16Height,
                pstSensorImageMode->f32Fps,
                genSensorMode);

            return -1;
        }
    }
    else
    {
        printf("Not support! Width:%d, Height:%d, Fps:%f, WDRMode:%d\n", 
            pstSensorImageMode->u16Width, 
            pstSensorImageMode->u16Height,
            pstSensorImageMode->f32Fps,
            genSensorMode);

        return -1;
    }

    /* Sensor first init */
    if (HI_FALSE == bSensorInit)
    {
        gu8SensorImageMode = u8SensorImageMode;
        
        return 0;
    }

    /* Switch SensorImageMode */
    if (u8SensorImageMode == gu8SensorImageMode)
    {
        /* Don't need to switch SensorImageMode */
        return -1;
    }
    
    gu8SensorImageMode = u8SensorImageMode;

    return 0;
}

static HI_VOID sensor_global_init(ISP_ID IspId)
{   
    gu8SensorImageMode = SENSOR_720P_30FPS_MODE;
    genSensorMode = HI_MPP_WDR_MODE_NONE;
    gu32FullLinesStd = VMAX_OV9732_720P30_LINEAR; 
    gu32FullLines = VMAX_OV9732_720P30_LINEAR;
    bInit = HI_FALSE;
    bSensorInit = HI_FALSE; 

    memset(&g_stSnsRegsInfo, 0, sizeof(HI_MPP_ISP_SNS_REGS_INFO_S));
    memset(&g_stPreSnsRegsInfo, 0, sizeof(HI_MPP_ISP_SNS_REGS_INFO_S));
}

static HI_S32 cmos_init_sensor_exp_function(HI_MPP_ISP_SENSOR_EXP_FUNC_S *pstSensorExpFunc)
{
    memset(pstSensorExpFunc, 0, sizeof(HI_MPP_ISP_SENSOR_EXP_FUNC_S));

    pstSensorExpFunc->pfn_cmos_sensor_init = ov9732_init;
    pstSensorExpFunc->pfn_cmos_sensor_exit = ov9732_exit;
    pstSensorExpFunc->pfn_cmos_sensor_global_init = sensor_global_init;
    pstSensorExpFunc->pfn_cmos_set_image_mode = cmos_set_image_mode;
    pstSensorExpFunc->pfn_cmos_set_wdr_mode = cmos_set_wdr_mode;
    
    pstSensorExpFunc->pfn_cmos_get_isp_default = cmos_get_isp_default;
    pstSensorExpFunc->pfn_cmos_get_isp_black_level = cmos_get_isp_black_level;
    pstSensorExpFunc->pfn_cmos_set_pixel_detect = cmos_set_pixel_detect;
    pstSensorExpFunc->pfn_cmos_get_sns_reg_info = cmos_get_sns_regs_info;

    return 0;
}

/****************************************************************************
 * callback structure                                                       *
 ****************************************************************************/
 
int sensor_register_callback(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib)
{
    HI_S32 s32Ret;
    HI_MPP_ISP_SENSOR_REGISTER_S stIspRegister;
    HI_MPP_AE_SENSOR_REGISTER_S  stAeRegister;
    HI_MPP_AWB_SENSOR_REGISTER_S stAwbRegister;
	
    cmos_init_sensor_exp_function(&stIspRegister.stSnsExp);
    s32Ret = HI_MAPI_ISP_SensorRegCallBack(IspId, OV9732_ID, &stIspRegister);
    if (s32Ret)
    {
        printf("sensor register callback function failed!\n");
        return s32Ret;
    }
	
    pstAeLib->s32Id = 0;
    strncpy(pstAeLib->acLibName, HI_AE_LIB_NAME, ALG_LIB_NAME_SIZE_MAX);
    cmos_init_ae_exp_function(&stAeRegister.stSnsExp);
    s32Ret = HI_MAPI_AE_SensorRegCallBack(IspId, pstAeLib, OV9732_ID, &stAeRegister);
    if (s32Ret)
    {
        printf("sensor register callback function to ae lib failed!\n");
        return s32Ret;
    }
	
    pstAwbLib->s32Id = 0;
    strncpy(pstAwbLib->acLibName, HI_AWB_LIB_NAME, ALG_LIB_NAME_SIZE_MAX);
    cmos_init_awb_exp_function(&stAwbRegister.stSnsExp);
    s32Ret = HI_MAPI_AWB_SensorRegCallBack(IspId, pstAwbLib, OV9732_ID, &stAwbRegister);
    if (s32Ret)
    {
        printf("sensor register callback function to awb lib failed!\n");
        return s32Ret;
    }
    return 0;
}

int sensor_unregister_callback(ISP_ID IspId, HI_MPP_ALG_LIB_S *pstAeLib, HI_MPP_ALG_LIB_S *pstAwbLib)
{
    HI_S32 s32Ret;
    s32Ret = HI_MAPI_ISP_SensorUnRegCallBack(IspId, OV9732_ID);
    if (s32Ret)
    {
        printf("sensor unregister callback function failed!\n");
        return s32Ret;
    }
    
    pstAwbLib->s32Id = 0;
    strncpy(pstAwbLib->acLibName, HI_AE_LIB_NAME, sizeof(HI_AE_LIB_NAME));
    s32Ret = HI_MAPI_AE_SensorUnRegCallBack(IspId, pstAeLib, OV9732_ID);
    if (s32Ret)
    {
        printf("sensor unregister callback function to ae lib failed!\n");
        return s32Ret;
    }

    pstAwbLib->s32Id = 0;
    strncpy(pstAwbLib->acLibName, HI_AWB_LIB_NAME, sizeof(HI_AWB_LIB_NAME));
    s32Ret = HI_MAPI_AWB_SensorUnRegCallBack(IspId, pstAwbLib, OV9732_ID);
    if (s32Ret)
    {
        printf("sensor unregister callback function to awb lib failed!\n");
        return s32Ret;
    }
    
    return 0;
}

ISP_SNS_OBJ_S stSnsOv9732Obj = 
{
    .pfnRegisterCallback    = sensor_register_callback,
    .pfnUnRegisterCallback  = sensor_unregister_callback,
    .pfnStandby             = ov9732_standby,
    .pfnRestart             = ov9732_restart,
    .pfnWriteReg            = ov9732_write_register,
    .pfnReadReg             = ov9732_read_register,
    .pfnSetBusInfo          = NULL
};


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __MN34220_CMOS_H_ */
