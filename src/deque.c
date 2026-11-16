#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

Deque create_deque(void) {
    Deque d;
    d.size = 0;
    d.head = NULL;
    d.tail = NULL;
    return d;
}

static Node *create_node(char key, const char *value) {
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

int is_key_used(const Deque *d, char key) {
    const Node *curr = d->head;
    while (curr != NULL) {
        if (curr->key == key) {
            return 1;
        }
        curr = curr->NextPtr;
    }
    return 0;
}

void push_front(Deque *d, char key, const char *value) {
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

void push_back(Deque *d, char key, const char *value) {
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

static void swap_neighbours(Deque *d, Node *first, Node *second) {
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

void insert_in_sorted(Deque *d, char key, const char *value) {
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