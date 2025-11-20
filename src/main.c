
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

void print_menu(void) {
    printf("\n========================================\n");
    printf("  INVENTORY MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf(" 1. Add Product\n");
    printf(" 2. List All Products\n");
    printf(" 3. List Active Products\n");
    printf(" 4. Search Product by Name\n");
    printf(" 5. Search by Category\n");
    printf(" 6. Update Product\n");
    printf(" 7. Update Stock\n");
    printf(" 8. Delete Product\n");
    printf(" 9. Check Low Stock\n");
    printf("10. Show Statistics\n");
    printf("11. Save Inventory\n");
    printf("12. Load Inventory\n");
    printf(" 0. Exit\n");
    printf("========================================\n");
    printf("Choose an option: ");
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_product_interactive(Inventory* inv) {
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    float price;
    int quantity;

    printf("\n=== Add New Product ===\n");

    printf("Name: ");
    clear_input_buffer();
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Category: ");
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = '\0';

    printf("Price: $");
    if (scanf("%f", &price) != 1) {
        printf("Invalid price!\n");
        return;
    }

    printf("Quantity: ");
    if (scanf("%d", &quantity) != 1) {
        printf("Invalid quantity!\n");
        return;
    }

    add_product(inv, name, category, price, quantity);
}

void update_product_interactive(Inventory* inv) {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    float price;
    int quantity;

    printf("\n=== Update Product ===\n");
    printf("Product ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    Product* product = find_product_by_id(inv, id);
    if (product == NULL) {
        printf("Product not found!\n");
        return;
    }

    printf("\nCurrent product:\n");
    print_product_header();
    print_product(product);

    printf("\nNew name (or press Enter to keep current): ");
    clear_input_buffer();
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("New category (or press Enter to keep current): ");
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = '\0';

    printf("New price (or -1 to keep current): $");
    if (scanf("%f", &price) != 1) {
        price = -1;
    }

    printf("New quantity (or -1 to keep current): ");
    if (scanf("%d", &quantity) != 1) {
        quantity = -1;
    }

    update_product(inv,
                   id,
                   strlen(name) > 0 ? name : NULL,
                   strlen(category) > 0 ? category : NULL,
                   price,
                   quantity);
}

void update_stock_interactive(Inventory* inv) {
    int id, change;

    printf("\n=== Update Stock ===\n");
    printf("Product ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    printf("Quantity change (use negative for decrease): ");
    if (scanf("%d", &change) != 1) {
        printf("Invalid quantity!\n");
        return;
    }

    update_stock(inv, id, change);
}

void search_by_name_interactive(Inventory* inv) {
    char name[MAX_NAME_LENGTH];

    printf("\n=== Search by Name ===\n");
    printf("Enter name to search: ");
    clear_input_buffer();
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    search_by_name(inv, name);
}

void search_by_category_interactive(Inventory* inv) {
    char category[MAX_CATEGORY_LENGTH];

    printf("\n=== Search by Category ===\n");
    printf("Enter category: ");
    clear_input_buffer();
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = '\0';

    search_by_category(inv, category);
}

void delete_product_interactive(Inventory* inv) {
    int id;

    printf("\n=== Delete Product ===\n");
    printf("Product ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    Product* product = find_product_by_id(inv, id);
    if (product != NULL) {
        printf("\nProduct to be deleted:\n");
        print_product_header();
        print_product(product);

        char confirm;
        printf("\nAre you sure? (y/n): ");
        clear_input_buffer();
        scanf("%c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {
            delete_product(inv, id);
        } else {
            printf("Deletion cancelled.\n");
        }
    }
}

void check_low_stock_interactive(Inventory* inv) {
    int threshold;

    printf("\n=== Check Low Stock ===\n");
    printf("Enter threshold: ");

    if (scanf("%d", &threshold) != 1 || threshold < 0) {
        printf("Invalid threshold!\n");
        return;
    }

    check_low_stock(inv, threshold);
}

int main(void) {
    Inventory* inv = init_inventory();

    if (inv == NULL) {
        printf("Failed to initialize inventory!\n");
        return 1;
    }

    load_inventory(inv);

    int choice;
    int running = 1;

    while (running) {
        print_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                add_product_interactive(inv);
                break;

            case 2:
                list_all_products(inv);
                break;

            case 3:
                list_active_products(inv);
                break;

            case 4:
                search_by_name_interactive(inv);
                break;

            case 5:
                search_by_category_interactive(inv);
                break;

            case 6:
                update_product_interactive(inv);
                break;

            case 7:
                update_stock_interactive(inv);
                break;

            case 8:
                delete_product_interactive(inv);
                break;

            case 9:
                check_low_stock_interactive(inv);
                break;

            case 10:
                show_statistics(inv);
                break;

            case 11:
                save_inventory(inv);
                break;

            case 12:
                load_inventory(inv);
                break;

            case 0:
                printf("\nSave inventory before exiting? (y/n): ");
                clear_input_buffer();
                char save_choice;
                scanf("%c", &save_choice);

                if (save_choice == 'y' || save_choice == 'Y') {
                    save_inventory(inv);
                }

                printf("\nThank you for using Inventory Management System!\n");
                running = 0;
                break;

            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    free_inventory(inv);
    return 0;
}
