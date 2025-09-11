CC      := gcc
CFLAGS  := -g -O2 -Wall -Wextra -std=c11
LDLIBS  := -lm

build/prog: grading-connundrum.c | build
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

build:
	mkdir -p $@

clean:
	rm -rf build

valgrind: build/prog
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/prog < 1.in
