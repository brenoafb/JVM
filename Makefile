CC=gcc
CFLAGS= -g -ansi -I. -UDEBUG
DEPS = types.h utils.h constant_info.h classfile.h access_flags.h
OBJ = utils.o constant_info.o classfile.o access_flags.o
MAINSRC = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main.out

main.out: $(OBJ)
	$(CC) -o $@ $^ $(MAINSRC) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out *.o
