#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NewCart.h"
#include "Product.h"
#include "Date.h"





void initializeCart(ShoppingCart* cart) {
	cart->items_quantity = 0;  // Set the items quantity to 0
	cart->items = NULL;        // Make sure the items pointer is initially NULL
}


int totalPriceOfCart(ShoppingCart* cart)
{
	int total = 0;
	for (int i = 0; i < cart->items_quantity; i++)
	{
		total += cart->items[i].price;
	}
	return total;
}

void printCart(const ShoppingCart* cart) {
    if (cart == NULL || cart->items_quantity == 0) {
        printf("The cart is empty.\n");
        return;
    }

    printf("Items in the cart:\n");
    printf("---------------------------------\n");
    printf("| %-10s | %-10s | %-8s |\n", "Barcode", "Quantity", "Price");
    printf("---------------------------------\n");

    float totalCost = 0;
    for (int i = 0; i < cart->items_quantity; i++) {
        const ShoppingItem* item = &cart->items[i];
        printf("| %-10s | %-10d | %-8.2f |\n", item->barcode, item->quantity, item->price);
        totalCost += item->quantity * item->price;
    }
    printf("---------------------------------\n");
    printf("Total cost: %.2f\n", totalCost);
}

