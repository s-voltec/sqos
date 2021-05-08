#include <arch/boot/context.h>
#include <arch/boot/mm.h>
#include <boot/mb2.h>
#include <types.h>

BootContext bootContext;
static int initBootContext(MB2BootInfo *bootInfo);

int boot_main(u32 paddrWidth, MB2BootInfo *bootInfo, u32 magic) {
  if(magic != MB2_MAGIC) {
    return -1;
  }
  if(initBootContext(bootInfo) != 0) {
    return -1;
  }

  return 0;
}

static int copyMemoryMap(MB2MemoryMapTag *t) {
  u32 num = (t->size - sizeof(MB2MemoryMapTag)) / t->entrySize;
  bootContext.numMBMMap = num;
  if(num >= BOOT_CONTEXT_MBMMAP_MAX) {
    return -1;
  }

  void *p = t->entHead;
  for(u32 i = 0;i < num;i++) {
    bootContext.mbMMap[i] = *((MB2MMap *) (p + t->entrySize * i));
  }

  return 0;
}

static int initBootContext(MB2BootInfo *bootInfo) {
  void *p = bootInfo->tagsHead;
  MB2BootInfoTag *t = p;
  while(t->type != MB2_BI_END_OF_TAGS) {
    switch(t->type) {
    case MB2_BI_MEMORY_MAP:
      if(copyMemoryMap(p) != 0) {
        return -1;
      }
      break;
    }
    p+= (t->size + MB2_TAG_ALIGN - 1) & ~(MB2_TAG_ALIGN - 1);
    t = p;
  }

  if (initBootMMap(bootInfo) != 0) {
    return -1;
  }

  return 0;
}
