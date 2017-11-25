#include "hi_type.h"
#include "dis_cfg_params.h"

const HI_DIS_CONFIG_ITEM_S dis_item[8] = 
{
	/*4Dof_soft,releated to motion type*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_4DOF_SOFT,
			.s32FrameRate = 30
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 4,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 0,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 2,
			.u32NoMovementLevel = 1
		}
	},
	/*4Dof_soft,releated to motion type*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_4DOF_SOFT,
			.s32FrameRate = 60
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 4,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 0,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 2,
			.u32NoMovementLevel = 1
		}
	},
	/*6Dof_soft,releated to motion type*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_6DOF_SOFT,
			.s32FrameRate = 30
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 4,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 0,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 2,
			.u32NoMovementLevel = 1
		}
	},
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_6DOF_SOFT,
			.s32FrameRate = 60
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 4,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 0,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 2,
			.u32NoMovementLevel = 1
		}
	},
	/*6Dof_Hybrid_30fps,releated to motion type and framerate*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_6DOF_HYBRID,
			.s32FrameRate = 30
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 5,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 39000,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 5,
			.u32NoMovementLevel = 0
		}
	},
	/*6Dof_Hybrid_60fps,releated to motion type and framerate*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_6DOF_HYBRID,
			.s32FrameRate = 60
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 5,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 16666,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 5,
			.u32NoMovementLevel = 0
		}
	},
	/*8Dof_Hard_30,releated to motion type and framerate*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_8DOF_HARD,
			.s32FrameRate = 30
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 4,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 33333,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 0,
			.u32NoMovementLevel = 1
		}
	},
	/*8Dof_Hard_60,releated to motion type and framerate*/
	{
		.stType = 
		{
			.enDisMotionType = HI_MPP_VCAP_DIS_MOTION_8DOF_HARD,
			.s32FrameRate = 60
		},
		.stCfg = 
		{
			.enAccuracy = HI_DIS_ACCURACY_HIGH,
			.enCameraMode = HI_DIS_CAMERA_MODE_NORMAL,
			.u32FixLevel = 4,
			.u32RollingShutterCoef = 80,
			.u32BufNum = 8,
			.u32CropRatio = 80,
			.u32TimeLag = 33333,
			.enAngleType = HI_DIS_ANGLE_TYPE_DIAGONAL,
			.u32Vangle = 934,
			.bScale = HI_TRUE,

			.u32MovingSubjectLevel = 0,
			.u32NoMovementLevel = 1
		}
	}
	/*you can add configs of other types*/
};

extern const HI_DIS_CFG_S dis_cfg =
{
	.s32TotalItem = 8,
	.pstDisCfgItems = (void*)dis_item
};