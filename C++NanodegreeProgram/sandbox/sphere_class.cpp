#include <cassert>
#include <cmath>
#include <stdexcept>
using namespace std;


class Sphere {
    public:
        Sphere(int r) : radius_(r) {};
        int Radius() { return radius_; }
        float Volume() { return 4 * M_PI * pow(radius_, 3) / 3.; }
    private:
        int radius_{0};
};

int main() {
    Sphere sphere(5);
    assert(sphere.Radius() == 5);
    assert(abs(sphere.Volume() - 523.6) < 1);
}
