//
// Created by akith on 12/20/2023.
//
#include "HashTable.h"

std::string *HashTable::findKey(unsigned int key) {
    int a = this->hash(key);
    int next = a;
    int numOfAccess = 0;
    for (int i = 0; i < size; i++) {
        numOfAccess++;
        if (table[next].validity == AddressValidity::EMPTY) {
            numOfAccessFailed += numOfAccess;
            numOfFails++;
            return nullptr;
        } else if (table[next].validity == AddressValidity::DELETED || table[next].key != key)
            next = hash(adrFunc->getAddress(key, a, i));
        else if (table[next].key == key) {
            numOfAccessSuccesfull += numOfAccess;
            numOfSuccesses++;
            return &(table[next].value);
        }

    }
    numOfAccessFailed += numOfAccess;
    numOfFails++;
    return nullptr;
}


bool HashTable::insertKey(unsigned int key, const std::string &value) {
    int a = this->hash(key);
    int next = a;
    if (size == numOfKeys) return false;


    for (int i = 0;; i++) {

        next = hash(adrFunc->getAddress(key, a, i));

        if (table[next].validity == AddressValidity::EMPTY || table[next].validity == AddressValidity::DELETED) {
            table[next].key = key;
            table[next].value = value;
            table[next].validity = AddressValidity::FULL;

            numOfKeys++;
            return true;
        } else if (table[next].key == key) return false;

    }

}

bool HashTable::deleteKey(unsigned int key) {
    int a = this->hash(key);
    int next = a;
    if (size == numOfKeys) return false;

    for (int i = 0; i < size; i++) {
        if (table[next].validity == AddressValidity::FULL && table[next].key != key)
            next = hash(adrFunc->getAddress(key, a, i));
        else if (table[next].validity == AddressValidity::EMPTY ||
                 table[next].validity == AddressValidity::DELETED)
            return false;
        else if (table[next].key == key) {
            table[next].validity = AddressValidity::DELETED;
            return true;
        }

    }
    return false;
}

int HashTable::avgAccessSucces() const {
    return numOfAccessSuccesfull / numOfSuccesses;
}

int HashTable::avgAccessUnsuccesEst() const {
    return 1 / (1 - fillRatio());
}

void HashTable::resetStatistics() {
    numOfSuccesses = 0;
    numOfAccessSuccesfull = 0;
    numOfFails = 0;
    numOfAccessFailed = 0;
}

void HashTable::clear() {
    for (int i = 0; i < size; i++) {
        table[i].validity = AddressValidity::EMPTY;
    }
    resetStatistics();
}

double HashTable::fillRatio() const {
    return keyCount() * 1.0 / size * 1.0;
}

std::ostream &operator<<(std::ostream &os, const HashTable ht) {
    for (int i = 0; i < ht.size; i++)
        os << ((ht.table[i].validity == AddressValidity::EMPTY || ht.table[i].validity == AddressValidity::DELETED)
               ? "EMPTY" : ht.table[i].value) << std::endl;
    return os;
}

unsigned int HashTable::hash(unsigned int key) const {
    return key % size;
}

int HashTable::avgAccessUnsucces() const {
    return numOfAccessFailed / numOfFails;
}

