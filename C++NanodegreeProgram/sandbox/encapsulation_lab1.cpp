#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


class Student {
    public:
        Student (string name, int grade, float gpa) {
            ValidateName(name);
            ValidateGrade(grade);
            ValidateGPA(gpa);
            name_ = name;
            grade_ = grade;
            gpa_ = gpa;
        };
        void setGrade(int g) {
            ValidateGrade(g);
            grade_ = g;
        };
        void setGPA(float gpa) {
            ValidateGPA(gpa);
            gpa_ = gpa;
        }
    private:
        string name_;
        int grade_;
        float gpa_;
        void ValidateName(string n) {
            if (n.length() <= 0) { throw invalid_argument("Invalid name length"); }
        }
        void ValidateGrade(int g) {
            if (g < 0 || 13 < g) { throw invalid_argument("Invalid grade"); }
        }
        void ValidateGPA(float gpa) {
            if (gpa < 0 || 4.0 < gpa) { throw invalid_argument("Invalid GPA"); }
        }
};

int main() {
    Student alice("Alice", 1, 4);

    bool caught{false};
    try {
        Student bob("Bob", -1, 100);
    } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try {
        alice.setGrade(-1);
    } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try {
        alice.setGrade(100);
    } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try {
        alice.setGPA(-1);
    } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try {
        alice.setGPA(100);
    } catch (...) { caught = true; }
    assert(caught);
}
