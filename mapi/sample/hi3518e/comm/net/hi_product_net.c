#include <stdio.h>
#include "sys/types.h"
#include "sys/time.h"
#include "hi_type.h"
#include "sys/prctl.h"
#include "eth_drv.h"
#include "bcm_wifi.h"
#include "fcntl.h"
#include "asm/io.h"
#include "shell.h"
#include "adaptsecure.h"
#include<stdlib.h>

#include "mwlan.h"
#include "wifi_info.h"
#include "wifi_zero_config.h"



static int netflag = 0;/*0-net is not inited; 1-net is inited*/

#ifdef CFG_SUPPORT_WIFI_AP
    int wifi_mode = 1;
#else
    int wifi_mode = 0;
#endif



#define himm(address, value) writel(value, address)
#define himd(address) readl(address)

void mrvl_sta_event_handler(mrvl_sta_event event)
{
    switch(event){
        case MRVL_EVT_SCAN_RESULTS:
            printf(" ===EVENT === scan results \n");
            break;
        case MRVL_EVT_CONNECTED:
            printf("===EVENT === connected \n");
            hi_start_dhcpc(0, NULL);
            break;
        case MRVL_EVT_DISCONNECTED:
            printf("===EVENT === disconnected \n");
            break;
        default:
            printf("other event \n");
            break;
    }
}

void Wifi_Register_Init(int nFirst)
{

dprintf("-----------------Wifi_Register_Init------------------ \n");


#if(WIFITYPE==WIFI_6214)

//#oob GPIO 6-5
		
		himm (0x200f00D4, 0x0);
		#if 0
		himm (0x200f0010,0x4);//GPIO2_0 RMII_CLK	SDIO1_CCLK_OUT
		himm (0x200f0014,0x4);//GPIO2_1 RMII_TX_EN	SDIO1_CARD_DETECT
		himm (0x200f0018,0x4);//GPIO2_2 RMII_TXD0	SDIO1_CWPR
		himm (0x200f001c,0x4);//GPIO2_3 			SDIO1_CDATA1
		himm (0x200f0020,0x4);//GPIO2_4 RMII_RX_DV	SDIO1_CDATA0
		himm (0x200f0024,0x4);//GPIO2_5 RMII_RXD0	SDIO1_CDATA3
		himm (0x200f0028,0x4);//GPIO2_6 RMII_RXD1	SDIO1_CCMD
		himm (0x200f002c,0x4);//GPIO2_7 EPHY_RST	SDIO1_CARD_POWER_EN
		himm (0x200f0034,0x4);//GPIO3_0 EPHY_CLK	SDIO1_CDATA2
		#else
		
		himm (0x200f0098,0x1);//0：GPIO1_7；1：SDIO0_CARD_POWER_EN。
		himm (0x200f009c,0x1);//0：GPIO4_7；1：SDIO0_CARD_DETECT。
		himm (0x200f00a0,0x1);//0：GPIO5_0；1：SDIO0_CWPR。
		himm (0x200f00a4,0x1);//0：GPIO5_1；1：SDIO0_CCLK_OUT。
		himm (0x200f00a8,0x1);//0：GPIO5_2；1：SDIO0_CCMD。
		himm (0x200f00ac,0x1);//0：GPIO5_3；1：SDIO0_CDATA0。
		himm (0x200f00b0,0x1);//0：TEST_CLK；1：SDIO0_CDATA1 ;   2 : GPIO5_3
		himm (0x200f00b4,0x1);//0：GPIO5_5；1：SDIO0_CDATA2。
		himm (0x200f00b8,0x1);//0：GPIO5_6；1：SDIO0_CDATA3。
		#endif
		//#regon GPIO 7.0
		himm (0x200f00E0, 0x0);
		//#set regon dir P7.0
		{
			char *p = 0x201b0400;
			unsigned int val = *p;
			
			himm (0x201B0400, val | 0x01);
		}
		//writel(0x40, 0x201a0400);//direction
		//writel(0x00, 0x201a0100);//pull down
		if (nFirst)
		{
			himm (0x201b0004, 0x00);
		}
		else
		{
			himm (0x201b0004, 0x01);
		}

#else if(WIFITYPE==WIFI_8801)

    int ret;
    struct netif *dev;

	#ifdef CFG_SUPPORT_WIFI_AP
	    printf("==========wifi_driver_init ap\n");
	    wifi_mode = 1;
	#else
	    printf("==========wifi_driver_init  sta\n");
	    wifi_mode = 0;
	#endif
	    msleep(2000);
	    printf("==========init wifi ok !\n");

	   ret = mrvl_wifi_init(wifi_mode);
    if (ret) {
        dprintf("wifi init failed\n");
        return;
    }
    msleep(1000);
    ret = mrvl_wlan_open(&dev);
    if (ret) {
        printf("open wifi failed\n");
        return;
    }

    if (wifi_mode == 0)
        mrvl_sta_register_event_cb(mrvl_sta_event_handler);

    dprintf("==========init wifi ok !\n");
#endif

}




