#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "Costumer.h"
#include "Product.h"

// Structure to represent the supermarket
typedef struct {
    char* name;            // Dynamically allocated name of the supermarket
    Costumer* customers;   // Dynamic array of registered customers
    int numCustomers;      // Number of registered customers
    Product** products;    // Dynamic array of product pointers
    int numProducts;       // Number of products
} SuperMarket;

// Function prototypes
void initSuperMarket(SuperMarket* market, const char* name); // Initialize the supermarket
void addCustomer(SuperMarket* market, const Costumer* customer); // Add a new customer to the supermarket
void addProduct(SuperMarket* market, const Product* product); // Add a new product to the supermarket
void freeSuperMarket(SuperMarket* market); // Free memory allocated for supermarket (customers, products)
void startShopping(SuperMarket* market, const char* customerId);
void printAllProducts(SuperMarket* market);
// In SuperMarket.h

// Function to find a product by its barcode in the supermarket
Product* findProductByBarcode(SuperMarket* market, const char* barcode);


#endif // SUPERMARKET_H
