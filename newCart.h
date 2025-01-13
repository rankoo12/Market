#ifndef CART_H
#define CART_H
#include "constants.h"
#include "Product.h"


typedef struct {
	char barcode[maxSizeBarCode];
	float price;
	int quantity;
} ShoppingItem;

typedef struct {
	ShoppingItem* items;
	int items_quantity;
} ShoppingCart;


void initializeCart(ShoppingCart* cart);
int totalPriceOfCart(ShoppingCart* cart);
void printCart(const ShoppingCart* cart);



#endif // DATE_H