#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
using namespace std;

class Sphere {
    public:
        Sphere(int radius) : radius_(radius), volume_(CalcVolume(radius_)) {
            ValidateRadius(radius_);
        }
        void Radius(int radius) {
            ValidateRadius(radius);
            radius_ = radius;
            volume_ = CalcVolume(radius_);
        }
        int Radius() const { return radius_; }
        float Volume() const { return volume_; }

    private:
        float const pi_{3.14159};
        int radius_;
        float volume_;
        void ValidateRadius(int radius) {
            if (radius <= 0) throw invalid_argument("radius must be positive");
        }
        float CalcVolume(int radius) { return pi_ * 4 / 3 * pow(radius_, 3); }
};


int main() {
    Sphere sphere(5);
    assert(sphere.Radius() == 5);
    assert(abs(sphere.Volume() - 523.6) < 1);

    sphere.Radius(3);
    assert(sphere.Radius() == 3);
    assert(abs(sphere.Volume() - 113.1) < 1);

    bool caught{false};
    try {
        sphere.Radius(-1);
    } catch (...) {
        caught = true;
    }
    assert(caught);
}
