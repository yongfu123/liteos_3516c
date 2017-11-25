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


static int netflag = 0;/*0-net is not inited; 1-net is inited*/




#define himm(address, value) writel(value, address)

void Wifi_Register_Init(int nFirst)
{
#if 0
//for 3518e 6214
    //for wifi led
    himm (0x200f005c, 0x0); //gpio 4_2
    himm (0x20180400, 0x04);
    himm (0x20180010, 0x00);


    //#oob GPIO 6-1
    himm (0x200f00C4, 0x0);


    himm (0x200f0020, 0x4); //dat0
    himm (0x200f001c, 0x4); //dat1
    himm (0x200f0034, 0x4); //dat2
    himm (0x200f0024, 0x4); //dat3
    himm (0x200f0018, 0x4); //cwpr
    himm (0x200f0028, 0x4); //cmd
    himm (0x200f0010, 0x4); //clk out
    himm (0x200f0014, 0x4); //card det
    himm (0x200f002c, 0x4); //pwr en


    //#regon GPIO 6-2
    himm (0x200f00C8, 0x0);
    //#set regon dir P6.2
    himm (0x201A0400, 0x04);

    if (nFirst)
    {
        himm (0x201A0010, 0x00);
    }
    else
    {
        himm (0x201a0010, 0x04);
    }
#else
dprintf("-----------------Wifi_Register_Init------------------ \n");

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
		
		himm (0x200f0098,0x1);//0£ºGPIO1_7£»1£ºSDIO0_CARD_POWER_EN¡£
		himm (0x200f009c,0x1);//0£ºGPIO4_7£»1£ºSDIO0_CARD_DETECT¡£
		himm (0x200f00a0,0x1);//0£ºGPIO5_0£»1£ºSDIO0_CWPR¡£
		himm (0x200f00a4,0x1);//0£ºGPIO5_1£»1£ºSDIO0_CCLK_OUT¡£
		himm (0x200f00a8,0x1);//0£ºGPIO5_2£»1£ºSDIO0_CCMD¡£
		himm (0x200f00ac,0x1);//0£ºGPIO5_3£»1£ºSDIO0_CDATA0¡£
		himm (0x200f00b0,0x1);//0£ºTEST_CLK£»1£ºSDIO0_CDATA1 ;   2 : GPIO5_3
		himm (0x200f00b4,0x1);//0£ºGPIO5_5£»1£ºSDIO0_CDATA2¡£
		himm (0x200f00b8,0x1);//0£ºGPIO5_6£»1£ºSDIO0_CDATA3¡£
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

#endif

}



void wifi_power_set()
	{
		writel(0x01, 0x201b0004);//16cv200
		//writel(0x04, 0x201a0010);//18ev200
	}


void hi_start_softap(char* ssid, char* password)
{
    uint8_t security = 2;
    uint8_t channel = 11;
    char* security_name[] = {"open", "wpa_psk_aes", "wpa2_psk_aes"};


    start_printf("config softap\n");
    start_printf("ssid    : %s\n", ssid);
    start_printf("password: %s\n", password);
    start_printf("security: %s\n", security_name[security]);
    start_printf("channel : %d\n", channel);

    mhd_softap_start(ssid, password, security, channel);


    uint32_t ip_address = 0xc0a80101;
    mhd_softap_start_dhcpd(ip_address);

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

void hi_start_sta(char* ssid, char* password)
{
    uint8_t security = 2;
    int i, conn;

    if (password == HI_NULL || strlen(password) == 0)
    {
        security = 0;
    }

    printf("wifi work in STA mode, begin to connect %s, password:%s\n", ssid, password);
    mhd_start_scan();
    mhd_sta_connect(ssid, NULL, security, password, 1);
    mhd_sta_network_up(0, 0, 0);
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
    hi_start_sta(CFG_ROUTER_SSID, CFG_ROUTER_PASSWD);
#endif
    printf("\nhi_startwifi   end\n");
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


void hi_product_cmd_reg(void)
{
	
}

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

