#include <string>
#include <cstring>
#include <iostream>
using namespace std;


class Car {
    private:
        int horsepower_{0};
        float weight_{0.f};
        char brand_[100]{"No Brand"};
    public:
        // Car (int hp, float w, string b);
        void SetHorsepower(int hp);
        void SetWeight(float w);
        void SetBrand(string b);
        int GetHorsepower() const;
        float GetWeight() const;
        string GetBrand() const;
};

void Car::SetHorsepower(int hp) {
    Car::horsepower_ = hp;
}
void Car::SetWeight(float w) {
    Car::weight_ = w;
}
void Car::SetBrand(string b) {
    // Car::brand_ = b.c_str();
    strcpy(Car::brand_, b.c_str());
}
int Car::GetHorsepower() const { return Car::horsepower_; }
float Car::GetWeight() const { return Car::weight_; }
string Car::GetBrand() const {
    string s(Car::brand_);
    return s;
}

int main() {
    Car car;
    car.SetBrand("Peugeot");
    cout << car.GetBrand() << endl;
}
