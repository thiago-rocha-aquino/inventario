

#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    float price;
    int quantity;
    int active;
} Product;

// Product operations
Product* create_product(int id, const char* name, const char* category, float price, int quantity);
void print_product(const Product* product);
void print_product_header(void);
int validate_product(const Product* product);

#endif // PRODUCT_H
