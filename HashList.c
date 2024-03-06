#include "HashList.h"
#include <stdlib.h>
#include <stdio.h>

// typedef struct HashList
// {
//     List *list;
//     void *(*f_hash)();
//     int (*f_comp)();
// } HashList;

HashList *create_hash_list(void *(*f_hash)(void *data), int (*f_comp)(void *hash1, void *hash2), void (*f_print)(Node *node))
{
    HashList *newHashList = (HashList *)malloc(sizeof(HashList));
    if (newHashList == NULL)
    {
        return NULL;
    }
    newHashList->list = create_list(f_print);
    newHashList->f_hash = f_hash;
    newHashList->f_comp = f_comp;
}

int insert(HashList *hashList, void *data)
{
    if (hashList == NULL)
    {
        printf("ERROR: insert: *hashList cannot be null\n");
        return 1;
    }

    void *dataHash = hashList->f_hash(data);

        return 0;
}

void print_hash_list(HashList *hashList)
{
    if (hashList == NULL)
    {
        printf("ERROR: print_hash_list: *hashList cannot be null\n");
        return 1;
    }
    print_list(hashList->list);
}

void delete_hash_list(HashList *hashList)
{
    delete_list(hashList->list);
    free(hashList);
}