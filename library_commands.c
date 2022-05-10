// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library_commands.h"
#include "types.h"
#include "hashtable.h"
#include "utils.h"

#define DEF_SIZE 21
#define BOOKS_HMAX 10

// This function adds a book to the library
void AddBook(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	// if a book with the same name allready exists remove it
	if (ht_has_key(library, bookname)) {
		book_t *book = (book_t *)ht_get(library, bookname);
		ht_free(book->content);
		ht_remove_entry(library, bookname);
	}

	// allocate memory for a new book
	book_t *book = malloc(sizeof(book_t));
	DIE(book == NULL, "book malloc");

	book->content =
		ht_create(BOOKS_HMAX, hash_function_string, compare_function_strings);
	book->rating = 0;
	book->purchases = 0;
	book->status = 0;
	memcpy(book->bookname, bookname, strlen(bookname) + 1);

	// transform the command's second argument string to integer
	int def_nr = strtol(argv[1], NULL, 10);

	char def_key[DEF_SIZE], val_key[DEF_SIZE];
	for (int i = 0; i < def_nr; i++) {
		scanf("%s %s", def_key, val_key);
		ht_put(book->content, def_key, strlen(def_key) + 1, val_key,
			   strlen(val_key) + 1);
	}
	if (def_nr != 0)
		getchar();

	// add the book to the library
	ht_put(library, bookname, strlen(bookname) + 1, book, sizeof(book_t));

	free(book);
}

// This function shows the details of a book
void GetBook(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	// find the book
	book_t *book = (book_t *)(ht_get(library, bookname));

	// show the book details
	float br = book->purchases == 0 ? 0 : book->rating / book->purchases;
	printf("Name:%s Rating:%.3f Purchases:%d\n", bookname, br, book->purchases);
}

// This function removes a book from the library
void RmvBook(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	// delete the book content and the book
	book_t *book = (book_t *)ht_get(library, bookname);
	ht_free(book->content);
	ht_remove_entry(library, bookname);
}

// This function adds a definition to a book
void AddDef(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	char *def_key = argv[1], *val_key = argv[2];

	// get the book
	book_t *book = (book_t *)ht_get(library, bookname);

	// add the definition in the book
	ht_put(book->content, def_key, strlen(def_key) + 1, val_key,
	 	   strlen(val_key) + 1);
}

// This function gets a definition from a book
void GetDef(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	// find the book
	book_t *book = (book_t *)(ht_get(library, bookname));

	char *def_key = argv[1];
	if (!ht_has_key(book->content, def_key)) {
		printf("The definition is not in the book.\n");
		return;
	}

	// get the definition
	char *val_key = (char *)ht_get(book->content, def_key);

	// print the definition
	printf("%s\n", val_key);
}

// This function removes a definition from a book
void RmvDef(hashtable_t *library, char *argv[])
{
	char *bookname = argv[0];

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	// find the book
	book_t *book = (book_t *)(ht_get(library, bookname));

	char *def_key = argv[1];
	if (!ht_has_key(book->content, def_key)) {
		printf("The definition is not in the book.\n");
		return;
	}

	// remove the definition
	ht_remove_entry(book->content, def_key);
}
