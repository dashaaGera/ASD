#include "../lib_binary_tree/binary_tree.h"
#include <gtest/gtest.h>
#include <string>

TEST(TestTreeNode, can_create_with_init_constructor_correctly) {
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

TEST(TestTree, can_create_with_init_constructor_correctly) {
    Tree<int,int> t1;
    EXPECT_EQ(t1.root(), nullptr);
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
}

TEST(TestTree, insert_work_correctly) {
    Tree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(1, 1);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);

}

TEST(TestTree, erase_work_correctly) {
    Tree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.is_empty(), false);
    t1.erase(1);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1.is_empty(), false);
    t1.erase(2);
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.is_empty(), true);
    ASSERT_NO_THROW(t1.erase(7));
}

TEST(TestTree, find_work_correctly) {
    Tree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, "one");
    t1.insert(2, "two");
    EXPECT_EQ(t1.find(1), "one");
    EXPECT_EQ(t1.find(2), "two");
    ASSERT_THROW(t1.find(6), std::logic_error);
}

TEST(TestTree, print_width_work_correctly) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(2, "two");
    tree.insert(8, "eight");
    tree.insert(1, "one");
    tree.insert(3, "three");
    std::stringstream output;
    tree.print_width(output);

    std::string expected =
        "(5, five) \n"
        "(2, two) (8, eight) \n"
        "(1, one) (3, three) \n";

    EXPECT_EQ(output.str(), expected);
}

TEST(TestTree, print_print_depth_current_left_right_work_correctly) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(2, "two");
    tree.insert(8, "eight");
    tree.insert(1, "one");
    tree.insert(3, "three");
    std::stringstream output;
    tree.print_depth_current_left_right(output);

    std::string expected =
        "(5, five) "
        "(2, two) "
        "(1, one) "
        "(3, three) "
        "(8, eight) ";

    EXPECT_EQ(output.str(), expected);
}

TEST(TestTree, print_print_depth_left_current_right_work_correctly) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(2, "two");
    tree.insert(8, "eight");
    tree.insert(1, "one");
    tree.insert(3, "three");
    std::stringstream output;
    tree.print_depth_left_current_right(output);

    std::string expected =
        "(1, one) "
        "(2, two) "
        "(3, three) "
        "(5, five) "
        "(8, eight) ";

    EXPECT_EQ(output.str(), expected);
}

TEST(TestTree, print_print_depth_left_right_current_work_correctly) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(2, "two");
    tree.insert(8, "eight");
    tree.insert(1, "one");
    tree.insert(3, "three");
    std::stringstream output;
    tree.print_depth_left_right_current(output);

    std::string expected =
        "(1, one) "
        "(3, three) "
        "(2, two) "
        "(8, eight) "
        "(5, five) ";

    EXPECT_EQ(output.str(), expected);
}