#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Costumer.h"



Costumer *initCostumer(Costumer* costumer)
{
    // Initialize pointers to NULL
    //initializeCart(costumer->cart);
    costumer->costumerName = "";
    *costumer->id = "NULL";
    return costumer;
}

Costumer* newCostumer(char *id)
{
    Costumer* new_costumer = (Costumer*)malloc(sizeof(Costumer));
    initCostumer(new_costumer);
    *new_costumer->id = malloc(maxSizeId);
    strcpy(new_costumer->id, id);
    //printf("Enter costumer id: ");
    //fgets(new_costumer->id, sizeof(new_costumer->id), stdin);  // Corrected size

    char first_name[255];
    char last_name[255];

    // Prompt user for first name
    printf("Enter customer first name: \n");
    fgets(first_name, sizeof(first_name), stdin);
    first_name[strcspn(first_name, "\n")] = '\0';  // Remove the trailing newline
    // Prompt user for last name
    printf("Enter customer last name: \n");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = '\0';  // Remove the trailing newline
    // Combine names and print the full name
    char* full_name = combineNames(first_name, last_name);
    printf("Full name: %s\n", full_name);
    new_costumer->costumerName = malloc(strlen(full_name) + 1);
    strcpy(new_costumer->costumerName, full_name);
    // Free the allocated memory for full name
    free(full_name);
    return new_costumer;
}

Costumer setCostumer(Costumer customer, const char id[maxSizeId], char *customer_name, ShoppingCart *cart)
{
    strcpy(*customer.costumerName, customer_name);
    strcpy(*customer.id, id);
    strcpy(customer.cart, cart);
    free(id);
    free(customer_name);
    return customer;
}

Costumer* getCostumerById(Costumer* customers, int numOfCustomers, const char* id)
{
	for (int i = 0; i < numOfCustomers; i++) {
		if (strcmp(customers[i].id, id) == 0) {
			return &customers[i]; // Return a pointer to the matching costumer
		}
	}
    Costumer* new_customer = malloc(sizeof(Costumer));
    new_customer = initCostumer(new_customer);
	return new_customer;
}

void capitalizeWords(char* str) {
    int len = strlen(str);
    int in_word = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            if (!in_word) {
                // Capitalize the first letter of the word
                str[i] = toupper(str[i]);
                in_word = 1;
            }
        }
        else {
            in_word = 0;  // Reset when a non-alphabetic character is encountered
        }
    }
}

// Function to combine the two strings with the desired format
char* combineNames(char* firstName, char* lastName) {
    // Capitalize both names
    capitalizeWords(firstName);
    capitalizeWords(lastName);

    // Calculate the length required for the result string
    int resultLength = strlen(firstName) + strlen(lastName) + strlen(" - ") + 1; // 5 is for " - " and the null terminator

    // Dynamically allocate memory for the result string
    char* result = (char*)malloc(resultLength);
    if (result == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Format the result string with " - " in between
    sprintf_s(result, resultLength, "%s - %s", firstName, lastName);

    return result;
}