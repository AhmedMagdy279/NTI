#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h> //On Windows, you can use the getch() function from the "conio.h" 
//library, which allows capturing single key presses without the need to press Enter

/*		Day 3		

--> DATA TYPES
	--> User defined
		-->Struct
		-->Enum
		-->Union
		-->typedef
-----------------------------------------------------------------------
			pointer to struct
			-----------------
example:
typedef struct { char* name, int ID} NTI;
NTI valeo, avelabs;
scanf("%d",valeo.ID);
NTI * ptr = & valeo;
						|
			<------------------------>
	(*ptr).ID=123;					ptr->ID=123;

Arthimetics used: =    || we can't use == or !=, unless "valeo" and "avelabs" are  from the same struct we can make valeo = avelabs;
-----------------------------------------------------------------------
			Bit field
			---------
struct employee{
int salary: 4 ;			//4 bits
int working hours: 3;	//3 bits
}Employee;

sizeof(Employee)=> default= 8 byte
				=> after bit field = 4 byte
-----------------------------------------------------------------------
			Union
			-----
shareable memory between inner variables
typedef union{
	struct{
	u8 b0:1;
	u8 b1:1;
	u8 b2:1;
	u8 b3:1;
	u8 b4:1;
	u8 b5:1;
	u8 b6:1;
	u8 b7:1;
	}Bit;
	
	u8 byte;
}Register;
--------------------------------------------------------------------


*/


/*
		C project 1
		-----------
		 Library
		 -------
1) func --> settter for the library and books (Add_book)
*Constraints:*
- The library should not exceed the maximum number of books (100 books).
- All input fields must be provided.
- Book title, author name, and status should not exceed their respective maximum lengths (100
characters for title and author, 50 characters for status).

- Book title (string)
- Author name (string)
- Publication year (integer)
- Number of copies (integer)
- Price (floating-point number)
- Status (string)
*/
void getString(char *str, int maxLength);
void Library_AddBook();
void Library_PrintInfo();
void Library_BorrowBook();
void Library_DeleteBook();
void Library_BuyBook();
void Menu_transitions();
#define MAX_BOOKS	100
static char BooksNumber;
typedef struct{
	char Title[100];
	char Author[100];
	int PubYear;
	int NumCopies;
	float Price;
	char status[50];
}Book;

Book Library[MAX_BOOKS];

typedef enum {
	Exit=0,
	Add_book,
	Print_Library,
	Borrow_Book,
	Delete_Book,
	Buy_Book
}operation_choice;

void main()
{
	char EXIT_Flag=0;
	char res;
	operation_choice choice;
	

	while (1)
	{
		printf("Welcome to NTI Interactive library Menu\n----------------------------------------\n");
		printf("\nSelect the NUMBER of operation you want to proceed with: ");
		printf("\n1-Add book\n2-Print Library\n3-Borrow Book\n4-Delete Book\n5-Buy Book\n0-Exit\n");
		printf ("Your choice: ");
		scanf("%d",&choice);
		switch (choice)
		{
			case Exit:
				EXIT_Flag=1;
			break;
			case Add_book:
				printf("Adding Book.... ");
				Library_AddBook();
				Menu_transitions();
				break;
			case Print_Library:
				Library_PrintInfo();
				Menu_transitions();
				break;
			case Borrow_Book:
				Library_BorrowBook();
				Menu_transitions();
				break;
			case Delete_Book:
				Library_DeleteBook();
				Menu_transitions();
				break;
			case Buy_Book:
				Library_BuyBook();
				Menu_transitions();
				break;
			default:
				break;
		}
		if (EXIT_Flag)
		{
			printf("\nThanks! Bye Bye");
			Menu_transitions();
			break;
		}
	}
	/*		testing the functions solo
	char res=0;
	printf("Welcome to NTI library\n---------------------------\n");

	printf("Adding Book: ");
    res=Library_AddBook("Harry Potter", "Rowlling", 2000, 5, 10.50, "Available");
	if(res)
		printf("Book Added sucessfully! printing the library...");
	else 
		printf("No more books can be added. printing the library...");
	Library_PrintInfo();

	printf("\nAdding Book: ");
	res=Library_AddBook("To Kill a Mockingbird", "Harper Lee", 1960, 1, 14.99, "Available");
	if(res)
		printf("Book Added sucessfully! printing the library...");
	else 
		printf("No more books can be added. printing the library...");
	Library_PrintInfo();
	printf("Adding Book: ");
	res=Library_AddBook("Dune", "Frank Herbert", 1965, 0, 12.75, "Borrowed");
	if(res)
		printf("Book Added sucessfully! printing the library...");
	else 
		printf("No more books can be added. printing the library...");
	Library_PrintInfo();


	printf("\n\n-------------------------BOOROW PART--------------------------------------\n");
	Library_BorrowBook();
	Library_PrintInfo();
	
	printf("\n\n-------------------------Delete PART--------------------------------------\n");
	Library_DeleteBook();
	Library_PrintInfo();

	printf("\n\n-------------------------Buy PART--------------------------------------\n");
	Library_BuyBook();
	Library_PrintInfo();
	*/
}

