#ifndef __INNER_AUDIO_COMPONENT_DEFINE_H__
#define __INNER_AUDIO_COMPONENT_DEFINE_H__

#include "hi_mapi_comm_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define MAX_AUDIO_POINT_BYTES  4        /*max bytes of one sample point(now 32bit max)*/
#define MAX_VOICE_POINT_NUM    480      /*max sample per frame for voice encode */
#if 0
typedef enum hiG726_BPS_E
{
    G726_16K = 0,       /* G726 16kbps, see RFC3551.txt  4.5.4 G726-16 */ 
    G726_24K,           /* G726 24kbps, see RFC3551.txt  4.5.4 G726-24 */
    G726_32K,           /* G726 32kbps, see RFC3551.txt  4.5.4 G726-32 */
    G726_40K,           /* G726 40kbps, see RFC3551.txt  4.5.4 G726-40 */
    MEDIA_G726_16K,     /* G726 16kbps for ASF ... */ 
    MEDIA_G726_24K,     /* G726 24kbps for ASF ... */
    MEDIA_G726_32K,     /* G726 32kbps for ASF ... */
    MEDIA_G726_40K,     /* G726 40kbps for ASF ... */
    G726_BUTT,
} G726_BPS_E;

typedef struct hiAENC_ATTR_G726_S
{
    G726_BPS_E enG726bps; 
}AENC_ATTR_G726_S;
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
