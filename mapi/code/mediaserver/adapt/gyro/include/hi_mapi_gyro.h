
HI_S32 HI_GYRO_Init(HI_S32 GyroDev, HI_S32 s32HZ);

HI_S32 HI_GYRO_DeInit(HI_S32 GyroDev);

HI_S32 HI_GYRO_DeInit(HI_S32 GyroDev);

HI_S32 HI_GYRO_Stop(HI_S32 GyroDev);

HI_S32 HI_GYRO_GetData(HI_S32 GyroDev,HI_U64 u64BeginPts, HI_U64 u64EndPts, HI_MPP_VCAP_DIS_GYRO_DATA_S *pstDISGyroData);

HI_S32 HI_GYRO_Release(HI_S32 GyroDev);