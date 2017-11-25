#include <stdio.h>
#include "sys/types.h"
#include "sys/time.h"
#include "hi_type.h"
#include "sys/prctl.h"
#include "los_runstop.h"
#include "fcntl.h"
#include "uart-hisilicon.h"
#include "hisoc/uart.h"
#include "hi_ext_hal_mcu.h"
#include "asm/platform.h"
#include "bcm_wifi.h"
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/tcpip.h"
#include "netif/ifaddrs.h"

#include "wifi_zero_config.h"


#define FLASH_APP_IMG_ADDR (0x40000)//0x40000
#define FLASH_WIFI_IMG_ADDR (0x450000)//0x300000

#define CRC_DATA_LEN (512)
#define CRC_FLASH_ADDRESS    (0x800000-0x10000)
#define WIFIINFOADDR    (0x720000-0x10000)


#define ERASE_ALIGN_SIZE   (0x10000)

#define READ_ALIGN_SIZE      (1)
#define WRITE_ALIGN_SIZE      (1)


#define IP4ADDR(ipaddr, a,b,c,d) \
        ipaddr = ((u32_t)((a) & 0xff) << 24) | \
                         ((u32_t)((b) & 0xff) << 16) | \
                         ((u32_t)((c) & 0xff) << 8)  | \
                          (u32_t)((d) & 0xff)


void uart2_gpio_cfg()
{
#if 0
		writew(0x04, IO_MUX_REG_BASE + 0x088);
		writew(0x04, IO_MUX_REG_BASE + 0x094);
#else
		writew(0x3, IO_MUX_REG_BASE + 0x0CC);	
		writew(0x3, IO_MUX_REG_BASE + 0x0D0);	
#endif

}

#ifdef CFG_SUPPORT_WIFI_STA
int wifi_info_suspend()
{
	struct wifi_info g_wifi_info;
	memset(&g_wifi_info,0,sizeof(struct wifi_info));
	hispinor_read(&g_wifi_info,WIFIINFOADDR,sizeof(struct wifi_info));

	struct wifi_info wifi_info;
	struct netif *netif=netif_find("wlan0");
	memset(&wifi_info,0,sizeof(struct wifi_info));
	memcpy(&wifi_info.addr.ipaddr,&netif->ip_addr,sizeof(unsigned int));
	memcpy(&wifi_info.addr.netmask,&netif->netmask,sizeof(unsigned int));
	memcpy(&wifi_info.addr.gw,&netif->gw,sizeof(unsigned int));
	
	if (memcmp(&g_wifi_info,&wifi_info,sizeof(wifi_info)) != 0)
	{
		printf("wifi info write to flash\n");
		hispinor_erase(WIFIINFOADDR, 0x10000);
		hispinor_write(&wifi_info, WIFIINFOADDR, sizeof(struct wifi_info));
	}
}

int wifi_info_resume()
{
	struct wifi_info g_wifi_info;
	memset(&g_wifi_info,0,sizeof(struct wifi_info));
	dprintf("wifi info resume read ip sizeof(struct wifi_info) %x\n",sizeof(struct wifi_info));

	hispinor_read(&g_wifi_info,WIFIINFOADDR,sizeof(struct wifi_info));
	dprintf("wifi info resume read over\n");

	struct wifi_info wifi_info;
	struct netif *netif=netif_find("wlan0");
	memset(&wifi_info,0,sizeof(struct wifi_info));
	memcpy(&wifi_info.addr.ipaddr,&netif->ip_addr,sizeof(unsigned int));
	memcpy(&wifi_info.addr.netmask,&netif->netmask,sizeof(unsigned int));
	memcpy(&wifi_info.addr.gw,&netif->gw,sizeof(unsigned int));

	if (memcmp(&g_wifi_info,&wifi_info,sizeof(wifi_info)) != 0)
	{
		unsigned int ip_addr;
		unsigned int gw;
		unsigned int netmask;
		uint8_t byte_ip[4];
		memcpy(byte_ip,&g_wifi_info.addr.ipaddr,4);
		IP4ADDR(ip_addr,byte_ip[0],byte_ip[1],byte_ip[2],byte_ip[3]);

		memcpy(byte_ip,&g_wifi_info.addr.gw,4);
		IP4ADDR(gw,byte_ip[0],byte_ip[1],byte_ip[2],byte_ip[3]);

		memcpy(byte_ip,&g_wifi_info.addr.netmask,4);
		IP4ADDR(netmask,byte_ip[0],byte_ip[1],byte_ip[2],byte_ip[3]);
		//start_printf("~~~~~~~~~~~~~~~~~~~~~ip_addr=%x wifi_info.addr.ip_addr=%x\n",ip_addr,g_wifi_info.addr.ipaddr);
		dprintf("wifi info resume to wifi driver\n");

		mhd_sta_network_down();
		mhd_sta_network_up(ip_addr, gw, netmask);
		dprintf("wifi info resume over\n");
	}
}
#endif

