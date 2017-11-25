#ifndef __HI_NETACCESS_H__
#define __HI_NETACCESS_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 HI_NetAccess_Start(HI_CHAR* confPath);

HI_S32 HI_NetAccess_Stop();

HI_S32 HI_NetAccess_Listen();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /*__HI_MBUF_EXT_H__*/