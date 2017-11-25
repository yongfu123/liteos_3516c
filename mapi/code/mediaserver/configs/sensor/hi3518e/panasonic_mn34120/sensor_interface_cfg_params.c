#include "sensor_interface_cfg_params.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/************************************************************************************/
/*                sensor dev interface config params:                                           */
/*                one type interface config params must be choiced at global var "user_dev_attr"         */
/************************************************************************************/

 const  lvds_dev_attr_t   user_lvds_dev_attr[4] = 
 {
    {
        .img_size =
        {
             .width = 4248,
             .height = 2182
        },

        .raw_data_type = RAW_DATA_12BIT,
        
        .wdr_mode = HI_WDR_MODE_NONE,
        
        .sync_mode = LVDS_SYNC_MODE_SAV,
        
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        
        .data_endian      = LVDS_ENDIAN_BIG,
        
        .sync_code_endian = LVDS_ENDIAN_BIG,
        
        .lane_id = {0, 1, 2, -1, 3, 4, -1, 5, 6, 7, -1, -1},
        
        .sync_code =   /*   LVDS_LANE_NUM * WDR_VC_NUM * SYNC_CODE_NUM = 8x4x4   */
        {
            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 0
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 1
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 2
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 3
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },
            
            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 4
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 5
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 6
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 7
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            }
        }
     },

     {
        .img_size =
        {
             .width = 2000,
             .height = 1104
        },

        .raw_data_type    = RAW_DATA_12BIT,
        
        .wdr_mode = HI_WDR_MODE_NONE,
        
        .sync_mode = LVDS_SYNC_MODE_SAV,
        
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        
        .data_endian      = LVDS_ENDIAN_BIG,
        
        .sync_code_endian = LVDS_ENDIAN_BIG,
        
        .lane_id = {0, 1, 2, -1, 3, 4, -1, 5, 6, 7, -1, -1},
        
        .sync_code =   /*   LVDS_LANE_NUM * WDR_VC_NUM * SYNC_CODE_NUM = 8x4x4   */
        {
            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 0
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 1
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 2
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 3
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },
            
            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 4
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 5
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 6
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
                {0xab0, 0xb60, 0x800, 0x9d0},      // lane 7
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
            }
        }
    },

    {
        .img_size =
        {
            .width = 1280,
            .height = 720
        },

        .raw_data_type    = RAW_DATA_10BIT,
        
        .wdr_mode = HI_WDR_MODE_NONE,
        
        .sync_mode = LVDS_SYNC_MODE_SAV,
        
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        
        .data_endian      = LVDS_ENDIAN_BIG,
        
        .sync_code_endian = LVDS_ENDIAN_BIG,
        
        .lane_id = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1},
        
        .sync_code =   /*   LVDS_LANE_NUM * WDR_VC_NUM * SYNC_CODE_NUM = 8x4x4   */
        {
            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 0
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },

            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 1
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },

            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 2
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },

            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 3
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },
            
            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 4
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },

            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 5
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },

            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 6
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },

            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 7
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },
            
            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 8
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },
            
            {
                {0x2AC,0x2D8,0x200,0x274},      // lane 9
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274},
                {0x2AC,0x2D8,0x200,0x274}
            },
            
            {
                {0x0,0x0,0x0,0x0},      // lane 9
                {0x0,0x0,0x0,0x0},
                {0x0,0x0,0x0,0x0},
                {0x0,0x0,0x0,0x0}
            },
            
            {
                {0x0,0x0,0x0,0x0},      // lane 9
                {0x0,0x0,0x0,0x0},
                {0x0,0x0,0x0,0x0},
                {0x0,0x0,0x0,0x0}
            }
        }
    },

    {
        .img_size =
        {
             .width = 4248,
             .height = 3062
        },

        .raw_data_type    = RAW_DATA_12BIT,
        
        .wdr_mode = HI_WDR_MODE_NONE,
        
        .sync_mode = LVDS_SYNC_MODE_SAV,
        
        .vsync_type       = {LVDS_VSYNC_NORMAL, 0, 0},
        
        .fid_type         = {LVDS_FID_NONE, HI_TRUE},
        
        .data_endian      = LVDS_ENDIAN_BIG,
        
        .sync_code_endian = LVDS_ENDIAN_BIG,
        
        .lane_id = {0, 1, 2, -1, 3, 4, -1, 5, 6, 7, -1, -1},
        
        .sync_code =   /*   LVDS_LANE_NUM * WDR_VC_NUM * SYNC_CODE_NUM = 8x4x4   */
        {
            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 0
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0},
                {0xab0, 0xb60, 0x800, 0x9d0}
	        },

            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 1
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 2
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
            },

            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 3
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
            },
	        {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 4
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
	        },

            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 5
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
	        },

            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 6
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
	        },

            {
		        {0xab0, 0xb60, 0x800, 0x9d0},      // lane 7
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0},
		        {0xab0, 0xb60, 0x800, 0x9d0}
	        }
        }
    }
};

/*more interface mode can be added following*/
   //...

/*final interface here*/
 extern const HI_COMBO_DEV_ATTR_S user_dev_attr =   /*var name "user_dev_attr" mustn't be modified,or media module can't get params */
{
	.bInitByFastboot = HI_FALSE,
    .devno = 0,
    .input_mode = INPUT_MODE_LVDS,
    .phy_clk_share = HI_PHY_CLK_SHARE_PHY0,
    .dev_attr_total_num = 4,                     /*user_mipi_dev_attr[x], x =2 */
    .stPhyCmv =
    {
        .bSetPhyCmv = HI_FALSE,
        .enPhyCmv = HI_PHY_CMV_BUTT
    },
    .ptr_dev_attr = (void*)user_lvds_dev_attr  /*.ptr_dev_attr =  user_lvds_dev_attr  when .input_mode = INPUT_MODE_LVDS;*/
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

