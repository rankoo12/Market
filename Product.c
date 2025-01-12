#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Date.h"
#include "Product.h"
#include "constants.h"

void initializeProduct(Product* product) {
	if (product != NULL) {
		// Initialize the product to default values
		product->name[0] = '\0';  // Set first character of name to null-terminator
		product->barcode[0] = '\0';  // Set first character of barcode to null-terminator
		product->price = 0.0f;
		product->quantity = 0;
		product->date.day = 0;
		product->date.month = 0;
		product->date.year = 0;
	}
}

void newProduct(Product* product) {
	char productType[3];

	// Initialize product with empty values (optional)
	//initializeProduct(product);

	printf("Enter product name: ");
	fgets(product->name, sizeof(product->name), stdin);
	product->name[strcspn(product->name, "\n")] = '\0';

	printf("Enter product type: ");
	fgets(productType, sizeof(productType), stdin);
	toUpperCase(productType);

	// Generate barcode based on product type
	newBarcode(product, productType);

	printf("Enter product price: ");
	scanf_s("%f", &product->price);

	printf("Enter product quantity: ");
	scanf_s("%d", &product->quantity);

	printf("Enter a date in format DDMMYYYY: ");
	int input;
	scanf_s("%d", &input);
	newDate(&product->date, input);
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
	printf("Product %s barcode : %s\n", product->name, product->barcode);
}
void toUpperCase(char* input) {
	while (*input) {
		*input = toupper((unsigned char)*input);  // Convert to uppercase
		input++;
	}
}

Product* getProductByBarCode(Product* products, int numOfProducts, const char* barcode)
{
	for (int i = 0; i < numOfProducts; i++) {
		if (strcmp(products[i].barcode, barcode) == 0) {
			return &products[i]; // Return a pointer to the matching product
		}
	}
	return NULL;
}


int validateProduct(Product* product)
{
	if (product->barcode != NULL && valiDate(&product->date) && product->name != NULL && product->price >= 0 && product->quantity >= 0) return 1;
	return 0;
}