void wifi_power_set()
{
	writel(0x01, 0x201b0004);//16cv200
    //writel(0x04, 0x201a0010);//18ev200
}

void hi_start_softap(char* ssid, uint8_t channel, uint8_t security, char* password)
	{
		char *security_name[] = {"open", "wep", "wpa-psk",
								 "wpa2-psk", "wpa-wpa2-psk_mix"};
		uint32_t ip_address = 0xc0a80101;
		int ret;
	
		if (ssid == NULL) {
			dprintf("hi_start_softap: ssid is null\n");
			return;
		}
	
		if (channel < 1 || channel > 14) {
			dprintf("hi_start_softap: channel is out of range\n");
			return;
		}
	
		if (security < 1 || security > 4) {
			dprintf("hi_start_softap: security is out of range\n");
			return;
		}
	
		dprintf("config softap\n");
		dprintf("ssid	 : %s\n", ssid);
		dprintf("channel : %d\n", channel);
		dprintf("security: %s\n", security_name[security]);
		dprintf("password: %s\n", password);
		if (security >= 2 && security <= 4)
			security = 40;
		else
			security = 0;
		ret = mrvl_softap_start(ssid, security, password, channel);
		if (ret) {
			printf("mrvl_softap_start failed ret = %d\n", ret);
			return;
		}
		hi_start_dhcpd(0, 0);	 
	}


#define MMC_DEVICE_TRY_TIME (2000)
#define MMC_DEVICE_SLEEP_TIME (10)

int hi_mmcdev_isready(const char* pDev)
{
    int nTryTime = 0;

    if (pDev == NULL)
    {
        printf("%s is not exist \n", pDev);
        return  -1;
    }

    while ((0 != access(pDev, 0)) && (nTryTime < MMC_DEVICE_TRY_TIME))
    {
        nTryTime += MMC_DEVICE_SLEEP_TIME;
        msleep(MMC_DEVICE_SLEEP_TIME);
    }

    if (nTryTime >= MMC_DEVICE_TRY_TIME)
    {
        printf("\n[%s] cannot find the device: %s\n", __func__, pDev);
        return -1;
    }

    return 0;
}


/**************************
*key press return 0
*
*key1	7_3
*key2	7_4
*key3	7_2
***************************/
int hi_zeroconfig_key_press()
{
	int val=0;

	himm(0x200F00ec,0x01);//config for 7_3

	val = himd(0x201b0400);
	himm(0x201b0400,val &(~(0x01<<3)));//set dir for output

	msleep(1);//need
	val = himd(0x201b0020);	
	val =val&(0x01<<3);

	return val;
}


#if(WIFITYPE==WIFI_8801)

t_u8 dst_mac[ETH_ALEN] = {0xc4,0xa8,0x1d,0x8c,0x0c,0x88};
t_u8 src_mac[ETH_ALEN] = {0x00,0x50,0x43,0x11,0x22,0x33};
t_u8 pkt[] = {0x45,0x00,0x00,0x43,0x8c,0x9e,0x00,0x00,0xff,0x06,0xac,0xbf,0xc0,0xa8,0x00,0x7c,0xc0,0xa8,0x00,0x8a,0xc0,0x03,0x22,0xb7,0xb0,0xb6,0x60,0x9f,0x42,0xdd,0x9e,0x1e,0x50,0x18,0x80,0x00,0xd0,0x88,0x00,0x00,0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x6b,0x65,0x65,0x70,0x20,0x61,0x6c,0x69,0x76,0x65,0x20,0x70,0x61,0x63,0x6b,0x65,0x74};


