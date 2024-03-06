#include <stdio.h>
#include "List.h"

void print_node(Node *node)
{
    if (node->previous != NULL)
    {
        printf("%d <- ", *(int *)node->previous->data);
    }
    else
    {
        printf("NULL <- ");
    }

    printf("%d", *(int *)node->data);

    if (node->next != NULL)
    {
        printf(" -> %d", *(int *)node->next->data);
    }
    else
    {
        printf(" -> NULL");
    }
    printf("\n");
}

int main()
{
    List *l = create_list();
    if (l == NULL)
    {
        printf("ERROR: Failed to create a list. Closing\n");
        return 1;
    }
    const int N_COUNT = 10;
    int ns[N_COUNT];
    for (int i = 0; i < N_COUNT; i++)
    {
        ns[i] = i;
        if (push(l, &ns[i]) != 0)
        {
            printf("ERROR: Push failed. Closing\n");
            return 1;
        }
    }

    printf("Initialization complete\n");

    print(l, &print_node);
    delete_list(l);
    return 0;
}