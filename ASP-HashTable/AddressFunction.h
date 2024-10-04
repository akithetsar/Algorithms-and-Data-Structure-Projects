//
// Created by akith on 12/20/2023.
//

#ifndef ASP2DO3_ADDRESSFUNCTION_H
#define ASP2DO3_ADDRESSFUNCTION_H
#include "Helper.h"

//Apstraktna klasa adresne funkcije koja implementira nalaženje sledeće adrese u razrešavanju kolizija

class AddressFunction{

public:
    virtual int getAddress(unsigned int key, int a, int i) const = 0;

};


#endif //ASP2DO3_ADDRESSFUNCTION_H
