#include <stdio.h>

#include "hashtable.h"

int main() {
    HashTable * table = createHashTable(6, 4, 0);
    //printHashTable(table);
    
    char * name1 = "Eytha";
    char * name2 = "Nolan";
    char * name3 = "Samue";
    char * name4 = "Bayon";
    char * name5 = "Aliss";

    int age1 = 20;
    int age2 = 22;
    int age3 = 24;
    int age4 = 26;
    int age5 = 28;

    if (HTInsert(table, name1, &age1)) {
        printf("error adding to hash table\n");
    }
    if (HTInsert(table, name2, &age2)) {
        printf("error adding to hash table\n");
    }
    if (HTInsert(table, name3, &age3)) {
        printf("error adding to hash table\n");
    }
    printHashTable(table);

    if (HTDelete(table, name1)) {
        printf("error deleting to hash table\n");
    }
    printHashTable(table);
    
    if (HTInsert(table, name4, &age4)) {
        printf("error adding to hash table\n");
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

    if (HTGet(table, name4, &ageRecup)) {
        printf("erreur getting the value\n");
    }
    else {
        printf("age got for %s : %d\n", name4, ageRecup);
    }

    if (HTInsert(table, name4, &age4)) {
        printf("error adding to hash table\n");
    }
    printHashTable(table);

    
    printf("final table occupancy : %ld\n", table->occupancy);
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
    printf("hash of Guisk is %d\n", hash("Guisk", 6) % 16);
    printf("hash of Romai is %d\n", hash("Romai", 6) % 16);
    printf("hash of Romeo is %d\n", hash("Romeo", 6) % 16);
    printf("hash of Aliss is %d\n", hash("Aliss", 6) % 16);
    printf("hash of Jade  is %d\n", hash("Jade ", 6) % 16);
    printf("hash of Jimmy is %d\n", hash("Jimmy", 6) % 16);
    printf("hash of Eytha is %d\n", hash("Eytha", 6) % 16);
    printf("hash of Nyna  is %d\n", hash("Nyna ", 6) % 16);
    printf("hash of Loren is %d\n", hash("Loren", 6) % 16);
    printf("hash of Samue is %d\n", hash("Samue", 6) % 16);
    */ 
    return 0;
}
