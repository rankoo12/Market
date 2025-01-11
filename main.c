#include <stdio.h>
#include <stdlib.h>
#include "SuperMarket.h"
#include "Product.h"
#include "Costumer.h"
#include "newCart.h"
void printMenu() {
    printf("\nSuperMarket Menu:\n");
    printf("1. Print supermarket data\n");
    printf("2. Add a product\n");
    printf("3. Add a customer\n");
    printf("4. Start shopping for a customer\n");
    printf("5. Print shopping cart\n");
    printf("6. Manage shopping cart (Pay or Cancel)\n");
    printf("7. Print all products of a specific type\n");
    printf("8. Exit\n");
}

int main() {
    SuperMarket market;
    initSuperMarket(&market, "My SuperMarket");

    int choice;
    int productTypeChoice;

    while (1) {
        printMenu();
        printf("Choose an option: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // Print supermarket data
            getchar();
            printf("SuperMarket Name: %s\n", market.name);
            printf("Number of customers: %d\n", market.numCustomers);
            printf("Number of products: %d\n", market.numProducts);
            break;

        case 2: {
            // Add a product
            getchar();
            Product newProductItem;  // Renamed the local variable
            newProduct(&newProductItem);  // Now the function call is correct
            addProduct(&market, &newProductItem);
            break;
        }

        case 3: {
            // Add a customer
            getchar();
            Costumer newCustomer;
            newCostumer(&newCustomer);  // Assuming `newCostumer` prompts the user for customer details
            addCustomer(&market, &newCustomer);
            break;
        }

        case 4: {
            // Start shopping for a customer
            getchar();  // Clear any leftover input

            char customerId[maxSizeID];
            printf("Enter customer ID: ");
            scanf_s("%s", customerId, maxSizeID);

            // Find the customer by their ID using findCustomerById
            Costumer* customer = findCustomerById(&market, customerId);
            if (customer == NULL) {
                printf("Customer with ID %s not found.\n", customerId);
                break;  // Exit the case if the customer isn't found
            }

            // Initialize the cart for the customer
            initializeCart(&customer->cart);  // Create a new cart for the customer
            printf("Started shopping for customer %s.\n", customer->name);

            // Now add products to the cart for the customer
            // We'll enter this part immediately below.
            // Proceed with adding items to the cart.

            char productName[maxSizeProductName];
            int quantity;

            printf("Enter product name to add to cart: ");
            scanf_s("%s", productName, maxSizeProductName);

            // Find the product in the market
            Product* product = findProductByName(&market, productName);
            if (product == NULL) {
                printf("Product not found in the supermarket.\n");
                break;  // If product not found, exit
            }

            printf("Enter quantity: ");
            scanf_s("%d", &quantity);

            // Create a new shopping item and add it to the cart
            ShoppingItem newItem;
            newItem.product = *product;  // Copy the product details into the shopping item
            newItem.quantity = quantity;

            // Add the item to the cart
            addItemToCart(&customer->cart, &newItem);
            printf("Added '%s' to cart with quantity %d.\n", product->name, quantity);

            break;
        }

        case 5: {
            // Print shopping cart
            getchar();
            char customerId[maxSizeID];
            printf("Enter customer ID: ");
            scanf_s("%s", customerId, maxSizeID);
            // Assume the printCart function is available to print the shopping cart of a customer
            // printCart(&market, customerId);
            break;
        }

        case 6: {
            // Manage shopping cart (Pay or Cancel)
            getchar();
            char customerId[maxSizeID];
            printf("Enter customer ID: ");
            scanf_s("%s", customerId, maxSizeID);
            // Assume the manageCart function allows the customer to pay or cancel
            // manageCart(&market, customerId);
            break;
        }

        case 7: {
            // Print all products of a specific type
            getchar();
            printf("Enter product type (shelf, frozen, fridge, etc.): ");
            char productType[20];
            scanf_s("%s", productType, 20);
            // Print products of the specified type
            // printProductsByType(&market, productType);
            break;
        }

        case 8:
            // Exit program
            printf("Exiting program...\n");
            getchar();
            freeSuperMarket(&market);  // Free allocated memory
            return 0;

        default:
            getchar();
            printf("Invalid choice. Please try again.\n");
        }
    }
}
