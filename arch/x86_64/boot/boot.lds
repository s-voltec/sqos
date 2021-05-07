OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

SECTIONS {
  . = 0;
  __init_code_begin = .;
  .text : { *(.text) }
  . = ALIGN(4);
  .rodata : { *(.rodata) }
  . = ALIGN(4);
  .data : { *(.data) }
  . = ALIGN(4);
  .bss : { *(.bss) }
  . = ALIGN(4);
  .stack : {
    /* スタックは少なくとも2ページを確保し、終端をページ境界へ合わせる。 */
    . += 0x2000;
    . = ALIGN(0x1000);
    __stack_init = . - 4;
  }
  __init_code_end = .;

  . = 0x00100000;
  __kernel_elf_begin = .;
  kernel64 : { *(kernel64) }
  __kernel_elf_end = .;
}
