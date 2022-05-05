#include <arch/boot/context.h>
#include <arch/boot/mm.h>
#include <arch/boot/serial.h>
#include <arch/page.h>
#include <arch/serial.h>
#include <stddef.h>

// メモリ管理処理。
// メモリ領域はページ境界に合わせて処理する。

extern BootContext bootContext;

int initBootMMap(MB2BootInfo *bootInfo) {
  // 処理簡略化のため、メモリマップの先頭はサイズ0のエントリにしておく。
  bootContext.mmap = &bootContext.mmapBuffer[0];
  bootContext.mmap->base = 0;
  bootContext.mmap->limit = 0;
  bootContext.mmap->next = bootContext.mmap;
  bootContext.mmap->prev = bootContext.mmap;

  // free listを初期化する。
  bootContext.freeMMapEnt = &bootContext.mmapBuffer[1];
  bootContext.mmapBuffer[1].prev = &bootContext.mmapBuffer[BOOT_CONTEXT_NUM_MMAP - 1];
  bootContext.mmapBuffer[1].next = &bootContext.mmapBuffer[2];
  for(int i = 2;i < BOOT_CONTEXT_NUM_MMAP;i++) {
    bootContext.mmapBuffer[i].prev = &bootContext.mmapBuffer[i - 1];
    bootContext.mmapBuffer[i].next = &bootContext.mmapBuffer[i + 1];
  }

  // Boot InfoのRAM領域をコピー
  for(u32 i = 0;i < bootContext.numMBMMap;i++) {
    if(bootContext.mbMMap[i].type == MB2MMAP_TYPE_RAM) {
      BootMMap *p;
      if(allocBootMMap(&p) != 0) {
        return -1;
      }
      p->base = bootContext.mbMMap[i].baseAddr;
      p->limit = p->base + bootContext.mbMMap[i].length;
      p->base = (p->base + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
      p->limit = p->limit & ~(PAGE_SIZE - 1);
      connectBootMMap(bootContext.mmap->prev, p);
    }
  }

  return 0;
}

int allocBootMMap(BootMMap **pMap) {
  if(bootContext.freeMMapEnt == NULL) {
    // あらかじめコピー元の要素数をチェックしているので、足りなくなることはないはず。
    // だが、コピー先配列の長さに番兵の要素を考慮していないので、コピー元要素数が最大の場合に足りなくなる。
    bootSerialPrint(SERIAL_COM1, "BUG: unable to allocate boot memory map entry.\n");
    return -1;
  }

  BootMMap *map = bootContext.freeMMapEnt;
  if(map->next != map) {
    map->next->prev = map->prev;
    map->prev->next = map->next;
    bootContext.freeMMapEnt = map->next;
  } else {
    bootContext.freeMMapEnt = NULL;
  }

  map->prev = map;
  map->next = map;
  *pMap = map;

  return 0;
}

void connectBootMMap(BootMMap *p, BootMMap *q) {
  p->next->prev = q;
  q->next = p->next;
  p->next = q;
  q->prev = p;
}
