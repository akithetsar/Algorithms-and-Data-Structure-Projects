//
// Created by akith on 12/20/2023.
//

#ifndef ASP2DO3_HELPER_H
#define ASP2DO3_HELPER_H
#include <string>

enum class AddressValidity{
    EMPTY, FULL, DELETED
};

struct Address{
    unsigned int key;
    std::string value;
    AddressValidity validity;
    Address() : key(-1), validity(AddressValidity::EMPTY) {}
};
#endif //ASP2DO3_HELPER_H
