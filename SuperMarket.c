#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SuperMarket.h"
#include "Costumer.h"
#include "Product.h"

void initSuperMarket(SuperMarket* market, const char* name) {
    // Dynamically allocate memory for the supermarket name and remove newline character
    market->name = malloc((strlen(name) + 1) * sizeof(char));
    if (market->name == NULL) {
        perror("Failed to allocate memory for supermarket name");
        exit(EXIT_FAILURE);
    }

    // Copy the name of the supermarket, use strcspn to remove newline if present
    snprintf(market->name, strlen(name) + 1, "%s", name);

    market->customers = NULL;  // Initially, no customers
    market->numCustomers = 0;
    market->products = NULL;   // Initially, no products
    market->numProducts = 0;
}

void addCustomer(SuperMarket* market, const Costumer* customer) {
    // Resize the array of customers if necessary
    market->customers = realloc(market->customers, (market->numCustomers + 1) * sizeof(Costumer));
    if (market->customers == NULL) {
        perror("Failed to reallocate memory for customers");
        exit(EXIT_FAILURE);
    }

    // Add the new customer
    market->customers[market->numCustomers] = *customer;
    market->numCustomers++;
}

void addProduct(SuperMarket* market, const Product* product) {
    // Resize the array of products if necessary
    market->products = realloc(market->products, (market->numProducts + 1) * sizeof(Product*));
    if (market->products == NULL) {
        perror("Failed to reallocate memory for products");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the new product and copy the details
    market->products[market->numProducts] = malloc(sizeof(Product));
    if (market->products[market->numProducts] == NULL) {
        perror("Failed to allocate memory for new product");
        exit(EXIT_FAILURE);
    }

    // Copy product details
    *market->products[market->numProducts] = *product;
    market->numProducts++;
}

void freeSuperMarket(SuperMarket* market) {
    // Free customers and products
    for (int i = 0; i < market->numCustomers; i++) {
        free(market->customers[i].name);  // Free dynamically allocated customer name
        freeCart(&market->customers[i].cart);  // Free shopping cart for each customer
    }
    free(market->customers);

    for (int i = 0; i < market->numProducts; i++) {
        free(market->products[i]);  // Free each dynamically allocated product
    }
    free(market->products);

    // Free supermarket name
    free(market->name);
}

Costumer* findCustomerById(SuperMarket* market, const char* customerId) {
    for (int i = 0; i < market->numCustomers; i++) {
        if (strcmp(market->customers[i].id, customerId) == 0) {
            return &market->customers[i];  // Return the customer if found
        }
    }
    return NULL;  // Return NULL if customer not found
}

Product* findProductByName(SuperMarket* market, const char* productName) {
    for (int i = 0; i < market->numProducts; i++) {
        if (strcmp(market->products[i]->name, productName) == 0) {
            return market->products[i];  // Return the product if found
        }
    }
    return NULL;  // Return NULL if product is not found
}