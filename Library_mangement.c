#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for book details
typedef struct bookDetails
{
    char genre[50];
    int year;
} bookDetails;

typedef struct library
{
    int id;
    char name[50];
    char author[50];
    bookDetails details;
    char status[10];
} library;

// Global variables
library *book = NULL;
int count = 0;

// Function prototypes
void welcomeMessage();
void addBook();
void viewAllBooks();
void searchBook();
void removeBook();
void updateBook();
void saveToFile();
void loadFromFile();
void exitProgram();
void printBooks(int index);

// Main function
int main()
{
    int choice;

    // Load books from file
    loadFromFile();

    // Welcome message
    welcomeMessage();

    // Allocate initial memory
    book = (library *)malloc(sizeof(library));
    if (book == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    do
    {
        printf("\n\n\t\t****** Main Menu ******");
        printf("\n\t\t*   1. Add Book         *");
        printf("\n\t\t*   2. View All Books   *");
        printf("\n\t\t*   3. Search Book      *");
        printf("\n\t\t*   4. Remove Book      *");
        printf("\n\t\t*   5. Update Book      *");
        printf("\n\t\t*   6. Exit             *");
        printf("\n\t\t*************************");
        printf("\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            viewAllBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            removeBook();
            break;
        case 5:
            updateBook();
            break;
        case 6:
            exitProgram();
            break;
        default:
            printf("\nInvalid choice. Try again.");
        }
    } while (choice != 6);

    free(book);
    return 0;
}

// Function to display a welcome message
void welcomeMessage()
{
    printf("\n\n\t*");
    printf("\n\t*             WELCOME TO THE LIBRARY         *");
    printf("\n\t*                     CSE, AMRITA            *");
    printf("\n\t*\n");
}

// Function to add a new book
void addBook()
{
    book = (library *)realloc(book, (count + 1) * sizeof(library));
    if (book == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("\n\t\t** Add New Book Details ***");
    printf("\n\t\t* Enter Book Id: ");
    scanf("%d", &book[count].id);
    printf("\t\t* Enter Book Name: ");
    getchar(); // Clear newline character from buffer
    fgets(book[count].name, sizeof(book[count].name), stdin);
    book[count].name[strcspn(book[count].name, "\n")] = 0; // Remove newline
    printf("\t\t* Enter Book Author: ");
    fgets(book[count].author, sizeof(book[count].author), stdin);
    book[count].author[strcspn(book[count].author, "\n")] = 0; // Remove newline
    printf("\t\t* Enter Book Genre: ");
    fgets(book[count].details.genre, sizeof(book[count].details.genre), stdin);
    book[count].details.genre[strcspn(book[count].details.genre, "\n")] = 0; // Remove newline
    printf("\t\t* Enter Book Year: ");
    scanf("%d", &book[count].details.year);

    // Set the status as "Available" when adding a new book
    strcpy(book[count].status, "Available");

    count++;
    printf("\t\t**********************************");

    // Save to file after addition
    saveToFile();
}

// Function to view all books
void viewAllBooks()
{
    printf("\n\t\t|************************ View All Books ********************************");
    printf("\n\t\t|-------------------------------------------------------------------------|");
    printf("\n\t\t| Id     \tTitle\t       \tAuthor\t    \tGenre\t    \tYear\t    Status|");
    printf("\n\t\t|-------------------------------------------------------------------------|");
    if (count == 0)
    {
        printf("\n\t\tNo books available.");
    }
    else
    {
        printBooks(0);
    }

    printf("\n\t\t+==========================================================================+");
}

// Recursive function to print books
void printBooks(int index)
{
    if (index >= count)
        return;
    printf("\n\t\t|%d%s%s%s%d%s|", book[index].id, book[index].name,
           book[index].author, book[index].details.genre, book[index].details.year, book[index].status);
    printBooks(index + 1);
}

// Function to search for a book by name
void searchBook()
{
    char bname[50];
    printf("\n\n\t\tEnter Book Name to Search: ");
    getchar(); // Clear newline character from buffer
    fgets(bname, sizeof(bname), stdin);
    bname[strcspn(bname, "\n")] = 0; // Remove newline

    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(book[i].name, bname) == 0)
        {
            printf("\n\t\t**** Search Book Details ****");
            printf("\n\t\t* Book Id: %d", book[i].id);
            printf("\n\t\t* Book Name: %s", book[i].name);
            printf("\n\t\t* Book Author: %s", book[i].author);
            printf("\n\t\t* Book Genre: %s", book[i].details.genre);
            printf("\n\t\t* Book Year: %d", book[i].details.year);
            return;
        }
    }
    printf("\n\t\tBook not found.");
}

