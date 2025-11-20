

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Inventory* init_inventory(void) {
    Inventory* inv = (Inventory*)malloc(sizeof(Inventory));

    if (inv == NULL) {
        return NULL;
    }

    inv->count = 0;
    inv->next_id = 1;

    return inv;
}

void free_inventory(Inventory* inv) {
    if (inv != NULL) {
        free(inv);
    }
}

int add_product(Inventory* inv, const char* name, const char* category, float price, int quantity) {
    if (inv == NULL || inv->count >= MAX_PRODUCTS) {
        return 0;
    }

    Product* product = create_product(inv->next_id, name, category, price, quantity);

    if (product == NULL || !validate_product(product)) {
        free(product);
        return 0;
    }

    inv->products[inv->count] = *product;
    inv->count++;
    inv->next_id++;

    free(product);

    printf("✓ Product added successfully! ID: %d\n", inv->next_id - 1);
    return 1;
}

Product* find_product_by_id(Inventory* inv, int id) {
    if (inv == NULL) {
        return NULL;
    }

    for (int i = 0; i < inv->count; i++) {
        if (inv->products[i].id == id) {
            return &inv->products[i];
        }
    }

    return NULL;
}

int update_product(Inventory* inv, int id, const char* name, const char* category, float price, int quantity) {
    Product* product = find_product_by_id(inv, id);

    if (product == NULL) {
        printf("Product not found with ID: %d\n", id);
        return 0;
    }

    if (name != NULL) {
        strncpy(product->name, name, MAX_NAME_LENGTH - 1);
        product->name[MAX_NAME_LENGTH - 1] = '\0';
    }

    if (category != NULL) {
        strncpy(product->category, category, MAX_CATEGORY_LENGTH - 1);
        product->category[MAX_CATEGORY_LENGTH - 1] = '\0';
    }

    if (price >= 0) {
        product->price = price;
    }

    if (quantity >= 0) {
        product->quantity = quantity;
    }

    if (!validate_product(product)) {
        return 0;
    }

    printf(" Product updated successfully!\n");
    return 1;
}

int delete_product(Inventory* inv, int id) {
    if (inv == NULL) {
        return 0;
    }

    for (int i = 0; i < inv->count; i++) {
        if (inv->products[i].id == id) {
           
            for (int j = i; j < inv->count - 1; j++) {
                inv->products[j] = inv->products[j + 1];
            }
            inv->count--;
            printf("Product deleted successfully!\n");
            return 1;
        }
    }

    printf("Product not found with ID: %d\n", id);
    return 0;
}

void list_all_products(const Inventory* inv) {
    if (inv == NULL || inv->count == 0) {
        printf("\nNo products in inventory.\n");
        return;
    }

    print_product_header();
    for (int i = 0; i < inv->count; i++) {
        print_product(&inv->products[i]);
    }
    printf("\nTotal products: %d\n", inv->count);
}

void list_active_products(const Inventory* inv) {
    if (inv == NULL || inv->count == 0) {
        printf("\nNo products in inventory.\n");
        return;
    }

    int active_count = 0;
    print_product_header();

    for (int i = 0; i < inv->count; i++) {
        if (inv->products[i].active) {
            print_product(&inv->products[i]);
            active_count++;
        }
    }

    printf("\nActive products: %d\n", active_count);
}

int update_stock(Inventory* inv, int id, int quantity_change) {
    Product* product = find_product_by_id(inv, id);

    if (product == NULL) {
        printf("✗ Product not found with ID: %d\n", id);
        return 0;
    }

    int new_quantity = product->quantity + quantity_change;

    if (new_quantity < 0) {
        printf("✗ Insufficient stock! Current: %d, Requested: %d\n",
               product->quantity, -quantity_change);
        return 0;
    }

    product->quantity = new_quantity;
    printf("✓ Stock updated successfully! New quantity: %d\n", product->quantity);
    return 1;
}

int check_low_stock(const Inventory* inv, int threshold) {
    if (inv == NULL) {
        return 0;
    }

    int low_stock_count = 0;

    printf("\n=== Low Stock Alert (threshold: %d) ===\n", threshold);
    print_product_header();

    for (int i = 0; i < inv->count; i++) {
        if (inv->products[i].quantity <= threshold && inv->products[i].active) {
            print_product(&inv->products[i]);
            low_stock_count++;
        }
    }

    if (low_stock_count == 0) {
        printf("No products with low stock.\n");
    } else {
        printf("\nTotal products with low stock: %d\n", low_stock_count);
    }

    return low_stock_count;
}

void search_by_name(const Inventory* inv, const char* name) {
    if (inv == NULL || name == NULL) {
        return;
    }

    int found = 0;
    print_product_header();

    for (int i = 0; i < inv->count; i++) {
        if (strstr(inv->products[i].name, name) != NULL) {
            print_product(&inv->products[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("No products found with name containing: %s\n", name);
    } else {
        printf("\nFound %d product(s)\n", found);
    }
}

void search_by_category(const Inventory* inv, const char* category) {
    if (inv == NULL || category == NULL) {
        return;
    }

    int found = 0;
    print_product_header();

    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->products[i].category, category) == 0) {
            print_product(&inv->products[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("No products found in category: %s\n", category);
    } else {
        printf("\nFound %d product(s)\n", found);
    }
}

int save_inventory(const Inventory* inv) {
    if (inv == NULL) {
        return 0;
    }

    FILE* file = fopen(DATA_FILE, "wb");

    if (file == NULL) {
        printf("Error opening file for writing\n");
        return 0;
    }

    // Write metadata
    fwrite(&inv->count, sizeof(int), 1, file);
    fwrite(&inv->next_id, sizeof(int), 1, file);

    // Write products
    fwrite(inv->products, sizeof(Product), inv->count, file);

    fclose(file);
    printf("✓ Inventory saved successfully!\n");
    return 1;
}

int load_inventory(Inventory* inv) {
    if (inv == NULL) {
        return 0;
    }

    FILE* file = fopen(DATA_FILE, "rb");

    if (file == NULL) {
        printf("No previous inventory data found. Starting fresh.\n");
        return 0;
    }

    // Read metadata
    fread(&inv->count, sizeof(int), 1, file);
    fread(&inv->next_id, sizeof(int), 1, file);

    // Read products
    fread(inv->products, sizeof(Product), inv->count, file);

    fclose(file);
    printf("Inventory loaded successfully! (%d products)\n", inv->count);
    return 1;
}

void show_statistics(const Inventory* inv) {
    if (inv == NULL || inv->count == 0) {
        printf("\nNo statistics available.\n");
        return;
    }

    int active_count = 0;
    int total_items = 0;
    float total_value = 0.0f;

    for (int i = 0; i < inv->count; i++) {
        if (inv->products[i].active) {
            active_count++;
        }
        total_items += inv->products[i].quantity;
        total_value += inv->products[i].price * inv->products[i].quantity;
    }

    printf("\n=== Inventory Statistics ===\n");
    printf("Total products: %d\n", inv->count);
    printf("Active products: %d\n", active_count);
    printf("Total items in stock: %d\n", total_items);
    printf("Total inventory value: $%.2f\n", total_value);
    printf("===========================\n");
}
