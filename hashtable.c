// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "linkedlist.h"
#include "types.h"
#include "utils.h"

#define MAX_STRING_SIZE 256
#define HMAX 10

/*
 * Functii de comparare a cheilor:
 */
int compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char *)a;
	unsigned int hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

/*
 * Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
 * Trebuie alocate si initializate si listele inlantuite.
 */
hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
					   int (*compare_function)(void *, void *))
{
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));
	if (!hashtable) {
		printf("Memory allocation failed.\n");
		exit(-1);
	}

	hashtable->buckets = malloc(hmax * sizeof(linked_list_t));
	if (!hashtable->buckets) {
		printf("Memory allocation failed.\n");
		exit(-1);
	}

	for (unsigned int i = 0; i < hmax; i++) {
		hashtable->buckets[i] = ll_create(sizeof(info));
	}

	hashtable->size = 0;
	hashtable->hmax = hmax;
	hashtable->hash_function = hash_function;
	hashtable->compare_function = compare_function;

	return hashtable;
}

/*
 * Functie care intoarce:
 * 1, daca pentru cheia key a fost asociata anterior o valoare in hashtable
 * folosind functia put 0, altfel.
 */
int ht_has_key(hashtable_t *ht, void *key)
{
	unsigned int index = ht->hash_function(key) % HMAX;

	ll_node_t *it = ht->buckets[index]->head;

	while (it) {
		if (ht->compare_function(((info *)it->data)->key, key) == 0)
			return 1;
		it = it->next;
	}

	return 0;
}

void *ht_get(hashtable_t *ht, void *key)
{
	unsigned int index = ht->hash_function(key) % HMAX;

	ll_node_t *it = ht->buckets[index]->head;

	while (it) {
		if (ht->compare_function(((info *)it->data)->key, key) == 0)
			return ((info *)it->data)->value;
		it = it->next;
	}

	return NULL;
}

/*
 * Atentie! Desi cheia este trimisa ca un void pointer (deoarece nu se impune
 * tipul ei), in momentul in care se creeaza o noua intrare in hashtable (in
 * cazul in care cheia nu se gaseste deja in ht), trebuie creata o copie a
 * valorii la care pointeaza key si adresa acestei copii trebuie salvata in
 * structura info asociata intrarii din ht. Pentru a sti cati octeti trebuie
 * alocati si copiati, folositi parametrul key_size.
 *
 * Motivatie:
 * Este nevoie sa copiem valoarea la care pointeaza key deoarece dupa un apel
 * put(ht, key_actual, value_actual), valoarea la care pointeaza key_actual
 * poate fi alterata (de ex: *key_actual++). Daca am folosi direct adresa
 * pointerului key_actual, practic s-ar modifica din afara hashtable-ului cheia
 * unei intrari din hashtable. Nu ne dorim acest lucru, fiindca exista riscul sa
 * ajungem in situatia in care nu mai stim la ce cheie este inregistrata o
 * anumita valoare.
 */
void ht_put(hashtable_t *ht, void *key, unsigned int key_size, void *value,
			unsigned int value_size)
{
	void *p = ht_get(ht, key);

	if (p) {
		ht_remove_entry(ht, key);
	}

	unsigned int index = ht->hash_function(key) % HMAX;

	info *node_data = malloc(sizeof(info));
	if (!node_data) {
		printf("Memory allocation failed.\n");
		exit(-1);
	}
	node_data->key = malloc(key_size);
	if (!node_data->key) {
		printf("Memory allocation failed.\n");
		exit(-1);
	}
	node_data->value = malloc(value_size);
	if (!node_data->value) {
		printf("Memory allocation failed.\n");
		exit(-1);
	}
	memmove(node_data->key, key, key_size);
	memmove(node_data->value, value, value_size);

	ll_add_nth_node(ht->buckets[index], ht->buckets[index]->size + 1,
					node_data);

	free(node_data);

	ht->size++;
}

/*
 * Procedura care elimina din hashtable intrarea asociata cheii key.
 * Atentie! Trebuie avuta grija la eliberarea intregii memorii folosite pentru o
 * intrare din hashtable (adica memoria pentru copia lui key --vezi observatia
 * de la procedura put--, pentru structura info si pentru structura Node din
 * lista inlantuita).
 */
void ht_remove_entry(hashtable_t *ht, void *key)
{
	if (ht_has_key(ht, key) == 0)
		return;

	unsigned int index = ht->hash_function(key) % HMAX;

	ll_node_t *it = ht->buckets[index]->head;
	unsigned int n = 0;

	while (it) {
		if (ht->compare_function(((info *)it->data)->key, key) == 0) {
			free(((info *)it->data)->key);
			free(((info *)it->data)->value);
			ll_node_t *p = ll_remove_nth_node(ht->buckets[index], n);
			if (p) {
				free(p->data);
				p->data = NULL;
				free(p);
				p = NULL;
			}
			return;
		}
		it = it->next;
		n++;
	}
}

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable,
 * dupa care elibereaza si memoria folosita pentru a stoca structura hashtable.
 */
void ht_free(hashtable_t *ht)
{
	for (int i = 0; i < HMAX; i++) {
		ll_node_t *it = ht->buckets[i]->head;
		while (it) {
			free(((info *)it->data)->key);
			free(((info *)it->data)->value);
			it = it->next;
		}
		ll_free(&(ht->buckets[i]));
	}
	free(ht->buckets);
	free(ht);
}

unsigned int ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}

unsigned int ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}
