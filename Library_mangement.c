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
    loadFromFile(); // Load data at startup

    int choice;
    do
    {
        printf("\n***** Main Menu *****\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Remove Book\n");
        printf("5. Update Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
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
            saveToFile(); // Save data on exit
            printf("\nExiting program. Goodbye!\n");
            break;
        default:
            printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to display a welcome message
void welcomeMessage()
{
    printf("\n\n\t*");
    printf("\n\t*             WELCOME TO THE LIBRARY         *");
    printf("\n\t*                     CSE, AMRITA            *");
    printf("\n\t                                             *\n");
}

// Function to add a new book
void addBook()
{
    library *temp = realloc(book, (count + 1) * sizeof(library));
    if (temp == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    book = temp;

    printf("\n\t\t** Add New Book Details ***");
    printf("\n\t\t* Enter Book Id: ");
    scanf("%d", &book[count].id);
    printf("\t\t* Enter Book Name: ");
    getchar();
    fgets(book[count].name, sizeof(book[count].name), stdin);
    book[count].name[strcspn(book[count].name, "\n")] = 0;
    printf("\t\t* Enter Book Author: ");
    fgets(book[count].author, sizeof(book[count].author), stdin);
    book[count].author[strcspn(book[count].author, "\n")] = 0;
    printf("\t\t* Enter Book Genre: ");
    fgets(book[count].details.genre, sizeof(book[count].details.genre), stdin);
    book[count].details.genre[strcspn(book[count].details.genre, "\n")] = 0;
    printf("\t\t* Enter Book Year: ");
    scanf("%d", &book[count].details.year);

    strcpy(book[count].status, "Available");

    count++;
    printf("\t\tBook added successfully.\n");

    saveToFile();
}

// Function to view all books
void viewAllBooks()
{
    printf("\n\t\t|************************ View All Books ********************************");
    printf("\n\t\t|-------------------------------------------------------------------------|");
    printf("\n\t\t| Id\tTitle\tAuthor\tGenre\tYear\tStatus|");
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
    printf("\n\t\t|%d\t%s\t%s\t%s\t%d\t%s|", book[index].id, book[index].name,
           book[index].author, book[index].details.genre, book[index].details.year, book[index].status);
    printBooks(index + 1);
}

// Function to search for a book by name
void searchBook()
{
    int choice, found = 0;
    char title[50];
    int id;

    printf("\nSearch Book by:\n1. ID\n2. Title\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter Book ID: ");
        scanf("%d", &id);

        for (int i = 0; i < count; i++)
        {
            if (book[i].id == id)
            {
                printf("\nBook Found:\n");
                printf("ID: %d, Title: %s, Author: %s, Genre: %s, Year: %d, Status: %s\n",
                       book[i].id, book[i].name, book[i].author, book[i].details.genre, book[i].details.year, book[i].status);
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter Book Title: ");
        scanf(" %[^\n]s", title);

        for (int i = 0; i < count; i++)
        {
            if (strcmp(book[i].name, title) == 0)
            {
                printf("\nBook Found:\n");
                printf("ID: %d, Title: %s, Author: %s, Genre: %s, Year: %d, Status: %s\n",
                       book[i].id, book[i].name, book[i].author, book[i].details.genre, book[i].details.year, book[i].status);
                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("\nInvalid choice!\n");
        return;
    }

    if (!found)
    {
        printf("\nBook not found.\n");
    }
}

void removeBook()
{
    int id, found = 0;
    printf("Enter Book ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (book[i].id == id)
        {
            found = 1;
            // Shift all books after the found index one position back
            for (int j = i; j < count - 1; j++)
            {
                book[j] = book[j + 1];
            }
            count--;
            printf("\nBook with ID %d removed successfully.\n", id);
            saveToFile(); // Save updated data
            break;
        }
    }

    if (!found)
    {
        printf("\nBook with ID %d not found.\n", id);
    }
}

// Function to update a book by name
void updateBook()
{
    int id, found = 0;
    printf("Enter Book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (book[i].id == id)
        {
            found = 1;
            printf("\nEnter new details:\n");
            printf("Title: ");
            scanf(" %[^\n]s", book[i].name);
            printf("Author: ");
            scanf(" %[^\n]s", book[i].author);
            printf("Genre: ");
            scanf(" %[^\n]s", book[i].details.genre);
            printf("Year: ");
            scanf("%d", &book[i].details.year);
            printf("Status: ");
            scanf(" %[^\n]s", book[i].status);

            printf("\nBook with ID %d updated successfully.\n", id);
            saveToFile(); // Save updated data
            break;
        }
    }

    if (!found)
    {
        printf("\nBook with ID %d not found.\n", id);
    }
}

// Function to save all books to a text file
// Function to save all books to a text file
void saveToFile()
{
    FILE *file = fopen("library.txt", "w");
    if (file == NULL)
    {
        printf("\nError saving library data to file!\n");
        return;
    }

    // Write header for clarity (optional)
    fprintf(file, "Id\tTitle\tAuthor\tGenre\tYear\tStatus\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d\t%s\t%s\t%s\t%d\t%s\n",
                book[i].id, book[i].name, book[i].author,
                book[i].details.genre, book[i].details.year,
                book[i].status);
    }

    fclose(file);
    printf("\nLibrary data saved successfully to library.txt.\n");
}

// Function to load all books from a text file
void loadFromFile()
{
    FILE *file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("\nNo existing library data found. Starting fresh.\n");
        return;
    }

    // Read the first line (header) and ignore it
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        library tempBook;

        // Match the exact format used in saveToFile
        if (sscanf(buffer, "%d\t%49s\t%49s\t%49s\t%d\t%49s",
                   &tempBook.id, tempBook.name, tempBook.author,
                   tempBook.details.genre, &tempBook.details.year,
                   tempBook.status) == 6)
        {
            library *temp = realloc(book, (count + 1) * sizeof(library));
            if (temp == NULL)
            {
                printf("\nMemory allocation failed while loading books!");
                free(book);
                fclose(file);
                exit(1);
            }
            book = temp;
            book[count++] = tempBook;
        }
        else
        {
            printf("\nError parsing line: %s", buffer);
        }
    }

    fclose(file);
    printf("\nBooks loaded successfully from library.txt. Total books: %d\n", count);
}

// Function to exit the program
void exitProgram()
{
    printf("\n\n\t\tExiting Program. Thank you!");
}
