// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#ifndef TYPES_H_
#define TYPES_H_

#define BOOKNAME_LEN 41
#define USERNAME_LEN 21

typedef struct ll_node_t {
	void *data;
	struct ll_node_t *next;
} ll_node_t;

typedef struct linked_list_t {
	ll_node_t *head;
	unsigned int data_size;
	unsigned int size;
} linked_list_t;

typedef struct info info;
struct info {
	void *key;
	void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t {
	linked_list_t **buckets;
	unsigned int size;  // total number of elements
	unsigned int hmax;  // number of buckets
	unsigned int (*hash_function)(void *);
	int (*compare_function)(void *, void *);
};

typedef struct book_t {
	hashtable_t *content;
	float rating;
	int purchases;
	int status;  // 0 - book not borrowed, 1 - book borrowed
	char bookname[BOOKNAME_LEN];
} book_t;

typedef struct user_t {
	int points;
	int status;  // 0 - book not borrowed, 1 - book borrowed, 2 - user banned
	int days_available;
	char username[USERNAME_LEN];
	char borrowed_book[BOOKNAME_LEN];
} user_t;

#endif  // TYPES_H_
