#ifndef _HASH_H_
#define _HASH_H_

/**
 * struct HashTable - Structure hash table
 * 
 * @key: index
 * @value: data
 * 
 * Description: This structure help to store key and value
*/
struct HashTable {

    int key;
    char *value;

};

typedef struct HashTable HashTable;

#endif