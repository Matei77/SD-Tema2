// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_commands.h"
#include "library_commands.h"
#include "types.h"
#include "hashtable.h"
#include "utils.h"

#define USER_DEFAULT_POINTS 100

void AddUser(hashtable_t *users, char *argv[]) {
	
	char *username = argv[0];

	if (ht_has_key(users, username)) {
		printf("User is already registered.\n");
		return;
	}

	user_t *user = malloc(sizeof(user_t));
	DIE (user == NULL, "user malloc");

	user->points = USER_DEFAULT_POINTS;
	user->status = 0;
	user->days_available = 0;
	memcpy(user->username, username, strlen(username) + 1);

	ht_put(users, username, strlen(username) + 1, user, sizeof(user_t));
}


void Borrow(hashtable_t *users, hashtable_t *library, char *argv[]) {
	
	char *username = argv[0];
	char *bookname = argv[1];
	// transform the command's first argument string to integer
	char *endptr;
	int days_available = strtol(argv[2], &endptr, 10);

	// check if the provided value was not a number
	DIE (argv[2] == endptr || *endptr != '\0', "wrong days_available value");

	if (!ht_has_key(users, username)) {
		printf("You are not registered yet.\n");
		return;
	}

	user_t *user = (user_t *)ht_get(users, username);

	if (user->status == 2) {
		printf("You are banned from this library.\n");
		return;
	}

	if (!ht_has_key(library, bookname)) {
		printf("The book is not in the library.\n");
		return;
	}

	book_t *book = (book_t*)ht_get(library, bookname);

	if (book->status == 1) {
		printf("The book is borrowed.\n");
		return;
	}

	if (user->status == 1) {
		printf("You have already borrowed a book.\n");
		return;
	}

	user->status = 1;
	user->days_available = days_available;
	memcpy(user->borrowed_book, bookname, BOOKNAME_LEN);
	book->status = 1;
	
}

void Return(hashtable_t *users, hashtable_t *library, char *argv[]) {

	char *username = argv[0];
	char *bookname = argv[1];

	// transform the command's first argument string to integer
	char *endptr;
	int days_since_borrow = strtol(argv[2], &endptr, 10);
	// check if the provided value was not a number
	DIE (argv[2] == endptr || *endptr != '\0', "wrong days_since_borrow value");

	int rating = strtol(argv[3], &endptr, 10);
	// check if the provided value was not a number
	DIE (argv[3] == endptr || *endptr != '\0', "wrong rating value");


	user_t *user = (user_t *)ht_get(users, username);

	book_t *book = (book_t*)ht_get(library, bookname);

	if (user->status == 2) {
		printf("You are banned from this library.\n");
		return;
	}

	if (user->status == 0 || strcmp(bookname, user->borrowed_book) != 0) {
		printf("You didn't borrow this book.\n");
		return;
	}

	if (user->days_available - days_since_borrow < 0) {
		user->points -= 2 * (days_since_borrow - user->days_available);
	} else {
		user->points += user->days_available - days_since_borrow;
	}

	book->status = 0;
	book->purchases++;
	book->rating += rating;

	if (user->points >= 0) {
		user->status = 0;
	} else {
		user->status = 2;
		printf("The user %s has been banned.\n", username);
	}
}

void Lost(hashtable_t *users, hashtable_t *library, char *argv[]) {

	char *username = argv[0];
	char *bookname = argv[1];

	user_t *user = (user_t *)ht_get(users, username);

	if (!ht_has_key(users, username)) {
		printf("You are not registered yet.\n");
		return;
	}

	if (user->status == 2) {
		printf("You are banned from this library.\n");
	}

	ht_remove_entry(library, bookname);

	user->points -= 50;

	if (user->points >= 0) {
		user->status = 0;
	} else {
		user->status = 2;
		printf("The user %s has been banned.\n", username);
	}
}


