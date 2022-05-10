// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#ifndef LIBRARY_COMMANDS_H_
#define LIBRARY_COMMANDS_H_

#include "types.h"

void AddBook(hashtable_t *library, char *argv[]);

void GetBook(hashtable_t *library, char *argv[]);

void RmvBook(hashtable_t *library, char *argv[]);

void AddDef(hashtable_t *library, char *argv[]);

void GetDef(hashtable_t *library, char *argv[]);

void RmvDef(hashtable_t *library, char *argv[]);

#endif  // LIBRARY_COMMANDS_H_
