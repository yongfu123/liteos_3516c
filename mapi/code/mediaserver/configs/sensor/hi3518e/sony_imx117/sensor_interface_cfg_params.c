#include "sensor_interface_cfg_params.h"
#include "hi_mapi_sns_ctrl_define.h"

/************************************************************************************/
/*                sensor dev interface config params:                                           */
/*                one type interface config params must be choiced at global var "user_dev_attr"         */
/************************************************************************************/

 /*can be changed by user if needed */
const  lvds_dev_attr_t   user_lvds_dev_attr[4] =
{
	/*Mipi:4k,user_lvds_dev_attr[0]*/
	{
        .wdr_mode = HI_WDR_MODE_NONE,
        .sync_mode = LVDS_SYNC_MODE_SAV,
        .raw_data_type = RAW_DATA_12BIT,
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        .data_endian      = LVDS_ENDIAN_BIG,
        .sync_code_endian = LVDS_ENDIAN_BIG,
        .lane_id = {0, 1, 2, -1, 3, 4, -1, 5, 6, 7, -1, -1},
        .sync_code =
        {
            {   
		  {0xab0, 0xb60, 0x800, 0x9d0},      // lane 0
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 1
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 2
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 3
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 4
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 5
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 6
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 7
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            }
        }
	},
	/*Mipi:1080p,user_lvds_dev_attr[1]*/
    {
        .raw_data_type    = RAW_DATA_12BIT,
        .wdr_mode         = HI_WDR_MODE_NONE,
        .sync_mode        = LVDS_SYNC_MODE_SAV,
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        .data_endian      = LVDS_ENDIAN_BIG,
        .sync_code_endian = LVDS_ENDIAN_BIG,
        .lane_id = {0, 1, 2, -1, 3, 4, -1, 5, 6, 7, -1, -1},
        .sync_code = 
        {
            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 0
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 1
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 2
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 3
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 4
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 5
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 6
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},

            {{0xab0, 0xb60, 0x800, 0x9d0},      // lane 7
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}, 
            {0xab0, 0xb60, 0x800, 0x9d0}},                    
        }
    },
    /*Mipi:720p,user_lvds_dev_attr[2]*/
    {
            .raw_data_type    = RAW_DATA_10BIT,
            .wdr_mode         = HI_WDR_MODE_NONE,
            .sync_mode        = LVDS_SYNC_MODE_SAV,
            .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
            .fid_type         = {LVDS_FID_NONE, HI_TRUE},
            .data_endian      = LVDS_ENDIAN_BIG,
            .sync_code_endian = LVDS_ENDIAN_BIG,
            .lane_id = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1},
            .sync_code = {
                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },
                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },

                {   {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274},
                    {0x2ac, 0x2d8, 0x200, 0x274}
                },     
        }
    },
    /*Mipi:12M,user_lvds_dev_attr[3]*/
    {
        .raw_data_type    = RAW_DATA_12BIT,
        .wdr_mode         = HI_WDR_MODE_NONE,
        .sync_mode        = LVDS_SYNC_MODE_SAV,
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        .data_endian      = LVDS_ENDIAN_BIG,
        .sync_code_endian = LVDS_ENDIAN_BIG,
        .lane_id = {0, 1, 2, -1, 3, 4, -1, 5, 6, 7, -1, -1},
        .sync_code =
        {
            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 0
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 1
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 2
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 3
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 4
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 5
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 6
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {   {0xab0, 0xb60, 0x800, 0x9d0},      // lane 7
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },
        }
    }
};

