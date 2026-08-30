
all: calc test-mini test-mini2 caller

# TODO: complete makefile rules for calc, test-mini, test-mini2, caller.
CC = gcc
calc: calc.c mystery.o
	$(CC) -Wall calc.o mystery.o -o calc

test-mini: mini.c test.c
	$(CC) mini.c test.c -Wall -o test-mini

test-mini2: mini_mod.S test.c
	$(CC) -c -o test.o test.c
	as -o mini2.o mini_mod.S
	$(CC) test.o mini2.o -Wall -o test-mini2


caller: caller.c
	$(CC) caller.c -Wall -o caller
clean:
	rm -f *.o
	rm -f calc
	rm -f caller
	rm -f test-mini
	rm -f test-mini2