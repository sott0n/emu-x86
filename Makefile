OBJS = main.o emulator_function.o instruction.o modrm.o
CFALGS += -Wall

all:
	make emux86
	rm -f *.o

%.o: %.c Makefile
	cc $(CFALGS) -c $<

emux86: $(OBJS) Makefile
	cc -o $@ $(OBJS)

.PHONY: all