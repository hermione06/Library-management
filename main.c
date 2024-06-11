/*-----------------------Library:Book Management----------------*/

#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
// a structure to represent books, including attributes like title, author, genre, price, and quantity.
struct books
{
    char Title[50];
    char Author[50];
    char Genre[30];
    float Price;
    int Quantity_sale;
    int Quantity_rent;
};
int Books_Count = 0; // the number of books in the library
//Function declarations 
void procedures();
int add_new_book(int count) ;
void display_all_books() ;
void update_details() ;
bool search_book(char search_param[], char search_value[]) ;
void sell_book();
void rent_book();
void return_book();
void capitalize_first_letter(char *str) ;
void delete_book(const char* title, const char* file);
void report();
void sales_report();
float calculate_total_sales_revenue();
void bestselling_books();
void rental_report();
void calculate_total_rental_revenue();
void bestrenting_books();

void replaceSpacesWithUnderscores(char *str);
void replaceUnderscoresWithSpaces(char *str);

int main()
{

    printf("Welcome to the Library!\n\nWhat do you want to do?");

    char reply;
    do{
        procedures();
        printf("Would you like to continue with another procedure?(y for yes, n for no): ");
        scanf(" %c", &reply);
    } while (reply ==  'y' || reply=='Y');

    return 0;
}
/*Deals with operations in library management */
void procedures()
{
    printf("\n**********************************");
    printf("\n1. Add a new book \n");
    printf("2. Display all books \n");
    printf("3. Search for a book(s) \n");
    printf("4. Update existing book details \n");
    printf("5. Manage sale of book(s) \n");
    printf("6. Rental of book(s) \n");
    printf("7. Return of book(s) \n");
    printf("8. Display Sales/Rent Reports \n");
    printf("9. Exit \n");
    printf("10.Delete a book \n");
    printf("\n**********************************\n");

    int num;
    do 
    {
        printf("Enter procedure number: ");
        scanf("%d", &num);

        if (num < 1 || num > 10) 
        {
            printf("Invalid number. Please enter again: ");
        }
    } while (num < 1 || num > 10);
    int count;    
    char title[20];

    switch(num)
    {
        case 1: 
            printf("\n----Addition of new book----\nHow many books(different) do you want to add: ");
            scanf("%d", &count);            
            int Books_Count = add_new_book(count) ; 
            break;

        case 2: 
            display_all_books(); 
            break;
        case 3:
            printf("\n----Searching for book(s)----\n");

            printf("How many books (different) are you looking for : ");
            scanf("%d",&count);
            for (int i =0;i<count;i++)
            {
                printf("By which feature you want to search book %d: \n", i+1);
                printf("1.Title\n");
                printf("2.Author\n");
                printf("3.Genre\n");
                printf("4.Price Range\n");

                int num;
                printf("Enter procedure number: ");
                scanf("%d", &num);
                char feature[30];

                if (num == 1)
                {
                    printf("Enter title of book%d: ", i+1);
                    scanf(" %[^\n]s",feature);
                    search_book("title",feature);
                }
                else if (num == 2)
                {
                    printf("Enter Author: ");
                    scanf(" %[^\n]s",feature);    
                    search_book("author",feature);
                
                }
                else if ( num == 3)
                {
                    printf("Enter Genre of the book: ");
                    scanf(" %[^\n]s",feature);  
                    search_book("genre",feature);

                }     
                else if ( num == 4)
                {
                    printf("Enter price range (example: 12-23):\n ");
                    search_book("price_range","0");
                }                
            } 
            break;
        case 4: 
            update_details(); 
            break;
        case 5: 
            sell_book();
            break;
        case 6:
            rent_book();
            break;
        case 7:
           return_book();
           break;
        case 8:
            report();
            break;
         case 9:
            printf( "\nYou exit \n");
            exit(0);
        case 10:
            printf("Which book do you want to remove from library: ");
            scanf(" %[^\n]s", title);
            replaceSpacesWithUnderscores(title);
            delete_book(title,"books.txt");
            printf("Book is deleted successfully.");
    }
}

