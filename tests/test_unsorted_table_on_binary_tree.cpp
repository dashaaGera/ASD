#include "../lib_unsorted_table_on_binary_tree/unsorted_table_on_binary_tree.h"
#include <gtest/gtest.h>
#include <string>

TEST(TestUnsortedTableOnBinaryTree, is_emty_work_correctly) {
    UnsortedTableOnBinaryTree<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);

    table.erase(1);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

}

TEST(TestUnsortedTableOnBinaryTree, func_consist_work_correctly) {
    UnsortedTableOnBinaryTree<int, std::string> table;
    EXPECT_FALSE(table.consist(1));

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_FALSE(table.consist(4));
    EXPECT_FALSE(table.is_empty());

}

TEST(TestUnsortedTableOnBinaryTree, find_work_corretly) {
    UnsortedTableOnBinaryTree<int, std::string> table;

    table.insert(1, "one");
    table.insert(5, "five");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(3), "three");

   
    EXPECT_THROW(table.insert(1, "1");, std::logic_error);
    EXPECT_THROW(table.insert(1, "one");, std::logic_error);
    EXPECT_THROW(table.find(4), std::logic_error);

    UnsortedTableOnBinaryTree<int, double> table1;
    table1.insert(1, 1.1);
    table1.insert(2, 2.2);
    EXPECT_DOUBLE_EQ(table1.find(1), 1.1);
    EXPECT_DOUBLE_EQ(table1.find(2), 2.2);
}


TEST(TestUnsortedTableOnBinaryTree, erase_work_corretly) {
    UnsortedTableOnBinaryTree<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(2);
    table.erase(9);
    EXPECT_EQ(table.size(), 2);

    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_NO_THROW(table.erase(4));
}

TEST(TestUnsortedTableOnBinaryTree, print_work_corretly) {
    UnsortedTableOnBinaryTree<int, std::string> table;
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    table.insert(3, "three");

    std::stringstream output;
    table.print(output);
    std::string result = output.str();

    std::string expected = "(5, five) \n(2, two) (8, eight) \n(1, one) (3, three) \n";

    EXPECT_EQ(result, expected);

}
