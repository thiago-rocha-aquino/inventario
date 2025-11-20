

#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"

#define MAX_PRODUCTS 1000
#define DATA_FILE "data/inventory.dat"

typedef struct {
    Product products[MAX_PRODUCTS];
    int count;
    int next_id;
} Inventory;


Inventory* init_inventory(void);
void free_inventory(Inventory* inv);

// CRUD operations
int add_product(Inventory* inv, const char* name, const char* category, float price, int quantity);
Product* find_product_by_id(Inventory* inv, int id);
int update_product(Inventory* inv, int id, const char* name, const char* category, float price, int quantity);
int delete_product(Inventory* inv, int id);
void list_all_products(const Inventory* inv);
void list_active_products(const Inventory* inv);

// Stock operations
int update_stock(Inventory* inv, int id, int quantity_change);
int check_low_stock(const Inventory* inv, int threshold);

// Search operations
void search_by_name(const Inventory* inv, const char* name);
void search_by_category(const Inventory* inv, const char* category);

// File operations
int save_inventory(const Inventory* inv);
int load_inventory(Inventory* inv);

// Statistics
void show_statistics(const Inventory* inv);

#endif // INVENTORY_H
