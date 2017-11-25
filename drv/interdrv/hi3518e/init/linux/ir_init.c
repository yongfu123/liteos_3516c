#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/version.h>

#include "hi_type.h"

#define OSDRV_MODULE_VERSION_STRING "HISI_ir @HiMPP"
extern int hiir_init(void);
extern void hiir_exit(void);

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,0,0)

static int __init hiir_mod_init(void)
{
    return hiir_init();
}

static void __exit hiir_mod_exit(void)
{
    hiir_exit();
}

module_init(hiir_mod_init);
module_exit(hiir_mod_exit);
MODULE_LICENSE("Proprietary");

#else
#include <linux/of_platform.h>

extern unsigned int ir_irq;
extern void* ir_reg_base;

static int hi_ir_probe(struct platform_device *pdev)
{
    
    struct resource *mem;
    mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    ir_reg_base = devm_ioremap_resource(&pdev->dev, mem);
    if (IS_ERR(ir_reg_base))
            return PTR_ERR(ir_reg_base);

    ir_irq = platform_get_irq(pdev, 0);
    if (ir_irq <= 0) {
        dev_err(&pdev->dev, "cannot find rtc IRQ\n");
    }
    return hiir_init();
}

static int hi_ir_remove(struct platform_device *pdev)
{
    hiir_exit();
    return 0;
}

static const struct of_device_id hi_ir_match[] = {
    { .compatible = "hisilicon,hi_ir" },
    {},
};

static struct platform_driver hi_ir_driver = {
    .probe  = hi_ir_probe,
    .remove = hi_ir_remove,
    .driver =  { .name = "hi_ir",
                .of_match_table = hi_ir_match,
               },
};

module_platform_driver(hi_ir_driver);
MODULE_LICENSE("GPL");
#endif

MODULE_AUTHOR("Hisilicon");
MODULE_DESCRIPTION("Hisilicon Infrared remoter(HIIR11) Device Driver");
MODULE_VERSION("HI_VERSION=" OSDRV_MODULE_VERSION_STRING);
