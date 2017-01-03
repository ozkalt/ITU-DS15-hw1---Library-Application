/*
@Author
Student Name	:Tuðba Özkal
Student Number	:150120053
*/

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>

#include "operations.h"

using namespace std;

typedef File Datastructure;

Datastructure record;

void menu();
bool operate(char);
void registry_searchAuthor();
void registry_searchTitle();
void registry_searchType();
void registry_add();
void registry_update();
void registry_remove();
void registry_print();

int main(){
	record.create();
	bool finish = false;
	char choice;
	while (!finish) {
		menu();
		cin >> choice;
		finish = operate(choice);
	}
	record.close();
	return EXIT_SUCCESS;
}

void menu(){
	cout << endl << endl;
	cout << "Library Application" << endl;
	cout << "Choose an option" << endl;
	cout << "P: Print the whole catalogue" << endl;
	cout << "A: Search the catalogue by author" << endl;
	cout << "T: Search the catalogue by type" << endl;
	cout << "I: Insert a new book record" << endl;
	cout << "U: Update an existing book record" << endl;
	cout << "R: Remove a book record" << endl;
	cout << "E: Exit the program" << endl;
	cout << endl;
	cout << "Enter your option: ";
}

bool operate(char inchoice){
	bool finish = false;
	switch (inchoice){
	case 'P': case 'p':
		registry_print();			//print the whole catalogue
		break;
	case 'A': case 'a':
		registry_searchAuthor();	//Author search
		break;
	case 'T': case 't':
		registry_searchType();		//Type search
		break;
	case 'I': case 'i':
		registry_add();				//add a new record
		break;
	case 'U': case 'u':
		registry_update();			//update a record
		break;
	case 'R': case 'r':
		registry_remove();			//delete a record
		break;
	case 'E': case 'e':
		cout << "Are you sure that you want to terminate the program? (E/H):";
		cin >> inchoice;
		if (inchoice == 'E' || inchoice == 'e')
			finish = true;
		break;
	default:
		cout << "Error: You have made an invalid choice." << endl;
		cout << "Try again {P, A, T, I, U, R, E}: ";
		cin >> inchoice;
		finish = operate(inchoice);
		break;
	}
	return finish;
}

void registry_searchAuthor(){
	char name[NAME_LENGHT];
	char surname[LASTNAME_LENGHT];
	cout << "Please enter the first name of the author you want to search (press '*' for listing all):" ;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGHT);
	cout << "Please enter the last name of the author you want to search (press '*' for listing all):" ;
	cin.getline(surname, LASTNAME_LENGHT);
	if (record.searchAuthor(name, surname) == 0)
		cout << "Author cannot be found." << endl;
	getchar();
}

void registry_searchTitle(){
	char bookTitle[TITLE_LENGHT];
	cout << "Please enter the title of the book you want to search (press '*' for listing all):" ;
	cin.ignore(1000, '\n');
	cin.getline(bookTitle, TITLE_LENGHT);
	if (record.searchTitle(bookTitle) == 0)
		cout << "Book title cannot be found." << endl;
	getchar();
}

void registry_searchType(){
	char bookType[TITLE_LENGHT];
	cout << "Please enter the type of the book you want to search (press '*' for listing all):";
	cin.ignore(1000, '\n');
	cin.getline(bookType, TITLE_LENGHT);
	if (record.searchType(bookType) == 0)
		cout << "Book type cannot be found." << endl;
	getchar();
}