void removeBook()
{
    int choice;
    printf("\n\n\t\tChoose how to remove the book:\n");
    printf("\t\t1. By Book ID\n");
    printf("\t\t2. By Book Name\n");
    printf("\t\tEnter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // Clear newline character from buffer

    if (choice == 1)
    {
        int bookId;
        printf("\n\t\tEnter Book ID to Remove: ");
        scanf("%d", &bookId);
        getchar(); // Clear newline character from buffer

        for (int i = 0; i < count; i++)
        {
            if (book[i].id == bookId)
            {
                for (int j = i; j < count - 1; j++)
                {
                    book[j] = book[j + 1];
                }
                count--;
                book = (library *)realloc(book, count * sizeof(library));
                if (book == NULL && count > 0)
                {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }
                printf("\n\t\tBook removed successfully.\n");

                // Save to file after removal
                saveToFile();
                return;
            }
        }
        printf("\n\t\tBook not found.");
    }
    else if (choice == 2)
    {
        char bname[50];
        printf("\n\t\tEnter Book Name to Remove: ");
        fgets(bname, sizeof(bname), stdin);
        bname[strcspn(bname, "\n")] = 0; // Remove newline

        for (int i = 0; i < count; i++)
        {
            if (strcasecmp(book[i].name, bname) == 0)
            {
                for (int j = i; j < count - 1; j++)
                {
                    book[j] = book[j + 1];
                }
                count--;
                book = (library *)realloc(book, count * sizeof(library));
                if (book == NULL && count > 0)
                {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }
                printf("\n\t\tBook removed successfully.\n");

                // Save to file after removal
                saveToFile();
                return;
            }
        }
        printf("\n\t\tBook not found.");
    }
    else
    {
        printf("\n\t\tInvalid choice. Please enter 1 or 2.\n");
    }
}

// Function to update a book by name
void updateBook()
{
    char bname[50];
    printf("\n\n\t\tEnter Book Name to Update: ");
    getchar(); // Clear newline character from buffer
    fgets(bname, sizeof(bname), stdin);
    bname[strcspn(bname, "\n")] = 0; // Remove newline

    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(book[i].name, bname) == 0)
        {
            printf("\n\t\t*** Update Book Details ***");
            printf("\n\t\t* Enter New Book Id: ");
            scanf("%d", &book[i].id);
            printf("\t\t* Enter New Book Name: ");
            getchar(); // Clear newline character from buffer
            fgets(book[i].name, sizeof(book[i].name), stdin);
            book[i].name[strcspn(book[i].name, "\n")] = 0; // Remove newline
            printf("\t\t* Enter New Book Author: ");
            fgets(book[i].author, sizeof(book[i].author), stdin);
            book[i].author[strcspn(book[i].author, "\n")] = 0; // Remove newline
            printf("\t\t* Enter New Book Genre: ");
            fgets(book[i].details.genre, sizeof(book[i].details.genre), stdin);
            book[i].details.genre[strcspn(book[i].details.genre, "\n")] = 0; // Remove newline
            printf("\t\t* Enter New Book Year: ");
            scanf("%d", &book[i].details.year);

            // Save to file after update
            saveToFile();
            return;
        }
    }
    printf("\n\t\tBook not found.");
}

// Function to save all books to a text file
void saveToFile()
{
    FILE *file = fopen("library.txt", "w");
    if (file == NULL)
    {
        perror("\nError opening file");
        return;
    }

    // Write the heading with proper alignment
    fprintf(file, "%-5s%-30s%-30s%-20s%-10s%-10s\n", "Id", "Title", "Author", "Genre", "Year", "Status");

    // Write the book details with proper alignment
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%-5d%-30s%-30s%-20s%-10d%-10s\n", book[i].id, book[i].name, book[i].author,
                book[i].details.genre, book[i].details.year, book[i].status);
    }
    fclose(file);
    printf("\nBooks saved successfully in library.txt.\n");
}

// Function to load all books from a text file
void loadFromFile()
{
    FILE *file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("\nNo existing library data found.");
        return;
    }

    // Skip the header line
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        library tempBook;
        if (sscanf(buffer, "%d\t%49[^\t]\t%49[^\t]\t%49[^\t]\t%d\t%9s",
                   &tempBook.id, tempBook.name, tempBook.author, tempBook.details.genre,
                   &tempBook.details.year, tempBook.status) == 6)
        {
            library *temp = realloc(book, (count + 1) * sizeof(library));
            if (temp == NULL)
            {
                printf("Memory allocation failed!\n");
                free(book);
                fclose(file);
                exit(1);
            }
            book = temp;
            book[count++] = tempBook;
        }
    }

    fclose(file);
    printf("\nBooks loaded successfully from library.txt.");
}

// Function to exit the program
void exitProgram()
{
    printf("\n\n\t\tExiting Program. Thank you!");
}