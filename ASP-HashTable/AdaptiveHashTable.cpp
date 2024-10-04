//
// Created by akith on 12/24/2023.
//
#include "AdaptiveHashTable.h"
#include "Helper.h"
bool AdaptiveHashTable::insertKey(unsigned int key, const std::string &value) {
    bool is_inserted = HashTable::insertKey(key, value);
    if(fillRatio() > 0.75){

        Address *new_table = new Address[size*2];
        for(int i = 0; i < size; i++){
            new_table[i] = table[i];
        }
        size *= 2;

        table = new_table;
    }

    return is_inserted;
}

