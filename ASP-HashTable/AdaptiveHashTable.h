//
// Created by akith on 12/24/2023.
//

#ifndef ASP2DO3_ADAPTIVEHASHTABLE_H
#define ASP2DO3_ADAPTIVEHASHTABLE_H
#include "HashTable.h"
class AdaptiveHashTable : public HashTable{
public:
    AdaptiveHashTable(int size, const AddressFunction *adrFunc) : HashTable(size, adrFunc) {}

    bool insertKey(unsigned int key, const std::string &value) override;
};
#endif //ASP2DO3_ADAPTIVEHASHTABLE_H
