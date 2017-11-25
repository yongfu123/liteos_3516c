#include "hi_mapi_vcap_define.h"
typedef enum hiDIS_ACCURACY_E
{
	HI_DIS_ACCURACY_HIGH,
	HI_DIS_ACCURACY_MIDDLE,
	HI_DIS_ACCURACY_LOW,
	
	HI_DIS_ACCURACY_BUTT
}HI_DIS_ACCURACY_E;

typedef enum hiDIS_CAMERA_MODE_E
{
	HI_DIS_CAMERA_MODE_NORMAL,
	HI_DIS_CAMERA_MODE_IPC,
	
	HI_DIS_CAMERA_MODE_BUTT	
}HI_DIS_CAMERA_MODE_E;

typedef enum hiDIS_ANGLE_TYPE_E
{
    HI_DIS_ANGLE_TYPE_HORIZONTAL,
    HI_DIS_ANGLE_TYPE_VERTICAL,
    HI_DIS_ANGLE_TYPE_DIAGONAL,

    HI_DIS_ANGLE_TYPE_BUTT,
}HI_DIS_ANGLE_TYPE_E;

typedef struct hiDIS_CONFIG_S
{
	HI_DIS_ACCURACY_E		enAccuracy;			/* Accuracy setting of motion detection */
	HI_DIS_CAMERA_MODE_E    enCameraMode;		/* DIS Camera mode */
	HI_U32  				u32FixLevel;				/* Level of how strong the screen is fixated. range:[0~7] */	
	HI_U32  				u32RollingShutterCoef;		/* Rolling shutter distortion correction coefficient. range:[0~100]*/
	HI_U32					u32BufNum;					/* Buf num for DIS ,range:[4~8]*/
	HI_U32					u32CropRatio;				/* crop ratio of output image,[80~98]*/
	HI_U32					u32TimeLag;					/* Time lag between Frame and gyro data*/
	HI_DIS_ANGLE_TYPE_E		enAngleType;    /* View angle type [0~2] HORIZONTAL = 0, VERTICAL = 1, DIAGONAL = 2,*/
	HI_U32                  u32Vangle;                  /* View angle*/
	HI_BOOL					bScale;						/* Scale output image */

	HI_U32  		u32MovingSubjectLevel;		/* Threshold level to determine moving subject in the screen. range:[0~7] */
    HI_U32  		u32NoMovementLevel;			/* Threshold level to determine that the screen is still. range:[0~7] */	
}HI_DIS_CONFIG_S;

typedef struct hiDIS_CONFIG_TYPE_S
{
	HI_MPP_VCAP_DIS_MOTION_TYPE_E enDisMotionType;
	HI_S32 s32FrameRate;
}HI_DIS_CONFIG_TYPE_S;

typedef struct hiDIS_CONFIG_ITEM_S
{
	HI_DIS_CONFIG_TYPE_S stType;
	HI_DIS_CONFIG_S stCfg;
}HI_DIS_CONFIG_ITEM_S;

typedef struct hiDIS_CFG_S
{
	HI_S32 s32TotalItem;
	HI_VOID* pstDisCfgItems;
}HI_DIS_CFG_S;
