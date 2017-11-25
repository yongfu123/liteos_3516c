#include "los_printf.h"

#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "eth_drv.h"
#include "arch/perf.h"

#include "fcntl.h"
#include "fs/fs.h"

#include "stdio.h"

#include "shell.h"
#include "hisoc/uart.h"
#include "vfs_config.h"
#include "disk.h"

#include "los_cppsupport.h"

#include "los_scatter.h"

extern UINT32 g_sys_mem_addr_end;
extern unsigned int g_uart_fputc_en;
extern unsigned int g_uwFatSectorsPerBlock;
extern unsigned int g_uwFatBlockNums;


void board_config(void)
{
	g_sys_mem_addr_end = SYS_MEM_BASE + SYS_MEM_SIZE_DEFAULT;
	g_uwSysClock = OS_SYS_CLOCK;
	g_uart_fputc_en = 1;
#ifndef TWO_OS
	extern unsigned long g_usb_mem_addr_start;
	extern unsigned long g_usb_mem_size;
	g_usb_mem_addr_start = g_sys_mem_addr_end;
	g_usb_mem_size = 0x20000; //recommend 128K nonCache for usb

	g_uwFatSectorsPerBlock = CONFIG_FS_FAT_SECTOR_PER_BLOCK;
	g_uwFatBlockNums	   = CONFIG_FS_FAT_BLOCK_NUMS;
	//different board should set right mode:"rgmii" "rmii" "mii"
	//if you don't set :
	//hi3516a board's default mode is "rgmii"
	//hi3518ev200 board's default mode is "rmii"
	//hi3519 board's default mode is "rgmii"
#if defined(HI3516A) || defined(HI3519) || defined(HI3519V101) || defined(HI3559)
	hisi_eth_set_phy_mode("rgmii");
#endif
#if defined(HI35168EV200)
	hisi_eth_set_phy_mode("rmii");
#endif
	//different board should set right addr:0~31
	//if you don't set ,driver will detect it automatically
	//hisi_eth_set_phy_addr(0);//0~31

#if (defined(HI3518EV200) &&defined(LOSCFG_DRIVERS_EMMC)) || defined(HI3519) || defined(HI3519V101) || defined(HI3559)
	size_t part0_start_sector = 16	 * (0x100000/512);
	size_t part0_count_sector = 1024 * (0x100000/512);
	size_t part1_start_sector = 16	 * (0x100000/512) + part0_count_sector;
	size_t part1_count_sector = 1024 * (0x100000/512);
	extern struct disk_divide_info emmc;
	add_mmc_partition(&emmc, part0_start_sector, part0_count_sector);
	add_mmc_partition(&emmc, part1_start_sector, part1_count_sector);
#endif
#endif
}




void misc_driver_post_init()
{
	ran_dev_register();
    
    i2c_dev_init();
    hi_gpio_init();
    hi_dmac_init();
}


void misc_driver_init()
{
    hi_uartdev_init();
    system_console_init(TTY_DEVICE);
    SD_MMC_Host_init();
	//misc_driver_post_init();
    spinor_init();
}

