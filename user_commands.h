// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#ifndef USER_COMMANDS_H_
#define USER_COMMANDS_H_

#include "types.h"

void AddUser(hashtable_t *users, char *argv[]);

void Borrow(hashtable_t *users, hashtable_t *library, char *argv[]);

void Return(hashtable_t *users, hashtable_t *library, char *argv[]);

void Lost(hashtable_t *users, hashtable_t *library, char *argv[]);

#endif  // USER_COMMANDS_H_
