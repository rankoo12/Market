#ifndef COSTUMER_H
#define COSTUMER_H
#include "constants.h"
#include "newCart.h"

typedef struct {
	char id[maxSizeID];
	char* name;
	ShoppingCart cart;
} Costumer;

void newCostumer(Costumer* costumer);

#endif // COSTUMER_H
