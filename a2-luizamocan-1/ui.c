#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_valid_float(const char* str) {
    char* endptr;
    strtof(str, &endptr);  // Convert string to float
    return (*endptr == '\0');  // Check if the entire string was valid
}

// Function to check if a date is in the correct format (YYYY-MM-DD)
int is_valid_date(const char* date) {
    int year, month, day;
    return sscanf(date, "%4d-%2d-%2d", &year, &month, &day) == 3 &&
           month >= 1 && month <= 12 && day >= 1 && day <= 31;
}
// Function to check if the type is valid (one of city-break, mountain, or seaside)
int is_valid_type(const char* type) {
    return (strcmp(type, "city-break") == 0 || strcmp(type, "mountain") == 0 || strcmp(type, "seaside") == 0);
}


// Function to handle invalid integer input
int read_int() {
    int value;
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');  // Clear the input buffer
        printf("Invalid input. Please enter a valid integer: ");
    }
    return value;
}

// Function to handle invalid float input
float read_float() {
    float value;
    char buffer[100];
    while (1) {
        if (scanf("%s", buffer) != 1 || !is_valid_float(buffer)) {
            printf("Invalid input. Please enter a valid number: ");
            while (getchar() != '\n');  // Clear the input buffer
        } else {
            value = strtof(buffer, NULL);
            break;
        }
    }
    return value;
}

// Function to handle invalid string input (non-empty)
void read_string(char* buffer, size_t size) {
    while (1) {
        if (scanf("%s", buffer) != 1 || strlen(buffer) == 0) {
            printf("Invalid input. Please enter a non-empty string: ");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
}

void print_menu() {
    printf("\nWelcome to Happy Holidays!\n");
    printf("1. Add a new offer\n");
    printf("2. Delete an offer\n");
    printf("3. Update an offer\n");
    printf("4. Display all tourism offers whose destinations contain a given string\n");
    printf("5. Display all offers of a given type, having their departure after a given date.\n");
    printf("6. Print all offers\n");
    printf("7. Undo \n");
    printf("8. Redo \n");
    printf("0. Exit\n");
}

void start_ui(OfferService* service) {
    int option;
    initialize_offers(service);
    while (1) {
        print_menu();
        printf("Choose an option: ");
        option = read_int();

        if (option == 1) {
            char type[50], destination[50], date[50];
            float price;

            // Input type with validation
            printf("Enter type (mountain/seaside/city-break): ");
            read_string(type, sizeof(type));

            while (!is_valid_type(type)) {
                printf("Invalid type! Please enter a valid type (mountain/seaside/city-break): ");
                read_string(type, sizeof(type));
            }

            printf("Enter destination: ");
            read_string(destination, sizeof(destination));
            printf("Enter date (YYYY-MM-DD): ");
            read_string(date, sizeof(date));

            if (!is_valid_date(date)) {
                printf("Invalid date format! Please use YYYY-MM-DD.\n");
                continue;
            }

            printf("Enter price: ");
            price = read_float();
            service_add_offer(service, type, destination, date, price);
            printf("Offer added successfully.\n");
        }
        else if (option == 2) {
            char destination[50], date[50];
            printf("Enter destination: ");
            read_string(destination, sizeof(destination));
            printf("Enter date: ");
            read_string(date, sizeof(date));

            if (!is_valid_date(date)) {
                printf("Invalid date format! Please use YYYY-MM-DD.\n");
                continue;
            }

            service_delete_offer(service, destination, date);
            printf("Offer deleted successfully.\n");
        }
        else if (option == 3) {
            char destination[50], date[50], new_date[50];
            float new_price;
            printf("Enter destination: ");
            read_string(destination, sizeof(destination));
            printf("Enter date: ");
            read_string(date, sizeof(date));

            if (!is_valid_date(date)) {
                printf("Invalid date format! Please use YYYY-MM-DD.\n");
                continue;
            }

            printf("Enter new date: ");
            read_string(new_date, sizeof(new_date));

            if (!is_valid_date(new_date)) {
                printf("Invalid date format! Please use YYYY-MM-DD.\n");
                continue;
            }

            printf("Enter new price: ");
            new_price = read_float();
            service_update_offer(service, destination, date, new_date, new_price);
            printf("Offer updated successfully.\n");
        }
        else if (option == 4) {
            char search[50];
            printf("Enter destination filter string(empty for all): ");
            read_string(search, sizeof(search));
            display_offers(service,search);

        }
        else if (option == 5) {
            char type[50], departure_date[50];
            printf("Enter the type :");
            read_string(type, sizeof(type));
            if (!is_valid_type(type)) {
                printf("Invalid type! Please enter a valid type (empty for all): \n");
                continue;
            }

            printf("Enter departure date: ");
            read_string(departure_date, sizeof(departure_date));
            if (!is_valid_date(departure_date)) {
                printf("Invalid date format! Please use YYYY-MM-DD.\n");
                continue;
            }
            display_offers_given_type(service, type, departure_date);

        }
        else if (option == 6) {
            service_print_offers(service);
        }
        else if (option == 7) {
            undo(service->undo_redo_service);
        }
        else if (option == 8) {
            redo(service->undo_redo_service);
        }
        else if (option == 0) {
            break;
        }
        else {
            printf("Invalid option! Please try again.\n");
        }
    }
}
