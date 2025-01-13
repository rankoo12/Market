#ifndef PRODUCT_H
#define PRODUCT_H
#include "constants.h"
#include "Date.h"

typedef struct {
    char name[maxSizeProductName];
    char barcode[maxSizeBarCode];
    float price;
    int quantity;
    Date date;
} Product;

void initializeProduct(Product* product);
void newProduct(Product* product);
int validateType(char* input);
void newBarcode(Product* product, char* type);
void toUpperCase(char* input);
Product* getProductByBarCode(Product* products, int numOfProducts, const char* barcode);
int validateProduct(Product* product);

#endif // PRODUCT_H