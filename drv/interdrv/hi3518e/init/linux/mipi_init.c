#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/version.h>

#include "hi_mipi.h"

#define OSDRV_MODULE_VERSION_STRING "HISI_mipi @HiMPP"

extern int mipi_init(void);
extern void  mipi_exit(void);

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,0,0)
static int __init mipi_mod_init(void)
{
	return mipi_init();
}

static void __exit mipi_mod_exit(void)
{
	mipi_exit();
}

module_init(mipi_mod_init);
module_exit(mipi_mod_exit);
MODULE_LICENSE("Proprietary");

#else
#include <linux/of_platform.h>

/*external symbol*/
extern void* reg_misc_base_va;
extern void* reg_crg_base_va;
/*internal symbol*/
extern unsigned int mipi_irq;
extern void  *gpMipiAllReg;
extern void* gpMiscRegBase;
extern void* gpCrgRegBase;

static int hi_mipi_probe(struct platform_device *pdev)
{
    struct resource *mem;
    mipi_irq = platform_get_irq(pdev, 0);
    if (mipi_irq <= 0) {
        dev_err(&pdev->dev, "cannot find mipi IRQ\n");
    }
    mem = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mipi");
    gpMipiAllReg = devm_ioremap_resource(&pdev->dev, mem);
    if (IS_ERR(gpMipiAllReg))
            return PTR_ERR(gpMipiAllReg);

    gpMiscRegBase = reg_misc_base_va;
    gpCrgRegBase = reg_crg_base_va;
    return mipi_init();
}

static int hi_mipi_remove(struct platform_device *pdev)
{
    mipi_exit();
    return 0;
}

static const struct of_device_id hi_mipi_match[] = {
    { .compatible = "hisilicon,hi35xx_mipi" },
    {},
};

static struct platform_driver hi_mipi_driver = {
    .probe  = hi_mipi_probe,
    .remove = hi_mipi_remove,
    .driver =  { .name = "hi_mipi",
                .of_match_table = hi_mipi_match,
               },
};
module_platform_driver(hi_mipi_driver);
MODULE_LICENSE("GPL");

#endif
/****************************************************************************
 * Export symbol                                                            *
 ****************************************************************************/
 extern int mipi_set_combo_dev_attr(combo_dev_attr_t* p_attr);
EXPORT_SYMBOL(mipi_set_combo_dev_attr);

int mipi_drv_set_phy_reg_start(HI_BOOL en);
EXPORT_SYMBOL(mipi_drv_set_phy_reg_start);

MODULE_AUTHOR("Digital Media Team ,Hisilicon crop ");
MODULE_DESCRIPTION("Mipi Driver");
MODULE_VERSION("HI_VERSION=" OSDRV_MODULE_VERSION_STRING);


