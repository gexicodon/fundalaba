#include <stdio.h>

#include "deque.h"
#include "print.h"

int main(void) {
    Deque d = create_deque();
    int choice;
    int display_mode = 0;

    char key;
    char buffer[256];

    printf("=== Demonstration of deque ===\n");

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1 - push to front of deque\n");
        printf("2 - push to back of deque\n");
        printf("3 - delete from front of deque\n");
        printf("4 - delete from back of deque\n");
        printf("5 - sort by keys\n");
        printf("6 - insert in sorted deque\n");
        printf("7 - find by key\n");
        printf("8 - change mode of show deque (current: %s)\n", display_mode == 0 ? "Elements" : "Detailed");
        printf("0 - exit\n");
        printf("Select action: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter key (1 char): ");
                scanf(" %c", &key);
                printf("Enter value (string): ");
                scanf(" %255[^\n]", buffer);
                push_front(&d, key, buffer);
                break;

            case 2:
                printf("Enter key (1 char): ");
                scanf(" %c", &key);
                printf("Enter value (string): ");
                scanf(" %255[^\n]", buffer);
                push_back(&d, key, buffer);
                break;

            case 3:
                if (pop_front(&d) == 0) {
                    printf("Deleted from front.\n");
                } 
                break;

            case 4:
                if (pop_back(&d) == 0) {
                    printf("Deleted from back.\n");
                }
                break;

            case 5:
                bubble_sort(&d);
                break;

            case 6:
                printf("Enter key (1 char): ");
                scanf(" %c", &key);
                printf("Enter value (string): ");
                scanf(" %255[^\n]", buffer);
                insert_in_sorted(&d, key, buffer);
                printf("Element inserted in sorted order.\n");
                break;

            case 7: {
                if (is_empty(&d)) {
                    break;
                }
                printf("Enter key to find (1 char): ");
                scanf(" %c", &key);
                Node *found = search_by_key(&d, key);
                if (found != NULL) {
                    printf("Found -> [%c]: \"%s\" (Addr: %p)\n", found->key, found->value, (void *)found);
                } else {
                    printf("Element with key '%c' not found.\n", key);
                }
                break;
            }

            case 8:
                display_mode = !display_mode;
                printf("Display mode changed.\n");
                break;

            default:
                printf("Unknown command! Try again.\n");
                continue;
        }

        if (display_mode == 0) {
            print_elements(&d);
        } else {
            print_deque(&d);
        }
    }

    while (!is_empty(&d)) {
        pop_front(&d);
    }
    printf("Memory freed. Program finished.\n");

    return 0;
}