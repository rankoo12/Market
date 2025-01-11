#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Date.h"
#include "Product.h"
#include "constants.h"

// Global array for product shelf (if needed)
char** arrayShelf = NULL;

void newProduct(Product* product) // todo: add DATE
{
    char productType[3];

    printf("Enter product name: \n");
    fgets(product->name, sizeof(product->name), stdin);
    // Remove the newline character from the product name
    product->name[strcspn(product->name, "\n")] = '\0';

    printf("Enter product type: \n");
    fgets(productType, sizeof(productType), stdin);
    // Remove newline and convert product type to uppercase
    productType[strcspn(productType, "\n")] = '\0';
    toUpperCase(productType);

    // Create barcode based on the type of product
    newBarcode(product, productType);

    printf("Enter product price: \n");
    scanf_s("%f", &product->price);
    getchar(); // Consume the newline character after scanf_s

    printf("Enter product quantity: \n");
    scanf_s("%d", &product->quantity);
    getchar(); // Consume the newline character after scanf_s

    printf("Enter a date in format DDMMYYYY: \n");
    int input;
    scanf_s("%d", &input);
    printf("Input value: %d\n", input);
    newDate(&product->date, input);

    // Clear any leftover characters in the input buffer
    getchar();
}

int validateType(char* input)
{
    if (strcmp(input, shelf) == 0) {
        printf("Product is on the shelf.\n");
    }
    else if (strcmp(input, frozen) == 0) {
        printf("Product is frozen.\n");
    }
    else if (strcmp(input, fridge) == 0) {
        printf("Product is in the fridge.\n");
    }
    else if (strcmp(input, fruitVegtable) == 0) {
        printf("Product is a fruit or vegetable.\n");
    }
    else {
        printf("Unknown product type.\n");
        return 0;
    }
    return 1;
}

void newBarcode(Product* product, char* type)
{
    // Validate the product type and generate the barcode
    if (validateType(type))
    {
        // Generate a random 5-digit number for the barcode
        int num = rand() % 90000 + 10000;  // Ensures the number is between 10000 and 99999

        // Convert the number to a string
        char numStr[6];  // 5 digits + 1 for the null terminator
        snprintf(numStr, sizeof(numStr), "%d", num);

        // Create the full barcode string with the product type and number
        snprintf(product->barcode, sizeof(product->barcode), "%s%s", type, numStr);
    }
}

void toUpperCase(char* input) {
    while (*input) {
        *input = toupper((unsigned char)*input);  // Convert each character to uppercase
        input++;
    }
}
