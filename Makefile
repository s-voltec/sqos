# options
MAKEFLAGS += -rR

# constants
ARCH := x86_64
DEBUG := true
ROOTDIR := $(CURDIR)
ARCHDIR := $(ROOTDIR)/arch/$(ARCH)
BOOTDIR := $(ARCHDIR)/boot
OBJECTS := *.elf
# サンプル用のコードなので、複雑になるヘッダファイルの依存解決は行わず、すべて.cをすべての.hに依存させる
HEADERS := $(shell find $(ROOTDIR) -type f -name '*.h')

# commands
CC := gcc
LD := ld
RM := rm -f

# flags
CFLAGS := -pipe -fno-stack-protector -fno-pie -fno-common -fno-builtin \
	-fno-asynchronous-unwind-tables -nostdinc -Wall -c -DARCH_$(ARCH) \
	-I$(ROOTDIR)/include -I$(ARCHDIR)/include
ifeq ($(DEBUG), true)
	CFLAGS += -DDEBUG -O0 -g
else
	CFLAGS += -Os
endif
LDFLAGS := -nostdlib

# default action
.PHONY: default
default: boot.elf

include $(BOOTDIR)/Makefile

# rules
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $*.o $*.c

# actions
.PHONY: clean
clean:
	$(RM) $(OBJECTS)

.PHONY: run
run:
	$(MAKE) boot.elf
	$(MAKE) -C run
