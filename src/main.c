#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"

void f_print(void *value)
{
    printf("%s\n", (char *)value);
}

void *f_hash(void *value)
{
    unsigned char *str = (unsigned char *)value;
    unsigned long *hash = (unsigned long *)malloc(sizeof(long));
    if (hash == NULL)
    {
        printf("ERROR: Failed to allocate hash\n");
        return NULL;
    }
    *hash = 0;
    int c;
    while (c = *str++)
    {
        *hash = c + (*hash << 6) + (*hash << 16) - *hash;
    }
    // f_print(value);
    // printf("hash: %lu\n", *hash);
    return hash;
}

int f_comp(void *key1, void *key2)
{
    long diff = *(unsigned long *)key1 - *(unsigned long *)key2;
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
    char *str1 = "kebab";
    char *str2 = "abcde";
    char *str3 = "12345";
    char *str4 = "PRoz1";
    char *str5 = "yo";
    char *str6 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    HashMap *hm = create_hash_map(&f_hash, &f_comp, &f_print);

    int success = insert(hm, str1);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }
    success = insert(hm, str2);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }
    success = insert(hm, str2);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }
    success = insert(hm, str3);
    insert(hm, str4);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }
    success = insert(hm, str4);
    insert(hm, str5);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }
    success = insert(hm, str6);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }
    success = insert(hm, str6);
    if (success != 0)
    {
        delete_hash_map(hm);
        return 1;
    }

    printf("Before remove:\n");
    print_hash_map(hm);

    unsigned long *htest = f_hash(str4);
    char *strtest = remove_value(hm, htest);
    free(htest);
    printf("After remove:\n");
    print_hash_map(hm);

    delete_hash_map(hm);
    return 0;
}