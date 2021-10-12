cc=gcc
CFLAGS = -ansi -O2 -I. -UDEBUG
DEPS = types.h utils.h constant_info.h classfile.h access_flags.h jvm.h methodarea.h opcodes.h frame.h object.h
OBJ = utils.o constant_info.o classfile.o access_flags.o jvm.o methodarea.o opcodes.o frame.o

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) main.c -o $@ $^ $(CFLAGS)

clean:
	rm -f ${OBJ} main

.PHONY: clean
