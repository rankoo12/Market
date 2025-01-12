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
int validateType(char* input);
void newBarcode(Product* product, char* type);
void toUpperCase(char* input);
Product* getProductByBarCode(Product* products, int numOfProducts, const char* barcode);
int validateProduct(Product* product);
void initializeProduct(Product* product);

//functions declerations

//struct


#endif // PRODUCT_H
