CC=gcc
CFLAGS=-I.
DEPS = types.h utils.h
OBJ = utils.o
MAINSRC = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.out: $(OBJ)
	$(CC) -o $@ $^ $(MAINSRC) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out *.o