void update_details() {
    int count;
    printf("How many books do you want to update?: ");
    scanf("%d", &count);

    // Open the file in read and update mode
    FILE* file = fopen("books.txt", "r+");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    // Rewind the file pointer to the beginning
    rewind(file);

    for (int i = 0; i < count; i++) {
        char title[100];
        printf("Enter title of the book: ");
        scanf(" %[^\n]s", title);
        replaceSpacesWithUnderscores(title);

        // Search for the book
        bool found = search_book("title", title);
        if (found) {
            char respond;
            printf("Do you want to update all details of this book? (y/n): ");
            scanf(" %c", &respond);
            if ('Y' == (respond) || 'y' == (respond)) {
                // Add new book
                add_new_book(1);
                delete_book(title,"books.txt");
            } else {
                char detail[20];
                printf("Which detail (Title, Author, Genre, Price, Rent Quantity, Sale Quantity) do you want to change: ");
                scanf(" %s", detail);

                struct books book;
                char line[1000];
                while (fgets(line, sizeof(line), file) != NULL) {
                    struct books book = { .Title = "", .Author = "", .Genre = "", .Price = 0, .Quantity_rent = 0, .Quantity_sale = 0 };

                    if (sscanf(line, "%99s %99s %99s %f %d %d", book.Title, book.Author, book.Genre, &book.Price, &book.Quantity_rent, &book.Quantity_sale) == 6) {
                        // Compare the title of the current book with the input title
                        if (strcasecmp(book.Title, title) == 0) {
                            char new_value[100];
                            if (strcasecmp(detail, "Title") == 0) {
                                printf("Enter new title: ");
                                scanf(" %[^\n]s", new_value);
                                capitalize_first_letter(new_value);
                                replaceSpacesWithUnderscores(new_value);
                                strcpy(book.Title, new_value);
                            } else if (strcasecmp(detail, "Author") == 0) {
                                printf("Enter new author: ");
                                scanf(" %[^\n]s", new_value);
                                capitalize_first_letter(new_value);
                                replaceSpacesWithUnderscores(new_value);
                                strcpy(book.Author, new_value);
                            } else if (strcasecmp(detail, "Genre") == 0) {
                                printf("Enter new genre: ");
                                scanf(" %s", new_value);
                                capitalize_first_letter(new_value);
                                strcpy(book.Genre, new_value);
                            } else if (strcasecmp(detail, "Price") == 0) {
                                printf("Enter new price: ");
                                scanf("%f", &book.Price);
                            } else if (strcasecmp(detail, "Rent Quantity") == 0) {
                                printf("Enter new quantity for rent: ");
                                scanf("%d", &book.Quantity_rent);
                            } else if (strcasecmp(detail, "Sale Quantity") == 0) {
                                printf("Enter new quantity for sale: ");
                                scanf("%d", &book.Quantity_sale);
                            } else {
                                printf("Invalid input!\n");
                                continue;
                            }
                            // Write the book details to the file
                            fseek(file, -strlen(line), SEEK_CUR); // Move the file pointer back to overwrite the line
                            fprintf(file, "%-30s%-30s%-20s%10.2f%15d%15d\n", book.Title, book.Author, book.Genre, book.Price, book.Quantity_rent, book.Quantity_sale);

                             printf("This book is updated!\n");
                            break; // Exit the loop after updating the book
                        }
                    }
                }
            }
        } else {
            printf("Book not found!\n");
        }
    }

    // Close the file
    fclose(file);
}

/* Searches for books in the library based on the specified search parameter and value.
    Displays books matching the search criteria, including title, author, genre, price, and quantity.
    allows searching by title, author, genre, or price range.*/
