#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"

void f_print(void *value)
{
    printf("value: %s\n", (char *)value);
}

void *f_hash(void *value)
{
    unsigned char *str = (unsigned char *)value;
    // djb2
    unsigned long *hash = (unsigned long *)malloc(sizeof(long));
    if (hash == NULL)
    {
        printf("ERROR: Failed to allocate hash\n");
        return NULL;
    }
    *hash = 5381;
    int c;
    while (c = *str++)
    {
        *hash = ((*hash << 5) + *hash) + c; /* hash * 33 + c */
    }
    return hash;
}

int f_comp(void *key1, void *key2)
{
    unsigned long diff = *(unsigned long *)key1 - *(unsigned long *)key2;
    if (diff == 0)
    {
        return 0;
    }
    else if (diff > 0)
    {
        return 1;
    }
    return -1;
}

int main()
{
    char *str1 = "abc";
    char *str2 = "banan";
    char *str3 = "kebab";
    char *str4 = "1234";

    HashMap *hm = create_hash_map(&f_hash, &f_comp, &f_print);
    insert(hm, str1);
    insert(hm, str2);
    insert(hm, str1);
    insert(hm, str2);

    insert(hm, str1);
    insert(hm, str2);
    insert(hm, str3);
    insert(hm, str4);

    insert(hm, str3);
    insert(hm, str2);
    insert(hm, str1);
    insert(hm, str4);
    print_hash_map(hm);

    delete_hash_map(hm);
    return 0;
}