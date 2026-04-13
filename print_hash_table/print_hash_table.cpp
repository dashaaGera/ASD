#include <iostream>
#include "../lib_hash_table_chain/hash_table_c.h"
#include "../lib_hash_table_open_address/hash_table_oa.h"
int main() {

    TVector<std::pair<std::string, int>> dict1;
    dict1.push_back({ "hash", 10072 });
    dict1.push_back({ "list", 13736 });
    dict1.push_back({ "vector", 16262 });
    dict1.push_back({ "massive", 10626 });
    dict1.push_back({ "table", 10083 });


    TVector<std::pair<std::string, int>> dict2;
    dict2.push_back({ "table", 22727 });
    dict2.push_back({ "vector", 20728 });
    dict2.push_back({ "queue", 28282 });
    dict2.push_back({ "stack", 20607 });
    dict2.push_back({ "list", 20618 });


    HashTableChain<int> result = merge_dict(dict1, dict2);
    result.print(std::cout);
    return 0;


}