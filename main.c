#include <stdio.h>
#include "List.h"

void print_node(Node *node)
{
    printf("%d\n", *(int *)node->data);
}

int main()
{
    List *l = create_list();

    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    insert(l, &n1, 0);
    insert(l, &n2, 1);
    insert(l, &n3, 1);

    print(l, &print_node);
    return 0;
}