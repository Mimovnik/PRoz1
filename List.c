#include "List.h"
#include <stdlib.h>
#include <stdio.h>

Node *create_node(void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

List *create_list(void (*f_print)(Node *))
{
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->f_print = f_print;
    return list;
}

int push(List *list, void *data)
{
    if (list == NULL)
    {
        printf("ERROR: push: '*list' can't be null\n");
        return 1;
    }

    Node *newNode = create_node(data);
    if (newNode == NULL)
    {
        printf("ERROR: Failed to create a node\n");
        return 1;
    }

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = list->head;
        list->size++;
        return 0;
    }

    list->tail->next = newNode;
    newNode->previous = list->tail;
    list->tail = newNode;

    list->size++;
    return 0;
}

void print_list(List *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        list->f_print(currentNode);
        currentNode = currentNode->next;
    }
}

void delete_list(List *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *currentNode = list->head;
    if (currentNode == NULL)
    {
        return;
    }
    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        free(currentNode->previous);
    }
    free(currentNode);
    free(list);
}