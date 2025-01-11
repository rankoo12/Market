#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NewCart.h"
#include "Product.h"
#include "Date.h"





void initializeCart(ShoppingCart* cart) {
    cart->size = 0;
    cart->capacity = 2;
    cart->items = malloc(cart->capacity * sizeof(ShoppingItem));
    if (cart->items == NULL) {
        perror("Failed to allocate memory for shopping cart");
        exit(EXIT_FAILURE);
    }
}

void addItemToCart(ShoppingCart* cart, const ShoppingItem* newItem) {
    // Check if the cart already has the product
    for (int i = 0; i < cart->size; i++) {
        if (strcmp(cart->items[i].product.name, newItem->product.name) == 0) {
            // Update quantity if the product already exists
            cart->items[i].quantity += newItem->quantity;
            printf("Updated quantity of '%s' to %d\n",
                cart->items[i].product.name, cart->items[i].quantity);
            return;
        }
    }

    // Resize the array if needed
    if (cart->size == cart->capacity) {
        cart->capacity *= 2;
        cart->items = realloc(cart->items, cart->capacity * sizeof(ShoppingItem));
        if (cart->items == NULL) {
            perror("Failed to reallocate memory for shopping cart");
            exit(EXIT_FAILURE);
        }
    }

    // Add the new item to the cart
    cart->items[cart->size] = *newItem;
    cart->size++;
    printf("Added '%s' to the cart\n", newItem->product.name);
}

void removeItemFromCart(ShoppingCart* cart, const char* productName) {
    for (int i = 0; i < cart->size; i++) {
        if (strcmp(cart->items[i].product.name, productName) == 0) {
            // Shift items left to remove the item
            for (int j = i; j < cart->size - 1; j++) {
                cart->items[j] = cart->items[j + 1];
            }
            cart->size--;
            printf("Removed '%s' from the cart\n", productName);
            return;
        }
    }
    printf("Product '%s' not found in the cart\n", productName);
}

/*
void printCart(const ShoppingCart* cart) {
    if (cart->size == 0) {
        printf("The shopping cart is empty.\n");
        return;
    }

    printf("Shopping Cart:\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < cart->size; i++) {
        const ShoppingItem* item = &cart->items[i];
        printf("Product: %s\n", item->product.name);
        printf("Type: %s\n", item->product.barcode);
        printf("Price: $%.2f\n", item->product.price);
        printf("Quantity: %d\n", item->quantity);
        printf("Expiration Date: %02d/%02d/%04d\n",
            item->product.date.day, item->product.date.month, item->product.date.year);
        printf("----------------------------------------------------\n");
    }
}
*/

void freeCart(ShoppingCart* cart) {
    free(cart->items);
    cart->items = NULL;
    cart->size = 0;
    cart->capacity = 0;
}

