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

#endif // SUPERMARKET_H
