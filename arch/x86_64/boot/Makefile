# constants
OBJS := mb2.o boot.o
BOOTOBJS := $(addprefix $(BOOTDIR)/, $(OBJS))
OBJECTS += $(BOOTOBJS)

# rules
boot.elf: $(BOOTDIR)/boot.lds $(BOOTOBJS)
	$(LD) $(LDFLAGS) -T $(BOOTDIR)/boot.lds -o boot.elf $(BOOTOBJS)

$(BOOTDIR)/%.o: $(BOOTDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -m32 -Wa,--32 -o $(BOOTDIR)/$*.o $(BOOTDIR)/$*.c

$(BOOTDIR)/%.o: $(BOOTDIR)/%.S $(HEADERS)
	$(CC) $(CFLAGS) -m32 -Wa,--32 -o $(BOOTDIR)/$*.o $(BOOTDIR)/$*.S
