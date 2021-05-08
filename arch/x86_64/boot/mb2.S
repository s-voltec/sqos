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
  push eax  # magic
  push ebx  # Multiboot2 Boot Information
  mov eax, 0x80000000
  cpuid
  cmp eax, 0x80000008
  jae l1
  push 0  # maxphyaddr (dummy)
  jmp l2
l1:
  mov eax, 0x80000008
  cpuid
  and eax, 0xff
  push eax  # paddrWidth
l2:
  call boot_main
  add esp, 12
loop:
  hlt
  jmp loop