void Library_AddBook()
{
	if (BooksNumber==99)
		return ;
	char title[100], author[100], strcmpare=-1, stat[50]="Available";
	int PublishYear, Copies,cop;
	float price;
	fflush(stdin);
	printf("\nEnter Book's title: ");
	getString(title,100);
	for (int i=0;i<BooksNumber;i++)
	{
		if (!strcmp(title,Library[i].Title))
		{
			strcmpare=i;
			break;
		}
	}
	if (strcmpare!=-1)
	{
		while (1)
		{
			printf("\nEnter the number of copies you want to Add from 1 to %d:  ",MAX_BOOKS-BooksNumber);
			scanf("%d",&cop);
			/// phase 1.2 check number avalilability
			if (cop < 0 || cop > MAX_BOOKS-BooksNumber)
				printf("\nTry a valid number!\n");
			else break;
		}
		/// phase 3 enter number of copies to increment with
		printf("\nCopies added sucessfully\n");
		Library[strcmpare].NumCopies += cop;
		if (Library[strcmpare].NumCopies==0)
		{
			strcpy(Library[strcmpare].status,stat);
		}
		else
		{
			//nothing
		}
	}
	else 
	{
		printf("\nEnter Author's name: ");
		getString(author,100);

		printf("\nEnter publish year: ");
		scanf("%d",&PublishYear);
		printf("\nEnter book's price: ");
		scanf("%f",&price);
		Library[BooksNumber].PubYear=PublishYear;
		Library[BooksNumber].NumCopies=1;
		Library[BooksNumber].Price = price;
		strcpy(Library[BooksNumber].Title, title);
		strcpy(Library[BooksNumber].Author, author);
		strcpy(Library[BooksNumber].status, stat);
		BooksNumber = BooksNumber+Library[BooksNumber].NumCopies;
	}
	
}

void Library_PrintInfo()
{
	printf("\n\n---------------------------------------------------------------");
	if (BooksNumber!=0)
	{
	for (int i = 0 ; i< BooksNumber; i++)
		{
			printf("\nBOOK %d: %s, by %s",i+1,Library[i].Title,Library[i].Author);
			printf("\nPublished on: %d	With Number of copies: %d	and price: %.2f",Library[i].PubYear, Library[i].NumCopies,Library[i].Price);
			printf("\nBook status: %s\n",Library[i].status);
		}
	}
	else
		printf("\nNo books right now\n");
	printf("---------------------------------------------------------------\n\n");
}

void Library_BorrowBook()
{
	char stat[50]="Borrowed";
	int pick;
	if (BooksNumber>0)
	{
		/// phase 1 picking the book 
		Library_PrintInfo();
		while (1)
		{
			printf("PICK ONE OF THE PREVIOUS AVAILABLE BOOKS TO BORROW from 1 to %d:  ",BooksNumber);
			scanf("%d",&pick);

			/// phase 1.2 check number avalilability
			if (pick < 0 || pick > BooksNumber)
				printf("\nTry a valid number!\n");
			else break;
		}
		/// phase 2 check book avalilability
		if (Library[pick-1].NumCopies==0)
			printf("\nSorry! Book is not available at the moment, We'll contact you once available\n");
		else
		{
			Library[pick-1].NumCopies--;
			printf("\nCongrats!! you will receive the book in 24 hours. Enjoy!\n");
			if (Library[pick-1].NumCopies==0)
				strcpy(Library[pick-1].status,stat);
		}
	}
	else 
		printf("There are no books available at the moment. Check back later\n");
}

void Library_DeleteBook()
{
	int pick;
	if (BooksNumber>0)
	{
		/// phase 1 picking the book 
		Library_PrintInfo();
		while (1)
		{
			printf("PICK ONE OF THE PREVIOUS AVAILABLE BOOKS TO Delete from 1 to %d:  ",BooksNumber);
			scanf("%d",&pick);

			/// phase 1.2 check number avalilability
			if (pick < 0 || pick > BooksNumber)
				printf("\nTry a valid number!\n");
			else break;
		}
			//phase 2.1 if there is only one book 
		if (BooksNumber==1)
			BooksNumber--;
		//phase 2.2 swap that book with the last one in the array then decrement array number
		else 
		{
			Library[pick-1]=Library[BooksNumber-1];
			printf("\nDone, Book deleted from library\n");
			BooksNumber--;
		}
	}
	else 
	{
		//nothing
	}

}


void Library_BuyBook()
{
	char stat[50]="Available";
	int pick;
	int cop;
	if (BooksNumber>0)
	{
		/// phase 1 picking the book 
		Library_PrintInfo();
		while (1)
		{
			printf("PICK ONE OF THE PREVIOUS AVAILABLE BOOKS TO Buy from 1 to %d:  ",BooksNumber);
			scanf("%d",&pick);

			/// phase 1.2 check number avalilability
			if (pick < 0 || pick > BooksNumber)
				printf("\nTry a valid number!\n");
			else break;
		}
		while (1)
		{
			printf("\nEnter the number of copies you want to Add from 1 to %d:  ",MAX_BOOKS-BooksNumber);
			scanf("%d",&cop);
			/// phase 1.2 check number avalilability
			if (cop < 0 || cop > MAX_BOOKS-BooksNumber)
				printf("\nTry a valid number!\n");
			else break;
		}
		/// phase 3 enter number of copies to increment with
		printf("\nCopies added sucessfully\n");
		Library[pick-1].NumCopies += cop;
		BooksNumber+=cop;
		if (Library[pick-1].NumCopies==0)
		{
			strcpy(Library[pick-1].status,stat);
		}
		else
		{
			//nothing
		}
	}
	else 
		{printf("There are no books available at the moment. Add first then Buy more copies later\n");
	}
}

void Menu_transitions()
{
    char ch;
    printf("\n\nPress Space to proceed");
    
    while (1)
    {
        ch = getch(); // Use getch() to capture a single key press
        if (ch == ' ')
        {
            system("cls");
            break;
        }
    }
}

void getString(char *str, int maxLength) 
{
    if (str == NULL || maxLength <= 0) {
        return; // Error handling
    }
    
    // Read characters from the user until a newline or the maximum length
    fgets(str, maxLength, stdin);
    
    // Remove the trailing newline character, if present
    int length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}