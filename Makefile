CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -I.
DEPS = types.h utils.h constant_info.h classfile.h attributes.h
OBJ = utils.o constant_info.o classfile.o attributes.o
MAINSRC = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.out: $(OBJ)
	$(CC) -o $@ $^ $(MAINSRC) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out *.o
