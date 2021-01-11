#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

class Car {
    public:
        void PrintCarData();
        void IncrementDistance();
        Car(string c, int n) : color(c), number(n) {}
    private:
        string color;
        int number;
        int distance = 0;
};

#endif
