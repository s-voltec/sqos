#ifndef BOOT_MB2_H
#define BOOT_MB2_H

#include <boot/mb2magic.h>
#include <types.h>

#define MB2_BI_MEMORY_MAP 6
typedef struct _MB2MMap {
  u64 baseAddr, length;
  #define MB2MMAP_TYPE_RAM 1
  u32 type;
  u32 reserved;
} MB2MMap;
typedef struct _MB2MemoryMapTag {
  u32 type, size;
  u32 entrySize, entryVersion;
  struct _MB2MMap entHead[];
} MB2MemoryMapTag;

#define MB2_BI_END_OF_TAGS 0
#define MB2_TAG_ALIGN 8
typedef struct _MB2BootInfoTag {
  u32 type, size;
} MB2BootInfoTag;

typedef struct _MB2BootInfo {
  u32 totalSize, reserved;
  struct _MB2BootInfoTag tagsHead[];
} MB2BootInfo;

#endif
