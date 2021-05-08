#ifndef ARCH_BOOT_MM_H
#define ARCH_BOOT_MM_H

#include <boot/mb2.h>
#include <types.h>

typedef struct _BootMMap {
  u64 base, limit;
  struct _BootMMap *next, *prev;
} BootMMap;

int initBootMMap(struct _MB2BootInfo *bootInfo);
int allocBootMMap(struct _BootMMap **pMap);
void connectBootMMap(struct _BootMMap *p, struct _BootMMap *q);

#endif
