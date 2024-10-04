#include <iostream>
#include "HashTable.h"
#include "AddressFunction.h"
#include "QuadraticHashing.h"
#include "AdaptiveHashTable.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


void statistics(HashTable &ht, int num_of_test_cases) {
    srand(time(0));
    for (int i = 0; i < num_of_test_cases; i++) {
        int test_key = rand() % 9999999 + 1000000;
        ht.findKey(test_key);
    }

    std::cout << ht.avgAccessSucces() << std::endl;
    std::cout << ht.avgAccessUnsucces() << std::endl;
}


int main() {




    AddressFunction *adrF = new QuadraticHashing(1, 3);
    HashTable *ht = new HashTable(10000, adrF);
    int opcija;
    std::cout << "Izaberite vrstu tabele: " << std::endl;
    std::cout << "1. Obicna" << std::endl;
    std::cout << "2. Adaptivna" << std::endl;
    std::cin >> opcija;
    int size;
    std::cout << "Duzina tabele? ";
    std::cin >> size;
    if(opcija == 1)  ht = new HashTable(size, adrF);
    else ht = new AdaptiveHashTable(size, adrF);
    std::string dat;
    std::cout << "Unesi datoteku? ";
    std::cin >> dat;
    if(dat != "0"){
        int i = 0;
        std::ifstream myfile(dat);

        if (!myfile.is_open()) {
            std::cout << "Could not open file!\n";
            return -1;
        }

        std::string line;
        int nof;
        while (getline(myfile, line)) {
            std::vector<std::string> res;
            int pos = 0;
            for (int i = 0; i < 2; i++) {
                pos = line.find('\t');
                res.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }

            if (ht->insertKey(std::stoll(res[1]), res[0])) nof++;
        }
    }


    while(true){
        int opcija;
        std::cout << std::endl;
        std::cout << "Opcije: " << std::endl;
        std::cout << "0. Izadji" << std::endl;
        std::cout << "1. Ispisi tabelu" << std::endl;
        std::cout << "2. Nadji kljuc" << std::endl;
        std::cout << "3. Insert kljuc" << std::endl;
        std::cout << "4. Delete kljuc" << std::endl;
        std::cout << "5. AvgUnsuccessEstimate?" << std::endl;
        std::cout << "6. Statistics?" << std::endl;
        std::cout << "7. Reset Statistics" << std::endl;
        std::cout << "8. Clear table" << std::endl;
        std::cout << "9. Key count" << std::endl;

        std::cin >> opcija;

        std::cout << std::endl;

        bool to_break = false;
        int key;
        std::string st;
        switch (opcija) {

            case 0:
                to_break = true;
                break;
            case 1:
                std::cout << *ht << std::endl;
                break;
            case 2:
                std::cout << "Kljuc? ";
                std::cin >> key;
                ht->findKey(key);
                break;
            case 3:
                std::cout << "Kljuc? ";
                std::cin >> key;
                std::cout << "String? ";
                std::cin >> st;
                ht->insertKey(key, st);
                break;
            case 4:
                std::cout << "Kljuc? ";
                std::cin >> key;
                ht->deleteKey(key);
                break;
            case 5:
                std::cout << ht->avgAccessUnsuccesEst() << std::endl;
                break;
            case 6:
                statistics(*ht, size*10);
                break;
            case 7:
                ht->resetStatistics();
                break;
            case 8:
                ht->clear();
                break;
            case 9:
                std::cout << ht->keyCount() << std::endl;
                break;
        }
        if(to_break) break;
    }


    delete ht;

    return 0;
}
