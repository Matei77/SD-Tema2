#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "types.h"

linked_list_t *ll_create(unsigned int data_size);

void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data);

ll_node_t *ll_remove_nth_node(linked_list_t *list, unsigned int n);

unsigned int ll_get_size(linked_list_t *list);

void ll_free(linked_list_t **pp_list);

// ? Maybe useless
void ll_print_int(linked_list_t *list);

// ? Maybe useless
void ll_print_string(linked_list_t *list);

// ? NOT IMPLEMENTED. Maybe should be
// ll_node_t *get_nth_node(linked_list_t *list, unsigned int n);

#endif  // LINKED_LIST_H_