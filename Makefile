OBJS = main.o
CFALGS += -Wall

all :
	make emux86

%.o : %.c Makefile
	cc $(CFALGS) -c $<

emux86 : $(OBJS) Makefile
	cc -o $@ $(OBJS)

.PHONY: all