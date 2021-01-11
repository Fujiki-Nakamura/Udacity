#include <cassert>
#include <string>
using namespace std;


class Person {
    public:
        Person(string name_) : name(name_) {};
        string name;
};

int main() {
    Person alice("Alice");
    Person bob("Bob");
    assert(alice.name != bob.name);
}
