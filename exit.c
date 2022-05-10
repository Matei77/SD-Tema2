// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit.h"
#include "hashtable.h"
#include "types.h"

int CompareBook(book_t *book1, book_t *book2)
{
	float b1_rt = book1->purchases == 0 ? 0 : book1->rating / book1->purchases;
	float b2_rt = book2->purchases == 0 ? 0 : book2->rating / book2->purchases;

	if (b1_rt > b2_rt) {
		return 1;
	} else if (b1_rt < b2_rt) {
		return 2;
	} else if (book1->purchases > book2->purchases) {
		return 1;
	} else if (book1->purchases < book2->purchases) {
		return 2;
	} else if (strcmp(book1->bookname, book2->bookname) < 0) {
		return 1;
	} else {
		return 2;
	}
}

void TopBooks(hashtable_t *library)
{
	book_t **array = malloc(library->size * sizeof(book_t *));

	int k = 0;

	for (unsigned int i = 0; i < library->hmax; i++) {
		ll_node_t *it = library->buckets[i]->head;
		while (it) {
			array[k++] = ((book_t *)((info *)it->data)->value);
			it = it->next;
		}
	}

	for (int i = 0; i < k - 1; i++) {
		for (int j = i + 1; j < k; j++) {
			if (CompareBook(array[i], array[j]) == 2) {
				book_t *aux = array[i];
				array[i] = array[j];
				array[j] = aux;
			}
		}
	}

	printf("Books ranking:\n");
	for (int i = 0; i < k; i++) {
		float br = array[i]->purchases == 0
			? 0
			: array[i]->rating / array[i]->purchases;
		printf("%d. Name:%s Rating:%.3f Purchases:%d\n", i + 1,
			   array[i]->bookname, br, array[i]->purchases);
	}

	free(array);
}

int CompareUsers(user_t *user1, user_t *user2)
{
	if (user1->points > user2->points) {
		return 1;
	} else if (user1->points < user2->points) {
		return 2;
	} else if (strcmp(user1->username, user2->username) < 0) {
		return 1;
	} else {
		return 2;
	}
}

void TopUsers(hashtable_t *users)
{
	user_t **array = malloc(users->size * sizeof(user_t *));

	int k = 0;

	for (unsigned int i = 0; i < users->hmax; i++) {
		ll_node_t *it = users->buckets[i]->head;
		while (it) {
			if (((user_t *)((info *)it->data)->value)->status != 2)
				array[k++] = ((user_t *)((info *)it->data)->value);
			it = it->next;
		}
	}

	for (int i = 0; i < k - 1; i++) {
		for (int j = i + 1; j < k; j++) {
			if (CompareUsers(array[i], array[j]) == 2) {
				user_t *aux = array[i];
				array[i] = array[j];
				array[j] = aux;
			}
		}
	}

	printf("Users ranking:\n");
	for (int i = 0; i < k; i++) {
		printf("%d. Name:%s Points:%d\n", i + 1, array[i]->username,
			   array[i]->points);
	}

	free(array);
}

void Exit(hashtable_t *users, hashtable_t *library)
{
	TopBooks(library);
	TopUsers(users);

	for (unsigned int i = 0; i < library->hmax; i++) {
		ll_node_t *it = library->buckets[i]->head;
		while (it) {
			ht_free(((book_t *)((info *)it->data)->value)->content);
			it = it->next;
		}
	}
	ht_free(library);
	ht_free(users);
}
