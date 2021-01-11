#include <iostream>
using namespace std;


class Car {
    public:
    Car(string c, int n) {
        color = c;
        number = n;
    }
    string color;
    int number;
    int distance = 0;

    void IncrementDistance() {
        distance++;
    }
    void PrintCarData() {
        cout << "Color: " << color << " Number: " << number << " Distance: " << distance << endl;
    }
};


int main() {
    Car car_1 = Car("green", 1);
    Car car_2 = Car("red", 2);
    Car car_3 = Car("blue", 3);
    car_1.IncrementDistance();
    car_1.PrintCarData();
    car_2.PrintCarData();
    car_3.PrintCarData();
}
