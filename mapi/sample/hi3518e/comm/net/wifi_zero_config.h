
#ifndef __WIFI_ZERO_CONFIG_H__
#define __WIFI_ZERO_CONFIG_H__

#include "bcm_wifi.h"
#ifndef ZERO_CONF_RANDOM_LEN
#define ZERO_CONF_RANDOM_LEN  8
#endif

#ifndef ZERO_CONF_ADDR_LEN
#define ZERO_CONF_ADDR_LEN 8
#endif

struct net_addr
{
	unsigned int ipaddr;
	unsigned int netmask;
	unsigned int gw;
};

struct wifi_info
{
	struct net_addr addr;
	mhd_es_ap_info_t zero_cfg;
};

#define FLASH_ZEROCFG_ADDR (0x720000-0x10000)
#define FLASH_EDI_MIN_SZIE 0x10000


#endif
