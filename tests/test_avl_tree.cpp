#include "../lib_avl_tree/avl_tree.h"
#include <gtest/gtest.h>
#include <string>
TEST(TestAVLNode, can_create_with_init_constructor_correctly) {
    AVLNode<int, int> n1;
    EXPECT_EQ(n1.value.first, 0);
    EXPECT_EQ(n1.value.second, 0);
    EXPECT_EQ(n1.left, nullptr);
    EXPECT_EQ(n1.right, nullptr);
    EXPECT_EQ(n1.parent, nullptr);
    EXPECT_EQ(n1.height, 1);

    AVLNode<int, int> n2(std::pair<int, int>(5, 10));
    EXPECT_EQ(n2.value.first, 5);
    EXPECT_EQ(n2.value.second, 10);
    EXPECT_EQ(n2.left, nullptr);
    EXPECT_EQ(n2.right, nullptr);
    EXPECT_EQ(n2.parent, nullptr);
    EXPECT_EQ(n2.height, 1);

    AVLNode<int, int> child1(std::pair<int, int>(1, 2));
    AVLNode<int, int> child2(std::pair<int, int>(3, 4));
    AVLNode<int, int> parent(std::pair<int, int>(7, 4));

    AVLNode<int, int> n3(std::pair<int, int>(5, 6), &parent);
    EXPECT_EQ(n3.value.first, 5);
    EXPECT_EQ(n3.value.second, 6);
    EXPECT_EQ(n3.parent, &parent);
    EXPECT_EQ(n3.right, nullptr);
    EXPECT_EQ(n3.left, nullptr);
    EXPECT_EQ(n3.height, 1);

    AVLNode<int, int> n4(std::pair<int, int>(7, 8), &parent, &child2);
    EXPECT_EQ(n4.value.first, 7);
    EXPECT_EQ(n4.value.second, 8);
    EXPECT_EQ(n4.parent, &parent);
    EXPECT_EQ(n4.left, &child2);
    EXPECT_EQ(n4.right, nullptr);
    EXPECT_EQ(n4.height, 1);


    AVLNode<int, int> n5(std::pair<int, int>(7, 8), &parent, &child1, &child2,8);
    EXPECT_EQ(n5.value.first, 7);
    EXPECT_EQ(n5.value.second, 8);
    EXPECT_EQ(n5.left, &child1);
    EXPECT_EQ(n5.right, &child2);
    EXPECT_EQ(n5.parent, &parent);
    EXPECT_EQ(n5.height, 8);
}
TEST(TestAVLTree, can_create_with_init_constructor_correctly) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.root(), nullptr);
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
}

TEST(TestAVLTree, insert_work_correctly_case_LL) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(4, 4);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(6, 6);
    t1.insert(3, 3);
    t1.insert(2, 2);
    EXPECT_EQ(t1.to_string(), "5 3 6 2 4 ");
    EXPECT_EQ(t1.to_string_sorted(), "2 3 4 5 6 ");
    EXPECT_EQ(t1.size(), 5);

}

TEST(TestAVLTree, insert_work_correctly_case_RR) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(4, 4);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(6, 6);
    t1.insert(7, 7);
    t1.insert(8, 8);
    EXPECT_EQ(t1.to_string(), "5 4 7 6 8 ");
    EXPECT_EQ(t1.to_string_sorted(), "4 5 6 7 8 ");
    EXPECT_EQ(t1.size(), 5);
}

TEST(TestAVLTree, insert_work_correctly_case_LR) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(8, 8);
    t1.insert(6, 6);
    t1.insert(7, 7);
    EXPECT_EQ(t1.to_string(), "5 2 7 6 8 ");
    EXPECT_EQ(t1.to_string_sorted(), "2 5 6 7 8 ");
    EXPECT_EQ(t1.size(), 5);
}

TEST(TestAVLTree, insert_work_correctly_case_RL) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(6, 6);
    t1.insert(8, 8);
    t1.insert(7, 7);
    EXPECT_EQ(t1.to_string(), "5 2 7 6 8 ");
    EXPECT_EQ(t1.to_string_sorted(), "2 5 6 7 8 ");
    EXPECT_EQ(t1.size(), 5);
}

TEST(TestAVLTree, insert_work_correctly) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    ASSERT_THROW(t1.insert(5, 5), std::logic_error);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.to_string(), "5 ");

}
TEST(TestAVLTree, find_work_correctly) {
    AVLTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, "one");
    t1.insert(2, "two");
    EXPECT_EQ(t1.find(1), "one");
    EXPECT_EQ(t1.find(2), "two");
    ASSERT_THROW(t1.find(6), std::logic_error);
}