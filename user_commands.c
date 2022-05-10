// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_commands.h"
#include "types.h"
#include "hashtable.h"
#include "utils.h"

#define USER_DEFAULT_POINTS 100

// This function adds a new user to the database
void AddUser(hashtable_t *users, char *argv[])
{
	char *username = argv[0];

	if (ht_has_key(users, username)) {
		printf("User is already registered.\n");
		return;
	}

	// allocate memory for the new user
	user_t *user = malloc(sizeof(user_t));
	DIE(user == NULL, "user malloc");

	user->points = USER_DEFAULT_POINTS;
	user->status = 0;
	user->days_available = 0;
	memcpy(user->username, username, strlen(username) + 1);

	// add the new user to the database
	ht_put(users, username, strlen(username) + 1, user, sizeof(user_t));

	free(user);
}

// This function lets a user borrow a book
void Borrow(hashtable_t *users, hashtable_t *library, char *argv[])
{
	char *username = argv[0];
	char *bookname = argv[1];

	// transform the command's third argument string to integer
	int days_available = strtol(argv[2], NULL, 10);

	if (!ht_has_key(users, username)) {
		printf("You are not registered yet.\n");
		return;
	}

	user_t *user = (user_t *)ht_get(users, username);

	if (user->status == 2) {
		printf("You are banned from this library.\n");
		return;
	}

	if (user->status == 1) {
		printf("You have already borrowed a book.\n");
		return;
	}

	book_t *book = (book_t *)ht_get(library, bookname);

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	if (book->status == 1) {
		printf("The book is borrowed.\n");
		return;
	}

	// update the user and book status
	user->status = 1;
	user->days_available = days_available;
	memcpy(user->borrowed_book, bookname, BOOKNAME_LEN);
	book->status = 1;
}

// This function lets a user return a book
void Return(hashtable_t *users, hashtable_t *library, char *argv[])
{
	char *username = argv[0];
	char *bookname = argv[1];

	// transform the command's third and fourth argument strings to integers
	int days_since_borrow = strtol(argv[2], NULL, 10);
	int rating = strtol(argv[3], NULL, 10);

	user_t *user = (user_t *)ht_get(users, username);

	book_t *book = (book_t *)ht_get(library, bookname);

	if (user->status == 2) {
		printf("You are banned from this library.\n");
		return;
	}

	if (user->status == 0 || strcmp(bookname, user->borrowed_book) != 0) {
		printf("You didn't borrow this book.\n");
		return;
	}

	// check if the return was late
	if (user->days_available - days_since_borrow < 0) {
		user->points -= 2 * (days_since_borrow - user->days_available);
	} else {
		user->points += user->days_available - days_since_borrow;
	}

	// update book status
	book->status = 0;
	book->purchases++;
	book->rating += rating;

	// update user status
	if (user->points >= 0) {
		user->status = 0;
	} else {
		user->status = 2;
		printf("The user %s has been banned from this library.\n", username);
	}
}

// This function removes a lost book from the library
void Lost(hashtable_t *users, hashtable_t *library, char *argv[])
{
	char *username = argv[0];
	char *bookname = argv[1];

	user_t *user = (user_t *)ht_get(users, username);

	if (!ht_has_key(users, username)) {
		printf("You are not registered yet.\n");
		return;
	}

	if (user->status == 2) {
		printf("You are banned from this library.\n");
		return;
	}

	// remove the lost book
	book_t *book = (book_t *)ht_get(library, bookname);
	ht_free(book->content);
	ht_remove_entry(library, bookname);

	// update user points
	user->points -= 50;

	// update user status
	if (user->points >= 0) {
		user->status = 0;
	} else {
		user->status = 2;
		printf("The user %s has been banned from this library.\n", username);
	}
}
