#include <iostream>
#include "../lib_hash_table_chain/hash_table_c.h"
#include "../lib_hash_table_open_address/hash_table_oa.h"
int main() {
    HashTableChain<int> result;

    result.insert("hash", 325);
    result.insert("list", 47);
    result.insert("vector", 99);

    try {
        result.insert("vector", 35);
    }
    catch (const std::logic_error& e) {
    }

    result.insert("stack", 103);

    try {
        result.insert("list", 36);
    }
    catch (const std::logic_error& e) {
    }

    result.insert("queue", 15);

    std::cout << "Hash Table:" << std::endl;
    result.print(std::cout);


    HashTableChain<std::string> table;
    table.insert("five", "5");
    table.insert("two", "2");
    table.insert("eight", "8");
    table.insert("one", "1");
    std::cout << "Hash Table:" << std::endl;
    table.print(std::cout);


    HashTableOpenAddress<std::string> table1;
    table1.insert("five", "5");
    table1.insert("two", "2");
    table1.insert("eight", "8");
    table1.insert("one", "1");
    std::cout << "Hash Table:" << std::endl;
    table1.print(std::cout);

    table1.erase("one");
    std::cout << "Hash Table:" << std::endl;
    table1.print(std::cout);
    return 0;


}