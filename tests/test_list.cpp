#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestNode, can_create_with_default_constructor_correctly) {
    ASSERT_NO_THROW(Node<int> n1);
}

TEST(TestNode, can_create_with_init_constructor_correctly) {
    Node<int> n;
    EXPECT_EQ(n.value, 0);
    EXPECT_EQ(n.next, nullptr);

    Node<int> n1(4);
    EXPECT_EQ(n1.value, 4);
    EXPECT_EQ(n1.next, nullptr);

    Node<int> n2(7, &n1);
    EXPECT_EQ(n2.value, 7);
    EXPECT_EQ(n2.next, &n1);
}

TEST(TestList, can_create_with_default_constructor_correctly) {
    ASSERT_NO_THROW(List<int> l1);
}

TEST(TestList, can_create_with_init_constructor_correctly) {
    List<int> l1;
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.tail(), nullptr);
    EXPECT_EQ(l1.size(), 0);
}