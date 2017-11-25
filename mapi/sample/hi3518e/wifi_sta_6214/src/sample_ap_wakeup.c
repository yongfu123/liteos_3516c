#include "sys/types.h"
#include "los_printf.h"
#include "stdio.h"
#include "shell.h"

#include "hisoc/uart.h"


int debug_on = 1;

void app_init(void)
{
    misc_driver_init();

    mcu_uart_proc();

    wifi_pre_proc();

    hi_product_wifi_image_proc();


#ifndef CFG_WIFI_IMAGE
    //User can place business code here.
    osShellInit(TTY_DEVICE);
    hi_product_cmd_reg();
    net_init();

    sleep(2);//wait a moment
    dprintf("------------------start finish------------------ \n");
    wait_standby();

#endif

    while (1)
    {
        sleep(1);
    }
}


