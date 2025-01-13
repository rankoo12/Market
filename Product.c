#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Product.h"

void initializeProduct(Product* product) {
    if (!product) return;
    memset(product->name, 0, sizeof(product->name));
    memset(product->barcode, 0, sizeof(product->barcode));
    product->price = 0.0f;
    product->quantity = 0;
    product->date = (Date){ 0, 0, 0 };
}

void newProduct(Product* product) {
    getchar();
    if (!product) return;
    printf("Enter product name: ");
    fgets(product->name, sizeof(product->name), stdin);
    product->name[strcspn(product->name, "\n")] = '\0';

    char productType[3];
    printf("Enter product type: ");
    fgets(productType, sizeof(productType), stdin);
    productType[strcspn(productType, "\n")] = '\0';
    toUpperCase(productType);

    if (!validateType(productType)) {
        printf("Invalid product type.");
        return;
    }

    newBarcode(product, productType);

    printf("Enter product price: ");
    scanf("%f", &product->price);

    printf("Enter product quantity: ");
    scanf("%d", &product->quantity);

    printf("Enter a date in format DDMMYYYY: ");
    int input;
    scanf("%d", &input);
    newDate(&product->date, input);
    while (getchar() != '\n'); // Clear buffer
}

int validateType(char* input) {
    return strcmp(input, shelf) == 0 || strcmp(input, frozen) == 0 ||
        strcmp(input, fridge) == 0 || strcmp(input, fruitVegtable) == 0;
}

void newBarcode(Product* product, char* type) {
    int num = rand() % 90000 + 10000;
    snprintf(product->barcode, sizeof(product->barcode), "%s%05d", type, num);
}

void toUpperCase(char* input) {
    while (*input) {
        *input = toupper((unsigned char)*input);
        input++;
    }
}

Product* getProductByBarCode(Product* products, int numOfProducts, const char* barcode) {
    for (int i = 0; i < numOfProducts; i++) {
        if (strcmp(products[i].barcode, barcode) == 0) {
            return &products[i];
        }
    }
    return NULL;
}

int validateProduct(Product* product) {
    return product && product->price >= 0 && product->quantity >= 0;
}