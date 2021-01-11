#include <cassert>
using namespace std;


class Date {
    public:
        Date (int day, int month, int year) {
            Day(day);
            Month(month);
            Year(year);
        }
        void Day(int d) {
            if (1 <= d && d <= 31) day = d;
        }
        int Day() { return day; }
        void Month(int m) {
            if (1 <= m && m <= 12) month = m;
        }
        int Month() { return month; }
        void Year(int y) { year = y; }
        int Year() { return year; }
    private:
        int day{1};
        int month{1};
        int year{0};
};

int main() {
    Date date(8, 29, 1981);
    assert(date.Day() == 8);
    assert(date.Month() == 29);
    assert(date.Year() == 1981);
}
