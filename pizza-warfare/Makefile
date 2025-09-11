build/prog: pizza-warfare.c
	mkdir -p build
	gcc -g -o build/prog pizza-warfare.c

clean:
	rm -rf build

valgrind: build/prog
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/prog < 1.in
