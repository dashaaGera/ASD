#include <iostream>
#include <string>
#include "../lib_binary_tree/binary_tree.h"
int main() {

        Tree<int, char> t;
        t.insert(1, 'R');
        t.insert(2, 'C');
        t.insert(3, 'A');
        t.insert(4, 'D');
        t.insert(5, 'E');
        t.insert(6, 'F');
        t.insert(7, 'B');
        t.insert(8, 'U');
        t.insert(9, 'T');
        t.insert(10, 'O');
        t.insert(11, 'K');
        t.print();
 
}