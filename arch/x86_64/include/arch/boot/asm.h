#ifndef ARCH_BOOT_ASM_H
#define ARCH_BOOT_ASM_H

#include <types.h>

u8 in8(u16 port);
void out8(u16 port, u8 data);

#endif
