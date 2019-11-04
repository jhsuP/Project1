/****************************************************************************
//   
//   Name:       Jennifer Hsu
//
//   Homework:   Project 1
//
//   Class:      ICS 212
//
//   Instructor: Ravi Narayan
//
//   Date:       Oct. 28, 2019
//
//   File Name:  database.c
//
//   Description: 
//    This file contain functions that allow us to create,
//    view, delete, and modifying records. 
//
******************************************************************************/

#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int debugmode;

/******************************************************************************
//
//   Function name:    addRecord
//
//   Description:      Adds a new record into the database.
//
//   Parameters:       accountnum (int) : contains the account number
//                     name (char) : contains the name of the account owwner
//                     address (char) : contains the address 
//                     start (record **) : pointer to the record
//
//   Return values:    0 : success
// 
*******************************************************************************/

int addRecord (struct record ** start, int accountnum, char name[ ], char address[ ])
{

    struct record * temp = NULL;
    struct record * input = NULL;
    int success = 0;
    int valid = 0;
    int counter = 0;

    if (debugmode == 0)
    {
        printf("=== Entering addRecord function ===\n");
        printf("=== Passing in accountnum: \n%d \n\nName: \n%s \n\nAddress: \n%s===\n", accountnum, name, address);
    }


    temp = *start;
   
    while ( temp != NULL && success == 0) 
    {
        if ( accountnum < (*temp).accountno)
        {
            counter++;
        }
        else if ( accountnum == (*temp).accountno)
        {
            success = -1;
        }
        temp = (*temp).next;
    }

    if (success == 0)
    {  
        input =  malloc(sizeof(struct record));

        if (*start == NULL)
        {
            (*input).next = NULL;
            *start = input;

        }
        else 
        {
            temp = *start;           

            if (counter == 0)
            {
                (*input).next = temp;
                *start = input;
            }

            else 
            {   

                while (valid < counter - 1)
                {
                    temp = (*temp).next;
                    valid++;
                }    
            
                if (temp->next == NULL) 
                {
                    (*temp).next = input;
                    (*input).next = NULL;
                }
                else
                { 
                    input->next = temp->next;
                    temp->next = input;

                }
            }
        }
 
        (*input).accountno = accountnum;
        strcpy((*input).name, name);
        strcpy((*input).address, address);
    }

    return success;
}

/*******************************************************************************
//    
//   Function name:    printRecord
//
//   Description:      Prints out the account information. 
//
//   Parameters:       accountnum (int) : contains the account number
//                     start (record *) : pointer to the start of record
//
//   Return values:    0 : success
//
*******************************************************************************/

int printRecord (struct record * start, int accountnum)
{

    struct record * temp = NULL;
    int success = -1;

    if (debugmode == 0)
    {
        printf("=== Entering printRecord function ===\n");
        printf("=== Passing in accountnum: %d === \n", accountnum);
    }

    temp = start;

    while (temp != NULL && success == -1)
    { 
        if (accountnum == (*temp).accountno)
        {
            success = 0;
            printf("Num: %d\n", (*temp).accountno);
            printf("Name: %s\n", (*temp).name);
            printf("Address: %s\n", (*temp).address);
        }

        temp = temp->next;

    }

    return success;
}


/******************************************************************************
//   
//   Function name:    printAllRecords
//
//   Description:      Prints all the information of a given account.
//
//   Parameters:       start (record *) : Pointer to the start of record
//
//   Return values:    None
//
******************************************************************************/

void printAllRecords(struct record * start)
{

    struct record * temp;

    if (debugmode == 0)
    {
        printf("=== Entering printAllRecords function ===\n");
    }

    temp = start;

    while (temp != NULL)
    {
        printf("%d\n", temp->accountno);
        printf("%s\n", temp->name);
        printf("%s\n", temp->address);

        temp = temp->next;
    }

}

/*****************************************************************************
//   
//   Function name:    modifyRecord
//
//   Description:      Modifies an account's name or address.
//
//   Parameters:       accountnum (int) : contains the account number.
//                     start (record *) : pointer to the start of record
//                     address (char [ ]) : the address to change
//
//   Return values:    0 : success
//
*****************************************************************************/

int modifyRecord (struct record * start, int accountnum, char address[ ])
{

    struct record * temp = NULL;
    int success = -1;

    if (debugmode == 0)
    {
        printf("=== Entering modifyRecord function ===\n");
        printf("=== Passing in accountnum: \n%d \n\nAddress: \n%s=== \n", accountnum, address);
    }

    temp = start;

    while (temp != NULL && success == -1)
    {
        if (accountnum == (*temp).accountno)
        {
            success = 0;
            strcpy((*temp).address, address);
        }

        temp = temp->next;

    }

    return success;
}