void registry_add(){
	Book_Record newRecord;
	
	cin.ignore(1000, '\n');
	cout << "Please enter the information of the book you want to save." << endl;
	cout << "Title : ";
	cin.getline(newRecord.title, TITLE_LENGHT);
	cout << "Author's first name : ";
	cin.getline(newRecord.authorName, NAME_LENGHT);
	cout << "Author's last name : ";
	cin.getline(newRecord.authorLastname, LASTNAME_LENGHT);
	cout << "Book Type : ";
	cin.getline(newRecord.bookType, BOOKTYPE_LENGHT);
	cout << "ISBN :";
	cin >> setw(ISBN_LENGHT) >> newRecord.ISBN;
	cout << "Book Location : ";
	cin >> setw(LOCATION_LENGHT) >> newRecord.location;

	int control1 = record.searchISBN(newRecord.ISBN);				//check same ISBNs or not (seperate books cannot have same ISBNs)
	int control2 = record.searchLocation(newRecord.location);		//check same locations or not (seperate books cannot have same locations)
	if (control1 > 0){
		cout << "ISBN cannot be same, check the ISBN of book." << endl;
	}
	else if(control2 > 0) {
		cout << "Location cannot be same, check the location of book." << endl;
	}
	else{
		record.insert(&newRecord);
		cout << "Record has been added." << endl;
	}
	getchar();
}
//I created a function for seeing ISBN number of books with title but function update the book information by using ISBN.
//If you need to see ISBNs with books'titles, you can remove the slashes.
void registry_update(){
//	char bookTitle[TITLE_LENGHT];
	long long int choice;
//	cout << "Please enter the title of the book you want to update (press '*' for listing all):" ;
//	cin.ignore(1000, '\n');
//	cin.getline(bookTitle, TITLE_LENGHT);
//	int number = record.searchTitle(bookTitle);						//check valid title or not
//	if (number == 0){
//		cout << "Book title cannot be found." << endl;
//	}
//	else if (number > 0){
//		cout << "Book title(s) have been found." << endl;
		cout << "Please enter the ISBN of the book you want to update (Press -1 to exit without deletion) :" ;
		cin >> choice;
		if (choice == -1) return;
		else if (int control = record.searchISBN(choice) == 0){		//check valid ISBN or not
			cout << "Error! Invalid ISBN!..." << endl;
		}
		else{
			cout << "ISBN is found!..." << endl;
			Book_Record newRecord;
			cin.ignore(1000, '\n');
			cout << "Please enter the information of the book which will be updated." << endl;
			cout << "Title : ";
			cin.getline(newRecord.title, TITLE_LENGHT);
			cout << "Author Name : ";
			cin.getline(newRecord.authorName, NAME_LENGHT);
			cout << "Author Last Name : ";
			cin.getline(newRecord.authorLastname, LASTNAME_LENGHT);
			cout << "Book Type : ";
			cin.getline(newRecord.bookType, BOOKTYPE_LENGHT);
			cout << "ISBN :";
			cin >> setw(ISBN_LENGHT) >> newRecord.ISBN;
			cout << "Book Location : ";
			cin >> setw(LOCATION_LENGHT) >> newRecord.location;
			record.update(choice, &newRecord);
			cout << "Record has been updated." << endl;
		}
		getchar();
//	}
}

void registry_remove(){
//	char bookTitle[TITLE_LENGHT];
	long long int inisbn;
//	cout << "Please enter the title of the book you want to delete (press '*' for listing all): " ;
//	cin.ignore(1000, '\n');
//	cin.getline(bookTitle, TITLE_LENGHT);
//	int number = record.searchTitle(bookTitle);						//check valid title or not
//	if (number == 0){
//		cout << "Book title cannot be found." << endl;
//	} 
//	else if (number > 0){
//		cout << "Title(s) have been found." << endl;
		cout << "Please enter the isbn of the book you want to delete (Press -1 to exit without deletion): ";
		cin >> inisbn;
		if (inisbn == -1) return;
		else if (int control = record.searchISBN(inisbn) == 0){		//check valid ISBN or not
			cout << "Error! Invalid ISBN!..." << endl;
		}
		else{
			cout << "ISBN is found!..." << endl;
			record.remove(inisbn);
			cout << "Book record has been deleted." << endl;
		}
//	}
	getchar();
}

void registry_print(){
	record.print();
	getchar();
}