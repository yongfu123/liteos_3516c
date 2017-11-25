#ifndef __AUDIO_AAC_SRDK_H__
#define __AUDIO_AAC_SRDK_H__

#include "hi_mapi_comm_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 HI_MAPI_Register_AudioEncoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat);

HI_S32 HI_MAPI_UnRegister_AudioEncoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat);

HI_S32 HI_MAPI_Register_AudioDecoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat);

HI_S32 HI_MAPI_UnRegister_AudioDecoder(HI_MPP_AUDIO_FORMAT_E enAudioFormat);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
