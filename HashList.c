#include "HashList.h"
#include <stdlib.h>

typedef struct HashList
{
    List *list;
    void *(*f_hash)();
    int (*f_comp)();
} HashList;

HashList *create_hash_list(void *(*f_hash)(void *data), int (*f_comp)(void *hash1, void *hash2))
{
    HashList *newHashList = (HashList *)malloc(sizeof(HashList));
    if (newHashList == NULL)
    {
        return NULL;
    }
    newHashList->list = create_list();
    newHashList->f_hash = f_hash;
    newHashList->f_comp = f_comp;
}

int insert(HashList *hashList, void *data)
{
    void *dataHash = f_hash(data);
}

void print(HashList *hashList, void (*f_print)(Node *))
{
}

void delete_hash_list(HashList *hashList)
{
    delete_list(hashList->list);
    delete (hashList);
}