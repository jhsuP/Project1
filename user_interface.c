/*********************************************************************
//   
//   Name:         Jennifer Hsu
//
//   Homework:     Project 1
//
//   Class:        ICS 212
//
//   Instructor:   Ravi Narayan
//
//   Date:         Oct. 28, 2019
//
//   File:         user_interface.c
//
//   Description: 
//     This file contains the user interface for the software.
//
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"

int debugmode = -1;

/*******************************************************************
//
//   Function name:    main
//
//   Description:      Start of the program.
//
//   Parameters:       argc (int : Number of arguments passed in
//                     argv (char *) : Argument passed in
//
//   Return values:    0 : success
//
*******************************************************************/

int main (int argc, char * argv[])
{
    void getaddress (char [ ], int);
    
    char buffer [1000];
    char name [1000];
    char address [100];
    int accountnum = -1;
    int value = -1; 
    int starting = 0;
    int nameValid = -1;
    int counter;
    int error = -1;
    int success = 0;
    struct record * start = NULL;
    

    if (argc > 2)
    {
        printf("No such file, command, or directory.\n");
        starting = -1; 
    }
    else
    {   
        if ( strcmp(argv[0], "./project") == 0)
        {
            if (argc == 1) 
            {
                starting = 0;   
            }
            else
            { 
                if ( strcmp(argv[1], "debug") == 0)
                {
                    printf("\nDebug mode on.\n");
                    debugmode = 0;
                }
                else
                {
                    starting = -1;
                    printf("No such file, command, or directory.\n");
                }
            }
        }
    }

    readfile(&start, "recordDatabase.txt");

    if (starting == 0)
    {
        printf("\nWelcome to Xyro, the software that stores the customer's bank records for the bank 'Larkin'.");
    }

    while (value == -1 && starting == 0)
    {
        
        printf("\n\n============================================================================================\n");    
        printf("Menu:\n");
        printf("1: Add a new record in the database.\n");
        printf("2: Print information about a record using the account #.\n");
        printf("3: Print all records in the database.\n");
        printf("4: Modify the address field of a record specified by account #.\n");
        printf("5: Delete an existing record from the database.\n");
        printf("6: Quit the program.\n");
        printf("============================================================================================\n");
        printf("Please enter the respective number to select the option you want to use: ");

        fgets(buffer, 1000, stdin);
        if (sscanf(buffer, "%d", &value) != 1)
        {
            printf("\nInvalid menu option: No characters allowed. Please try again.\n");
            value = -1;
        }
        else
        {
            if (value <= 0)
            {
                printf("\nInvalid menu option. Please try again.\n");
                value = -1;
                 
            }
            if (value > 6)
            {
                printf("\nInvalid menu option. Please try again.\n");
                value = -1;
            }
        } 

        switch(value)
        {
            case 1:
                  printf("\nYou selected: 'Add a new record to the datebase.'\n");
                  printf("Please enter the account number. Press enter when done: ");

                  while(accountnum == -1)
                  {
                      fgets(buffer, 1000, stdin);
                      if (sscanf(buffer, "%d", &accountnum) != 1)
                      {
                          printf("No characters allowed. Please try again.\n");
                          accountnum = -1;
                      }
                      else
                      {
                          if (accountnum < 0)
                          {
                              printf("Account number must be positive. Please try again: ");
                              accountnum = -1;
                          }
                      }
                  }
                  
                  printf("Please enter the name. Press enter when done: ");
                  nameValid = -1;
                  while (nameValid == -1)
                  {
                      error = -1;
                      nameValid = 0;
                      fgets(name, 1000, stdin);  
                
                      if (name[0] == '\n')
                      {
                          printf("Invalid. Input is empty. Please try again: ");
                          nameValid = -1; 
                      }
                
                      for (counter = 0; name[counter] != '\n'; counter++)
                      {
                          if (name[counter] >= '0' && name[counter] <= '9')
                          {      
                               if (error == -1)
                               {
                                    printf("Invalid: no numbers allowed. Please try again: ");  
                                    error = 0;
                               }
                               nameValid = -1;
                          }
                          else if (( name[counter] >= 'A' && name[counter] <= 'Z') || 
                               (name[counter] >= 'a' && name[counter] <= 'z') || 
                               (name[counter] == '.') || (name[counter] == ' ' ))
                          {
                               ;                          
                          }
                          else
                          {    if (error == -1)
                               {
                                    printf("Invalid: No special characters allowed. Please try again: ");
                                    error = 0;
                               }
                               nameValid = -1;
                          }

                      }

                  }
                  name[counter] = '\0';
                  getaddress(address, 100);
                  success = addRecord(&start, accountnum, name, address);
                  if (success != -1)
                  {
                      printf("You have entered: \nAccount #:\n%d \n\nName:\n%s \n\nAddress: \n%s \n", accountnum, name, address);
                  }
                  else
                  {
                      printf("Sorry, an account with the number: '%d' already exists. Please try again.\n", accountnum);
                  }
             
                  value = -1;
                  nameValid = -1;
                  accountnum = -1;
                  error = -1;
                  break;
            case 2:
                  printf("\nYou selected: `Print information about a record using the account #.\n");
                  printf("Please enter the account number. Press enter when done: ");
                  while(accountnum == -1)
                  {
                      fgets(buffer, 1000, stdin);
                      if (sscanf(buffer, "%d", &accountnum) != 1)
                      {
                          printf("Invalid input.  Please try again.\n");
                          accountnum = -1;
                      }
                      else
                      {
                          if (accountnum < 0)
                          {
                              printf("Account number must be positive. Please try again: ");
                              accountnum = -1;
                          }
                      }
                  }
                  value = -1;
                  success = printRecord (start, accountnum);
                  if (success != 0) 
                  {
                      printf("Sorry, the account number: '%d' does not exist. Please try again.\n", accountnum);
                  } 
                  success = 0; 
                  accountnum = -1;
                  break;
            case 3:
                  printf("\nYou've selected: 'Print all records in the database'.\n");
                  printAllRecords(start);
                  value = -1;
                  break;
            case 4: 
                  printf("\nYou selected: 'Modify the address field of a record specified by account # as key.`\n");
                  printf("Please enter the account number. Press enter when done: ");
                  while(accountnum == -1)
                  {
                      fgets(buffer, 1000, stdin);
                      if (sscanf(buffer, "%d", &accountnum) != 1)
                      {
                          printf("Invalid input.  Please try again.\n");
                          accountnum = -1;
                      }
                      else
                      {
                          if (accountnum < 0)
                          {
                              printf("Account number must be positive. Please try again: ");
                              accountnum = -1;
                          }
                      }
                  }  
                  getaddress(address, 100);
                  success = modifyRecord(start, accountnum, address);
                  if (success != 0) 
                  {
                      printf("Sorry, the account #: '%d' you entered does not exist. Please try again.\n", accountnum);
                  } 
                  else
                  {
                      printf("Successfully changed the address for account #: '%d'\n", accountnum);
                  }
                  success = 0;
                  value = -1;
                  accountnum = -1;
                  break;
            case 5:
                  printf("You selected: 'Delete an existing record from the database using the account # as a key.`\n");
                  printf("Enter the account number you wish to delete. Press enter when done: ");
                  while(accountnum == -1)
                  {
                      fgets(buffer, 1000, stdin);
                      if (sscanf(buffer, "%d", &accountnum) != 1)
                      {
                          printf("Invalid input.  Please try again.\n");
                          accountnum = -1;
                      }
                      else
                      {
                          if (accountnum < 0)
                          {
                              printf("Account number must be positive. Please try again: ");
                              accountnum = -1;
                          }
                      }
                  }

                  success = deleteRecord(&start, accountnum);
                   
                  if (success != -1) 
                  {
                      printf("Account #: '%d' successfully deleted.\n", accountnum);
                  }
                  else
                  {
                      printf("Invalid, there are no records in the database that match the account #: '%d'. Please try again.\n", accountnum);
                  }
                  accountnum = -1;
                  value = -1;
                  break;
            case 6:
                  writefile(start, "recordDatabase.txt");
                  cleanup(&start);
                  printf("Closing program now.\n\n");
                  value = 0;
                  break;
            default:
                  value = -1;           
        }
    }
 
    return 0;
}


