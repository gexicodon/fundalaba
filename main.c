#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PTR_W 14

typedef struct Node {
    char *value;
    char key;

    struct Node *PrevPtr;
    struct Node *NextPtr;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} Deque;

Deque create_deque() {
    Deque d;
    d.size = 0;
    d.head = NULL;
    d.tail = NULL;
    return d;
}

Node *create_node(char key, char *value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        perror("Ошибка выделения памяти под узел");
        exit(EXIT_FAILURE);
    }

    new_node->key = key;

    new_node->value = (char *)malloc(strlen(value) + 1);
    if (!new_node->value) {
        perror("Ошибка выделения памяти под строку");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->value, value);

    new_node->PrevPtr = NULL;
    new_node->NextPtr = NULL;

    return new_node;
}

int is_empty(const Deque *d) {
    return d->size == 0;
}

int deque_size(const Deque *d) {
    return (int)d->size;
}

int is_key_used(Deque *d, char key) {
    if (d->size == 0) {
        return 0;
    }

    Node *curr = d->head;
    while (curr != NULL) {
        if (curr->key == key) {
            return 1;
        } else{
            curr = curr->NextPtr;
        }
    }
    return 0;
}

void push_front(Deque *d, char key, char *value) {
    if (is_key_used(d, key)) {
        printf("Key is already used\n");
        return;
    }

    Node *new_node = create_node(key, value);

    if (is_empty(d)) {
        d->head = new_node;
        d->tail = new_node;
    } else {
        new_node->NextPtr = d->head;
        d->head->PrevPtr = new_node;
        d->head = new_node;
    }
    d->size++;
}

void push_back(Deque *d, char key, char *value) {
    if (is_key_used(d, key)) {
        printf("Key is already used\n");
        return;
    }

    Node *new_node = create_node(key, value);

    if (is_empty(d)) {
        d->head = new_node;
        d->tail = new_node;
    } else {
        new_node->PrevPtr = d->tail;
        d->tail->NextPtr = new_node;
        d->tail = new_node;
    }
    d->size++;
}

int pop_front(Deque *d) {
    if (is_empty(d)) {
        return 1;
    }

    Node *old_head = d->head;

    if (d->size == 1) {
        d->head = NULL;
        d->tail = NULL;
    } else {
        d->head = d->head->NextPtr;
        d->head->PrevPtr = NULL;
    }

    free(old_head->value);
    free(old_head);
    d->size--;
    return 0;
}

int pop_back(Deque *d) {
    if (is_empty(d)) {
        return 1;
    }

    Node *old_tail = d->tail;

    if (d->size == 1) {
        d->tail = NULL;
        d->head = NULL;
    } else {
        d->tail = d->tail->PrevPtr;
        d->tail->NextPtr = NULL;
    }

    free(old_tail->value);
    free(old_tail);
    d->size--;
    return 0;
}


void print_border(const Node *head) {
    for (const Node *c = head; c != NULL; c = c->NextPtr) {
        printf("+----------------------+");
        if (c->NextPtr != NULL) printf("     ");
    }
    printf("\n");
}

void print_deque(const Deque *d) {
    printf("\n=== Deque ===\n");
    printf("Size: %zu | Head: %p | Tail: %p\n\n", d->size, (void *)d->head, (void *)d->tail);

    if (is_empty(d)) {
        printf("[ Deque is empty ]\n\n");
        return;
    }

    const Node *curr;

    print_border(d->head);

    for (curr = d->head; curr; curr = curr->NextPtr) {
        printf("| Addr: %-*p |", PTR_W, (void *)curr);
        if (curr->NextPtr) printf("     ");
    }
    printf("\n");

    for (curr = d->head; curr; curr = curr->NextPtr) {
        printf("| [%c] : %-*.*s |", curr->key, PTR_W, 11, curr->value);
        if (curr->NextPtr) printf(" <-> ");
    }
    printf("\n");

    for (curr = d->head; curr; curr = curr->NextPtr) {
        printf("| Prev: %-*p |", PTR_W, (void *)curr->PrevPtr);
        if (curr->NextPtr) printf("     ");
    }
    printf("\n");

    for (curr = d->head; curr; curr = curr->NextPtr) {
        printf("| Next: %-*p |", PTR_W, (void *)curr->NextPtr);
        if (curr->NextPtr) printf("     ");
    }
    printf("\n");

    print_border(d->head);
    printf("\n");
}

void print_elements(const Deque *d) {
    if (is_empty(d)) {
        printf("Deque is empty\n");
    } else {
        printf("=== Deque ===\n");
        const Node *curr = d->head;
        while (curr != NULL) {
            printf("| [%c]: \"%s\"  |", curr->key, curr->value);
            if (curr->NextPtr != NULL) printf("  <->  ");
            curr = curr->NextPtr;
        }
        printf("\n");
    }
}

void swap_neighbours(Deque *d, Node *first, Node *second) {
    Node *prev_node = first->PrevPtr;
    Node *next_node = second->NextPtr;

    if (prev_node != NULL) {
        prev_node->NextPtr = second;
    } else {
        d->head = second;
    }

    if (next_node != NULL) {
        next_node->PrevPtr = first;
    } else {
        d->tail = first;
    }

    second->PrevPtr = prev_node;
    second->NextPtr = first;
    first->PrevPtr = second;
    first->NextPtr = next_node;
}

void bubble_sort(Deque *d) {
    if (d == NULL || d->size < 2) {
        return;
    }

    int swapped;
    Node *curr;
    Node *last_sorted = NULL;

    do {
        swapped = 0;
        curr = d->head;

        while (curr->NextPtr != last_sorted) {
            if (strcmp(curr->value, curr->NextPtr->value) > 0) {
                swap_neighbours(d, curr, curr->NextPtr);
                swapped = 1;
            } else {
                curr = curr->NextPtr;
            }
        }
        last_sorted = curr;

    } while (swapped);
}

void insert_in_sorted(Deque *d, char key, char *value) {
    if (is_key_used(d, key)) {
        printf("Key is already used\n");
        return;
    }

    if (is_empty(d) || strcmp(value, d->head->value) <= 0) {
        push_front(d, key, value);
        return;
    }

    if (strcmp(value, d->tail->value) >= 0) {
        push_back(d, key, value);
        return;
    }

    Node *curr = d->head->NextPtr;
    while (curr != NULL && strcmp(curr->value, value) < 0) {
        curr = curr->NextPtr;
    }

    Node *new_node = create_node(key, value);
    Node *prev_node = curr->PrevPtr;

    new_node->PrevPtr = prev_node;
    new_node->NextPtr = curr;

    prev_node->NextPtr = new_node;
    curr->PrevPtr = new_node;

    d->size++;
}

Node *search_by_key(const Deque *d, char key) {
    Node *curr = d->head;
    while (curr != NULL) {
        if (key == curr->key) {
            return curr;
        }
        curr = curr->NextPtr;
    }
    return NULL;
}

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
        printf("5 - sort by values\n");
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
                } else {
                    printf("Deque is already empty!\n");
                }
                break;

            case 4:
                if (pop_back(&d) == 0) {
                    printf("Deleted from back.\n");
                } else {
                    printf("Deque is already empty!\n");
                }
                break;

            case 5:
                bubble_sort(&d);
                printf("Deque sorted by values.\n");
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
                    printf("Deque is empty!\n");
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