#include <cassert>
using namespace std;


template <typename T> T Product(T a, T b) {
    return a * b;
}

int main() {
    assert(Product<int>(10, 2) == 20);
    assert(Product<float>(10.0, 2.0) == 20.0);
}
