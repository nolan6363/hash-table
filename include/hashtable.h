#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STARTING_HT_SIZE 16

typedef struct {
    void * key;
    void * value;
} KV;

typedef struct {
    KV * table;
    size_t tableSize;
    size_t keySize;
    size_t valueSize;
} HashTable;

HashTable * createHashTable(size_t keySize, size_t valueSize);
void printHashTable(HashTable * hashTable);
unsigned int hash(void * key, size_t key_size);
int HTInsert(HashTable * hashTable, void * key, void * value);
int HTGet(HashTable * hashTable, void * key, void * value);
