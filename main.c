#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Product.h"
#include "NewCart.h"
#include "SuperMarket.h"




int main() {
    SuperMarket* market = (SuperMarket*)malloc(sizeof(SuperMarket));
    initSuperMarket(market);
    int choice;

    while (1) {
        printf("\n1. Print SuperMarket Data\n");
        printf("2. Add Product\n");
        printf("3. Add Customer\n");
        printf("4. Start Customer Purchase\n");
        printf("5. Print Customer Cart\n");
        printf("6. Manage Cart (Payment/Cancel)\n");
        printf("7. Print Products by Category\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printSuperMarketData(market);
            break;
        case 2:
            getchar();
            printf("Please enter product barcode : \n");
            char barcode[maxSizeBarCode];
            fgets(barcode, 255, stdin);
            addProductToSuperMarket(market, barcode);
            break;
        case 3:
            addCostumerToSuperMarket(market);
            break;
        case 4:
            //startPurchase(market);
            break;
        /*case 5: {
            int customerId;
            printf("Enter Customer ID: ");
            scanf("%d", &customerId);
            Customer* customer = findCustomer(market, customerId);
            if (customer != NULL) {
                printCart(customer);
            }
            else {
                printf("Customer not found.\n");
            }
            break;
        }
        case 6: {
            int customerId;
            printf("Enter Customer ID: ");
            scanf("%d", &customerId);
            Customer* customer = findCustomer(market, customerId);
            if (customer != NULL) {
                manageCart(customer);
            }
            else {
                printf("Customer not found.\n");
            }
            break;
        }
        case 7:
            printProductsByCategory(market);
            break;
        case 8:
            // Ensure to complete any purchase and clear carts before exiting
            for (int i = 0; i < market->totalCustomers; i++) {
                if (market->customers[i].cartSize > 0) {
                    printf("Customer %s has ongoing purchase. Cancelling the purchase...\n", market->customers[i].name);
                    market->customers[i].cartSize = 0;  // Empty cart if any customer has an ongoing purchase
                }
            }
            freeMemory(market);
            printf("Exiting...\n");
            return 0;
            */
        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}