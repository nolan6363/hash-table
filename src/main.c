#include <stdio.h>

#include "hashtable.h"

int main() {
    printf("Hello, World!\n");

    HashTable * table = createHashTable(6, 4);
    //printHashTable(table);
    
    char * name1 = "Thoma";
    char * name2 = "Marce";
    char * name3 = "Gauth";
    int age1 = 20;
    int age2 = 22;
    int age3 = 24;
    if (HTInsert(table, name1, &age1)) {
        printf("erreur adding to hash table\n");
    }
    if (HTInsert(table, name2, &age2)) {
        printf("erreur adding to hash table\n");
    }
    if (HTInsert(table, name3, &age3)) {
        printf("erreur adding to hash table\n");
    }
    printHashTable(table);
    int ageRecup = 0;

    if (HTGet(table, name1, &ageRecup)) {
        printf("erreur getting the value\n");
    } else {
        printf("age got for %s : %d\n", name1, ageRecup);
    }

    if (HTGet(table, name3, &ageRecup)) {
        printf("erreur getting the value\n");
    }
    else {
        printf("age got for %s : %d\n", name3, ageRecup);
    }
    
    /*
    printf("hash of Nolan is %d\n", hash("Nolan", 6) % 16);
    printf("hash of Loris is %d\n", hash("Loris", 6) % 16);
    printf("hash of Thoma is %d\n", hash("Thoma", 6) % 16);
    printf("hash of Bayon is %d\n", hash("Bayon", 6) % 16);
    printf("hash of Engue is %d\n", hash("Engue", 6) % 16);
    printf("hash of Cleme is %d\n", hash("Cleme", 6) % 16);
    printf("hash of Gauth is %d\n", hash("Gauth", 6) % 16);
    printf("hash of Marce is %d\n", hash("Marce", 6) % 16);
    printf("hash of Alien is %d\n", hash("Alien", 6) % 16);
    printf("hash of Thais is %d\n", hash("Thais", 6) % 16);
    printf("hash of Sasha is %d\n", hash("Sasha", 6) % 16);
    */ 
    return 0;
}
