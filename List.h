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
} List;

Node *create_node(void *data);

List *create_list();

int push(List *list, void *data);

void print(List *list, void (*f_print)(Node *));

void delete_list(List *list);

#endif