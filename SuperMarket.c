#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SuperMarket.h"

void initSuperMarket(SuperMarket* market) {
    market->shopName = NULL;
    market->customers = NULL;
    market->products = NULL;
    market->totalCustomers = 0;
    market->totalProducts = 0;
}

void printSuperMarketData(SuperMarket* market) {
    printf("Shop Name: %s\n", market->shopName);
    printf("Total Customers: %d\n", market->totalCustomers);
    printf("Total Products: %d\n", market->totalProducts);
    for (int i = 0; i < market->totalCustomers; i++) {
        printf("Customer %d: ID=%s, Name=%s\n", i + 1, market->customers[i].id, market->customers[i].costumerName);
    }
    for (int i = 0; i < market->totalProducts; i++) {
        printf("Product %d: Name=%s, Barcode=%s, Price=%.2f, Quantity=%d\n",
            i + 1, market->products[i].name, market->products[i].barcode, market->products[i].price, market->products[i].quantity);
    }
}

void addProductToSuperMarket(SuperMarket* market, const char* barcode) {
    if (!barcode) {
        char localBarcode[maxSizeBarCode];
        printf("Enter product barcode: ");
        scanf("%s", localBarcode);
        barcode = localBarcode;
    }

    Product* product = getProductByBarCode(market->products, market->totalProducts, barcode);
    if (product) {
        printf("Product found. Enter quantity to add: ");
        int quantity;
        scanf("%d", &quantity);
        product->quantity += quantity;
    }
    else {
        printf("Product not found. Adding new product.\n");
        market->products = realloc(market->products, (market->totalProducts + 1) * sizeof(Product));
        if (!market->products) {
            perror("Failed to allocate memory for products");
            return;
        }
        Product* newProductPtr = &market->products[market->totalProducts];
        newProduct(newProductPtr); // Call the function correctly
        market->totalProducts++;
    }
}

void addCostumerToSuperMarket(SuperMarket* market)
{
    printf("Enter costumer ID : \n");
    char id[maxSizeId];
    fgets(id, maxSizeId, stdin);  // Corrected size
    getchar();
    Costumer* new_customer = getCostumerById(market->customers, market->totalCustomers, id);
    if (!checkCostumerExists(market->customers, *new_customer, market->totalCustomers))
    {
        market->customers = increaseCustomersArraySize(market->customers, &market->totalCustomers);
        new_customer = newCostumer(id);
        strncpy(market->customers[market->totalCustomers - 1].id, new_customer->id, maxSizeId - 1);
        market->customers[market->totalCustomers - 1].id[maxSizeId - 1] = '\0';
        market->customers[market->totalCustomers - 1].costumerName = malloc(strlen(new_customer->costumerName) + 1);
        strcpy(market->customers[market->totalCustomers - 1].costumerName, new_customer->costumerName);
        new_customer->cart = malloc(sizeof(ShoppingCart));
        initializeCart(new_customer->cart);
        new_customer->cart->items = malloc(new_customer->cart->items_quantity * sizeof(ShoppingItem));
        market->customers[market->totalCustomers - 1].cart = new_customer->cart;
    }
    else printf("Customer already exists");
}

void printCustomerCart(SuperMarket* market) {
    printf("Enter costumer ID : \n");
    char id[maxSizeId];
    fgets(id, maxSizeId, stdin);  // Corrected size
    getchar();
    Costumer* new_customer = getCostumerById(market->customers, market->totalCustomers, id);
    if (checkCostumerExists(market->customers, *new_customer, market->totalCustomers))
    {
        // Print the customer's cart
        printf("Cart for customer %s:\n", new_customer->costumerName);
        printCart(new_customer->cart);
    }
}

void startPurchase(SuperMarket* market) {
    char barcode[maxSizeBarCode];
    int continueShopping = 1;
    printf("Enter costumer ID : \n");
    char id[maxSizeId];
    fgets(id, maxSizeId, stdin);  // Corrected size
    getchar();
    Costumer* new_customer = getCostumerById(market->customers, market->totalCustomers, id);
    if (checkCostumerExists(market->customers, *new_customer, market->totalCustomers))
    {
        while (continueShopping) {
            // Display all products
            printf("Available products:\n");
            for (int i = 0; i < market->totalProducts; i++) {
                Product* product = &market->products[i];
                printf("%s | %s | Price: %.2f | Stock: %d\n",
                    product->barcode, product->name, product->price, product->quantity);
            }
            
            // Prompt for the barcode
            printf("Enter the barcode of the product to add to the cart: ");
            if (!fgets(barcode, sizeof(barcode), stdin)) {
                printf("Error reading input. Please try again.\n");
                continue;
            }

            // Remove trailing newline from fgets
            barcode[strcspn(barcode, "\n")] = '\0';
            // Validate the product
            toUpperCase(barcode);
            Product* product = getProductByBarCode(market->products, market->totalProducts, barcode);
            if (product && product->quantity > 0) {
                int quantity;
                printf("Enter quantity to purchase (available: %d): ", product->quantity);
                if (scanf("%d", &quantity) != 1 || quantity <= 0 || quantity > product->quantity) {
                    printf("Invalid quantity.\n");
                    while (getchar() != '\n'); // Clear the buffer
                    continue;
                }
                while (getchar() != '\n'); // Clear the buffer after scanf

                addItemToCart(market, new_customer->cart, product->barcode, quantity);
                product->quantity -= quantity;
                printf("Added %d of %s to the cart.\n", quantity, product->name);
            }
            else {
                printf("Product not found or out of stock.\n");
            }

            // Ask if the customer wants to continue
            printf("Continue shopping? (1 for Yes, 0 for No): ");
            if (scanf("%d", &continueShopping) != 1) {
                continueShopping = 0; // Default to stop shopping on invalid input
            }
            while (getchar() != '\n'); // Clear the buffer after scanf
        }
    }
    else printf("No Customer found\n");
}