bool search_book(char search_param[], char search_value[]) 
{
    FILE* file = fopen("books.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return false;
    }
    replaceSpacesWithUnderscores(search_value);
    struct books book;
    bool found = false;
    // Print header
    printf("Title                        Author                         Genre               Price         Rent_Quantity    Sale_Quantity\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");


    char line[4096];
    fgets(line, sizeof(line), file); // Skip the header line

    while (fgets(line, sizeof(line), file)) 
    {
        // Use sscanf to parse the line
        if (sscanf(line, "%99s %99s %99s %f %d %d", book.Title, book.Author, book.Genre, &book.Price, &book.Quantity_rent, &book.Quantity_sale) == 6)
        { 
        

    // Read each book from the file
        if (strcasecmp(search_param, "title") == 0 && strcasecmp(book.Title, search_value) == 0) {
            found = true;
            replaceUnderscoresWithSpaces(book.Title);
            replaceUnderscoresWithSpaces(book.Author);
            printf("%-30s%-30s%-20s%-10.2f%15d%15d\n", book.Title, book.Author, book.Genre, book.Price, book.Quantity_rent, book.Quantity_sale);
        } else if (strcasecmp(search_param, "author") == 0 && strcasecmp(book.Author, search_value) == 0) {
            found = true;
            replaceUnderscoresWithSpaces(book.Title);
            replaceUnderscoresWithSpaces(book.Author);
            printf("%-30s%-30s%-20s%-10.2f%15d%15d\n", book.Title, book.Author, book.Genre, book.Price, book.Quantity_rent, book.Quantity_sale);
        } else if (strcasecmp(search_param, "genre") == 0 && strcasecmp(book.Genre, search_value) == 0) {
            found = true;
            replaceUnderscoresWithSpaces(book.Title);
            replaceUnderscoresWithSpaces(book.Author);
            printf("%-30s%-30s%-20s%-10.2f%15d%15d\n", book.Title, book.Author, book.Genre, book.Price, book.Quantity_rent, book.Quantity_sale);
        }
        else if (strcmp(search_param, "price_range") == 0) {
            float min_price, max_price;
            printf("Enter the low value of the price range: ");
            scanf("%f", &min_price);
            printf("Enter the high value of the price range: ");
            scanf("%f", &max_price);

            // Ensure min_price is less than or equal to max_price
            if (min_price <= max_price) {
                // Read book details from file and check if price is within the range
                struct books book;
                printf("Title                        Author                         Genre               Price         Rent_Quantity    Sale_Quantity\n");
                printf("----------------------------------------------------------------------------------------------------------------------------\n");
                while (fscanf(file, "%99s %99s %99s %f %d %d",
                            book.Title, book.Author, book.Genre,
                            &book.Price, &book.Quantity_rent, &book.Quantity_sale) == 6) {
                    if (book.Price >= min_price && book.Price <= max_price) {
                        // Print the book details
                        found = true;
                        replaceUnderscoresWithSpaces(book.Title);
                        replaceUnderscoresWithSpaces(book.Author);
                        printf("%-30s%-30s%-20s%-10.2f%15d%15d\n", 
                            book.Title, book.Author, book.Genre, 
                            book.Price, book.Quantity_rent, book.Quantity_sale);
                    }
                }
                // Close the file
                fclose(file);
            } else {
                // Handle invalid price range input (min_price > max_price)
                printf("Invalid price range input.\n");
            }
}

    }
    }

    if (!found) {
        printf("No books found matching the search criteria.\n");
    }

    fclose(file);
    return found;
}


