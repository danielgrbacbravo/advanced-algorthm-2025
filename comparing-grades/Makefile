CC      := gcc
CFLAGS  := -g -O2 -Wall -Wextra -std=c11
LDLIBS  := -lm

build/prog: comparing-grades.c | build
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

build:
	mkdir -p $@

clean:
	rm -rf build
