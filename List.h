#ifndef LIST_H
#define LIST_H

typedef struct Node
{
    void *data;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
    int size;
    void (*f_print)(struct Node *);
} List;

Node *create_node(void *data);

List *create_list(void (*f_print)(Node *));

int push(List *list, void *data);

void print_list(List *list);

void delete_list(List *list);

#endif