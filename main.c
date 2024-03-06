#include <stdio.h>
#include "List.h"

void print_node(Node *node)
{
    printf("NULL");
}

int main()
{
    List *l = create_list();

    insert(l, NULL, 0);
    print(l, &print_node);
    return 0;
}