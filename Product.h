#ifndef PRODUCT_H
#define PRODUCT_H
#include "constants.h"
#include "Date.h"

// Product structure
typedef struct {
    char name[maxSizeProductName];
    char productType[maxSizeBarCode];
    float price;
    int quantity;
    Date date;
} Product;

void newProduct(Product* product);


//functions declerations

//struct


#endif // PRODUCT_H
