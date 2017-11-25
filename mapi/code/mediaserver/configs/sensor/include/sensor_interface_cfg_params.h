#ifndef __HI_SENSOR_DEFINE_H__
#define __HI_SENSOR_DEFINE_H__

#include "hi_mipi.h"
#include "hi_type.h"
#include "hi_mapi_vcap_define.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef enum
{
    HI_PHY_CMV_GE900MV    = 0x00,
    HI_PHY_CMV_LT900MV    = 0x01,
    HI_PHY_CMV_BUTT
} HI_PHY_CMV_E;

typedef struct
{
	HI_BOOL bSetPhyCmv;
    HI_PHY_CMV_E enPhyCmv;
} HI_PHY_CMV_S;

typedef enum
{
	HI_BAYER_RGGB = 0,
	HI_BAYER_GRBG,
	HI_BAYER_GBRG,
	HI_BAYER_BGGR
}HI_BAYERFORMAT;

typedef struct
{
	HI_BAYERFORMAT enBayerFormat;
	HI_S32 s32start_x;
	HI_S32 s32start_y;
} HI_SENSOR_INPUT_ATTR_S;

typedef enum{    
	HI_PHY_CLK_SHARE_NONE = 0x0,    
	HI_PHY_CLK_SHARE_PHY0 = 0x1,      /* PHY share clock with PHY0 */    
	HI_PHY_CLK_SHARE_BUTT = 0x2
} HI_PHY_CLK_SHARE_E;

typedef struct
{
	HI_PHY_CLK_SHARE_E   	phy_clk_share;
	HI_PHY_CMV_S            stPhyCmv;
	img_rect_t      img_rect;
	void*              ptr_dev_attr;           /*  pointer to user_mipi_dev_attr or user_lvds_dev_attr */
	HI_U32            	au32CompMask[2];			/*对应ViDev的掩码*/
}HI_SENSOR_MIPI_LVDS_INTF_S;

typedef struct
{
    HI_U32                  dev_attr_total_num;
    void* psensorIntf;					/*HI_SENSOR_MIPI_LVDS_INTF_S*/
}HI_SENSOR_MIPI_LVDS_INTF_CFG_S;
#if 0
/*设备输入时序的消隐信息*/
typedef struct hiVIDEO_INPUT_TIMING_BLANK_S
{
    HI_U32 u32HsyncHfb ;                    //水平前消隐区宽度
    //    HI_U32 u32HsyncAct ;                    //水平有效宽度
    HI_U32 u32HsyncHbb ;                    //水平后消隐区宽度
    HI_U32 u32VsyncOfb ;                    //帧图像或隔行输入时奇场图像的垂直前消隐区高度
    //    HI_U32 u32VsyncOAct ;                   //帧图像或隔行输入时奇场垂直有效宽度
    HI_U32 u32VsyncObb ;                    //帧图像或隔行输入时奇场垂直后消隐区高度
    HI_U32 u32VsyncEfb ;                    //隔行输入时偶场垂直前消隐区高度 (帧输入时无效)
    HI_U32 u32VsyncEAct ;                   //隔行输入时偶场垂直有效宽度 (帧输入时无效)
    HI_U32 u32VsyncEbb ;                    //隔行输入时偶场垂直后消隐区高度  (帧输入时无效)
} HI_VIDEO_INPUT_TIMING_BLANK_S;


/* 同步时序配置 (BT601/DC 接口必须配置) */
typedef struct hiVIDEO_BT601_DC_SYNC_CFG_S
{
    HI_U32 uVsync;                          /*垂直同步模式，0:垂直同步翻转模式，1:垂直同步脉冲模式*/
    HI_U32 uVsyncNeg;                       /* 垂直同步信号的极性,0:表示偶数场的vsync信号为高电平,或是表示正脉冲表示vsync同步脉冲,或是表示vsync有效信号为高电平
                                                                       1:表示偶数场的vsync信号为低电平，或是表示负脉冲表示vsync同步脉冲，或是表示vsync有效信号为低电平*/
    HI_U32 uHsync;                          /*水平同步类型 ,0:水平同步有效信号模式,1:水平同步脉冲模式:*/
    HI_U32 uHsyncNeg;                       /**水平同步信号极性，0:表示水平同步脉冲为正脉冲,或是表示数据有效信号为高电平
                                                                     1:表示水平同步脉冲为负脉冲,或是表示数据有效信号为低电平*/
    HI_U32 uVsyncValid;                     /* 有效垂直同步类型,0:垂直同步翻转模式，1:垂直同步脉冲模式*/
    HI_U32 uVsyncValidNeg;
    HI_VIDEO_INPUT_TIMING_BLANK_S stTimingBlank;/*设备输入时序的消隐信息*/
} HI_VIDEO_BT601_DC_SYNC_CFG_S;

