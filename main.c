#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Product.h"
#include "Cart.h"




int main() {
	ShoppingCart cart;
	initializeCart(&cart);

	// Create a new product
	Product p;
	newProduct(&p);


	// Create a ShoppingItem for the product
	ShoppingItem item = { p, 2 }; // Adding 2 units of the product
	Product a;
	newProduct(&a);
	ShoppingItem item2 = { a, 2 }; // Adding 2 units of the product

	// Add the item to the cart
	addItemToCart(&cart, &item);
	addItemToCart(&cart, &item2);

	// Print the cart
	printCart(&cart);

	// Free the cart memory
	//freeCart(&cart);
	return 0;
}


