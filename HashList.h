#ifndef HASH_LIST_H
#define HASH_LIST_H

#include "List.h"

typedef struct HashList
{
    void *(*f_hash)();
    int (*f_comp)();
    List *list;
} HashList;

HashList *create_hash_list();

int insert(List *list, void *data, int index);

void print(List *list, void (*f_print)(Node *));

void delete_hash_list(HashList *list);

#endif