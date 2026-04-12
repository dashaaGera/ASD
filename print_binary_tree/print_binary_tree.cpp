#include <iostream>
#include <string>
#include "../lib_binary_tree/binary_tree.h"
#include "../lib_avl_tree/avl_tree.h"
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
        t.print_tree();


        std::cout << "" << std::endl;


        AVLTree<int, char> t1;
        t1.insert(1, 'R');
        t1.insert(2, 'C');
        t1.insert(3, 'A');
        t1.insert(4, 'D');
        t1.insert(5, 'E');
        t1.insert(6, 'F');
        t1.insert(7, 'B');
        t1.insert(8, 'U');
        t1.insert(9, 'T');
        t1.insert(10, 'O');
        t1.insert(11, 'K');
        t1.print_tree();
        std::cout << "" << std::endl;
 
}