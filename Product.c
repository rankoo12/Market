#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Product.h"



void newProduct(Product *product) //todo : add DATE
{
	printf("Enter product name: ");
	fgets(product->name, sizeof(product->name), stdin);
	product->name[strcspn(product->name, "\n")] = '\0';

	printf("Enter product type: ");
	fgets(product->productType, sizeof(product->productType), stdin);
	product->productType[strcspn(product->productType, "\n")] = '\0'; // todo : add 4 random numbers (also check if already exist)

	printf("Enter product price: ");
	scanf_s("%f", &product->price);

	printf("Enter product quantity: ");
	scanf_s("%d", &product->quantity);

	printf("Enter a date in format DDMMYYYY: ");
	int input;
	scanf_s("%d", &input);
	printf("Input value: %d\n", input);
	newDate(&product->date, input);
	
	getchar();


}



