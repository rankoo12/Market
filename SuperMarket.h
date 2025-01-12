#ifndef SUPERMARKET_H
#define SUPERMARKET_H
#include "Costumer.h"
#include "Product.h"

typedef struct {
    char* shopName;
    Costumer* customers;
    Product* products;
    int totalCustomers;
    int totalProducts;
} SuperMarket;

void initSuperMarket(SuperMarket* market);
void printSuperMarketData(SuperMarket* market);
Costumer* increaseCustomersArraySize(Costumer* customers, int* totalCustomers);
Product* increaseProductsArraySize(Product* products, int* totalProducts);
void addProductToSuperMarket(SuperMarket* market, const char* barcode);
Product* getProductByBarCodeInMarket(SuperMarket* market, const char* barcode);
Product* removeProductFromMarket(SuperMarket* market, Product* product_to_remove);
void addCostumerToSuperMarket(SuperMarket* market);
void addItemToCart(SuperMarket* market, ShoppingCart* cart, const char barcode[maxSizeBarCode]);
#endif // SUPERMARKET_H

