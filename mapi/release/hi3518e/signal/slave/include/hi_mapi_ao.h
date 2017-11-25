#ifndef __HI_MAPI_AO_H__
#define __HI_MAPI_AO_H__

#define MODULE_NAME   "HI_MAPI_AO"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 HI_MAPI_AO_Init(HI_HANDLE AoHdl,HI_MPP_AO_ATTR_S* pstAoAttr);

HI_S32 HI_MAPI_AO_DeInit(HI_HANDLE AoHdl);

HI_S32 HI_MAPI_AO_Start(HI_HANDLE AoHdl);

HI_S32 HI_MAPI_AO_Stop(HI_HANDLE AoHdl);

HI_S32 HI_MAPI_AO_SetVolume(HI_HANDLE AoHdl,HI_MPP_AUDIO_GAIN_S* pstVol);

HI_S32 HI_MAPI_AO_GetVolume(HI_HANDLE AoHdl,HI_MPP_AUDIO_GAIN_S* pstVol);

HI_S32 HI_MAPI_AO_Mute(HI_HANDLE AoHdl);

HI_S32 HI_MAPI_AO_unMute(HI_HANDLE AoHdl);

HI_S32 HI_MAPI_AO_SendFrame(HI_HANDLE AoHdl, HI_MPP_AUDIO_FRAME_INFO_S *pstAudioFrame, HI_U32 u32Timeout);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MAPI_AO_H__ */

