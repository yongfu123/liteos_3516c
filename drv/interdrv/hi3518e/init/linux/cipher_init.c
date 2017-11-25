#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

#include "hi_type.h"
#include "drv_cipher.h"

#define OSDRV_MODULE_VERSION_STRING "HISI_mipi @HiMPP"

extern int CIPHER_DRV_ModInit(void);
extern void  CIPHER_DRV_ModExit(void);

static int __init cipher_mod_init(void)
{
	return CIPHER_DRV_ModInit();
}
static void __exit cipher_mod_exit(void)
{
	CIPHER_DRV_ModExit();
}


module_init(cipher_mod_init);
module_exit(cipher_mod_exit);

/*
****************************************************************************
* Export symbol                                                            *
****************************************************************************/
EXPORT_SYMBOL(HI_DRV_CIPHER_CreateHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_ConfigChn);
EXPORT_SYMBOL(HI_DRV_CIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_Encrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_Decrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_EncryptMulti);
EXPORT_SYMBOL(HI_DRV_CIPHER_DecryptMulti);
EXPORT_SYMBOL(HI_DRV_CIPHER_GetHandleConfig);
EXPORT_SYMBOL(HI_DRV_CIPHER_SoftReset);
EXPORT_SYMBOL(HI_DRV_CIPHER_Resume);
EXPORT_SYMBOL(HI_DRV_CIPHER_Suspend);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcRsa);

EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashInit);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashUpdate);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashFinal);

MODULE_AUTHOR("Digital Media Team ,Hisilicon crop ");
MODULE_DESCRIPTION("Cipher Driver");
MODULE_VERSION("HI_VERSION=" OSDRV_MODULE_VERSION_STRING);
MODULE_LICENSE("Proprietary");

