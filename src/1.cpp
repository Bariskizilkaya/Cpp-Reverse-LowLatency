/*
g++ -O0 -g3 -std=c++20 -o ./out/1 1.cpp
*/


#include <iostream>


class Car
{
private:
    /* data */
    std::string brand;
    std::string model;
    int year;
public:
    Car(std::string b, std::string m, int y) : brand(b), model(m), year(y) {
        std::cout << "Car created: " << brand << " " << model << " (" << year << ")" << std::endl;
    }
};



int main()
{
    Car car1("Toyota", "Corolla", 2020);
    Car car2("Honda", "Civic", 2019);
    return 0;
}