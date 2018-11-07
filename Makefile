PROGRAMS := executavel
SOURCES := function
CC := gcc
FLAGS := -Wall -Werror -pedantic -Wextra -fno-stack-protector -std=c11

all: $(SOURCES) $(PROGRAMS) rmobj

function: adjlist.h adjlist.c
	$(CC) $(FLAGS) -c adjlist.c
executavel: gentree.c adjlist.o
	$(CC) $(FLAGS) gentree.c adjlist.o -o executavel

rmobj: adjlist.o
	rm -rf *.o

clean: 
	rm -rf executavel