void hi_start_uaputl(UINT32 argc, CHAR **argv)
{
    uaputl_common(argc, argv);
}

void hi_start_mlanutl(UINT32 argc, CHAR **argv)
{
	cloud_keep_alive keepAlive;

	if(strcmp(argv[1],"cloud_keep_alive") == 0) {
		memset(&keepAlive,0x0,sizeof(keepAlive));
		keepAlive.mkeep_alive_id = 1;
		if(strcmp(argv[2], "start") == 0) {
			keepAlive.sendInterval = 55000; 	
			keepAlive.pkt_len = 67;
			keepAlive.enable = 1;
			memcpy(keepAlive.src_mac,src_mac,ETH_ALEN);
			memcpy(keepAlive.dst_mac,dst_mac,ETH_ALEN);
			memcpy(keepAlive.pkt,pkt,sizeof(pkt));
		} else if(strcmp(argv[2], "stop") == 0) {
			keepAlive.enable = 0;
		} else {
            printf("cloud_keep_alive: parameter is invalid\n");
            return;
        }

        mlanutl_keepalive(&keepAlive);
	}else if(strcmp(argv[1], "mefcfg") == 0){
		cloud_pkt_pattern wakeupPacket;
		memset(&wakeupPacket, 0, sizeof(cloud_pkt_pattern));
		wakeupPacket.filter_num = 4;//5
/*		
		wakeupPacket.filter[0].len = 6;
		wakeupPacket.filter[0].offset = 50;
		wakeupPacket.filter[0].repeat = 1;
		wakeupPacket.filter[0].rpn = 1;
		t_u8 byte_mac0[ETH_ALEN] = {0x00,0x00,0x00,0x00,0x00,0x00};//{0x57,0x61,0x6b,0x65,0x75,0x70}
		memcpy(wakeupPacket.filter[0].bytes, byte_mac0, ETH_ALEN);
*/
		wakeupPacket.filter[1].len = 6;
		wakeupPacket.filter[1].offset = 56;
		wakeupPacket.filter[1].repeat = 1;
		wakeupPacket.filter[1].rpn = 1;
		t_u8 byte_mac1[ETH_ALEN] = {0x00,0x00,0x00,0x00,0x00,0x00};//{0x42,0x79,0x48,0x69,0x6b,0x76}
		memcpy(wakeupPacket.filter[1].bytes, byte_mac1, ETH_ALEN);

		wakeupPacket.filter[2].len = 6;
		wakeupPacket.filter[2].offset = 62;
		wakeupPacket.filter[2].repeat = 1;
		wakeupPacket.filter[2].rpn = 1;
		t_u8 byte_mac2[6] = {0x00,0x00,0x00,0x00,0x00,0x00};//{0x69,0x73,0x69,0x6f,0x6e,0x48}
		memcpy(wakeupPacket.filter[2].bytes, byte_mac2, wakeupPacket.filter[2].len);
		
		wakeupPacket.filter[3].len = 6;
		wakeupPacket.filter[3].offset = 68;
		wakeupPacket.filter[3].repeat = 1;
		wakeupPacket.filter[3].rpn = 0;
		t_u8 byte_mac3[ETH_ALEN] = {0x00,0x00,0x00,0x00,0x00,0x00};//{0x57,0x61,0x6b,0x65,0x75,0x70}
		memcpy(wakeupPacket.filter[3].bytes, byte_mac3, ETH_ALEN);

		wakeupPacket.filter[4].len = 6;
		wakeupPacket.filter[4].offset = 74;
		wakeupPacket.filter[4].repeat = 1;
		wakeupPacket.filter[4].rpn = 0;
		t_u8 byte_mac4[ETH_ALEN] = {0x98,0x3b,0x16,0xf8,0xf3,0x9c};//{0x00,0x50,0x43,0x02,0xfe,0x01}
		memcpy(wakeupPacket.filter[4].bytes, byte_mac4, wakeupPacket.filter[4].len);
		mlanutl_wakeup(&wakeupPacket);
		
		
	}else 
        mlanutl_common(argc, argv);
}


