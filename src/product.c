
#include "product.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Product* create_product(int id, const char* name, const char* category, float price, int quantity) {
    Product* product = (Product*)malloc(sizeof(Product));

    if (product == NULL) {
        return NULL;
    }

    product->id = id;
    strncpy(product->name, name, MAX_NAME_LENGTH - 1);
    product->name[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(product->category, category, MAX_CATEGORY_LENGTH - 1);
    product->category[MAX_CATEGORY_LENGTH - 1] = '\0';

    product->price = price;
    product->quantity = quantity;
    product->active = 1;

    return product;
}

void print_product_header(void) {
    printf("\n%-5s %-30s %-20s %10s %10s %8s\n",
           "ID", "Name", "Category", "Price", "Quantity", "Status");
    printf("-------------------------------------------------------------------------------------------\n");
}

void print_product(const Product* product) {
    if (product == NULL) {
        return;
    }

    printf("%-5d %-30s %-20s $%9.2f %10d %8s\n",
           product->id,
           product->name,
           product->category,
           product->price,
           product->quantity,
           product->active ? "Active" : "Inactive");
}

int validate_product(const Product* product) {
    if (product == NULL) {
        return 0;
    }

    if (strlen(product->name) == 0) {
        printf("Error: Product name cannot be empty\n");
        return 0;
    }

    if (product->price < 0) {
        printf("Error: Price cannot be negative\n");
        return 0;
    }

    if (product->quantity < 0) {
        printf("Error: Quantity cannot be negative\n");
        return 0;
    }

    return 1;
}