/***************************************************************************************
//
//   Function name:    getaddress
//
//   Description:      Obtains address information for the following fields:
//                     account number 
//                     name
//                     mailing address
//
//   Parameters:       input (char []) : The address field
//                     size (int) : size of input
//
//   Return values:    None
//
***************************************************************************************/

void getaddress (char input [ ], int size)
{
    char c; 
    char line = '\n';
    int i;
    int count = 0; 

    if (debugmode == 0)
    {
        printf("=== Entering getaddress function ===\n");
        printf("=== Passing in: char input []: \n%sInt size: %d===\n", input, size);

    }

    printf("\nPlease enter the new address. Signify that you are done inputting by adding a `@` at the end.");
    printf("\nFor example: 1234 Dole Street, Honolulu, HI@");
    printf("\nEnter here: ");
   
    c = getchar();
    while (c != '@' && count < size)
    {
        input[count] = c;
        count++;
        c = getchar();
    }
    input[count] = '\0'; 
    getchar();

    for (i = 0; i <=strlen(input); i++) 
    {
        if(input[i] == line) 
        {
            input[i] = ' ';
        } 
 
    }

    if (debugmode == 0)
    {
        printf("=== At the end of getaddress (after code is ran). ===\n");
        printf("=== char input []: \n%s \nInt size: %d===\n\n", input, size);

    }


} 
