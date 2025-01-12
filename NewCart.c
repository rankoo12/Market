#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NewCart.h"
#include "Product.h"
#include "Date.h"





void initializeCart(ShoppingCart* cart) {
	cart = malloc(sizeof(ShoppingCart));
	cart->items = NULL;
	cart->items_quantity = 0;
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

