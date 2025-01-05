#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Date.h"
#include "Product.h"
#include "constants.h"

char** arrayShelf = NULL;



void newProduct(Product *product) //todo : add DATE
{
	char productType[3];
	
	printf("Enter product name: ");
	fgets(product->name, sizeof(product->name), stdin);
	product->name[strcspn(product->name, "\n")] = '\0';

	printf("Enter product type: ");
	fgets(productType, sizeof(productType), stdin);
	toUpperCase(productType);
	newBarcode(product, productType);

	printf("Enter product price: ");
	scanf_s("%f", &product->price);

	printf("Enter product quantity: ");
	scanf_s("%d", &product->quantity);

	printf("Enter a date in format DDMMYYYY: "); //todo : when entering number that starts with 0 its not working.
	int input;
	scanf_s("%d", &input);
	printf("Input value: %d\n", input);
	newDate(&product->date, input);
	
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

void newBarcode(Product *product,char* type)
{
	if (validateType(type))
	{
		// Generate a random 5-digit number
		int num = rand() % 90000 + 10000;  // Ensures the number is between 10000 and 99999

		// Convert the number to a string
		char numStr[6];  // 5 digits + 1 for the null terminator
		snprintf(numStr, sizeof(numStr), "%d", num);

		// Append the number to the original string
		char* newBarcode = (char*)malloc(maxSizeBarCode);
		snprintf(product->barcode, sizeof(product->barcode), "%s%s",type, numStr);
	}
}
void toUpperCase(char* input) {
	while (*input) {
		*input = toupper((unsigned char)*input);  // Convert to uppercase
		input++;
	}
}




