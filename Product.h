#ifndef PRODUCT_H
#define PRODUCT_H
#include "constants.h"
#include "Date.h"

// Product structure
typedef struct {
    char name[maxSizeProductName];
    char barcode[maxSizeBarCode];
    float price;
    int quantity;
    Date date;
} Product;

void newProduct(Product* product);
void newBarcode(char* type);
int validateType(char* input);
void toUpperCase(char* input);


//functions declerations

//struct


#endif // PRODUCT_H
