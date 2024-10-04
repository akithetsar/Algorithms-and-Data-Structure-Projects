//
// Created by akith on 12/20/2023.
//

#ifndef ASP2DO3_QUADRATICHASHING_H
#define ASP2DO3_QUADRATICHASHING_H
#include "AddressFunction.h"

//Specijalizacija adresne funkcije za kvadratno adresiranje

class QuadraticHashing : public AddressFunction{

public:
    QuadraticHashing(int c1, int c2) : c1(c1), c2(c2) {}

    int getAddress(unsigned int key, int a, int i) const override;

private:
    int c1, c2;

};


#endif //ASP2DO3_QUADRATICHASHING_H
