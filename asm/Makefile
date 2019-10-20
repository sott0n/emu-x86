TARGET = modrm-test.bin
TOOLS = ../tools

CC = gcc
LD = ld
AS = nasm
CFLAGS += -nostdlib -fno-asynchronous-unwind-tables \
	-I$(TOOLS)/i386-elf-gcc/include -g -fno-stack-protector
LDFLAGS += --entry=func --oformat=binary

.PHONY: all
all :
	make $(TARGET)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $<

%.bin : %.o Makefile
	$(LD) $(LDFLAGS) -o $@ $<

%.bin : %.asm Makefile
	$(AS) -f bin -o $@ $<
