#include <stdlib.h>

#include "hashtable.h"

// FNV-1a constants for 32 bits
#define FNV_OFFSET_BASIS_32 2166136261u
#define FNV_PRIME_32 16777619u

#define DELETE_PTR (void *) 0xFFFFFFFFFFFFFFFF

//from http://en.wikipedia.org/wiki/Circular_shift
unsigned int _rotl(unsigned int value, int shift) {
    if ((shift &= 31) == 0)
      return value;
    return (value << shift) | (value >> (32 - shift));
}

HashTable * createHashTable(size_t keySize, size_t valueSize, size_t initialSize) {
    HashTable * hashTable = (HashTable *) malloc(sizeof(HashTable));
    if(initialSize == 0) {
        hashTable->tableSize = STARTING_HT_SIZE;
    }
    else {
        hashTable->tableSize = initialSize;
    }
    hashTable->table = (KV *) calloc(hashTable->tableSize, sizeof(KV));
    hashTable->keySize = keySize;
    hashTable->valueSize = valueSize;
    hashTable->occupancy = 0;

    return hashTable;
}

void printHashTable(HashTable * hashTable) {
    for (size_t i = 0; i < hashTable->tableSize; i++) {
        printf("[%ld] ==> ", i);
        if (hashTable->table[i].key == NULL) {
            printf("---");
        }
        else if (hashTable->table[i].key == DELETE_PTR) {
            printf("<deleted>");
        }
        else {
            printf("0x");
            for (size_t hex_pos = 0; hex_pos < hashTable->keySize; hex_pos++) {
                printf("%02x", ((uint8_t *) hashTable->table[i].key)[hex_pos]);
            }
            printf(" : ");
            for (size_t hex_pos = 0; hex_pos < hashTable->valueSize; hex_pos++) {
                printf("%02x", ((uint8_t*) hashTable->table[i].value)[hex_pos]);
            }
        }
        printf("\n");
    }
}

//from https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
unsigned int hash(void * key, size_t len) {
    unsigned int hash = FNV_OFFSET_BASIS_32;
    
    for (size_t i = 0; i < len; i++) {
        hash ^= ((char *) key)[i];
        hash *= FNV_PRIME_32;
    }
    
    return hash;    
}

int HTInsert(HashTable * hashTable, void * key, void * value) {
    HTScaleIfNeeded(hashTable);
    unsigned int pos = hash(key, hashTable->keySize) % hashTable->tableSize;
    for (int i = 0; i < hashTable->tableSize; i++) {
        if (hashTable->table[pos].key == NULL || hashTable->table[pos].key == DELETE_PTR) {
            hashTable->table[pos].key = (void *) malloc(hashTable->keySize);
            hashTable->table[pos].value = (void *) malloc(hashTable->valueSize);
            memcpy(hashTable->table[pos].key, key, hashTable->keySize);
            memcpy(hashTable->table[pos].value, value, hashTable->valueSize);
            hashTable->occupancy += 1;

            return 0;
        } 
        else {
            pos = (pos + 1) % hashTable->tableSize;

            continue; 
        }
    }
    return 1;
}

int HTGet(HashTable * hashTable, void * key, void * value) {
    unsigned int pos = hash(key, hashTable->keySize) % hashTable->tableSize;

    for (int i = 0; i < hashTable->tableSize; i++) {
        if (hashTable->table[pos].key == NULL) {
            return 1;
        }
        else if (hashTable->table[pos].key != DELETE_PTR && memcmp(key, hashTable->table[pos].key, hashTable->keySize) == 0) {
            memcpy(value, hashTable->table[pos].value, hashTable->valueSize);
            return 0;
        }
        else {
            pos = (pos + 1) % hashTable->tableSize;
            continue;
        }
    }

    return 1;
}

int HTDelete(HashTable * hashTable, void * key) {
    unsigned int pos = hash(key, hashTable->keySize) % hashTable->tableSize;

    for (int i = 0; i < hashTable->tableSize; i++) {
        if (hashTable->table[pos].key == NULL) {
            return 1;
        }
        else if (memcmp(key, hashTable->table[pos].key, hashTable->keySize) == 0) {
            free(hashTable->table[pos].key);
            free(hashTable->table[pos].value);
            hashTable->table[pos].key = DELETE_PTR;
            hashTable->table[pos].value = DELETE_PTR;
            hashTable->occupancy -= 1;

            return 0;
        }
        else {
            pos = (pos + 1) % hashTable->tableSize;
            continue;
        } 
    }

    return 1;
}

int HTScaleIfNeeded(HashTable * oldHashTable) {
    if (oldHashTable->occupancy < oldHashTable->tableSize * 0.75) {
        return 0;
    }
    else {
        HashTable * newHashTable = createHashTable(oldHashTable->keySize, oldHashTable->valueSize, oldHashTable->tableSize * 2);

        for (size_t i = 0; i < oldHashTable->tableSize; i++) {
            if (oldHashTable->table[i].key == NULL || oldHashTable->table[i].key == DELETE_PTR) {
                continue;
            }
            else {
                HTInsert(newHashTable, oldHashTable->table[i].key, oldHashTable->table[i].value);
            }
        }
        free(oldHashTable->table);
        memcpy(oldHashTable, newHashTable, sizeof(HashTable));
        return 1;
    }
}