int checkCostumerExists(Costumer* customers, Costumer customer_to_check, int numOfCustomers)
{
    for (int i = 0; i < numOfCustomers; i++)
    {
        if (strcmp(customers[i].id, customer_to_check.id) == 0) return 1;
    }
    return 0;
}

Product* increaseProductsArraySize(Product* products, int* totalProducts) {
    products = realloc(products, (*totalProducts + 1) * sizeof(Product));
    if (!products) {
        perror("Memory allocation failed");
        return NULL;
    }
    (*totalProducts)++;
    return products;
}

Costumer* increaseCustomersArraySize(Costumer* customers, int* totalCustomers) {
    customers = realloc(customers, (*totalCustomers + 1) * sizeof(Costumer));
    if (!customers) {
        perror("Memory allocation failed");
        return NULL;
    }
    (*totalCustomers)++;
    return customers;
}

void manageCart(SuperMarket* market) {
    char barcode[maxSizeBarCode];
    printf("Enter costumer ID : \n");
    char id[maxSizeId];
    fgets(id, maxSizeId, stdin);  // Corrected size
    getchar();
    Costumer* new_customer = getCostumerById(market->customers, market->totalCustomers, id);
    if (checkCostumerExists(market->customers, *new_customer, market->totalCustomers))
    {
        if (new_customer->cart->items_quantity != 0)
        {
            printCart(new_customer->cart);
            printf("1. Checkout\n2. Cancel Purchase\nChoose an option: ");
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Processing payment...\n");
                float total = 0;
                for (int i = 0; i < new_customer->cart->items_quantity; i++) {
                    total += new_customer->cart->items[i].price * new_customer->cart->items[i].quantity;
                }
                printf("Payment of %.2f successful.\n", total);
                free(new_customer->cart->items);
                new_customer->cart->items = NULL;
                new_customer->cart->items_quantity = 0;
            }
            else if (choice == 2) {
                printf("Cancelling purchase and restoring stock...\n");
                for (int i = 0; i < new_customer->cart->items_quantity; i++) {
                    ShoppingItem* item = &new_customer->cart->items[i];
                    Product* product = getProductByBarCode(market->products, market->totalProducts, item->barcode);
                    if (product) {
                        product->quantity += item->quantity;
                    }
                }
                free(new_customer->cart->items);
                new_customer->cart->items = NULL;
                new_customer->cart->items_quantity = 0;
            }
        }
    }
}

void addItemToCart(SuperMarket* market, ShoppingCart* cart, const char barcode[maxSizeBarCode], int quantity) {
    Product* product = getProductByBarCode(market->products, market->totalProducts, barcode);
    if (!product) {
        printf("Product not found.\n");
        return;
    }

    // Check if the item is already in the cart
    for (int i = 0; i < cart->items_quantity; i++) {
        if (strcmp(cart->items[i].barcode, barcode) == 0) {
            cart->items[i].quantity += quantity;
            printf("Updated quantity of %s in the cart.\n", product->name);
            return;
        }
    }

    // Add a new item to the cart
    cart->items = realloc(cart->items, (cart->items_quantity + 1) * sizeof(ShoppingItem));
    strcpy(cart->items[cart->items_quantity].barcode, barcode);
    cart->items[cart->items_quantity].price = product->price;
    cart->items[cart->items_quantity].quantity = quantity;
    cart->items_quantity++;
    printf("Added %s to the cart.\n", product->name);
}

void printProductsByCategory(SuperMarket* market) {
    char category[3];

    // Prompt the user for the category
    printf("Enter a category (SH, FZ, FR, FV): ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0'; // Remove trailing newline
    toUpperCase(category);
    // Validate the category
    if (strcmp(category, shelf) != 0 && strcmp(category, frozen) != 0 &&
        strcmp(category, fridge) != 0 && strcmp(category, fruitVegtable) != 0) {
        printf("Invalid category. Please enter one of the following: SH, FZ, FR, FV.\n");
        return;
    }

    // Display the products in the specified category
    int found = 0;
    printf("Products in category %s:\n", category);
    printf("-------------------------------------------\n");
    printf("| %-10s | %-20s | %-8s | %-8s |\n", "Barcode", "Name", "Price", "Stock");
    printf("-------------------------------------------\n");

    for (int i = 0; i < market->totalProducts; i++) {
        Product* product = &market->products[i];
        if (strncmp(product->barcode, category, strlen(category)) == 0) {
            printf("| %-10s | %-20s | %-8.2f | %-8d |\n",
                product->barcode, product->name, product->price, product->quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found in this category.\n");
    }

    printf("-------------------------------------------\n");
}

void exitProgram(SuperMarket* market) {
    for (int i = 0; i < market->totalCustomers; i++) {
        free(market->customers[i].costumerName);
        free(market->customers[i].cart->items);
        free(market->customers[i].cart);
    }
    free(market->customers);
    free(market->products);
    free(market->shopName);
    printf("Exiting program. Goodbye!\n");
    exit(0);
}
