#ifndef COSTUMER_H
#define COSTUMER_H
#include "constants.h"
#include "newCart.h"
#include "Date.h"

typedef struct {
    char id[maxSizeId];
    char* costumerName;
    ShoppingCart *cart;
} Costumer;

Costumer* initCostumer(Costumer* costumer);
Costumer* getCostumerById(Costumer* customers, int numOfCustomers, const char* id);
Costumer* newCostumer(char* id);
void capitalizeWords(char* str);
char* combineNames(char* firstName, char* lastName);
#endif // COSTUMER_H
