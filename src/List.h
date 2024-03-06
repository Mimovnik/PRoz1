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
    void (*f_print)(void *);
} List;

Node *create_node(void *data);

List *create_list(void (*f_print)(void *));

int push(List *list, void *data);

int print_list(List *list);

void delete_list(List *list);

#endif