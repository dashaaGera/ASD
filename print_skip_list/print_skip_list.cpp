#include <iostream>
#include <iomanip>
#include "../lib_skip_list/skip_list.h"
int main() {

    SkipList<int, double> list(8);
    list.insert(1, 12.15);
    list.insert(2, 4.0);
    list.print();
    list.insert(6, 7.523);
    list.insert(13, 87.2);
    list.insert(234, 78.5);
    list.insert(634, 5.8);
    list.print();
    list.insert(655, 58.4238);
    list.insert(7654, 8.769455);
    list.print();


    return 0;
}