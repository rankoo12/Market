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
Costumer setCostumer(Costumer customer, const char id[maxSizeId], char* customer_name, ShoppingCart* cart);
void capitalizeWords(char* str);
char* combineNames(char* firstName, char* lastName);
#endif // COSTUMER_H
