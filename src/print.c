#include <stdio.h>

#include "print.h"

#define PTR_W 14

static void print_border(const Node *head) {
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