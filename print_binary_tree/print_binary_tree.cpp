#include <iostream>
#include <string>
#include "../lib_binary_tree/binary_tree.h"
int main() {
    Tree<int, std::string> t1;
    t1.insert(1, "one");
    t1.insert(2, "two");
    t1.insert(3, "three");
    t1.insert(4, "four");
    t1.insert(5, "five");
    t1.insert(6, "six");
    t1.print_width();

    std::cout << "" << std::endl;
    t1.print_depth_left_current_right();

    std::cout << "" << std::endl;
    t1.print_depth_current_left_right();

    std::cout << "" << std::endl;
    t1.print_depth_left_right_current();

    std::cout << "" << std::endl;
    std::cout << "tree after erase node (1,one): " << std::endl;
    t1.erase(1);
    t1.print_width();

    std::cout << "" << std::endl;
    std::cout << "tree after erase node (3,three): " << std::endl;
    t1.erase(3);
    t1.print_width();
 
}