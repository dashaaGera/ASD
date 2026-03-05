#include "../lib_bstree/bstree.h"
#include <gtest/gtest.h>
#include <string>
TEST(TestBSTreeNode, can_create_with_init_constructor_correctly) {
    TreeNode<int, int> n1;
    EXPECT_EQ(n1.value.first, 0);
    EXPECT_EQ(n1.value.second, 0);
    EXPECT_EQ(n1.left, nullptr);
    EXPECT_EQ(n1.right, nullptr);

    TreeNode<int, int> n2(std::pair<int, int>(5, 10));
    EXPECT_EQ(n2.value.first, 5);
    EXPECT_EQ(n2.value.second, 10);
    EXPECT_EQ(n2.left, nullptr);
    EXPECT_EQ(n2.right, nullptr);

    TreeNode<int, int> child1(std::pair<int, int>(1, 2));
    TreeNode<int, int> child2(std::pair<int, int>(3, 4));

    TreeNode<int, int> n3(std::pair<int, int>(5, 6), &child1);
    EXPECT_EQ(n3.value.first, 5);
    EXPECT_EQ(n3.value.second, 6);
    EXPECT_EQ(n3.left, &child1);
    EXPECT_EQ(n3.right, nullptr);

    TreeNode<int, int> n4(std::pair<int, int>(7, 8), &child1, &child2);
    EXPECT_EQ(n4.value.first, 7);
    EXPECT_EQ(n4.value.second, 8);
    EXPECT_EQ(n4.left, &child1);
    EXPECT_EQ(n4.right, &child2);
}

TEST(TestBSTree, can_create_with_init_constructor_correctly) {
    BSTree<int, int> t1;
    EXPECT_EQ(t1.root(), nullptr);
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
}

TEST(TestBSTree, insert_work_correctly) {
    BSTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(1, 1);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.to_string(), "1 2 ");

}

TEST(TestBSTree, find_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, "one");
    t1.insert(2, "two");
    EXPECT_EQ(t1.find(1), "one");
    EXPECT_EQ(t1.find(2), "two");
    ASSERT_THROW(t1.find(6), std::logic_error);
}
TEST(TestBSTree, erase_in_bstree_when_only_root_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, "one");
    t1.erase(1);
    EXPECT_EQ(t1.size(), 0);
}

TEST(TestBSTree, erase_in_bstree_when_only_root_and_left_and_right_children_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(5, "five");
    t1.insert(3, "three");
    t1.insert(6, "six");
    t1.erase(3);
    EXPECT_EQ(t1.to_string(), "5 6 ");
    EXPECT_EQ(t1.size(), 2);

    BSTree<int, std::string> t2;
    EXPECT_EQ(t2.is_empty(), true);
    t2.insert(5, "five");
    t2.insert(3, "three");
    t2.insert(6, "six");
    t2.erase(6);
    EXPECT_EQ(t2.to_string(), "5 3 ");
    EXPECT_EQ(t2.size(), 2);

    BSTree<int, std::string> t3;
    EXPECT_EQ(t3.is_empty(), true);
    t3.insert(5, "five");
    t3.insert(3, "three");
    t3.insert(6, "six");
    t3.erase(5);
    EXPECT_EQ(t3.to_string(), "3 6 ");
    EXPECT_EQ(t3.size(), 2);
}

TEST(TestBSTree, erase_in_bstree_when_only_root_and_left_branch_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(5, "five");
    t1.insert(3, "three");
    t1.insert(1, "one");
    t1.insert(4, "four");
    t1.erase(5);
    EXPECT_EQ(t1.to_string(), "3 1 4 ");


    BSTree<int, std::string> t2;
    EXPECT_EQ(t2.is_empty(), true);
    t2.insert(5, "five");
    t2.insert(3, "three");
    t2.insert(1, "one");
    t2.insert(4, "four");
    t2.erase(4);
    EXPECT_EQ(t2.to_string(), "5 3 1 ");

    BSTree<int, std::string> t3;
    EXPECT_EQ(t3.is_empty(), true);
    t3.insert(5, "five");
    t3.insert(3, "three");
    t3.insert(1, "one");
    t3.insert(4, "four");
    t3.erase(3);
    EXPECT_EQ(t3.to_string(), "5 1 4 ");

}

TEST(TestBSTree, erase_in_bstree_when_only_root_and_right_branch_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(4, "four");
    t1.insert(6, "six");
    t1.insert(5, "five");
    t1.insert(7, "seven");
    t1.erase(5);
    EXPECT_EQ(t1.to_string(), "4 6 7 ");


    BSTree<int, std::string> t2;
    EXPECT_EQ(t2.is_empty(), true);
    t2.insert(4, "four");
    t2.insert(6, "six");
    t2.insert(5, "five");
    t2.insert(7, "seven");
    t2.erase(4);
    EXPECT_EQ(t2.to_string(), "6 5 7 ");
    EXPECT_EQ(t2.root()->value.first, 6);

    BSTree<int, std::string> t3;
    EXPECT_EQ(t3.is_empty(), true);
    t3.insert(4, "four");
    t3.insert(6, "six");
    t3.insert(5, "five");
    t3.insert(7, "seven");
    t3.erase(6);
    EXPECT_EQ(t3.to_string(), "4 5 7 ");

}

TEST(TestBSTree, erase_work_correctly) {
    BSTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    t1.insert(3, 3);
    t1.insert(4, 4);
    t1.insert(9, 9);
    t1.insert(7, 7);
    t1.insert(11, 11);
    EXPECT_EQ(t1.to_string(), "5 3 9 4 7 11 ");
    t1.erase(9);
    EXPECT_EQ(t1.to_string(), "5 3 7 4 11 ");
}

TEST(TestBSTree, to_string_on_empty_bstree_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.to_string(), "");
}

TEST(TestBSTree, to_string_on_no_empty_bstree_work_correctly) {
    BSTree<int, std::string> t1;
    EXPECT_EQ(t1.to_string(), "");
    t1.insert(5, "five");
    t1.insert(3, "three");
    t1.insert(9, "nine");
    t1.insert(1, "one");
    t1.insert(7, "seven");
    EXPECT_EQ(t1.to_string(), "5 3 9 1 7 ");

}