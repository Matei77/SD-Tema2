# Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
# compiler setup
CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99

# define targets
DEPEND=main.c library_commands.c user_commands.c hashtable.c linkedlist.c exit.c

build: tema2

tema1: $(DEPEND)
		$(CC) $(CFLAGS) $(DEPEND) -o tema2
pack:
		zip -FSr 313CA_IonescuMateiStefan_Tema2.zip README.md Makefile *.c *.h

clean:
		rm -f tema2 *.o

.PHONY: pack clean