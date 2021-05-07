#ifndef BOOT_MB2MAGIC_H
#define BOOT_MB2MAGIC_H

#define MB2_H_MAGIC 0xe85250d6
#ifdef ARCH_x86_64
#define MB2_H_ARCH 0
#else
#error MB2_H_ARCH is used for unsupported architecture.
#endif

#endif
