#include <boot/mb2magic.h>

  .text
  .code32
  .intel_syntax noprefix

  .global _start
_start:
  jmp start
  # Multiboot2 Magic Fields
  .align 8
mb2h_start:
  .long MB2_H_MAGIC
  .long MB2_H_ARCH
  .long mb2h_end - mb2h_start
  .long (-(MB2_H_MAGIC + MB2_H_ARCH + mb2h_end - mb2h_start)) & 0xffffffff
  # End of Tags
  .align 8
  .long 0  # type
  .long 8  # length
mb2h_end:

  .extern __stack_init
  .extern boot_main
start:
  lea esp, [__stack_init]
  call boot_main
loop:
  hlt
  jmp loop
