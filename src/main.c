#include <stdio.h>

#include "hashtable.h"

int main() {
    printf("Hello, World!\n");

    HashTable * table = createHashTable(4, 4);
    printHashTable(table);
    
    printf("[Nolan] ==> %u\n", hash("Nolan", 6));
    printf("[Bayon] ==> %u\n", hash("Bayon", 6));
    int num = 14;
    printf("[14] ==> %u\n", hash(&num, 4));
    printf("[Hello, World!] ==> %u\n", hash("Hello, World!", 12));
    int tab[4] = {12, 14, 67, 69};
    printf("[{12, 14, 67, 69}] ==> %u\n", hash(tab, 16));
    long int bignum = 6789437895;
    printf("[6789437895] ==> %u\n", hash(&bignum, 8));

    return 0;
}
