#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Costumer.h"



void newCostumer(Costumer* costumer) {
    char buffer[256]; // Temporary buffer for user input

    // Get customer ID from user
    printf("Enter customer ID: ");
    fgets(costumer->id, sizeof(costumer->id), stdin);
    // Remove trailing newline character from ID if present
    size_t len = strlen(costumer->id);
    if (len > 0 && costumer->id[len - 1] == '\n') {
        costumer->id[len - 1] = '\0';
    }
    getchar();
    // Get first name from user
    printf("Enter first name: ");
    fgets(buffer, sizeof(buffer), stdin);
    // Remove trailing newline character if present
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Dynamically allocate memory for firstName using snprintf
    len = strlen(buffer);
    char* firstName = malloc((len + 1) * sizeof(char)); // +1 for null terminator
    if (!firstName) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    snprintf(firstName, len + 1, "%s", buffer);

    // Get last name from user
    printf("Enter last name: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Remove trailing newline character if present
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Dynamically allocate memory for lastName using snprintf
    len = strlen(buffer);
    char* lastName = malloc((len + 1) * sizeof(char)); // +1 for null terminator
    if (!lastName) {
        printf("Memory allocation failed\n");
        free(firstName);
        exit(1);
    }
    snprintf(lastName, len + 1, "%s", buffer);

    // Allocate memory for costumer->name and concatenate firstName and lastName
    size_t totalLength = strlen(firstName) + strlen(lastName) + 2; // +2 for space and null terminator
    costumer->name = malloc(totalLength * sizeof(char));
    if (!costumer->name) {
        printf("Memory allocation failed\n");
        free(firstName);
        free(lastName);
        exit(1);
    }

    // Concatenate firstName and lastName into costumer->name using snprintf
    snprintf(costumer->name, totalLength, "%s %s", firstName, lastName);

    // Print the full name and ID
    printf("Customer ID: '%s'\n", costumer->id);
    printf("Name: '%s'\n", costumer->name);

    // Free temporary dynamic allocations
    free(firstName);
    free(lastName);
}

