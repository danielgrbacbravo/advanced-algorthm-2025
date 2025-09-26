CC      := gcc
CFLAGS  := -g -O2 -Wall -Wextra -std=c11
LDLIBS  := -lm

build/prog: card-game.c | build
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

build:
	mkdir -p $@

clean:
	rm -rf build

leaks: build/prog
	leaks --list --atExit -- ./build/prog < 1-valgrind.in
