#include <cassert>
#include <string>
#include <sstream>
using namespace std;

template <typename KeyType, typename ValueType>
class Mapping {
    public:
        Mapping(KeyType key, ValueType value) : key_(key), value_(value) {};
        string Print() const {
            ostringstream stream;
            stream << key_ << ": " << value_;
            return stream.str();
        }
    private:
        KeyType key_;
        ValueType value_;
};

int main() {
    Mapping<string, int> mapping("age", 20);
    assert(mapping.Print() == "age: 20");
}