/*****************************************************************************
// 
//   Function name:    deleteRecord
//
//   Description:      Deletes the record
//
//   Parameters:       accountnum (int) : contains the account number
//                     start (record **) : pointer to the start of record
// 
//   Return values:    0 : success
//
*****************************************************************************/

int deleteRecord(struct record ** start, int accountnum)
{
    struct record * temp = NULL;
    struct record * remove = NULL;
    struct record * prev = NULL;
    int success = -1;
    int counter = 0;

    if (debugmode == 0)
    {
        printf("=== Entering deleteRecord function ===\n");
        printf("=== Passing in accountnum: %d === \n", accountnum);
    }

    temp = *start;

    while (temp != NULL && success == -1)
    {
        if (accountnum < (*temp).accountno)
        {
            counter++;
            temp = (*temp).next;
        }
 
        else if (accountnum == (*temp).accountno)
        {
            success = 0;
        }
        else
        {
            temp = temp->next;
        }

    }

    if (success == 0)
    {
        if (counter == 0)
        {
            if ((*temp).next == NULL)
            {
                free(temp);
                *start = NULL;
            }
            else
            {
                *start = temp->next;
                free(temp);
            }

        }
        else
        {
            temp = *start;
            
            while (success <= counter - 1)
            { 
                prev = temp;
                temp = (*temp).next;
                success++;
            }

            if ((*temp).next == NULL)
            {
                (*prev).next = NULL;
                free(temp);
            }
            else
            {   
                remove = temp;
                temp = (*temp).next;
                (*prev).next = temp;
                free(remove);
            }
        
         }

        success = 0;
    }

    return success;
} 

/******************************************************************************
//    
//   Function name:     readfile
//
//   Description:       Reads the record files
//
//   Parameters:        start (struct record **): Pointer that points to the
//                      pointer of start.
//                      filename (char []): Name of the file being read.
//
//   Return values:     0 : success
//                      -1 : Failed
//
*******************************************************************************/

int readfile( struct record ** start, char filename[ ] ) 
{

    FILE *read; 
    int length = 0;
    int accountno = 0;
    char name [1000];
    char address[1000];
    int success = 0;

    read = fopen(filename, "r");

    if (read == NULL)
    {
        success = -1;
    }
    else
    {       

        while ( fscanf(read, "%d\n", &accountno) != EOF )
        {
            fgets(name, 1000, read);
            length = strlen(name);
            if (name[length - 1] == '\n')
            {
                name[length -1] = '\0';
            }
            fgets(address, 1000, read); 
 
            length = strlen(address);
            if (address[length - 1] == '\n')
            {
                address[length -1] = '\0';
            }

            addRecord (start, accountno, name, address);
        }

    fclose(read);

    }

    if (debugmode == 0)
    {
        printf("=== Entering readFile function ===\n");
        printf("=== Passing in readFile: '%s'\n", filename);
    }

    return success;

}

/******************************************************************************
//   
//   Function name:     writefile
//
//   Description:       Writes data to a text file.
//
//   Parameters:        start (struct record *): Start of linked list.
//                      filename (char): The name of the text file.
//
//   Return Values:     0 : success
//                      -1 : Failed to write to file.
//
******************************************************************************/

int writefile (struct record * start, char filename[ ] )
{

    FILE *inputFile;
    struct record * temp;
    int success = 0;

    if (debugmode == 0)
    {
        printf("=== Entering writeFile function ===\n");
        printf("=== Passing in writeFile: '%s'\n", filename);
    }


    temp = start;

    inputFile = fopen(filename, "w");

    if (inputFile == NULL)
    {
        success = -1;

    }
    else
    {
        while (temp != NULL)
        {
            fprintf(inputFile, "%d\n", temp->accountno);
            fprintf(inputFile, "%s\n", temp->name);
            fprintf(inputFile, "%s\n", temp->address);
    
            temp = temp->next;
        }

    fclose(inputFile);

    }

    return success;
}


/***************************************************************************
//     
//     Function name:     cleanup
//
//     Description:       Releases all the heap space.
//
//     Parameters:        start (struct record **): start of the linked list.
//
//     Return values:     None.
//
****************************************************************************/

void cleanup (struct record ** start) 
{
    struct record * temp = NULL;
    temp = *start;

    if (*start != NULL) 
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
            free(temp);
        }

        free(*start);
        *start = NULL;

    }
}