HI_SENSOR_MIPI_LVDS_INTF_S user_lvds_intf[4] =
{
	/*4k*/
	{
		.phy_clk_share = HI_PHY_CLK_SHARE_PHY0,
		.stPhyCmv =
		{
			.bSetPhyCmv = HI_FALSE,
			.enPhyCmv = PHY_CMV_BUTT
		},
		.img_rect =
		{
			.x = 96,
			.y = 8,
			.width = 4096,
			.height = 2200
		},
		.ptr_dev_attr =(void*)&user_lvds_dev_attr[0],  /*.ptr_dev_attr =  user_lvds_dev_attr  when .input_mode = INPUT_MODE_LVDS;*/
		.au32CompMask = {0xfff00000,0}
	},
	/*1080p*/
	{
		.phy_clk_share = HI_PHY_CLK_SHARE_PHY0,
		.stPhyCmv =
		{
			.bSetPhyCmv = HI_FALSE,
			.enPhyCmv = PHY_CMV_BUTT
		},
		.img_rect =
		{
			.x = 48,
			.y = 2,
			.width = 2000,
			.height = 1104
		},
		.ptr_dev_attr =(void*)&user_lvds_dev_attr[1],  /*.ptr_dev_attr =  user_lvds_dev_attr  when .input_mode = INPUT_MODE_LVDS;*/
		.au32CompMask = {0xfff00000,0}
	},
	/*720p*/
	{
		.phy_clk_share = HI_PHY_CLK_SHARE_PHY0,
		.stPhyCmv =
		{
			.bSetPhyCmv = HI_FALSE,
			.enPhyCmv = PHY_CMV_BUTT
		},
		.img_rect =
		{
			.x = 48,
			.y = 2,
			.width = 2000,
			.height = 750
		},
		.ptr_dev_attr =(void*)&user_lvds_dev_attr[2],  /*.ptr_dev_attr =  user_lvds_dev_attr  when .input_mode = INPUT_MODE_LVDS;*/
		.au32CompMask = {0xfff00000,0}
	},
	/*12M*/
	{
		.phy_clk_share = HI_PHY_CLK_SHARE_PHY0,
		.stPhyCmv =
		{
			.bSetPhyCmv = HI_FALSE,
			.enPhyCmv = PHY_CMV_BUTT
		},
		.img_rect =
		{
			.x = 96,
			.y = 8,
			.width = 4096,
			.height = 3062
		},
		.ptr_dev_attr =(void*)&user_lvds_dev_attr[3],  /*.ptr_dev_attr =  user_lvds_dev_attr  when .input_mode = INPUT_MODE_LVDS;*/
		.au32CompMask = {0xfff00000,0}
	}
};

HI_SENSOR_MIPI_LVDS_INTF_CFG_S sensor_lvds_intf_cfg =
{
	.dev_attr_total_num = 4,
	.psensorIntf = (void*) user_lvds_intf
};

const HI_SENSOR_MODE_S sensor_mode[7] =
{
	/*4K@30*/
	{
		.s32Width = 3840,
		.s32Height = 2160,
		.s32FrameRate = 30,
		.s32SensorIntfSeqNo = 0
	},
	/*4K@60*/
	{
		.s32Width = 3840,
		.s32Height = 2160,
		.s32FrameRate = 60,
		.s32SensorIntfSeqNo = 0
	},
	/*1080p@60*/
	{
		.s32Width = 1920,
		.s32Height = 1080,
		.s32FrameRate = 60,
		.s32SensorIntfSeqNo = 1
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
		.s32SensorIntfSeqNo = 2
	},
	/*720p@120*/
	{
		.s32Width = 1280,
		.s32Height = 720,
		.s32FrameRate = 120,
		.s32SensorIntfSeqNo = 2
	},
	/*12M*/
	{
		.s32Width = 4000,
		.s32Height = 3000,
		.s32FrameRate = 28,
		.s32SensorIntfSeqNo = 3
	}
};

/*final interface here*/
const HI_COMBO_DEV_ATTR_S user_dev_attrs[1] =   /*var name "user_dev_attr" mustn't be modified,or media module can't get params */
{
    {
		.stSensorInputAttr = 
		{
			.enBayerFormat = HI_BAYER_RGGB,
			.s32start_x = 0,
			.s32start_y = 0
		},
		.stSensorIntf = 
		{
			.bInitByFastboot = HI_FALSE,
			.devno = 0,
			.input_mode = INPUT_MODE_LVDS,
			.pstIntf= (void*)&sensor_lvds_intf_cfg
		},
		.stSensorMode = 
		{
			.s32SensorModeNum = 7,
			.pstSensorMode = (void*) sensor_mode
		}
    }
};

extern const HI_SENSOR_CFG_S sensor_cfg = 
{
	.s32TotalSensorNum = 1,
	.pstSensors = (void*) user_dev_attrs
};



/************************VB************************************/

const HI_VB_S vb_opts[1] = 
{
	{
		.u32MaxPoolCnt = 2,
		.astCommPool = 
		{
			{
				.u32BlkSize = 4000*3000*2,
				.u32BlkCnt = 15
			},
			{
				.u32BlkSize = 1024*576*2,
				.u32BlkCnt = 10
			}
		}
	}
};

extern const HI_VB_CFG_S vb_cfg =
{
	.s32TotalOptNum = 1,
	.u32CurrentOpt = 0,
	.pstVBOpts = (void*)vb_opts
};

/**********************sensor obj***************************/
extern const ISP_SNS_OBJ_S* g_pstSnsObj[2] =
{
    &stSnsImx117Obj, HI_NULL
};