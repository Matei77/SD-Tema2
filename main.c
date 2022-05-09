// Copyright Ionescu Matei-Stefan - 313CAb - 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "hashtable.h"
#include "library_commands.h"
#include "user_commands.h"
#include "exit.h"

#define COMMAND_LEN 256
#define MAX_ARG_COUNT 10

void ParseCommand(char *command_line, char **command, char *argv[],
				  unsigned int *argc);

int main(void)
{
	
	hashtable_t *library = ht_create(10, hash_function_string, compare_function_strings);
	hashtable_t *users = ht_create(10, hash_function_string, compare_function_strings);

	unsigned int argc;
	char command_line[COMMAND_LEN], *command = NULL, *argv[MAX_ARG_COUNT];

	while (1) {
		ParseCommand(command_line, &command, argv, &argc);

		 if (command != NULL) {
		 	if (strcmp(command, "ADD_BOOK") == 0) {
		 		AddBook(library, argv);
			} else if (strcmp(command, "GET_BOOK") == 0) {
		 		GetBook(library, argv);
			} else if (strcmp(command, "RMV_BOOK") == 0) {
		 		RmvBook(library, argv);
			} else if (strcmp(command, "ADD_DEF") == 0) {
		 		AddDef(library, argv);
			} else if (strcmp(command, "GET_DEF") == 0) {
		 		GetDef(library, argv);
			} else if (strcmp(command, "RMV_DEF") == 0) {
		 		RmvDef(library, argv);
			} else if (strcmp(command, "ADD_USER") == 0) {
		 		AddUser(users, argv);
			} else if (strcmp(command, "BORROW") == 0) {
		 		Borrow(users, library, argv);
			} else if (strcmp(command, "RETURN") == 0) {
		 		Return(users, library, argv);
			} else if (strcmp(command, "LOST") == 0) {
		 		Lost(users, library, argv);
			} else if (strcmp(command, "EXIT") == 0) {
		 		Exit(users, library);
				return 0;
			} else {
				printf("Invalid command. Please try again.\n");
			}
		}
	}
}

// This function will read a string from keyboard and it will divide it into
// multiple substrings that will represent the command and its arguments
void ParseCommand(char *command_line, char **command, char *argv[],
				  unsigned int *argc)
{
	fgets(command_line, COMMAND_LEN - 1, stdin);

	*command = command_line;
	*argc = 0;
	int qm_nr = 0;

	int len = strlen(command_line) - 1;
	command_line[len] = '\0';

	for (int i = 0; i < len && argc < MAX_ARG_COUNT; i++) {
		if (command_line[i] == ' ' && qm_nr != 1) {
			command_line[i] = '\0';
			if (command_line[i + 1] != '"') {
				argv[(*argc)] = &command_line[i + 1];
				(*argc)++;
			} else {
				command_line[i+1] = '\0';
				argv[(*argc)] = &command_line[i + 2];
				(*argc)++;
				qm_nr++;
			}
		} else if (command_line[i] == '"') {
			qm_nr++;
			command_line[i] = '\0';	
		}
	}
}