void hi_start_dhcpc(UINT32 argc, CHAR **argv)
{
    struct netif *dev;
    int ret;

    if(wifi_mode) {
        printf("Can't run dhcpc since WiFi is working at AP mode\n");
        return;
    }
    ret = mrvl_wlan_open(&dev); 
    if(ret == 0) {
        printf("start dhcpc ......\n");
        netifapi_dhcp_start(dev);
    } else
        printf("faile to start dhcpc since wlan interface can't be opened\n");
}




int host_read_mcu()
{
    int val;
    himm (0x200F00E4,0x00);
    val = himd (0x201B0400);
    himm (0x201B0400,val&(~(0x01<<1)));
    val = himd (0x201B0008);
   
    return val;  
}

void wakeup_wifi()
{
#ifdef CFG_SUPPORT_WIFI_AP
    wifi_driver_init(1);
    msleep(500);
    hi_start_dhcpd(0,0);
#else
    wifi_driver_init(0);
    msleep(500);
    hi_start_dhcpc(0,0);
    msleep(500);
#endif
 
}

#endif

void hi_start_sta(char *ssid, char *bssid, uint8_t security, char *password, uint8_t channel)
{
#if (WIFITYPE==WIFI_6214)
	if (password == HI_NULL || strlen(password) == 0)
	{
		security = 0;
	}

	printf("wifi work in STA mode, begin to connect %s, password:%s\n", ssid, password);
	mhd_start_scan();
	mhd_sta_connect(ssid, bssid, security, password, channel);
	mhd_sta_network_up(0, 0, 0);	
	
#else if(WIFITYPE==WIFI_8801)
    char *security_name[] = {"open", "wep", "wpa-psk",
                             "wpa2-psk", "wpa-wpa2-psk_mix"};
    int ret;

    if (ssid == NULL) {
        dprintf("hi_start_sta: ssid is null\n");
        return;
    }

    if (password == HI_NULL || strlen(password) == 0)
    {
        security = 0;
    }

    printf("connect to -\n");
    printf("  ssid    : %s\n", ssid);
    printf("  security: %s\n", security_name[security]);
    printf("  password: %s\n", password);

    ret = mrvl_sta_connect(ssid, NULL, security, password);
    if (ret) {
        printf("mrvl_sta_connect failed ret = %d\n", ret);
        return;
    }

#endif

}



void hi_startwifi()
{


#if 1
    if (hi_mmcdev_isready("/dev/sdio0") != HI_SUCCESS)///dev/sdio1  for 3518e
    {
        return;
    }
#else
    sleep(5);
#endif


#if(WIFITYPE==WIFI_6214)

    //mhd_gpio_oob_register(6, 1, 0xC4, 0, 31);//3518e
    mhd_gpio_oob_register(6, 5, 0xD4, 0, 31);//hi3516c

    if (mhd_module_init())
    {
        printf("www_module_init failed!\n");
        return;
    }
	
	#ifdef CFG_SUPPORT_WIFI_AP
	
	hi_start_softap(CFG_HI_WIFI_AP_NAME, CFG_HI_WIFI_AP_PASSWD);
	#else
	
	
	/* get wifi config info from flash */
	struct wifi_info *g_wifi_info = wifi_zero_info_init();
	if (( g_wifi_info->zero_cfg.SSID.len > 0 && g_wifi_info->zero_cfg.SSID.len < 32 )&&(hi_zeroconfig_key_press()!=0))
		{

		hi_start_sta( g_wifi_info->zero_cfg.SSID.val, g_wifi_info->zero_cfg.BSSID.octet, g_wifi_info->zero_cfg.security,
						g_wifi_info->zero_cfg.security_key, g_wifi_info->zero_cfg.channel);
		
	} else {
		printf("\r\n *************Enter zero config**************\r\n");
		wifi_open_zero_cfg();
	}

	#endif

#else if(WIFITYPE==WIFI_8801)
/**************************************************************************
*wifi 启动判断口gpio7_1 为高，则不执行wifi 搜索连接步骤
*gpio7_1 为低，则手动开机，需要执行wifi 搜索连接步骤
***************************************************************************/
    if(host_read_mcu() == 0x02) 
		{
		wakeup_wifi();	
	    }
	else
		{
		//hi_start_wifi(0);
		Wifi_Register_Init(0);
		
		#ifdef CFG_SUPPORT_WIFI_AP
		hi_start_softap(CFG_HI_WIFI_AP_NAME, 6, 2, CFG_HI_WIFI_AP_PASSWD);
		#else
	    hi_start_sta(WIFISSID,0,4, WIFIPASSWORD,0);
		#endif
		}
#endif

    printf("\n hi_startwifi   end\n");
}




