cc = gcc
prog = test


run: list.o main.o
	$(cc) -o $(prog) list.o main.o

list.o: list.c list.h node.h
	$(cc) -c list.c

main.o: main.c node.h list.h
	$(cc) -c main.c

clean:
	rm *.o
