#include "sensor_interface_cfg_params.h"
#include "hi_mapi_sns_ctrl_define.h"
#include "hi_mipi.h"
/************************************************************************************/
/*                sensor dev interface config params:                                           */
/*                one type interface config params must be choiced at global var "user_dev_attr"         */
/************************************************************************************/

 /*can be changed by user if needed */
const mipi_dev_attr_t user_mipi_dev_attr[1] =
{
   /*mipi  mode 0*/
   {
    .raw_data_type = RAW_DATA_12BIT,
    .lane_id =  {0, -1, -1, -1, -1, -1, -1, -1}
   }
};


HI_SENSOR_MIPI_LVDS_INTF_S user_mipi_intf[1] =
{
	{
		.phy_clk_share = HI_PHY_CLK_SHARE_PHY0,
		.stPhyCmv =
		{
			.bSetPhyCmv = HI_FALSE,
			.enPhyCmv = PHY_CMV_BUTT
		},
		.img_rect =
		{
			.x = 0,
			.y = 0,
			.width = 1280,
			.height = 720
		},
		.ptr_dev_attr =(void*)&user_mipi_dev_attr[0],  /*.ptr_dev_attr =  user_lvds_dev_attr  when .input_mode = INPUT_MODE_LVDS;*/
		.au32CompMask = {0xfff00000,0}
	}
};

HI_SENSOR_MIPI_LVDS_INTF_CFG_S sensor_mipi_intf_cfg =
{
	.dev_attr_total_num = 1,
	.psensorIntf = (void*)user_mipi_intf
};

const HI_SENSOR_MODE_S sensor_mode[7] =
{
	/*4K@30*/
	{
		.s32Width = 3840,
		.s32Height = 2160,
		.s32FrameRate = 30,
		.s32SensorIntfSeqNo = 0,
		.enWdrMode = HI_MPP_WDR_MODE_NONE
	},
	/*4K@60*/
	{
		.s32Width = 3840,
		.s32Height = 2160,
		.s32FrameRate = 60,
		.s32SensorIntfSeqNo = 0,
		.enWdrMode = HI_MPP_WDR_MODE_NONE
	},
	/*1080p@60*/
	{
		.s32Width = 1920,
		.s32Height = 1080,
		.s32FrameRate = 60,
		.s32SensorIntfSeqNo = 1,
		.enWdrMode = HI_MPP_WDR_MODE_NONE
	},
	/*1080p@120*/
	{
		.s32Width = 1920,
		.s32Height = 1080,
		.s32FrameRate = 120,
		.s32SensorIntfSeqNo = 1
	},
	/*720p@240*/
	{
		.s32Width = 1280,
		.s32Height = 720,
		.s32FrameRate = 240,
		.s32SensorIntfSeqNo = 2,
		.enWdrMode = HI_MPP_WDR_MODE_NONE
	},
	/*720p@30*/
	{
		.s32Width = 1280,
		.s32Height = 720,
		.s32FrameRate = 30,
		.s32SensorIntfSeqNo = 0,
		.enWdrMode = HI_MPP_WDR_MODE_NONE
	},
	/*12M*/
	{
		.s32Width = 4000,
		.s32Height = 3000,
		.s32FrameRate = 28,
		.s32SensorIntfSeqNo = 3,
		.enWdrMode = HI_MPP_WDR_MODE_NONE
	}
};

/*final interface here*/
const HI_COMBO_DEV_ATTR_S user_dev_attrs[1] =   /*var name "user_dev_attr" mustn't be modified,or media module can't get params */
{
    {
		.stSensorInputAttr = 
		{
			.enBayerFormat = HI_BAYER_BGGR,
			.s32start_x = 0,
			.s32start_y = 0
		},
		.stSensorIntf = 
		{
			.bInitByFastboot = HI_FALSE,
			.devno = 0,
			.input_mode = INPUT_MODE_MIPI,
			.pstIntf= (void*)&sensor_mipi_intf_cfg
		},
		.stSensorMode = 
		{
			.s32SensorModeNum = 7,
			.pstSensorMode = (void*)sensor_mode
		}
    }
};

const HI_SENSOR_CFG_S sensor_cfg = 
{
	.s32TotalSensorNum = 1,
	.pstSensors = (void*)user_dev_attrs
};

/************************VB************************************/

const HI_VB_S vb_opts[1] = 
{
	{
		.u32MaxPoolCnt = 2,
		.astCommPool = 
		{
			{
				.u32BlkSize = 1280*720*2,
				.u32BlkCnt = 15
			},
			{
				.u32BlkSize = 640*480*2,
				.u32BlkCnt = 10
			}
		}
	}
};

const HI_VB_CFG_S vb_cfg =
{
	.s32TotalOptNum = 1,
	.u32CurrentOpt = 0,
	.pstVBOpts = (void*)vb_opts
};


static const ISP_SNS_OBJ_S stSnsObjEmpty = 
{
    .pfnRegisterCallback    = NULL,
    .pfnUnRegisterCallback  = NULL,
    .pfnStandby             = NULL,
    .pfnRestart             = NULL,
    .pfnWriteReg            = NULL,
    .pfnReadReg             = NULL,
    .pfnSetBusInfo          = NULL
};


/**********************sensor obj***************************/
extern const ISP_SNS_OBJ_S* g_pstSnsObj[2] =
{
    &stSnsOv9732Obj, &stSnsObjEmpty
};
