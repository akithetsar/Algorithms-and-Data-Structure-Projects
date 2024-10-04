cmake_minimum_required(VERSION 3.24)
project(asp2do3)

set(CMAKE_CXX_STANDARD 17)

add_executable(asp2do3 main.cpp AddressFunction.h QuadraticHashing.h QuadraticHashing.cpp HashTable.h HashTable.cpp Helper.h AdaptiveHashTable.h AdaptiveHashTable.cpp)
