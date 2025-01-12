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

