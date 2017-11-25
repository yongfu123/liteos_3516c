
#include "sys/types.h"
#include "stdio.h"
#include "shell.h"
#include "los_scatter.h"

#include "hisoc/uart.h"



int debug_on =1;



void app_init(void)
{


    misc_driver_init();
    mcu_uart_proc();
    wifi_pre_proc();
	

   // hi_product_wifi_image_proc();

#ifndef CFG_WIFI_IMAGE
    //User can place business code here.
    misc_driver_post_init();
    osShellInit(TTY_DEVICE);
    hi_product_cmd_reg();
    net_init();
    HI_Product_OpenWifiStaServer();
    dprintf("------------------start finish------------------ \n");			
#endif

 
    while (1)
    {
        sleep(3);
		
    }

}


