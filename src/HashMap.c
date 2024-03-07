#include "HashMap.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct HashEntry
{
    void *key;
    List *values;
} HashEntry;

HashEntry *create_hash_entry(void *key, List *values)
{
    HashEntry *hashEntry = (HashEntry *)malloc(sizeof(HashEntry));
    if (hashEntry == NULL)
    {
        return NULL;
    }

    hashEntry->key = key;
    hashEntry->values = values;
}

void delete_hash_entry(HashEntry *hashEntry)
{
    free(hashEntry->key);
    delete_list(hashEntry->values);
    free(hashEntry);
}

HashMap *create_hash_map(void *(*f_hash)(void *value), int (*f_comp)(void *key1, void *key2), void (*f_print)(void *value))
{
    HashMap *newHashMap = (HashMap *)malloc(sizeof(HashMap));
    if (newHashMap == NULL)
    {
        return NULL;
    }
    newHashMap->entries = create_list(f_print);
    newHashMap->f_hash = f_hash;
    newHashMap->f_comp = f_comp;
    newHashMap->f_print = f_print;
}

int insert(HashMap *hashMap, void *value)
{
    if (hashMap == NULL)
    {
        printf("ERROR: insert: *hashMap cannot be null\n");
        return 1;
    }

    if (hashMap->entries == NULL)
    {
        printf("ERROR: insert: hashMap->entries cannot be null (Probably using insert() before create_hash_map()\n");
        return 1;
    }

    void *key = hashMap->f_hash(value);

    if (hashMap->entries->head == NULL)
    {
        printf("Inserting the first element\n");
        List *values = create_list(hashMap->f_print);
        push(values, value);
        HashEntry *newEntry = create_hash_entry(key, values);
        Node *newNode = create_node(newEntry);
        hashMap->entries->head = newNode;
        hashMap->entries->tail = newNode;
        hashMap->entries->size++;
        return 0;
    }

    Node *currentNode = hashMap->entries->head;
    for (int i = 0; i < hashMap->entries->size; i++)
    {
        if (currentNode->next == NULL)
        {
            break;
        }

        HashEntry *currentEntry = currentNode->data;
        if (hashMap->f_comp(key, currentEntry->key) < 0)
        {
            break;
        }

        currentNode = currentNode->next;
    }

    HashEntry *currentEntry = currentNode->data;
    if (hashMap->f_comp(key, currentEntry->key) == 0)
    {
        free(key);
        push(currentEntry->values, value);
        return 0;
    }

    List *values = create_list(hashMap->f_print);
    push(values, value);
    HashEntry *newEntry = create_hash_entry(key, values);
    Node *newNode = create_node(newEntry);

    hashMap->entries->size++;

    if (currentNode == hashMap->entries->head)
    {
        // h
        // CN
        // 1 <-> 2
        //
        //         CN
        // new <-> 1 <-> 2

        newNode->next = currentNode;
        currentNode->previous = newNode;

        hashMap->entries->head = newNode;
        return 0;
    }

    currentNode->previous->next = newNode;
    newNode->previous = currentNode->previous;
    currentNode->previous = newNode;
    newNode->next = currentNode;

    if (currentNode == hashMap->entries->tail && hashMap->f_comp(key, currentEntry->key) > 0)
    {
        hashMap->entries->tail = newNode;
    }

    return 0;
}

int print_hash_map(HashMap *hashMap)
{
    if (hashMap == NULL)
    {
        printf("ERROR: print_hash_map: *hashMap cannot be null\n");
        return 1;
    }
    if (hashMap->entries == NULL)
    {
        printf("ERROR: print_hash_map: hashMap->entries cannot be null (Probably using print_hash_map() before create_hash_map()\n");
        return 1;
    }

    Node *currentNode = hashMap->entries->head;
    for (int i = 0; i < hashMap->entries->size; i++)
    {
        printf("Printing element #%d\n", i);
        HashEntry *entry = currentNode->data;
        print_list(entry->values);
        currentNode = currentNode->next;
    }
}

void delete_hash_map(HashMap *hashMap)
{
    // hashMap
    // |
    //  ---entries
    //     |
    //      ---Node1
    //     |   |
    //     |   ---HashEntry
    //     |      |
    //     |       ---key
    //     |      |
    //     |       ---values (can delete it-self)
    //     |          |
    //     |           ---Node1
    //      ---Node2  |   |
    //     |   ...    |    --- data
    //     .          |
    //     |           ---Node2
    //      ---Node3  |   ...
    //         ...    .
    //                |
    //                 ---Node3
    //                    ...

    if (hashMap == NULL)
    {
        return;
    }

    if (hashMap->entries == NULL)
    {
        free(hashMap);
        return;
    }

    Node *currentNode = hashMap->entries->head;
    if (currentNode == NULL)
    {
        delete_list(hashMap->entries);
        free(hashMap);
        return;
    }

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        delete_hash_entry(currentNode->previous->data);
        free(currentNode->previous);
    }
    delete_hash_entry(currentNode->data);
    free(currentNode);
    free(hashMap->entries);
    free(hashMap);
}