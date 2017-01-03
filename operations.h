/*
@Author
Student Name	:Tuðba Özkal
Student Number	:150120053
*/

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include <stdio.h>
#include"library.h"

struct File{
	char* filename;
	FILE* bookregistry;
	void create();
	void close();
	void insert(Book_Record*);			//add a new book registry
	int searchAuthor(char[], char[]);	//user must enter the name of author
	int searchTitle(char[]);			//user must enter the name of book
	int searchType(char[]);
	void update(long long int, Book_Record*);		//user must enter isbn
	void remove(long long int);					//user must enter isbn
	void print();						//print all books with their authors
	int searchISBN(long long int);				//here books are checked by ISBN, this function is written to use in other functions.
	int searchLocation(int);			//here books are checked by location, this function is written to use in other functions.
};

#endif // !FILEOPERATIONS
