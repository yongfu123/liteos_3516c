#ifndef __HI_WOL_H__
#define __HI_WOL_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef HI_S32 (*Standby_Callback)();

HI_S32 HI_WOL_Init(Standby_Callback pStandbyCB);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /*__HI_MBUF_EXT_H__*/