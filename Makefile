CC = gcc 

OBJs = iloc.c instr.c simulator.c

default: build

build: ${OBJs}
	${CC} ${OBJs} -o iloc

clean:
	rm -f iloc *.o
