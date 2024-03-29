# ICS 212 | Project 1 | Bank Record Database

Project Requirements:

`addRecord` will add a new record into an appropriate place so the list is in descending order.

`addRecord` does not accept a duplicate account number.

`printRecord` will print the record with the matching account number.

`printAll` will print the contents of the entire database

`modifyRecord` will modify the address field of a record specified by account number.

`deleteRecord` will delete the record with the specified account number.

`readfile` must be called once at the start of the main function.

`writefile` must be called once at the end of the main function.

`cleanup` must release all allocated spaces in the heap memory and assign NULL to start.

The account number must be positive (> 0).

The name field must allow spaces but no other special characters such as a newline character

For example, "Tetsuya", "Dr. Dennis Ritchie", "John F. Kennedy Jr.", "Elizabeth Alexandra Mary Windsor", and so on.

Write your getaddress function to obtain the address information

The address field may have multiple lines of address

* It must be stored as one character array

* You CANNOT ask the user how many lines of address they are going to type

* You CANNOT ask if the user wants to fill another line while he/she is typing

* You CANNOT ask if the user wants to type one more line during typing.

* Prototype for the function is ``void getaddress (char [ ], int);``

# Debug Mode

* A global variable debugmode must be defined. No other global variables may be used.

* Your program must use command-line arguments for debugging.

* This program may be invoked by typing the executable name, i.e., `./project`, or with the option "debug", i.e., `./project debug`. Anything else such as `./project debug test` or `./project test` should give an error. The format of the error must be similar to the one you get when you type cp in UNIX.

* When the program is called using the debug option, additional output will be printed on the screen such as name of function called and parameters passed. This is in addition to everything the program does when called without the debug argument. (You may ignore the printing of pointer arguments)

* Every function definition must have output identifying the function called and the parameters passed, when the "debug" option is invoked.
