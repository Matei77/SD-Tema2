**Name: Ionescu Matei-Ștefan**  
**Group: 313CAb**

# Homework #2 - The Library of HashBabel

## Description:

The program starts by reading commands from the keyboard.  
The supported commands are:

1. **ADD_BOOK \<book_name> \<def_number>**

	*This command adds a book to the library.*

	When the *ADD_BOOK* command is given, the *AddBook* function will be called
	and it will read *\<def_number>* definitions from keyboard and add them to
	a new book with the name *\<book_name>*, that will be added to the library.

2. **GET_BOOK \<book_name>**
	
	*This command shows the details of a book from the library.*
	
	When the *GET_BOOK* command is given, the *GetBook* function will be called
	and it will check if the book with the name *\<book_name>* exists in the
	library. If this is the case it will show the details of the book.

3. **RMV_BOOK \<book_name>**
	
	*This command removes a book from the library.*
	
	When the *RMV_BOOK* command is given, the *RmvBook* function will be called
	and it will check if the book with the name *\<book_name>* exists in the
	library. If this is the case it will remove it from the library database.

4. **ADD_DEF \<book_name> \<def_key> \<def_val>**

	*This command adds a new definition to a book.*

	When the *ADD_DEF* command is given, the *AddDef* function will be called
	and it will check if the book with the name *\<book_name>* exists in the
	library. If this is the case it will add the *\<def_key> - \<def_val>* pair
	to the book's content.

5. **GET_DEF \<book_name> \<def_key>**

	*This command gets a definition from a book.*

	When the *GET_DEF* command is given, the *GetDef* function will be called
	and it will check if the book with the name *\<book_name>* exists in the
	library and if the definition exits in the book. If this is the case it will
	show the value of the definition with the name *\<def_key>*.

6. **RMV_DEF \<book_name> \<def_key>**

	*This command removes a definition from a book.*

	When the *RMV_DEF* command is given, the *RmvDef* function will be called
	and it will check if the book with the name *\<book_name>* exists in the
	library and if the definition exits in the book. If this is the case it will
	remove the *\<def_key>* definition from the book.

7. **ADD_USER \<user_name>**

	*This function adds a new user to the users database.*

	When the *ADD_USER* command is given the *AddUser* function will be called
	and it will check if the user with the name *\<user_name*> does not already
	exit. If this is the case, it will add it the the database.

8. **BORROW \<user_name> \<book_name> \<days_available>**

	*This command lets a user borrow a book.*

	When the *BORROW* command is given the *Borrow* function will be called and
	it will check if the user with the name *\<user_name>* and the book with the
	name *\<book_name> exist in the databases and are eligible. If this is the
	case, it will update the book's and the user's statuses and let the user
	borrow the book for *\<days_available>* days.

9. **RETURN \<user_name> \<book_name> \<days_since_borrow> \<rating>**

	*This command lets a user return a book.*

	When the *RETURN* command is given the *Return* function will be called and
	it will check if the user with the name *\<user_name>* borrowed the book
	*\<book_name>*. If this is the case, it will update the book's rating and
	status and the user's points and status.

10. **LOST \<user_name> \<book_name>**

	*This command removes a lost book from the library.*

	When the *LOST* command is given the *Lost* function will be called and it
	will check if the user with the name *\<user_name>* is registered. If this
	is the case the book will be removed from the library and the user's points
	will be updated.

11. **EXIT**

	*This command shows the rankings of books and users and exits the program.*

	When the *EXIT* command is given the *Exit* function will be called and it
	will show the rankings of books and users and free all the allocated memory.
	The command will then return 0 in main, ending the execution of the program.


## Comments on homework:

* Do you think you could have done a better implementation?
	
	> Well, I don't think that my implementation is perfect, so it could
	> probably be improved, but this is the best implementation that I could do
	> and I am pretty happy with how it turned out.

* What did you learn from doing this homework?

	> I learned to implement and use generic hashtables, and to better organize
	> my code.

* Other comments

	> I liked the homework and I think it achieved its objectives.
