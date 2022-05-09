// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library_commands.h"
#include "hashtable.h"
#include "types.h"
#include "utils.h"

#define DEF_SIZE 21

void AddBook(hashtable_t *library, char *argv[])
{

	char *bookname = argv[0];

	if (ht_has_key(library, bookname)) {
		ht_remove_entry(library, bookname);
	}

	book_t *book = malloc(sizeof(book_t));
	DIE(book == NULL, "book malloc");

	book->content =
		ht_create(10, hash_function_string, compare_function_strings);
	book->rating = 0;
	book->purchases = 0;
	book->status = 0;
	memcpy(book->bookname, bookname, strlen(bookname) + 1);

	// transform the command's first argument string to integer
	char *endptr;
	int def_nr = strtol(argv[1], &endptr, 10);

	// check if the provided value was not a number
	DIE(argv[1] == endptr || *endptr != '\0', "wrong def_nr value");

	char def_key[DEF_SIZE], val_key[DEF_SIZE];
	for (int i = 0; i < def_nr; i++) {
		scanf(" %s %s", def_key, val_key);
		ht_put(book->content, def_key, strlen(def_key) + 1, val_key,
			   strlen(def_key) + 1);
	}
	getchar();

	ht_put(library, bookname, strlen(bookname) + 1, book, sizeof(book_t));
}

void GetBook(hashtable_t *library, char *argv[])
{

	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	book_t *book = (book_t *)(ht_get(library, bookname));

	printf("Name:%s Rating:%.3f Purachases:%d\n", bookname, book->rating,
		   book->purchases);
}

void RmvBook(hashtable_t *library, char *argv[])
{

	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	ht_remove_entry(library, bookname);
}

void AddDef(hashtable_t *library, char *argv[])
{

	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	char *def_key = argv[1], *val_key = argv[2];

	book_t *book = (book_t *)ht_get(library, bookname);

	ht_put(book->content, def_key, strlen(def_key) + 1, val_key,
		   strlen(val_key) + 1);
}

void GetDef(hashtable_t *library, char *argv[])
{

	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	book_t *book = (book_t *)(ht_get(library, bookname));

	char *def_key = argv[1];
	if (!ht_has_key(book->content, def_key)) {
		printf("The definition is not in the book.\n");
		return;
	}

	char *val_key = (char *)ht_get(book->content, def_key);

	printf("%s\n", val_key);
}

void RmvDef(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	book_t *book = (book_t *)(ht_get(library, bookname));

	char *def_key = argv[1];
	if (!ht_has_key(book->content, def_key)) {
		printf("The definition is not in the book.\n");
		return;
	}

	ht_remove_entry(book->content, def_key);
}