void replaceSpacesWithUnderscores(char *str) {
    // Iterate through each character of the string
    for (int i = 0; str[i] != '\0'; i++) {
        // If the current character is a space, replace it with an underscore
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

void replaceUnderscoresWithSpaces(char *str) {
    // Iterate through each character of the string
    for (int i = 0; str[i] != '\0'; i++) {
        // If the current character is an underscore, replace it with a space
        if (str[i] == '_') {
            str[i] = ' ';
        }
    }
}


/* Allows users to add one or more new books to the library.
    Prompts users to enter details such as title, author, genre, price, and quantity for each book.
     Checks for existing books and offers to update quantities(rent/sale quantities) if a book with the same title and author is found.*/
int add_new_book(int count) 
{
    printf("Please enter details of the book:\n");

    for (int i = 0; i < count; i++) {
        printf("\nBook%d\n", i + 1);

        // getting the book title and authors name
        struct books new_book;
        printf("Enter title: ");
        scanf(" %[^\n]s", new_book.Title);
        capitalize_first_letter(new_book.Title);
        replaceSpacesWithUnderscores(new_book.Title);

        printf("Enter author: "); 
        scanf(" %[^\n]s", new_book.Author);
        capitalize_first_letter(new_book.Author);
        replaceSpacesWithUnderscores(new_book.Author);

        FILE* file = fopen("books.txt", "r");
        if (file == NULL) {
            printf("Error opening file.\n");
            return 0;
        }

        struct books existing_book;
        bool exists = false;
        char line[1000];
        while (fgets(line, sizeof(line), file) != NULL) {
            struct books existing_book = { .Title = "", .Author = "", .Genre = "", .Price = 0, .Quantity_rent = 0, .Quantity_sale = 0 };

            if (sscanf(line, "%99s %99s %99s %f %d %d", existing_book.Title, existing_book.Author, existing_book.Genre, &existing_book.Price, &existing_book.Quantity_rent, &existing_book.Quantity_sale) == 6) {
                // Check if the title of the current book matches the title of the new book
                if (strcasecmp(existing_book.Title, new_book.Title) == 0 && strcasecmp(existing_book.Author, new_book.Author)== 0) {
                    // checking for both title and author matches
                    exists = true;            
                    printf("The book exists\n");
                    break;
                }
            }
        }

        fclose(file);

        if (exists) {
            char reply;
            printf("This book already exists in the library.\n");
            search_book("title",existing_book.Title);
            printf("Would you like to continue adding this book again? (y/n): ");
            scanf(" %c", &reply);

            if (reply == 'y' || reply == 'Y') {
                // Increment existing book quantity
                int rent_num, sale_num;
                printf("How many books for renting would you like to add: ");
                while (scanf("%d", &rent_num) != 1 || rent_num < 0) {
                    printf("Invalid input. Please enter a non-negative number: ");
                    while (getchar() != '\n');
                }
                existing_book.Quantity_rent += rent_num;

                printf("How many books for selling would you like to add: ");
                while (scanf("%d", &sale_num) != 1 || sale_num < 0) {
                    printf("Invalid input. Please enter a non-negative number: ");
                    while (getchar() != '\n');
                }
                existing_book.Quantity_sale += sale_num;
                FILE *file = fopen("books.txt", "r+");
                if (file == NULL) {
                    printf("Error opening file for updating!\n");
                    return 0;
                }

                while (fgets(line, sizeof(line), file) != NULL) {
                    if (sscanf(line, "%99s %99s %99s %f %d %d", existing_book.Title, existing_book.Author, existing_book.Genre, &existing_book.Price, &existing_book.Quantity_rent, &existing_book.Quantity_sale) == 6) {
                        if (strcasecmp(existing_book.Title, new_book.Title) == 0 && strcasecmp(existing_book.Author, new_book.Author) == 0) {
                            delete_book(existing_book.Title,"books.txt");
                            fseek(file, 0, SEEK_END); 
                            fprintf(file,"\n");
                            fprintf(file, "%-30s%-30s%-20s%10.2f%15d%15d\n", existing_book.Title, existing_book.Author, existing_book.Genre, existing_book.Price, existing_book.Quantity_rent+rent_num, existing_book.Quantity_sale+sale_num);

                        break;
                        }
                    }
                }
                fclose(file);
                printf("Addition is completed. \n");
            } else if (reply == 'n' || reply == 'N') {
                printf("Okay. Thanks for choosing us.\n\n");
            } else {
                printf("Invalid input.\n");
            }
        } else {
            // Add a new book

            printf("Enter genre: ");
            scanf(" %[^\n]s", new_book.Genre);
            capitalize_first_letter(new_book.Genre);

            printf("Enter price ($) (of one): ");
            while (scanf("%f", &new_book.Price) != 1) {
                printf("Input is not a number. Please enter again: ");
                while (getchar() != '\n');
            }

            printf("Enter quantity available for rent: ");
            while (scanf("%d", &new_book.Quantity_rent) != 1) {
                printf("Input is not a number. Please enter again: ");
                while (getchar() != '\n');
            }

            printf("Enter quantity available for sale: ");
            while (scanf("%d", &new_book.Quantity_sale) != 1) {
                printf("Input is not a number. Please enter again: ");
                while (getchar() != '\n');
            }

            printf("Addition is completed. Thank you for donation.\n");

            // Open the file in append mode to add new book details
            FILE* appendFile = fopen("books.txt", "a");
            if (appendFile == NULL) {
                printf("Error opening file for appending!\n");
                return 0;
            }
            // Write book data
            fprintf(appendFile, "%-30s%-30s%-20s%.2f%15d%15d\n\n",
                    new_book.Title,
                    new_book.Author,
                    new_book.Genre,
                    new_book.Price,
                    new_book.Quantity_rent,
                    new_book.Quantity_sale);
            fclose(appendFile);

            Books_Count++;
        }
    }
    return Books_Count;
}

/*  Displays all books currently available in the library system.
    Reads book details from the "books.txt" file and prints them in a tabular form.
    Includes information such as title, author, genre, price, rent quantity, and sale quantity.
*/
void display_all_books() 
{
    printf("\n---------------------------------------------------BOOKS--------------------------------------------------------------\n");
    printf("%-30s%-30s%-20s%-10s%-15s%-15s\n",
           "Title", "Author", "Genre", "Price", "Quantity_rent", "Quantity_sale");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    char line[4096];
    fgets(line, sizeof(line), file); // Skip the header line

    while (fgets(line, sizeof(line), file)) 
    {
        char title[100], author[100], genre[100];
        float price;
        int quantity_rent, quantity_sale;

        // Use sscanf to parse the line
        if (sscanf(line, "%99[^  ] %99[^  ] %99[^  ] %f %d %d", title, author, genre, &price, &quantity_rent, &quantity_sale) == 6) {
            replaceUnderscoresWithSpaces(title);
            replaceUnderscoresWithSpaces(author);
            printf("%-30s%-30s%-20s%-10.2f%-15d%-15d\n", title, author, genre, price, quantity_rent, quantity_sale);
        }
    }

    fclose(file);
}
/* Makes the first letter of each word CAPITAL in the given string.
    Converts the first character to uppercase and subsequent characters to lowercase.
    Assumes the input string is null-terminated.(ends with '\0')
*/
void capitalize_first_letter(char *str) 
{
    // Capitalize first letter
    if (str[0] >= 'a' && str[0] <= 'z') 
    {
        str[0] = str[0] - ('a' - 'A');
    }
    
    // Capitalize first letter after spaces
    for (int i = 1; str[i] != '\0'; i++) 
    {
        if (str[i - 1] == ' ' && (str[i] >= 'a' && str[i] <= 'z')) 
        {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}
/*  Manages the sale of a book by updating its quantity in the main book inventory file and the sales record file.
    Prompts the user to enter the title and quantity of the book being sold.
    Calculates the total price of the sale and updates the quantity of the book in both files accordingly.
*/
void sell_book() {
    printf("----Sales Management----\n");
    char title[100];
    char choice[5];
    float total_price = 0;

    do {
        printf("Enter book title: ");
        scanf(" %[^\n]", title); 
        replaceSpacesWithUnderscores(title);

        bool found = search_book("title",title);

        if (!found) {
            printf("There is no such book in our library.\n");
        } else {
            FILE* file = fopen("books.txt", "r+");
            if (file == NULL) {
                printf("Error opening file.\n");
                return;
            }
            FILE* sold_file = fopen("sale.txt", "r+");
            if (file == NULL) {
                printf("Error opening file.\n");
                return;
            }

            char book_title[100];
            char author[100];
            char genre[100];
            float price;
            int quantity_rent, quantity_sale, quantity_sold;

            // Read each line from the file
            char line[1000]; char sold_line[1000];
            fgets(line, sizeof(line), file); // Skip the header line

            while (fgets(line, sizeof(line), file)) {
                // Use sscanf to parse the line
                if (sscanf(line, "%99s %99s %99s %f %d %d", book_title, author, genre, &price, &quantity_rent, &quantity_sale) == 6) {
                    if (strcasecmp(book_title, title) == 0) {
                        if (quantity_sale == 0) {
                            printf("Unfortunately, the quantity of this book available for sales is zero.\nPlease try again later.\n");
                        } else {
                            int count;
                            printf("Specify quantity of this book: ");
                            scanf("%d", &count);
                            while (count > quantity_sale || count < 1) {
                                printf("Invalid number! Please enter a valid quantity: ");
                                scanf("%d", &count);
                            }
                            float sale_price = price * count;
                            printf("The price to be paid is $%.2f\n", sale_price);
                            total_price += sale_price;
                            // Update the quantity of the book after the sale
                            delete_book(book_title, "books.txt");
                            fseek(file, 0, 2); // Move the file pointer back to overwrite the line
                            fprintf(file, "%-30s%-30s%-20s%.2f%15d%15d\n", book_title, author, genre, price, quantity_rent, quantity_sale - count);
                            
                            fseek(sold_file, 0, SEEK_SET);
                            bool found = false;
                            while (fgets(sold_line, sizeof(sold_line), sold_file)) {                           
                                //fprintf(sold_file,sold_line);
                                if (sscanf(sold_line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_sold) == 5) {
                                    if (strcasecmp(book_title, title) == 0) {
                                        found = true;
                                        delete_book(book_title, "sale.txt");
                                        fseek(sold_file, 0, SEEK_END); // Move the file pointer back to overwrite the line
                                        fprintf(sold_file,"\n");
                                        fprintf(sold_file, "%-30s%-30s%-20s%.2f%15d\n", book_title, author, genre, price, quantity_sold + count);
                                        
                                        break;
                                    }                       
                                }   
                            }
                            if (!found) {
                                sscanf(line, "%99s %99s %99s %f %d %d", book_title, author, genre, &price, &quantity_rent, &quantity_sale);
                                fseek(sold_file, 0, SEEK_END); // Move the file pointer to the end
                                fprintf(sold_file, "%-30s%-30s%-20s%.2f%15d\n", book_title, author, genre, price, count);
                            }
                        }
                        break;
                    }
                }
            }

            fclose(file); fclose(sold_file);
        }
        printf("Total price so far: $%.2f\n", total_price);
        printf("Do you want to continue buying? (yes/no): ");
        scanf(" %[^\n]", choice);
    } while (strcmp(choice,"yes") == 0);
}

/*Manages rental of the books
User inputs the book title, number of books, and number of days the books are rented for
Then the rented book is added to rent.txt which stores all rented books*/
void rent_book() {
    printf("----Rental Management----\n");
    char title[100];
    char choice[5];

    do {
        printf("Enter book title: ");
        scanf(" %[^\n]", title); 
        replaceSpacesWithUnderscores(title);

        bool found = search_book("title",title);

        if (!found) {
            printf("There is no such book in our library.\n");
        } else {
            FILE* file = fopen("books.txt", "r+");
            if (file == NULL) {
                printf("Error opening file.\n");
                return;
            }
            FILE* rent_file = fopen("rent.txt", "r+");
            if (file == NULL) {
                printf("Error opening file.\n");
                return;
            }

            char book_title[100];
            char author[100];
            char genre[100];
            float price;
            int quantity_rent, quantity_sale, quantity_rented;

            // Read each line from the file
            char line[1000]; char rented_line[1000];
            fgets(line, sizeof(line), file); // Skip the header line

            while (fgets(line, sizeof(line), file)) {
                // Use sscanf to parse the line
                if (sscanf(line, "%99s %99s %99s %f %d %d", book_title, author, genre, &price, &quantity_rent, &quantity_sale) == 6) {
                    if (strcasecmp(book_title, title) == 0) {
                        if (quantity_rent == 0) {
                            printf("Unfortunately, the quantity of this book available for rental is zero.\nPlease try again later.\n");
                        } else {
                            int count;
                            printf("Specify quantity of this book: ");
                            scanf("%d", &count);
                            while (count > quantity_sale || count < 1) {
                                printf("Invalid number! Please enter a valid quantity: ");
                                scanf("%d", &count);
                            }
                            int days;
                        printf("how many days would you like to rent for?\n");
                        scanf("%d", &days);
                        while (days < 1) {
                            printf("Invalid number! Please enter a valid number of days: ");
                            scanf("%d", &days);
                        }
                        printf("Book is rented for %d days! ", days);
                        // Update the quantity of the book after the sale
                        //fprintf(file,"\n\n");
                        delete_book(book_title,"books.txt");
                        fseek(file, 0, 2); // Move the file pointer back to overwrite the line
                        fprintf(file, "%-30s%-30s%-20s%.2f%15d%15d\n", book_title, author, genre, price, quantity_rent - count, quantity_sale);
                        
                        fseek(rent_file, 0, SEEK_SET);
                        bool foundd = false;
                        while (fgets(rented_line, sizeof(rented_line), rent_file)) {                           
                            //fprintf(rent_file,rented_line);
                            if (sscanf(rented_line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_rented) == 5) {
                                if (strcasecmp(book_title, title) == 0) {
                                    foundd = true;
                                    delete_book(book_title, "rent.txt");
                                    fseek(rent_file, 0, SEEK_END); // Move the file pointer back to overwrite the line
                                    fprintf(rent_file,"\n");
                                    fprintf(rent_file, "%-30s%-30s%-20s%.2f%15d\n", book_title, author, genre, price, quantity_rented + count);
                                    break;
                                }                       
                            }   
                        }
                            if (!found) {
                                sscanf(line, "%99s %99s %99s %f %d %d", book_title, author, genre, &price, &quantity_rent, &quantity_sale);
                                fseek(rent_file, 0, SEEK_END); // Move the file pointer to the end
                                fprintf(rent_file, "%-30s%-30s%-20s%.2f%15d\n", book_title, author, genre, price, count);
                            }
                        }
                        break;
                    }
                }
            }

            fclose(file); fclose(rent_file);
        }
        printf("Do you want to continue renting? (yes/no): ");
        scanf(" %[^\n]", choice);
    } while (strcmp(choice,"yes") == 0);
}

/*Manages returnal of the book after its rented*/
void return_book() {
    printf("----Return Management----\n");
    char title[100]; 
    printf("Enter book title: ");
    scanf(" %[^\n]", title); 
    replaceSpacesWithUnderscores(title);

    bool found = search_book("title",title);

    if (!found) {
        printf("There is no such book in our library.\n");
    } else {
        FILE* file = fopen("books.txt", "r+");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        FILE* rent_file = fopen("rent.txt", "r+");
        if (rent_file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        char book_title[100];
        char author[100];
        char genre[100];
        float price;
        int quantity_rent, quantity_sale, quantity_rented;

        // Read each line from the file
        char line[1000]; char rented_line[1000];
        fgets(line, sizeof(line), file); // Skip the header line

        while (fgets(line, sizeof(line), file)) {
            // Use sscanf to parse the line
            if (sscanf(line, "%99s %99s %99s %f %d %d", book_title, author, genre, &price, &quantity_rent, &quantity_sale) == 6) {
                if (strcasecmp(book_title, title) == 0) {
                        int count;
                        printf("Specify quantity of this book: ");
                        scanf("%d", &count);
                        while (count < 0) {
                            printf("Invalid number! Please enter a valid quantity: ");
                            scanf("%d", &count);
                        }
                        printf("Returned the book successfully! ");
                        // Update the quantity of the book after the sale
                        delete_book(book_title,"books.txt");
                        fseek(file, 0, 2); // Move the file pointer back to overwrite the line
                        fprintf(file, "%-30s%-30s%-20s%.2f%15d%15d\n", book_title, author, genre, price, quantity_rent + count, quantity_sale);                        
                    break;
                }
            }
        }

        fclose(file);
    }
}

/*Deletes book using its title
It copies all the books to a temporary file skiping the specified book
Then copies all bood to the main file again*/
void delete_book(const char* title, const char* file_name) {
    FILE* file = fopen(file_name, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[1000];
    bool found = false;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Use sscanf to parse the line and check if it contains the book title
        char book_title[100];
        sscanf(line, "%99s", book_title);
        if (strcasecmp(book_title, title) == 0) {
            found = true;
            continue; // Skip writing this line to temp file
        }
        // Write the line to the temporary file
        fprintf(temp_file, "%s", line);
    }

    fclose(file);
    fclose(temp_file);

    file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    temp_file = fopen("temp.txt", "r");
    if (temp_file == NULL) {
        printf("Error opeaning temporary file.\n");
        fclose(file);
        return;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), temp_file)) {
        // Use sscanf to parse the line and check if it contains the book title
        char book_title[100];
        sscanf(line, "%99s", book_title);
        // Write the line to the temporary file
        fprintf(file, "%s", line);
    }

    fclose(file);
    fclose(temp_file);
}

/*reporting function*/
void report(){
    printf("-------------Report--------------\n\n");
    printf("Would you like to see rental(1) or sales(2) reports? ");
    int n;
    scanf("%d", &n);
    if (n==1){
        rental_report();
    }
    else if (n==2){
        sales_report();
}
}

/*sales report function
outputs total number of books sold
total profit
and datas of the bestselling book*/
void sales_report() {
    printf("----Sales Report----\n\n");
    printf("Total revenue: %.2f\n", calculate_total_sales_revenue());
    bestselling_books(); 
}

/* calculates the profit and while doing so also counts the books*/
float calculate_total_sales_revenue() {

    FILE* sale_file = fopen("sale.txt","r");
    if (sale_file == NULL) {
        printf("Error opening file.\n");
        return 0.0;
    }
    char line[1000];
    char book_title[100];
    char author[100];
    char genre[100];
    float price;
    int quantity_sold;
    float total=0; int totalnum = 0;
    while (fgets(line, sizeof(line), sale_file)) {
            // Use sscanf to parse the line 
        if (sscanf(line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_sold) == 5){
            total = total + price * quantity_sold; 
            totalnum = totalnum + quantity_sold;
        }
    }
    fclose(sale_file);
    printf("total number of books: %d\n",totalnum);
    return total;
}

/*finds best selling book using the sales file*/
void bestselling_books() {
    FILE* sale_file = fopen("sale.txt","r");
    if (sale_file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char line[1000]; 
    char book_title[100]; char title [100];
    char author[100];
    char genre[100];
    float price;
    int quantity_sold = 0; int quantity_sold_max = 0;
    float total=0;
    while (fgets(line, sizeof(line), sale_file)) {
            // Use sscanf to parse the line 
        if (sscanf(line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_sold) == 5){
            if (quantity_sold > quantity_sold_max){
                strcpy(title, book_title);
                quantity_sold_max=quantity_sold;
            }
        }
    }
    fclose(sale_file);
    sale_file = fopen("sale.txt","r");
    if (sale_file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), sale_file)) {
            // Use sscanf to parse the line 
        if (sscanf(line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_sold) == 5){
            if (quantity_sold == quantity_sold_max){
            printf("Best sold book: \n");
            printf("Title                        Author                         Genre               Price            Quantity    \n");
            printf("--------------------------------------------------------------------------------------------------------------\n");
            replaceUnderscoresWithSpaces(book_title);
            replaceUnderscoresWithSpaces(author);
            printf("%-30s%-30s%-20s%-10.2f%15d\n", book_title, author, genre, price, quantity_sold_max);            }
        }
    }

    fclose(sale_file);
    
}

/*rental report function
outputs total number of books rented
and datas of the most rented book*/
void rental_report() {
    printf("----Rental Report----\n\n");
    calculate_total_rental_revenue();
    printf("\n");
    bestrenting_books();
}

/*counts the number of books rented*/
void calculate_total_rental_revenue() {
    FILE* rent_file = fopen("rent.txt","r");
    if (rent_file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char line[1000];
    char book_title[100];
    char author[100];
    char genre[100];
    float price;
    int quantity_rented;
    float total=0; int totalnum = 0;
    while (fgets(line, sizeof(line), rent_file)) {
            // Use sscanf to parse the line 
        if (sscanf(line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_rented) == 5){
            totalnum = totalnum + quantity_rented;
        }
    }
    fclose(rent_file);
    printf("total number of books: %d\n",totalnum);
    return;
}

/*finds most rented book using the rent file*/

void bestrenting_books() {
    FILE* rent_file = fopen("rent.txt","r");
    if (rent_file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char line[1000]; 
    char book_title[100]; char title [100];
    char author[100];
    char genre[100];
    float price;
    int quantity_rented = 0; int quantity_rented_max = 0;
    float total=0;
    while (fgets(line, sizeof(line), rent_file)) {
            // Use sscanf to parse the line 
        if (sscanf(line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_rented) == 5){
            if (quantity_rented > quantity_rented_max){
                strcpy(title, book_title);
                quantity_rented_max=quantity_rented;
            }
        }
    }
    fclose(rent_file);
    rent_file = fopen("rent.txt","r");
    if (rent_file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), rent_file)) {
            // Use sscanf to parse the line 
        if (sscanf(line, "%99s %99s %99s %f %d", book_title, author, genre, &price, &quantity_rented) == 5){
            if (quantity_rented == quantity_rented_max){
                    printf("Most rented book: \n");
                    printf("Title                        Author                         Genre               Price            Quantity    \n");
                    printf("--------------------------------------------------------------------------------------------------------------\n");
                    replaceUnderscoresWithSpaces(book_title);
                    replaceUnderscoresWithSpaces(author);
                    printf("%-30s%-30s%-20s%-10.2f%15d\n", book_title, author, genre, price, quantity_rented_max);
                    
            }
        }
    }
    
    fclose(rent_file);
} 
