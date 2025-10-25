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

TEST(TestList, is_empty_work_correctly) {
    List<int> l1;
    EXPECT_TRUE(l1.is_empty());
}

TEST(TestList, push_front_work_correctly) {
    List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    l1.push_front(6);

    EXPECT_FALSE(l1.is_empty());
    EXPECT_NE(l1.tail(), nullptr);  
    EXPECT_NE(l1.head(), nullptr);  
    EXPECT_EQ(l1.head(), l1.tail()); 
    EXPECT_EQ(l1.size(), 1);        
    EXPECT_EQ(l1.head()->value, 6);  

    l1.push_front(8);
    EXPECT_NE(l1.tail(), nullptr);
    EXPECT_NE(l1.head(), nullptr);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 8);
}

TEST(TestList, push_back_in_empty_list_work_correctly) {
    List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    l1.push_back(6);

    EXPECT_FALSE(l1.is_empty());
    EXPECT_NE(l1.tail(), nullptr);
    EXPECT_NE(l1.head(), nullptr);
    EXPECT_EQ(l1.head(), l1.tail());
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 6);

}

TEST(TestList, push_back_work_correctly) {
    List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    l1.push_back(6);
    EXPECT_FALSE(l1.is_empty());
    l1.push_back(3);
    EXPECT_FALSE(l1.is_empty());

    EXPECT_NE(l1.tail(), nullptr);
    EXPECT_NE(l1.head(), nullptr);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.tail()->value, 3);
    EXPECT_EQ(l1.tail()->next, nullptr);
}


TEST(TestList, insert_with_node_throw_exception_in_empty_list) {
    List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    ASSERT_THROW(l1.insert(nullptr, 10), std::logic_error);
}


TEST(TestList, insert_with_node_work_correctly) {
    List<int> l1;
    l1.push_back(3);
    l1.push_back(6);
    Node<int>* first_node = l1.head();
    ASSERT_NO_THROW(l1.insert(first_node, 10));

    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 3);
    EXPECT_EQ(l1.head()->next->value, 10);
    EXPECT_EQ(l1.head()->next->next->value, 6);
    EXPECT_EQ(l1.tail()->value, 6);

    Node<int>* second_node = l1.head()->next;
    ASSERT_NO_THROW(l1.insert(second_node, 5));

    EXPECT_EQ(l1.size(), 4);
    EXPECT_EQ(l1.head()->value, 3);
    EXPECT_EQ(l1.head()->next->value, 10);
    EXPECT_EQ(l1.head()->next->next->value, 5);
    EXPECT_EQ(l1.head()->next->next->next->value, 6);
    EXPECT_EQ(l1.tail()->value, 6);


}

TEST(TestList, insert_with_pos_throw_exception_when_pos_is_negative) {
    List<int> l1;
    ASSERT_THROW(l1.insert(-1, 10), std::logic_error);
}


TEST(TestList, insert_with_pos_throw_exception_when_pos_is_greater_size_list) {
    List<int> l1;
    ASSERT_THROW(l1.insert(1, 10), std::logic_error);
}

TEST(TestList, insert_with_pos_work_correctly) {
    List<int> l1;
    l1.insert(0,5);
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 5);
    EXPECT_EQ(l1.tail()->value, 5);

    l1.insert(1, 4);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 5);
    EXPECT_EQ(l1.head()->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 4);

    l1.insert(1, 3);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 5);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 4);

}

TEST(TestList, pop_front_throw_exception_when_list_is_empty) {
    List<int> l1;
    ASSERT_THROW(l1.pop_front(), std::logic_error);
}
TEST(TestList, pop_front_work_correctly) {
    List<int> l1;
    l1.push_front(6);
    l1.push_front(8);

    l1.pop_front();
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 6);

    l1.pop_front();
    EXPECT_EQ(l1.tail(), nullptr);
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.size(), 0);

    l1.push_front(5);
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 5);

}

TEST(TestList, pop_back_throw_exception_when_list_is_empty) {
    List<int> l1;
    ASSERT_THROW(l1.pop_back(), std::logic_error);
}
TEST(TestList, pop_back_work_correctly) {
    List<int> l1;
    l1.push_front(6);
    l1.push_front(8);

    l1.pop_back();
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 8);
    EXPECT_EQ(l1.tail()->value, 8);

    l1.pop_back();
    EXPECT_EQ(l1.tail(), nullptr);
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.size(), 0);

    l1.push_front(5);
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 5);

}

TEST(TestList, erase_with_node_throw_exception_when_node_indicates_nullptr) {
    List<int> l1;
    Node<int>* node = nullptr; 
    ASSERT_THROW(l1.erase(node), std::logic_error);
}


TEST(TestList, erase_with_node_work_correctly) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);

    Node<int>* first_node = l1.head();
    l1.erase(first_node);

    EXPECT_EQ(l1.size(), 4);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.head()->next->next->next->value, 5);
    EXPECT_EQ(l1.tail()->value, 5);

    Node<int>* last_node = l1.tail();
    l1.erase(last_node);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 4);

    Node<int>* second_node = l1.head()->next;
    l1.erase(second_node);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 4);

    l1.pop_back();

    Node<int>* remaining_node = l1.head();
    l1.erase(remaining_node);
    EXPECT_EQ(l1.size(), 0);
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.tail(), nullptr);
}


TEST(TestList, erase_with_pos_throw_exception_when_pos_is_negative) {
    List<int> l1;
    ASSERT_THROW(l1.erase(-1), std::logic_error);
}

TEST(TestList, erase_with_pos_throw_exception_when_pos_is_greater_size_list) {
    List<int> l1;
    ASSERT_THROW(l1.erase(1), std::logic_error);
}

TEST(TestList, erase_with_pos_work_correctly) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);

    l1.erase(0);
    EXPECT_EQ(l1.size(), 4);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 5);

    l1.erase(3);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 4);

    l1.erase(1);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 4);
    EXPECT_EQ(l1.tail()->value, 4);

    l1.erase(1);
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.tail()->value, 2);

    l1.erase(0);
    EXPECT_EQ(l1.size(), 0);
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.tail(), nullptr);
}