int secure_func_register(void)
{
    int ret;
    STlwIPSecFuncSsp stlwIPSspCbk= {0};
    stlwIPSspCbk.pfMemset_s = Stub_MemSet;
    stlwIPSspCbk.pfMemcpy_s = Stub_MemCpy;
    stlwIPSspCbk.pfStrNCpy_s = Stub_StrnCpy;
    stlwIPSspCbk.pfStrNCat_s = Stub_StrnCat;
    stlwIPSspCbk.pfStrCat_s = Stub_StrCat;
    stlwIPSspCbk.pfMemMove_s = Stub_MemMove;
    stlwIPSspCbk.pfSnprintf_s = Stub_Snprintf;
    stlwIPSspCbk.pfRand = rand;
    ret = lwIPRegSecSspCbk(&stlwIPSspCbk);
    if (ret != 0)
    {
        PRINT_ERR("\n***lwIPRegSecSspCbk Failed***\n");
        return -1;
    }

    PRINTK("\nCalling lwIPRegSecSspCbk\n");
    return ret;
}


void net_init(void)
{

    if (0 == netflag)
    {   
    printf("------------net_init-----------------\n");
		(void)secure_func_register();
		tcpip_init(NULL, NULL);
        hi_startwifi();
        netflag = 1;
    }
    else
    {
    
        //do nothing
    }
}


HI_S32 HI_Product_ShutDown(void)
{
    HI_S32 s32Ret = HI_SUCCESS;
    printf("------------shutdown-----------------\n");
    HI_HAL_MCUHOST_RegOn_Control(0);
    HI_Product_McuHost_Event_proc(0);
    HI_HAL_MCUHOST_PowreOff_Request();
    return s32Ret;
}

#if (WIFITYPE==WIFI_8801)

//wifi manual command just for debug
void hi_product_cmd_reg(void)
{
	osCmdReg(CMD_TYPE_EX, "closewifi", 0, (CMD_CBK_FUNC)mrvl_wifi_exit);
    osCmdReg(CMD_TYPE_EX, "mlanutl", 2, (CMD_CBK_FUNC)hi_start_mlanutl);
    osCmdReg(CMD_TYPE_EX, "uaputl", 2, (CMD_CBK_FUNC)hi_start_uaputl);
}
#endif
/*
	If receive any content, then shut down.
*/
void wait_standby()
{
    struct sockaddr_in addr;
    int sock;
    char* buf = NULL;
    int ret = 0;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("create sock failed \n");
        return;
    }

    buf = malloc(100);
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9527);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
    {
        printf("bind sock failed \n");
        goto errout;
    }

    int recv_bytes = recvfrom(sock, buf, 90, 0, NULL, NULL);

    printf("recv bytes:%d \n", recv_bytes);
    HI_Product_ShutDown();
errout:
    close(sock);
    free(buf);

}


void wifi_pre_proc()
{
	printf(" >>>>>%s line=%d \n",__FUNCTION__,__LINE__);
	
    Wifi_Register_Init(1);
   extern void wifi_power_set();
    sdio_squirk_dev_register(1, "broadcom", wifi_power_set);
    sdio_irq_enable(0);
	
}

