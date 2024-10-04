//
// Created by akith on 12/20/2023.
//

#ifndef ASP2DO3_HASHTABLE_H
#define ASP2DO3_HASHTABLE_H
#include "AddressFunction.h"
#include "Helper.h"

#include <string>
#include <iostream>
#include <vector>



class HashTable{

public:
    HashTable(int size, const AddressFunction *adrFunc) : adrFunc(adrFunc), table(new Address[size]), size(size), numOfKeys(0), numOfAccessSuccesfull(0),  numOfAccessFailed(0), numOfFails(0), numOfSuccesses(0) {}

    std::string* findKey(unsigned int key);
    virtual bool insertKey(unsigned int key, const std::string &value);
    bool deleteKey(unsigned int key);
    int avgAccessSucces() const;
    int avgAccessUnsuccesEst() const;
    int avgAccessUnsucces() const;
    void resetStatistics();
    void clear();
    int keyCount() const { return numOfKeys; }
    int tableSize() const { return size; }
    double fillRatio() const;

    friend std::ostream& operator<<(std::ostream& os, HashTable ht);

protected:
    int numOfKeys;
    int size;
    Address *table;
private:
    const AddressFunction *adrFunc;
    int numOfAccessFailed, numOfAccessSuccesfull;
    int numOfFails, numOfSuccesses;

    unsigned int hash(unsigned int key) const;


};

#endif //ASP2DO3_HASHTABLE_H
