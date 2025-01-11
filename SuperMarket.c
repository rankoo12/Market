#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SuperMarket.h"
#include "Product.h"
#include "Costumer.h"

// Function 1: Initialize the SuperMarket
void initSuperMarket(SuperMarket* market, const char* name) {
    market->name = malloc(strlen(name) + 1);  // Allocating memory for supermarket name
    if (!market->name) {
        printf("Memory allocation failed for supermarket name.\n");
        exit(1);
    }
    snprintf(market->name, strlen(name) + 1, "%s", name);  // Use snprintf instead of strcpy

    market->customers = NULL;
    market->numCustomers = 0;
    market->products = NULL;
    market->numProducts = 0;
}

// Function 2: Print SuperMarket Details
void printSuperMarketDetails(const SuperMarket* market) {
    printf("Supermarket Name: %s\n", market->name);
    printf("Number of Customers: %d\n", market->numCustomers);
    printf("Number of Products: %d\n", market->numProducts);
}

// Function 3: Add Product to SuperMarket
void addProduct(SuperMarket* market, const Product* product) {
    // Check if the product already exists
    for (int i = 0; i < market->numProducts; i++) {
        if (strcmp(market->products[i]->barcode, product->barcode) == 0) {
            // Update quantity if product exists
            market->products[i]->quantity += product->quantity;
            printf("Updated quantity of '%s' to %d.\n", product->name, market->products[i]->quantity);
            return;
        }
    }

    // Add new product if it doesn't exist
    market->products = realloc(market->products, (market->numProducts + 1) * sizeof(Product*));
    if (!market->products) {
        printf("Memory allocation failed for product.\n");
        exit(1);
    }

    market->products[market->numProducts] = malloc(sizeof(Product));
    if (!market->products[market->numProducts]) {
        printf("Memory allocation failed for new product.\n");
        exit(1);
    }
    *market->products[market->numProducts] = *product;  // Copy the product data
    market->numProducts++;
    printf("Added new product '%s' to the supermarket.\n", product->name);
}

// Function 4: Add Customer to SuperMarket
void addCustomer(SuperMarket* market, const Costumer* customer) {
    // Check if the customer already exists
    for (int i = 0; i < market->numCustomers; i++) {
        if (strcmp(market->customers[i].id, customer->id) == 0) {
            printf("Customer with ID %s already exists.\n", customer->id);
            return;
        }
    }

    // Add new customer if ID is unique
    market->customers = realloc(market->customers, (market->numCustomers + 1) * sizeof(Costumer));
    if (!market->customers) {
        printf("Memory allocation failed for customers.\n");
        exit(1);
    }

    market->customers[market->numCustomers] = *customer;  // Copy customer data
    market->numCustomers++;
    printf("Added new customer '%s' with ID %s.\n", customer->name, customer->id);
}

// Function 5: Start Shopping for a Customer
void startShopping(SuperMarket* market, const char* customerId) {
    printAllProducts(market);
    // Find the customer by their ID
    Costumer* customer = NULL;
    for (int i = 0; i < market->numCustomers; i++) {
        if (strcmp(market->customers[i].id, customerId) == 0) {
            customer = &market->customers[i];
            break;
        }
    }
    if (!customer) {
        printf("Customer not found.\n");
        return;
    }

    // Initialize a shopping cart for the customer
    ShoppingCart cart;
    initializeCart(&cart);

    // For simplicity, we'll add a sample product to the cart
    printf("Enter Product Barcode : .\n");
    char barcode[maxSizeBarCode];
    scanf_s("%s", barcode, maxSizeBarCode);
    Product* product = findProductByBarcode(market, &barcode);  // Example barcode
    if (product) {
        ShoppingItem item = { *product, 2 };  // Example: Adding 2 items of the product
        addItemToCart(&cart, &item);  // Add product to the cart
    }

    // Print the customer's cart
    printCart(market, cart);

    // Don't forget to free the cart after use
    freeCart(&cart);
}

// Function 6: Print Products by Type
void printProductsByType(const SuperMarket* market, const char* productType) {
    printf("Products of type '%s':\n", productType);
    for (int i = 0; i < market->numProducts; i++) {
        if (strcmp(market->products[i]->barcode, productType) == 0) {  // Assuming barcode represents type
            printf("Product: %s, Price: %.2f, Quantity: %d\n",
                market->products[i]->name, market->products[i]->price, market->products[i]->quantity);
        }
    }
}

// Function to find a product by its barcode in the supermarket
Product* findProductByBarcode(SuperMarket* market, const char* barcode) {
    // Loop through the products and compare their barcode
    for (int i = 0; i < market->numProducts; i++) {
        if (strcmp(market->products[i]->barcode, barcode) == 0) {
            return market->products[i];  // Return the pointer to the product if found
        }
    }
    return NULL;  // Return NULL if the product is not found
}

void printAllProducts(SuperMarket* market) {
    if (market == NULL || market->products == NULL || market->numProducts == 0) {
        printf("No products available in the supermarket.\n");
        return;
    }

    printf("List of all products in the supermarket:\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < market->numProducts; i++) {
        Product* product = market->products[i];

        // Printing product details
        printf("Product Name: %s\n", product->name);
        printf("Barcode: %s\n", product->barcode);
        printf("Price: %.2f\n", product->price);
        printf("Quantity: %d\n", product->quantity);
        printf("Expiration Date: %02d/%02d/%04d\n",
            product->date.day, product->date.month, product->date.year);
        printf("-------------------------------------------------\n");
    }
}

void printCart(SuperMarket* market, const char* customerId) {
    if (market == NULL || market->customers == NULL || market->numCustomers == 0) {
        printf("No customers available in the supermarket.\n");
        return;
    }

    // Find the customer by ID
    Costumer* customer = NULL;
    for (int i = 0; i < market->numCustomers; i++) {
        if (strcmp(market->customers[i].id, customerId) == 0) {
            customer = &market->customers[i];
            break;
        }
    }

    if (customer == NULL) {
        printf("Customer with ID '%s' not found.\n", customerId);
        return;
    }

    // Check if the customer has a cart
    if (customer->cart.size == 0) {
        printf("The shopping cart for customer ID '%s' is empty.\n", customerId);
        return;
    }

    // Print the cart items
    printf("Shopping Cart for Customer ID: %s\n", customerId);
    printf("-------------------------------------------------\n");

    for (int i = 0; i < customer->cart.size; i++) {
        const ShoppingItem* item = &customer->cart.items[i];
        printf("Product: %s\n", item->product.name);
        printf("Barcode: %s\n", item->product.barcode);
        printf("Price: $%.2f\n", item->product.price);
        printf("Quantity: %d\n", item->quantity);
        printf("Expiration Date: %02d/%02d/%04d\n",
            item->product.date.day, item->product.date.month, item->product.date.year);
        printf("-------------------------------------------------\n");
    }
}