static void Wifi_Wake_From_Suspend()
{
    uart_resume(NULL);
    //uart0_resume();
    hal_interrupt_unmask(5);
    hal_interrupt_unmask(25);

    extern UINT16 g_swtmr_id;
    LOS_SwtmrStart(g_swtmr_id);


    Wifi_Register_Init(0);

    mmc_host_resume(NULL);
    //mmc_host_resume_from_wakeup();


    host_oob_interrupt_config();
    host_oob_interrupt_enable();
    hal_interrupt_unmask(31);

	//hi_uart_config_2(); 
	uart2_gpio_cfg();
    HI_HAL_MCUHOST_WiFi_ON_Request(1);
#ifdef CFG_SUPPORT_WIFI_AP
    mhd_wowl_ap_disable();
#else
    mhd_wowl_sta_disable();
#if 1
    mhd_wifi_set_scansuppress(0); // set scansuppress to 1
    mhd_sta_set_powersave(2, 0);
    mhd_sta_set_bcn_li_dtim(0); // if ap router dtim is 2 seconds
#endif
#endif

    
	spinor_init();
	//extern int spinor_host_resume();
    //spinor_host_resume();


	#ifdef CFG_SUPPORT_WIFI_STA
	wifi_info_resume();
	#endif

}

HI_U32 wifi_image_update_flag()
{
    char strFlashTime[CRC_DATA_LEN] = {0};
    char strTempTime[100] = {0};

    sprintf(strTempTime, "%s_%s", __DATE__, __TIME__);
    printf("update flag compile time:%s \n", strTempTime);
    memset(strFlashTime, 0, sizeof(strFlashTime));
    memcpy(strFlashTime, strTempTime, sizeof(strTempTime));
    hispinor_erase(CRC_FLASH_ADDRESS, 0x10000);
    hispinor_write((void*)strFlashTime, CRC_FLASH_ADDRESS, CRC_DATA_LEN);
    return 0;
}
static void Wifi_Image_Done()
{
    uart_resume(NULL);
    //uart0_resume();
    extern UINT32 g_uwWowImgSize;
    printf("---------------flash ok! image length  0x%x\n", g_uwWowImgSize);
    extern UINT16 g_swtmr_id;
    LOS_SwtmrStart(g_swtmr_id);

    mmc_host_resume(NULL);
    //mmc_host_resume_from_image();
    host_oob_interrupt_enable();

#ifdef CFG_SUPPORT_WIFI_AP
    mhd_wowl_ap_disable();
#else
    mhd_wowl_sta_disable();
#endif

    wifi_image_update_flag();



}

static int Wifi_Read_Flash(void* memaddr, unsigned long start, unsigned long size)
{
    return hispinor_read(memaddr, start, size);

}


static int Wifi_Write_Flash(void* memaddr, unsigned long start, unsigned long size)
{
    int ret = 0;
    ret |= hispinor_erase(start, size);
    ret |= hispinor_write(memaddr, start, size);
    return ret;
}



int hi_product_wifi_image_proc()
{

    int uwRet = HI_SUCCESS;

    char strTempTime[CRC_DATA_LEN] = {0};
    sprintf(strTempTime, "%s_%s", __DATE__, __TIME__);

    char strFlashTime[CRC_DATA_LEN] = {0};

    hispinor_read(strFlashTime, CRC_FLASH_ADDRESS, 512);


    if (strcmp(strFlashTime, strTempTime) != 0)
    {
        net_init();

#ifdef CFG_SUPPORT_WIFI_AP
        mhd_wowl_ap_enable();
#else
		mhd_wowl_sta_add("0x983B16F8F39C", 66);
		mhd_wowl_sta_enable();

#endif


        host_oob_interrupt_disable();
        mmc_host_suspend(NULL);
        //extern UINT32 LOS_SwTmrStop(UINT16 usSwTmrID);
        extern UINT16 g_swtmr_id;
        LOS_SwtmrStop(g_swtmr_id);


        RUNSTOP_PARAM_S stRunstopParam;

        memset(&stRunstopParam, 0, sizeof(stRunstopParam));


        memset(&stRunstopParam, 0, sizeof(RUNSTOP_PARAM_S));
        stRunstopParam.pfFlashReadFunc			= Wifi_Read_Flash;
        stRunstopParam.pfFlashWriteFunc 		= Wifi_Write_Flash;
        stRunstopParam.pfImageDoneCallback		= Wifi_Image_Done;
        stRunstopParam.pfWakeupCallback 		= Wifi_Wake_From_Suspend;
        stRunstopParam.uwFlashEraseAlignSize	= ERASE_ALIGN_SIZE;
        stRunstopParam.uwFlashWriteAlignSize	= WRITE_ALIGN_SIZE;
        stRunstopParam.uwFlashReadAlignSize 	= READ_ALIGN_SIZE;
        stRunstopParam.uwImageFlashAddr 		= FLASH_APP_IMG_ADDR;
        stRunstopParam.uwWowFlashAddr			= FLASH_WIFI_IMG_ADDR;

        uart_suspend(NULL);
        //uart0_suspend();
        LOS_MakeImage(&stRunstopParam);

        printf("\nfile: %s func: %s line: %d  LOS_MakeImage done\n", __FILE__, __FUNCTION__, __LINE__);



        if (uwRet != HI_SUCCESS)
        {
            printf("\nLOS_MakeImage Error uwRet = 0x%x\n", uwRet);
            return HI_FAILURE;
        }

    }

}

