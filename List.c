#include "List.h"
#include <stdlib.h>
#include <stdio.h>

Node *create_node(void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

List *create_list()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int insert(List *list, void *data, int index)
{
    if (list == NULL)
    {
        printf("ERROR: List can't be null\n");
        return 1;
    }
    if (index < 0 || index > list->size)
    {
        printf("ERROR: Index is out of bound\n");
        return 1;
    }

    Node *newNode = create_node(data);

    if (list->head == NULL)
    {
        printf("Inserting the first element.\n");
        list->head = newNode;
        list->tail = list->head;
        list->size++;
        return 0;
    }

    Node *atIndex = list->head;
    for (int i = 0; i < index; i++)
    {
        printf("atIndex is null (Probaly inserting at the end). i: %d", i);
        atIndex = atIndex->next;
    }

    if (index == 0)
    {
        printf("Inserting at the front.\n");
        list->head = newNode;
        newNode->next = atIndex;
        atIndex->previous = newNode;
        list->size++;
        return 0;
    }

    if (index == list->size)
    {
        printf("Inserting at the end.\n");
        list->tail->next = newNode;
        newNode->previous = list->tail;
        list->tail = newNode;
        list->size++;
        return 0;
    }

    printf("Inserting at index: %d.", index);
    atIndex->previous->next = newNode;
    newNode->previous = atIndex->previous->next;
    atIndex->previous = newNode;
    newNode->next = atIndex;
    return 0;
}

void print(List *list, void (*f_print)(Node *))
{
    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        f_print(currentNode);
        currentNode = currentNode->next;
    }
}