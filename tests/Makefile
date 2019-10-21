TARGET = test.bin
OBJS = crt0.o test.o
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

%.o : %.asm Makefile
	$(AS) -f elf $<

$(TARGET) : $(OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

clean :
	rm *.o *.bin