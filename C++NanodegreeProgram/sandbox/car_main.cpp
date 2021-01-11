#include <iostream>
#include <string>
#include "car.h"
using namespace std;

int main() {
    Car car_1 = Car("green", 1); 
    Car car_2 = Car("red", 2); 
    Car car_3 = Car("blue", 3); 
    car_1.IncrementDistance();
    car_1.PrintCarData();
    car_2.PrintCarData();
    car_3.PrintCarData();
}
