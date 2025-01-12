#include <stdio.h>
#include "SuperMarket.h"
#include "Product.h"
#include <ctype.h>
#include <stdlib.h>

void initSuperMarket(SuperMarket* market)
{
    // Initialize pointers to NULL
    market->shopName = NULL;
    market->customers = NULL;
    market->products = NULL;

    // Initialize counters to 0
    market->totalCustomers = 0;
    market->totalProducts = 0;
}

void printSuperMarketData(SuperMarket* market)
{
    printf("Shop Name : %s\n", market->shopName);
    printf("Total Costumers : %d\n", market->totalCustomers);
    for (int i = 0; i < market->totalCustomers; i++)
    {
        printf("Costumer %d : \n", i + 1);
        printf("Costumer ID : %s\n", market->customers[i].id);
        printf("Costumer Name : %s\n", market->customers[i].costumerName);
    }
    printf("Total Products : %d\n", market->totalProducts);
    for (int i = 0; i < market->totalProducts; i++)
    {
        printf("Product %d : \n", i + 1);
        printf("Product Name : %s\n", market->products[i].name);
        printf("Product Barcode : %s\n", market->products[i].barcode);
        printf("Product Price : %f\n", market->products[i].price);
        printf("Product Quantity : %d\n", market->products[i].quantity);
        printf("Product Date: %02d/%02d/%d\n", market->products[i].date.day, market->products[i].date.month, market->products[i].date.year);
    }
}

Costumer* increaseCustomersArraySize(Costumer* customers, int* totalCustomers) {
    customers = realloc(customers, (*totalCustomers + 1) * sizeof(Costumer));
    if (!customers) {
        perror("Memory allocation failed");
        return NULL;
    }
    (*totalCustomers)++;
    return customers;
}

Product* increaseProductsArraySize(Product* products, int* totalProducts) {
    products = realloc(products, (*totalProducts + 1) * sizeof(Product));
    if (!products) {
        perror("Memory allocation failed");
        return NULL;
    }
    (*totalProducts)++;
    return products;
}

void addProductToSuperMarket(SuperMarket* market, const char* barcode)
{
    Product* foundProduct = getProductByBarCode(market->products, market->totalProducts, barcode);
    if (foundProduct != NULL)
    {
        getchar();
        printf("Product with barcode %s was found, please enter the quantity you would like to add :\n");
        int quantity = 1;
        scanf_s("%d", &quantity);
        if (quantity > foundProduct->quantity || foundProduct->quantity == 0) quantity = foundProduct->quantity;
        if (quantity != 0)
        {
            foundProduct->quantity -= quantity;
            market->products = increaseProductsArraySize(market->products, market->totalProducts);
            market->products[market->totalProducts - 1] = *foundProduct;
        }
        else printf("This product is out of stuck! please try other product !\n");
    }
    else
    {
        printf("Product with barcode %s was not found, would you like to create a new product?: (y/n)\n", barcode);
        char answer[255];
        fgets(answer, 255, stdin);
        answer[strcspn(answer, "\n")] = 0;
        if (strcmp(answer, "y") == 0)
        {
            Product *newProductToAdd = malloc(sizeof(Product));
            newProduct(newProductToAdd);
            if (validateProduct(newProductToAdd)) // validating if the new product was created according to the rules.
            {
                market->products = increaseProductsArraySize(market->products, &market->totalProducts);
                market->products[market->totalProducts - 1] = *newProductToAdd;
            }
        }
        if (answer == 'n')
        {
            //return to main menu
        }
    }
}

Product* getProductByBarCodeInMarket(SuperMarket *market, const char* barcode)
{
    for (int i = 0; i < market->totalProducts; i++) {
        if (strcmp(market->products[i].barcode, barcode) == 0) {
            return &market->products[i]; // Return a pointer to the matching product
        }
    }
    return NULL;
}

Product* removeProductFromMarket(SuperMarket *market, Product* product_to_remove)
{
    int product_index = -1;
    for (int i = 0; i < market->totalProducts; i++) {
        if (&market->products[i] == product_to_remove) {
            product_index = i;
            break;
        }
    }
    for (int i = product_index; i < market->totalProducts - 1; i++) {
        market->products[i] = market->products[i + 1];
    }
    market->totalProducts -= 1;
    Product* new_products = (Product*)realloc(market->products, (market->totalProducts) * sizeof(Product));
    return new_products;
}

void addCostumerToSuperMarket(SuperMarket* market)
{
    getchar();
    printf("Enter costumer ID : \n");
    char id[maxSizeId];
    fgets(id, maxSizeId, stdin);  // Corrected size
    getchar();
    Costumer *new_customer = getCostumerById(market->customers, market->totalCustomers, id);
    if (new_customer == NULL)
    {
        printf("Could not find a customer with id : %s, creating new costumer with that id\n", id);
        market->customers = increaseCustomersArraySize(market->customers, &market->totalCustomers);
        new_customer = newCostumer(id);
        //snprintf(market->customers[market->totalCustomers - 1].costumerName, nameLength, "%s", new_customer->costumerName);
        //*market->customers[market->totalCustomers - 1].id = new_customer->id;
        strcpy(market->customers[market->totalCustomers - 1].costumerName, new_customer->costumerName);
        strcpy(market->customers[market->totalCustomers - 1].id, new_customer->id);
        printf("");
    }
}

void addItemToCart(SuperMarket* market, ShoppingCart* cart, const char barcode[maxSizeBarCode])
{
    //create new item -> add it to items array in cart
    Product* foundProduct = getProductByBarCodeInMarket(market, barcode);
    if (foundProduct != NULL)
    {
        ShoppingItem* newItem = (ShoppingItem*)malloc(sizeof(ShoppingItem));
        *newItem->barcode = foundProduct->barcode;
        newItem->price = (float)foundProduct->price;


        getchar();
        printf("Product with barcode %s was found, please enter the quantity you would like to add :\n");
        int quantity = 1;
        scanf_s("%d", &quantity);
        if (quantity > foundProduct->quantity) quantity = foundProduct->quantity;
        if (quantity > 0)
        {
            newItem->quantity += quantity;
            foundProduct->quantity -= quantity;
        }
        else removeProductFromMarket(market, foundProduct);
    }
    else
    {
        getchar();
        printf("Product with barcode %s was not found, would you like to add other product?: (y/n)\n");
        char answer;
        scanf_s("%c", &answer);
        if (answer == 'y')
        {
            getchar();
            printf("Please enter product barcode : \n");
            char barcode[maxSizeBarCode];
            scanf_s("%s", &barcode);
            addItemToCart(market, cart, barcode);
        }
        if (answer == 'n')
        {
            //return to main menu
        }
    }
}