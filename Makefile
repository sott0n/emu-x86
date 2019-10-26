OBJS = main.o emulator_function.o instruction.o modrm.o io.o
CFALGS += -Wall -c

all:
	make emux86

%.o: %.c Makefile
	cc $(CFALGS) -o $@ $<

emux86: $(OBJS) Makefile
	cc -o emux86 $(OBJS)

.PHONY: all

clean:
	rm -f *.o emux86
