//
// Created by akith on 12/20/2023.
//
#include "QuadraticHashing.h"


int QuadraticHashing::getAddress(unsigned int key, int a, int i) const {
    return a + i*c1 + i*i*c2;
}

