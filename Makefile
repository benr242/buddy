cc:=gcc
ccflags:=-MMD -g -Wall
ldflags:=

LIST:=list.o node.o

all: list.o Buddy

Buddy: Buddy.c $(LIST)
	$(cc) $(ccflags) -o $@ Buddy.c $(LIST)

list.o: list.c node.o
	$(cc) $(ccflags) -c -o $@ list.c

node.o: node.c node.h
	$(cc) $(ccflags) -c -o $@ node.c
	
.PHONY: clean test valgrind

clean:
	rm -f *.[od] *.so $(prog) lib-$(prog) buddy

test: $(prog)
	$(test)

valgrind: $(prog)
	valgrind --tool=memcheck --leak-check=yes $(test)

