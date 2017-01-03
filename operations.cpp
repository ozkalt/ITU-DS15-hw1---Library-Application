/*
@Author
Student Name	:Tuðba Özkal
Student Number	:150120053
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

using namespace std;

void File::create(){
	filename = "bookregistry.txt";
	bookregistry = fopen(filename, "r+");
	if (!bookregistry){
		if (!(bookregistry = fopen(filename, "w+"))){
			cerr << "File can not be opened" << endl;
			exit(1);
		}
	}
}

void File::close(){
	fclose(bookregistry);
}

void File::insert(Book_Record * inPtr){		//CONTROL IF SAME LOCATIONS AND ISBNS
	fseek(bookregistry, 0, SEEK_END);
	fwrite(inPtr, sizeof(Book_Record), 1, bookregistry);
}

int File::searchAuthor(char searchn[], char searchln[]){
	Book_Record k;
	int counter = 0, found = 0;
	bool all = false;
	if (strcmp(searchn, "*") == 0)
		all = true;

	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		counter++;
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry))
			break;
		if (!all && strncmp(k.authorName, searchn, strlen(searchn)) != 0 && strncmp(k.authorLastname, searchln, strlen(searchln)) != 0){
			continue;
		}

		cout << counter << "." << k.authorName << " " << k.authorLastname << " which has written " << k.title << "." << endl;
		found++;
	}
	return found;
}
//I created this function before your explanation on Ninova. So I didnt change contains of other functions.
//I just added a new type search function.
int File::searchTitle(char searcht[]){
	Book_Record k;
	int counter = 0, found = 0;
	bool all = false;

	if (strcmp(searcht, "*") == 0)
		all = true;

	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		counter++;
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry)) break;
		if (!all && strncmp(k.title, searcht, strlen(searcht)) != 0)
			continue;
		cout << counter << "." << k.title << " which is written by " << k.authorName << " " << k.authorLastname << "." << endl;
		cout << "ISBN : " << k.ISBN << endl;
		found++;
	}
	return found;
}

int File::searchType(char searcht[]){
	Book_Record k;
	int counter = 0, found = 0;
	bool all = false;

	if (strcmp(searcht, "*") == 0)
		all = true;

	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		counter++;
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry)) break;
		if (!all && strncmp(k.bookType, searcht, strlen(searcht)) != 0)
			continue;
		cout << counter << "." << k.bookType << " - " << k.title << endl;
		cout << "ISBN : " << k.ISBN << endl;
		found++;
	}
	return found;
}

int File::searchISBN(long long int inisbn){
	Book_Record k;
	int counter = 0;
	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry)) 
			return 0;
		if (k.ISBN == inisbn){
			counter++;
			return counter;
		}
		else{
			counter++;
			continue;
		}
	}
}

int File::searchLocation(int inlocation){
	Book_Record k;
	int counter = 0;
	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry))
			return 0;
		if (k.location == inlocation){
			counter++;
			return counter;
		}
		else{
			counter++;
			continue;
		}
	}
}

void File::update(long long int inisbn, Book_Record* inPtr){
	int index = searchISBN(inisbn);
	//same situation here like what happened in remove function
/*	if (index == 0){
		cout << "Error! Invalid ISBN!..." << endl;
	}
	else */
	if (fseek(bookregistry, sizeof(Book_Record)*(index - 1), SEEK_SET) == 0)
		fwrite(inPtr, sizeof(Book_Record), 1, bookregistry);
}

void File::remove(long long int inisbn){
	Book_Record emptyRecord = { "", "", "", NULL, NULL, "" };

	int index = searchISBN(inisbn);
	// index is checked if zero or not in registry_remove function of Source.cpp
	// so, it has to be bigger than zero here.
/*	if (index == 0){
		cout << "Error! Invalid ISBN!..." << endl;
		return 0;
	}
	else   */
	if (fseek(bookregistry, sizeof(Book_Record)*(index - 1), SEEK_SET) == 0) {
		fwrite(&emptyRecord, sizeof(Book_Record), 1, bookregistry);
	}

	char* tempfile = "tempfile.txt";
	FILE* temprecord;
	Book_Record k;
	int counter = 0;
	temprecord = fopen(tempfile, "w+");
	if (!temprecord){
		cerr << "Could not open temporary file.";
		exit(1);
	}

	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry)) break;
		if (strcmp(k.title, "") == 0) //boþsa
			counter++;
		else
			fwrite(&k, sizeof(Book_Record), 1, temprecord);
	}

	fseek(temprecord, 0, SEEK_SET);
	int count = 1;
	while (!feof(bookregistry)){
		remove(count);
		count++;
	}

	fclose(bookregistry);
	bookregistry = fopen(filename, "w+");
	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(temprecord)){
		fread(&k, sizeof(Book_Record), 1, temprecord);
		if (feof(temprecord)) break;
		fwrite(&k, sizeof(Book_Record), 1, bookregistry);
	}

	if (counter > 0){
		fclose(bookregistry);
		fclose(temprecord);
/*		char command[500] = "copy ";
		strcat(command, tempfile);
		strcat(command, " ");
		strcat(command, filename);
		system(command);  */
		create();
	}
}

void File::print(){
	Book_Record k;
	fseek(bookregistry, 0, SEEK_SET);
	while (!feof(bookregistry)){
		fread(&k, sizeof(Book_Record), 1, bookregistry);
		if (feof(bookregistry)) break;
		cout << endl << "Book Title: " << k.title << endl
			<< "Author Name: " << k.authorName << " " << k.authorLastname << endl
			<< "Book Type: " << k.bookType << "	"
			<< "ISBN: " << k.ISBN << "	"
			<< "Location: " << k.location << endl;
	}
}