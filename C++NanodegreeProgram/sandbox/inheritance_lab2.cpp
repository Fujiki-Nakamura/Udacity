#include <iostream>
#include <cmath>
#include <assert.h>
#define pi 3.14159
using namespace std;

class LineSegment {
    public:
        LineSegment(int l) : length(l) {};
        int length;
};

class Circle {
    public:
        Circle(LineSegment ls) : radius(ls) {};
        LineSegment radius;
        float Area() {
            return pi * pow(radius.length, 2);
        }
};

int main() {
    LineSegment radius {3};
    Circle circle(radius);
    assert(int(circle.Area()) == 28);
}
