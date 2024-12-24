#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"

// Product structure
typedef struct {
	char name[maxSizeProductName];
	char productType[maxSizeBarCode];
	float price;
	int quantity;
} Product;

void newProduct(Product *product) //todo : add DATE
{
	printf("Enter product name: ");
	fgets(product->name, sizeof(product->name), stdin);
	product->name[strcspn(product->name, "\n")] = '\0';

	printf("Enter product type: ");
	fgets(product->productType, sizeof(product->productType), stdin);
	product->productType[strcspn(product->productType, "\n")] = '\0'; // todo : add 4 random numbers (also check if already exist)

	printf("Enter product price: ");
	scanf("%f", &product->price);

	printf("Enter product quantity: ");
	scanf("%d", &product->quantity);
	getchar();


}

