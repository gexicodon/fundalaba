CC = gcc
CFLAG = -Iinclude -Wall -g

main: build/deque.o build/print.o build/main.o
	@mkdir -p build
	${CC} ${CFLAG} build/main.o build/deque.o build/print.o -o build/main

build/deque.o: src/deque.c include/deque.h
	@mkdir -p build
	${CC} ${CFLAG} -c src/deque.c -o build/deque.o

build/print.o: src/print.c include/print.h include/deque.h
	@mkdir -p build
	${CC} ${CFLAG} -c src/print.c -o build/print.o

build/main.o: src/main.c include/deque.h include/print.h
	@mkdir -p build
	${CC} ${CFLAG} -c src/main.c -o build/main.o

run: main
	./build/main

clean:
	rm -rf build

.PHONY: run clean