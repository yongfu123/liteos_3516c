#ifndef __WIFI_INFO_H__
#define __WIFI_INFO_H__

#include "stdint.h"
#include "bcm_wifi.h"




#define WIFI_8801	0
#define WIFI_6214	1  //wifi image

//修改WIFITYPE，支持8801 ；WIFITYPE=WIFI_6214可以编译运行，但不做镜像。
//6214要做镜像的编译需到wifi_sta_6214文件编译
#define WIFITYPE WIFI_6214  


#define WIFISSID		"F4A_WX349823"//F4Ag00284866  F4A_WX349823
#define WIFIPASSWORD	"hdx12345"


#endif
