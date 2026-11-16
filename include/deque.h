#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

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

Deque create_deque(void);

int is_empty(const Deque *d);
int deque_size(const Deque *d);
int is_key_used(const Deque *d, char key);

void push_front(Deque *d, char key, const char *value);
void push_back(Deque *d, char key, const char *value);
int pop_front(Deque *d);
int pop_back(Deque *d);

void bubble_sort(Deque *d);
void insert_in_sorted(Deque *d, char key, const char *value);
Node *search_by_key(const Deque *d, char key);

#endif