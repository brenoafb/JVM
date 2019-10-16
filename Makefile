CC=gcc
CFLAGS= -D DEBUG -g -ansi -Wall -Wextra -I.
DEPS = types.h utils.h constant_info.h classfile.h
OBJ = utils.o constant_info.o classfile.o
MAINSRC = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main.out

main.out: $(OBJ)
	$(CC) -o $@ $^ $(MAINSRC) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out *.o
