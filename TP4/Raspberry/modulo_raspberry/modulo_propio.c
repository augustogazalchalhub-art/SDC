#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo propio - TP4 SDC");
MODULE_AUTHOR("Grupo Hijos del AOE4");

int modulo_lin_init(void)
{
    printk(KERN_INFO "Modulo cargado en el kernel. Grupo Hijos del AOE4\n");

    return 0;
}

void modulo_lin_clean(void)
{
    printk(KERN_INFO "Modulo descargado del kernel. Grupo Hijos del AOE4\n");
}

module_init(modulo_lin_init);
module_exit(modulo_lin_clean);
