TARGET = in.bin out.bin select.bin subroutin32.bin
TOOLS = ../tools

CC = gcc
LD = ld
AS = nasm
CFLAGS += -nostdlib -fno-asynchronous-unwind-tables \
	-I$(TOOLS)/i386-elf-gcc/include -g -fno-pie -fno-stack-protector -m32
LDFLAGS += --entry=start --oformat=binary -Ttext 0x7c00 -m elf_i386

.PHONY: all
all :
	make $(TARGET)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $<

%.bin : %.o Makefile
	$(LD) $(LDFLAGS) -o $@ $<

%.bin : %.asm Makefile
	$(AS) -f bin -o $@ $<

clean :
	rm *.o *.bin