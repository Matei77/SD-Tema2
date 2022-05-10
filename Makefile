# Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
# compiler setup
CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99

# define targets
DEPEND=main.c library_commands.c user_commands.c hashtable.c linkedlist.c exit.c

build: main

main: $(DEPEND)
		$(CC) $(CFLAGS) $(DEPEND) -o main
pack:
		zip -FSr 313CA_IonescuMateiStefan_Tema2.zip README.md Makefile *.c *.h

clean:
		rm -f main *.o

.PHONY: pack clean