#include <stdio.h>

#include "hashtable.h"

int main() {
    printf("Hello, World!\n");

    HashTable * table = createHashTable(6, 4);
    //printHashTable(table);
    
    char * name = "Nolan";
    int age = 20;
    if (HTInsert(table, name, &age)) {
        printf("erreur adding to hash table\n");
    }
    printHashTable(table);
    int ageRecup = 0;
    if (HTGet(table, name, &ageRecup)) {
        printf("erreur getting the value\n");
    }
    printf("age got : %d\n", ageRecup);
    
    return 0;
}
