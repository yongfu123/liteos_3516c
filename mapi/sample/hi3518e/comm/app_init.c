/******************************************************************************
  Some simple Hisilicon Hi3516A system functions.

  Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2016-6 Created
******************************************************************************/
#include "sys/types.h"
#include "sys/time.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/statfs.h"
#include "limits.h"

#include "los_event.h"
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

#include "linux/fb.h"

#include "adaptsecure.h"

#define HI35168EV200 1


int argc=9;
char **argv[9][17]=\
	{"eth0","192.168.1.2",\
	 "netmask","255.255.255.0",\
	 "gateway","192.168.1.1",\
	 "hw","ether","a2:88:92:4e:34:29"};


/*
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
*/
extern int mem_dev_register(void);
extern UINT32 osShellInit();
extern int app_main();

struct netif *pnetif;


static int taskid = -1;

void app_sample()
{
    int ret = 0;
    TSK_INIT_PARAM_S stappTask;

    if (taskid != -1)
    {
        dprintf("There's a sample task existed.");
    }

    memset(&stappTask, 0, sizeof(TSK_INIT_PARAM_S));
    stappTask.pfnTaskEntry = (TSK_ENTRY_FUNC)app_main;
    stappTask.uwStackSize = 0x10000;
    stappTask.pcName = "sample";
    stappTask.usTaskPrio = 10;
    stappTask.uwResved = LOS_TASK_STATUS_DETACHED;
    ret = LOS_TaskCreate(&taskid, &stappTask);
    if(ret != 0)
    {
        dprintf("Creat sample task fail...\n");
    }
    dprintf("sample task id %d\n", taskid);

    //chdir("/sd0");
    //chdir("/nfs");
    chdir("/sd0p0");

}

extern int _ipcm_vdd_init(void);

void sample_command(void)
{
    osCmdReg(CMD_TYPE_STD, "sample", 0, (CMD_CBK_FUNC)app_sample);
}

void net_init_tcp()
{
    (void)secure_func_register();
    tcpip_init(NULL, NULL);
#ifdef LOSCFG_DRIVERS_HIGMAC
    extern struct los_eth_driver higmac_drv_sc;
    pnetif = &(higmac_drv_sc.ac_if);
    higmac_init();
#endif
	
#ifdef LOSCFG_DRIVERS_HIETH_SF
    extern struct los_eth_driver hisi_eth_drv_sc;
    pnetif = &(hisi_eth_drv_sc.ac_if);
    hisi_eth_init();
#endif

    dprintf("cmd_startnetwork : DHCP_BOUND finished\n");

    netif_set_up(pnetif);
}

extern unsigned int g_uwFatSectorsPerBlock;
extern unsigned int g_uwFatBlockNums;
#define SUPPORT_FMASS_PARITION
#ifdef SUPPORT_FMASS_PARITION
extern int fmass_register_notify(void(*notify)(void* context, int status), void* context);
extern int fmass_partition_startup(char* path);
void fmass_app_notify(void* conext, int status)
{
    if(status == 1)/*usb device connect*/
    {
        char *path = "/dev/mmcblk0p0";
        //startup fmass access patition
        fmass_partition_startup(path);
    }
}
#endif

