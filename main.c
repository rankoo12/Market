#include <stdio.h>
#include <stdlib.h>
#include "SuperMarket.h"
#include "Product.h"
#include "Costumer.h"

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
            getchar();
            char customerId[maxSizeID];
            printf("Enter customer ID: ");
            scanf_s("%s", customerId, maxSizeID);
            startShopping(&market, customerId);
            // Assume the startShopping function handles the shopping process
            // startShopping(&market, customerId);
            break;
        }

        case 5: {
            // Print shopping cart
            getchar();
            char customerId[maxSizeID];
            printf("Enter customer ID: ");
            scanf_s("%s", customerId, maxSizeID);
            // Assume the printCart function is available to print the shopping cart of a customer
            printCart(&market, customerId);
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
            //freeSuperMarket(&market);  // Free allocated memory
            return 0;

        default:
            getchar();
            printf("Invalid choice. Please try again.\n");
        }
    }
}
