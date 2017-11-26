#ifndef __RTSP_SERVER_H
#define __RTSP_SERVER_H

#if defined (__cplusplus)
extern "C" {
#endif
#include <unistd.h>
#include <time.h>

/******************************************************************************
 *              DEFINITIONS
 ******************************************************************************/
#define SERVER_RTSP_PORT 554
#define SERVER_RTP_PORT 5004
#define SERVER_RTCP_PORT 5025
#define RTSP_MAXIMUM_FRAMERATE 60
#define RTSP_MAXIMUM_CONNECTIONS 16

#define STR_RTSP_VERSION "RTSP/1.0"

/* __rtsp_obj_t is private. you will not see it */
typedef struct __rtsp_obj_t *rtsp_handle;

/******************************************************************************
*创建一个callback 通知主线程已经退出，上层需关闭并且释放缓存
******************************************************************************/
typedef void (*Thr_Exit_Fun)(void);
extern Thr_Exit_Fun ThrExitFun;

/******************************************************************************
 *              LIBRARY FUNCTIONS
 ******************************************************************************/
/* put virtual pointer to 'buf', which consists of 1 or more NALUs (start code required). 
   SPS and PPS parameters are automatically collected during execution. */

int rtp_send_h264(rtsp_handle rtsp_h,signed char *buf, size_t len, struct timeval *p_tv);

extern void rtsp_finish(rtsp_handle rtsp_h);

extern rtsp_handle rtsp_create(unsigned char max_con, int priority, Thr_Exit_Fun fun);

#if defined (__cplusplus)
}
#endif

#endif
