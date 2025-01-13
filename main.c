#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Product.h"
#include "NewCart.h"
#include "SuperMarket.h"




// --- main.c ---
#include <stdio.h>
#include <stdlib.h>
#include "SuperMarket.h"

int main() {
    SuperMarket market;
    initSuperMarket(&market);

    int choice;
    do {
        printf("1. Print SuperMarket Data\n");
        printf("2. Add Product\n");
        printf("3. Add Customer\n");
        printf("4. Start Customer Purchase\n");
        printf("5. Print Customer Cart\n");
        printf("6. Manage Cart (Payment/Cancel)\n");
        printf("7. Print Products by Category\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            printSuperMarketData(&market); // Print supermarket data
            break;
        case 2:
            addProductToSuperMarket(&market, NULL); // Add product
            break;
        case 3:
            addCostumerToSuperMarket(&market); // Add customer
            break;
        case 4:
            startPurchase(&market); // Start purchase
            break;
        case 5:
            
            printCustomerCart(&market, NULL); // Print customer cart
            break;
        case 6:
            manageCart(&market); // Manage cart
            break;
        case 7:
            printProductsByCategory(&market); // Print products by category
            break;
        case 8:
            exitProgram(&market); // Exit program
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 8);

    return 0;
}