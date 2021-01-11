#include <iostream>
#include <string>
using namespace std;


class BankAccount {
    public:
        BankAccount(int number, string name, int fund);
        void Number(int number);
        int Number() const { return number_; };
        void Name(string name);
        string Name() const { return name_; };
        void Fund(int fund);
        int Fund() { return fund_; };
    private:
        int number_;
        string name_;
        int fund_;
};

BankAccount::BankAccount(int number, string name, int fund) {
    Number(number);
    Name(name);
    Fund(fund);
}

void BankAccount::Number(int number) { number_ = number; }
void BankAccount::Name(string name) { name_ = name; }
void BankAccount::Fund(int fund) { fund_ = fund; }
// int BankAccount::Number() const { return number_; }
// int BankAccount::Number() const { return number_; }
// int BankAccount::Number() const { return number_; }

int main() {
    BankAccount ba1(1, "Alice", 100);
    printf("Account Number: %d Owner Name: %s Available Funds: %d\n", ba1.Number(), ba1.Name(), ba1.Fund());
}
