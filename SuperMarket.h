#ifndef SUPERMARKET_H
#define SUPERMARKET_H
#include "Costumer.h"
#include "Product.h"
#include "newCart.h"

typedef struct {
    char* shopName;
    Costumer* customers;
    Product* products;
    int totalCustomers;
    int totalProducts;
} SuperMarket;

void initSuperMarket(SuperMarket* market);
void printSuperMarketData(SuperMarket* market);
void addProductToSuperMarket(SuperMarket* market, const char* barcode);
void addCostumerToSuperMarket(SuperMarket* market);
void addItemToCart(SuperMarket* market, ShoppingCart* cart, const char barcode[maxSizeBarCode], int quantity);
void startPurchase(SuperMarket* market);
void manageCart(SuperMarket* market);
void printProductsByCategory(SuperMarket* market);
void exitProgram(SuperMarket* market);
void printCustomerCart(SuperMarket* market);
Costumer* increaseCustomersArraySize(Costumer* customers, int* totalCustomers);

#endif // SUPERMARKET_H