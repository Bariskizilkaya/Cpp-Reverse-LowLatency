/*
g++ -O0 -g3 -std=c++20 -o ./out/1 1.cpp
*/


#include <iostream>


struct Car
{
    /* data */
    std::string brand;
    std::string model;
    int year;
};


int main()
{
    Car car1{"Toyota", "Corolla", 2020};
    Car car2{"Honda", "Civic", 2019};
    return 0;
}