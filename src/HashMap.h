#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "List.h"

typedef struct HashMap
{
    void *(*f_hash)(void *value);
    int (*f_comp)(void *key1, void *key2);
    void (*f_print)(void *value);
    List *entries;
} HashMap;

HashMap *create_hash_map(void *(*f_hash)(void *value), int (*f_comp)(void *key1, void *key2), void (*f_print)(void *value));

int insert(HashMap *hashMap, void *value);

void *get_value(HashMap *hashMap, void *key);

void *remove_value(HashMap *hashMap, void *key);

int print_hash_map(HashMap *hashMap);

void delete_hash_map(HashMap *hashMap);

#endif