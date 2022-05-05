#ifndef ARCH_BOOT_SERIAL_H
#define ARCH_BOOT_SERIAL_H

#include <types.h>

int initBootSerial(u16 port);
void bootSerialPrint(u16 port, const char *s);

#endif
