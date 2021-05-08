#ifndef ARCH_BOOT_CONTEXT_H
#define ARCH_BOOT_CONTEXT_H

#include <arch/boot/mm.h>
#include <boot/mb2.h>

#define BOOT_CONTEXT_MBMMAP_MAX 32
#define BOOT_CONTEXT_NUM_MMAP 32
typedef struct _BootContext {
  u32 numMBMMap;
  struct _MB2MMap mbMMap[BOOT_CONTEXT_MBMMAP_MAX];
  struct _BootMMap mmapBuffer[BOOT_CONTEXT_NUM_MMAP];
  struct _BootMMap *mmap, *freeMMapEnt;
} BootContext;

#endif
