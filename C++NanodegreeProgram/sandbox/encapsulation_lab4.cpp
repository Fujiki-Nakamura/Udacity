#include <cassert>
#include <stdexcept>
#include <iostream>
using namespace std;

class Pyramid {
    private:
        int length{1};
        int width{1};
        int height{1};
    public:
        Pyramid(int l, int w, int h) {
            if (l > 0 && w > 0 && h > 0) {
                length = l;
                width = w;
                height = h;
            } else { throw invalid_argument("Negative value(s)"); }
        }
        int Length() const;
        int Width() const;
        int Height() const;
        int Volume() const;
};

int Pyramid::Length() const { return Pyramid::length; }
int Pyramid::Width() const { return Pyramid::width; }
int Pyramid::Height() const { return Pyramid::height; }
int Pyramid::Volume() const { return (Pyramid::length * Pyramid::width * Pyramid::height) / 3; }


int main() {
    Pyramid pyramid(4, 5, 6);
    assert(pyramid.Length() == 4);
    assert(pyramid.Width() == 5);
    assert(pyramid.Height() == 6);
    assert(pyramid.Volume() == 40);

    bool caught{false};
    try {
        Pyramid invalid(-1, 2, 3);
    } catch (...) {
        caught = true;
    }
    assert(caught);
}