#include "board.h"
extern UINT32 g_sys_mem_addr_end;
extern unsigned int g_uart_fputc_en;
/*
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
    g_uwFatBlockNums       = CONFIG_FS_FAT_BLOCK_NUMS;
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
    size_t part0_start_sector = 16   * (0x100000/512);
    size_t part0_count_sector = 1024 * (0x100000/512);
    size_t part1_start_sector = 16   * (0x100000/512) + part0_count_sector;
    size_t part1_count_sector = 1024 * (0x100000/512);
    extern struct disk_divide_info emmc;
    add_mmc_partition(&emmc, part0_start_sector, part0_count_sector);
    add_mmc_partition(&emmc, part1_start_sector, part1_count_sector);
#endif
#endif
}
*/
void app_init(void)
{
    int s32Ret = 0;

    dprintf("uart init ...\n");
    hi_uartdev_init();

    dprintf("shell init ...\n");
    system_console_init(TTY_DEVICE);
    osShellInit(TTY_DEVICE);
 
    dprintf("spi bus init ...\n");
    hi_spi_init();
    
    dprintf("dmac init\n");
    hi_dmac_init();

    dprintf("i2c bus init ...\n");
    i2c_dev_init();
    
    dprintf("random dev init ...\n");
    ran_dev_register();
	
    dprintf("mem dev init ...\n");
	mem_dev_register();
	
    dprintf("fb dev init ...\n");
    struct fb_info *info = malloc(sizeof(struct fb_info));
	register_framebuffer(info);
	
	dprintf("porc fs init ...\n");
    proc_fs_init();

    dprintf("cxx init ...\n");
    extern char __init_array_start__, __init_array_end__;
    LOS_CppSystemInit((unsigned long)&__init_array_start__, (unsigned long)&__init_array_end__, NO_SCATTER);

#ifndef TWO_OS
    dprintf("nand init ...\n");
    if(!nand_init()) {
        add_mtd_partition("nand", 0x200000, 32*0x100000, 0);
        add_mtd_partition("nand", 0x200000 + 32*0x100000, 32*0x100000, 1);
        mount("/dev/nandblk0", "/yaffs0", "yaffs", 0, NULL);
        //mount("/dev/nandblk1", "/yaffs1", "yaffs", 0, NULL);
    }

    dprintf("spi nor flash init ...\n");
    if(!spinor_init()){
        add_mtd_partition("spinor", 0x100000, 2*0x100000, 0);
        add_mtd_partition("spinor", 3*0x100000, 2*0x100000, 1);
        mount("/dev/spinorblk0", "/jffs0", "jffs", 0, NULL);
        //mount("/dev/spinorblk1", "/jffs1", "jffs", 0, NULL);
    }
    
    dprintf("gpio init ...\n");
    hi_gpio_init();
	
	
#if 1//(WIFITYPE!=WIFI_8801)

    dprintf("net init ...\n");
    //net_init();
	net_init_tcp();
	
	lwip_ifconfig(argc,argv);

#endif
	
    dprintf("sd/mmc host init ...\n");
    SD_MMC_Host_init();
    msleep(2000);
    s32Ret = mount("/dev/mmcblk0p0", "/sd0p0", "vfat", 0, 0);
    if (s32Ret)
        dprintf("mount mmcblk0p0 to sd0p0 err %d\n", s32Ret);
    s32Ret = mount("/dev/mmcblk0p1", "/sd0p1", "vfat", 0, 0);
    if (s32Ret)
        dprintf("mount mmcblk0p1 to sd0p1 err %d\n", s32Ret);
    s32Ret = mount("/dev/mmcblk1p0", "/sd1p0", "vfat", 0, 0);
    if (s32Ret)
        dprintf("mount mmcblk1p0 to sd1p0 err %d\n", s32Ret);
    s32Ret = mount("/dev/mmcblk2p0", "/sd2p0", "vfat", 0, 0);
    if (s32Ret)
        dprintf("mount mmcblk2p0 to sd2p0 err %d\n", s32Ret);

    dprintf("usb init ...\n");
    //g_usb_mem_addr_start and g_usb_mem_size must be set in board_config
    //usb_init must behind SD_MMC_Host_init
    s32Ret = usb_init();
#ifdef SUPPORT_FMASS_PARITION
    if(!s32Ret)
        fmass_register_notify(fmass_app_notify,NULL);
#endif
	
#ifdef HI3516A
    dprintf("dvfs init ...\n");
    dvfs_init();
#endif
#endif

    dprintf("g_sys_mem_addr_end=0x%08x,\n",g_sys_mem_addr_end);
    dprintf("done init!\n");
    dprintf("Date:%s.\n", __DATE__);
    dprintf("Time:%s.\n", __TIME__);

#ifdef TWO_OS
    extern int _ipcm_vdd_init(void);
    extern int ipcm_net_init(void);

    dprintf("tcpip init ...\n");
    (void)secure_func_register();
    tcpip_init(NULL, NULL);

    dprintf("_ipcm vdd init ...\n");
    _ipcm_vdd_init();

    dprintf("ipcm net init ...\n");
    ipcm_net_init();
#endif
	
	 dprintf("------------------start app------------------ \n");
		
    SDK_init();
    CatLogShell();
    sample_command();
	//app_main();
		
    s32Ret = HI_MAPI_Sys_Init();
    if(0 != s32Ret)
    {
        printf("HI_MAPI_Sys_Init fail\n");
        return;
    }

    return;
}

/* EOF kthread1.c */
