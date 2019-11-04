/**********************************************************
// 
//   Name:        Jennifer Hsu
//
//   Homework:    Project 1
//
//   Class:       ICS 212
//
//   Instructor:  Ravi Narayan
//
//   Date:        Oct. 28, 2019
//
//   File:        database.h
//
//   Description:
//     This file contains the function prototype for 
//     'database.c'
//
**********************************************************/

int addRecord (struct record **, int, char [ ],char [ ]);
int printRecord (struct record *, int);
void printAllRecords(struct record *);
int modifyRecord (struct record *, int, char [ ]);
int deleteRecord(struct record **, int);
int readfile( struct record **,  char [ ] );
int writefile( struct record *,  char[ ] );
void cleanup (struct record **);