typedef enum hiVIDEO_DATA_YUV_SEQ_E
{
    /*The input sequence of the second component(only contains u and v) in BT.1120 mode */
    HI_VIDEO_INPUT_DATA_VUVU = 0,
    HI_VIDEO_INPUT_DATA_UVUV,

    /* The input sequence for yuv */
    HI_VIDEO_INPUT_DATA_UYVY,
    HI_VIDEO_INPUT_DATA_VYUY,
    HI_VIDEO_INPUT_DATA_YUYV,
    HI_VIDEO_INPUT_DATA_YVYU,

    HI_VIDEO_INPUT_DATA_YUV_BUTT
} HI_VIDEO_DATA_YUV_SEQ_E;

typedef struct hiVIDEO_VI_PUB_ATTR_S
{
    HI_VIDEO_DATA_YUV_SEQ_E enDataSeq;       /* 输入数据顺序 */
    HI_VIDEO_BT601_DC_SYNC_CFG_S stSynCfg;     /* 同步时序配置 (BT601/DC 接口必须配置) */
} HI_BT601_DC_INTF_S;
#endif

typedef struct
{
    HI_BOOL    bInitByFastboot;               		/* HI_TRUE: fastboot will do sensor init rather than RDK, make sure use correct fastboot, HI_FALSE: RDK do sensor init */
    HI_U32                  devno;                  		/* device number, select sensor0 and sensor 1 */
    input_mode_t            input_mode;             	/* input mode: MIPI/LVDS/SUBLVDS/HISPI/DC */
    void* pstIntf;							/*HI_SENSOR_MIPI_LVDS_INTF_CFG_S or HI_BT601_DC_INTF_S*/
}HI_SENSOR_INTF_S;

typedef struct
{
	HI_S32 s32Width;
	HI_S32 s32Height;
	HI_S32 s32FrameRate;
	HI_S32 s32SensorIntfSeqNo;
	HI_MPP_WDR_MODE_E enWdrMode;
}HI_SENSOR_MODE_S;

typedef struct
{
	HI_S32 s32SensorModeNum;
	void* pstSensorMode;			/*HI_SENSOR_MODE_S*/
}HI_SENSOR_MODE_INFO_S;

typedef enum hiSENSOR_COMMBUS_TYPE_E
{
	HI_SENSOR_COMMBUS_TYPE_I2C = 0,	
	HI_SENSOR_COMMBUS_TYPE_SPI,	
	HI_SENSOR_COMMBUS_TYPE_BUTT
}HI_SENSOR_COMMBUS_TYPE_E;

/*sensor interface description*/
typedef struct
{
    HI_SENSOR_INPUT_ATTR_S stSensorInputAttr;
	HI_SENSOR_INTF_S stSensorIntf;  
	HI_SENSOR_MODE_INFO_S stSensorMode;	
	HI_SENSOR_COMMBUS_TYPE_E enSensorCommBusType;
} HI_COMBO_DEV_ATTR_S;

typedef struct 
{
	HI_S32 s32TotalSensorNum;
	void* pstSensors;				/*HI_COMBO_DEV_ATTR_S*/
}HI_SENSOR_CFG_S;


/*************************VB********************************************/
typedef struct
{
    HI_U32 u32MaxPoolCnt;     /* max count of pools, (0,VB_MAX_POOLS]  */    
    struct hiPOOL_S
    {
        HI_U32 u32BlkSize;
        HI_U32 u32BlkCnt;
    }astCommPool[16];
} HI_VB_S;

typedef struct
{
	HI_S32 s32TotalOptNum;
	HI_U32 u32CurrentOpt;
	HI_VB_S* pstVBOpts;
}HI_VB_CFG_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* ARGPARSER_H__ */
