#include <iostream>
#include <assert.h>
using namespace std;

class Point {
    public:
        Point (int xx, int yy) : x(xx), y(yy) {};
        int x;
        int y;
        Point operator+(Point p) {
            return Point(x + p.x, y + p.y);
        }
};

int main() {
    Point p1(10, 5), p2(2, 4);
    Point p3 = p1 + p2;
    assert(p3.x == p1.x + p2.x);
    assert(p3.y == p1.y + p2.y);
}
