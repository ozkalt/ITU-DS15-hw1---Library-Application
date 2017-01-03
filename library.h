/*
@Author
Student Name	:Tuðba Özkal
Student Number	:150120053
*/

#define NAME_LENGHT 20
#define LASTNAME_LENGHT 20
#define TITLE_LENGHT 30
#define BOOKTYPE_LENGHT 10
#define ISBN_LENGHT 13
#define LOCATION_LENGHT 4

struct Book_Record{
	char authorName[NAME_LENGHT], authorLastname[LASTNAME_LENGHT], title[TITLE_LENGHT];
	long long int ISBN;		//ISBN has 13 digits
	int location;			//location has 4 digits
	char bookType[BOOKTYPE_LENGHT];
};