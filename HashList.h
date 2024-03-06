#ifndef HASH_LIST_H
#define HASH_LIST_H

#include "List.h"

typedef struct HashList
{
    void *(*f_hash)();
    int (*f_comp)();
    List *list;
} HashList;

HashList *create_hash_list(void *(*f_hash)(void *data), int (*f_comp)(void *hash1, void *hash2), void (*f_print)(Node *node));

int insert(HashList *hashList, void *data);

void print_hash_list(HashList *hashList, void (*f_print)(Node *));

void delete_hash_list(HashList *hashList);

#endif