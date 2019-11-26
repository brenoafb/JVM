
CC=gcc
CFLAGS= -g -ansi -I. -UDEBUG
DEPS = types.h utils.h constant_info.h classfile.h access_flags.h jvm.h methodarea.h opcodes.h frame.h
OBJ = utils.o constant_info.o classfile.o access_flags.o jvm.o methodarea.o opcodes.o frame.o
MAINSRC = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main.out

main.out: $(OBJ)
	$(CC) -o $@ $^ $(MAINSRC) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out *.o
