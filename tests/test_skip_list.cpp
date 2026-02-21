#include "../lib_skip_list/skip_list.h"
#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include <algorithm>
#include <random>
TEST(SkipNodeTest, constructor_skip_node_work_correctly) {
    SkipNode<int, std::string> node(10, "ten", 3);

    EXPECT_EQ(node.data.first, 10);
    EXPECT_EQ(node.data.second, "ten");
    EXPECT_EQ(node.levels, 3);

    for (size_t i = 0; i <= 3; i++) {
        EXPECT_EQ(node.next[i], nullptr);
    }

    SkipNode<int, std::string> node1(1, "one", 0);
    EXPECT_EQ(node1.levels, 0);
    EXPECT_EQ(node1.next[0], nullptr);
} 

TEST(SkipListTest, constructor_skip_list_work_correctly) {
    SkipList<int, std::string> list(8);
    EXPECT_TRUE(list.is_empty());

    SkipList<int, std::string> list1;
    EXPECT_TRUE(list1.is_empty());
}


TEST(SkipListTest, insert_one_element) {
    SkipList<int, std::string> list;
    list.insert(5, "five");
    auto node = list.find(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 5);
    EXPECT_EQ(node->data.second, "five");
}

TEST(SkipListTest, insert_more_elements) {
    SkipList<int, std::string> list;
    std::vector<int> keys = { 5, 3, 7, 1, 9, 2, 8, 4, 6 };

    for (int key : keys) {
        list.insert(key, std::to_string(key));
    }
    for (int key : keys) {
        auto node = list.find(key);
        ASSERT_NE(node, nullptr);
        EXPECT_EQ(node->data.first, key);
        EXPECT_EQ(node->data.second, std::to_string(key));
    }
}

TEST(SkipListTest, insert_duplicate) {
    SkipList<int, std::string> list;

    list.insert(5, "five");
    list.insert(5, "FIVE");  
    auto node = list.find(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 5);
    EXPECT_EQ(node->data.second, "FIVE"); 
}


TEST(SkipListTest, find_elems_work_corretly) {
    SkipList<int, std::string> list;

    list.insert(5, "five");
    list.insert(3, "three");
    list.insert(7, "seven");

    auto node = list.find(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 5);
    EXPECT_EQ(node->data.second, "five");

    node = list.find(3);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 3);
    EXPECT_EQ(node->data.second, "three");

    node = list.find(7);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 7);
    EXPECT_EQ(node->data.second, "seven");

    EXPECT_EQ(list.find(1), nullptr);

}



