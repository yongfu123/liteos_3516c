#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/version.h>

//#include "hi_type.h" 
#include "hi_rtc.h"

#define OSDRV_MODULE_VERSION_STRING "HISI_rtc @HiMPP"

extern int t_second;
module_param(t_second, int, 0);

extern int rtc_init(void);
extern void rtc_exit(void);

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,0,0)

static int __init rtc_mod_init(void)
{
    return rtc_init();
}

static void __exit rtc_mod_exit(void)
{
    rtc_exit();
}

module_init(rtc_mod_init);
module_exit(rtc_mod_exit);
MODULE_LICENSE("Proprietary");
#else
#include <linux/of_platform.h>

extern unsigned int rtc_irq;
extern void* rtc_base_addr;
extern void* crg_base_addr;
extern void* reg_crg_base_va;
static int hi_rtc_probe(struct platform_device *pdev)
{
    struct resource *mem;
   
    mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    rtc_base_addr = devm_ioremap_resource(&pdev->dev, mem);
    if (IS_ERR(rtc_base_addr))
            return PTR_ERR(rtc_base_addr);
    
    crg_base_addr = reg_crg_base_va;
    
    rtc_irq = platform_get_irq(pdev, 0);
    if (rtc_irq <= 0) {
            dev_err(&pdev->dev, "cannot find rtc IRQ\n");
    }
    return rtc_init();
}

static int hi_rtc_remove(struct platform_device *pdev)
{
    rtc_exit();
    return 0;
}

static const struct of_device_id hi_rtc_match[] = {
    { .compatible = "hisilicon,hi_rtc" },
    {},
};

static struct platform_driver hi_rtc_driver = {
    .probe  = hi_rtc_probe,
    .remove = hi_rtc_remove,
    .driver =  { .name = "hi_rtc",
                .of_match_table = hi_rtc_match,
               },
};
module_platform_driver(hi_rtc_driver);
MODULE_LICENSE("GPL");
#endif

MODULE_AUTHOR("Hisilicon");
MODULE_DESCRIPTION("Hisilicon Infrared remoter(HIIR11) Device Driver");
MODULE_VERSION("HI_VERSION=" OSDRV_MODULE_VERSION_STRING);
