#ifndef CART_H
#define CART_H
#include "constants.h"
#include "Product.h"



typedef struct {
	Product product; // Embed Product struct
	int quantity;    // Quantity of this product in the shopping item
} ShoppingItem;

typedef struct {
	ShoppingItem* items;
	int size;
	int capacity;
} ShoppingCart;


void initializeCart(ShoppingCart* cart);
void addItemToCart(ShoppingCart* cart, const ShoppingItem* newItem);
void removeItemFromCart(ShoppingCart* cart, const char* productName);
void printCart(const ShoppingCart* cart);
void freeCart(ShoppingCart* cart);



#endif // DATE_H