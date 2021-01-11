#include <iostream>
#include <string>
using namespace std;


class Animal {
    public:
        string color;
        string name;
        int age;
};

class Snake : public Animal {
    public:
        Snake(string c, string n, int a, int l) : length(l) {
            color = c;
            name = n;
            age = a;
        };
        int length;
        void MakeSound() {
            printf("Snake - Name %s Color %s Age %d Length %d\n", name.c_str(), color.c_str(), age, length);
        }
};

class Cat : public Animal {
    public:
        Cat(string c, string n, int a, int h) : height(h) {
            color = c;
            name = n;
            age = a;
        };
        int height;
        void MakeSound() {
            printf("Cat - Name %s Color %s Age %d Height %d\n", name.c_str(), color.c_str(), age, height);
        }
};

int main() {
    Snake snake("green", "snake1", 1, 10);
    Cat cat("white", "cat1", 2, 2);
    snake.MakeSound();
    cat.MakeSound();
}
