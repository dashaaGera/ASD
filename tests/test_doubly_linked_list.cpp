#include <gtest/gtest.h>
#include "../lib_doubly_linked_list/doubly_linked_list.h"

TEST(TestDoublyLinkedList, can_create_with_default_constructor_correctly) {
    ASSERT_NO_THROW(Doubly_Linked_List<int> l1);
}

TEST(TestDoublyLinkedList, can_create_with_init_constructor_correctly) {
    Doubly_Linked_List<int> l1;
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.tail(), nullptr);
    EXPECT_EQ(l1.size(), 0);
}

TEST(TestDoublyLinkedList, copy_constructor_works_corretly) {
    Doubly_Linked_List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    Doubly_Linked_List<int> copy(original);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.head()->value, 1);
    EXPECT_EQ(copy.head()->next->prev->value, 1);
    EXPECT_EQ(copy.head()->next->value, 2);
    EXPECT_EQ(copy.tail()->prev->value, 2);
    EXPECT_EQ(copy.tail()->value, 3);
}

TEST(TestDoublyLinkedList, nodes_store_in_different_places_when_copying) {
    Doubly_Linked_List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    Doubly_Linked_List<int> copy(original);

    EXPECT_NE(copy.head(), original.head());
    EXPECT_NE(copy.head()->next, original.head()->next);
    EXPECT_NE(copy.tail(), original.tail());

    original.push_back(4);
    EXPECT_NE(copy.size(), original.size());
}

TEST(TestDoublyLinkedList, push_back_in_empty_list_work_correctly) {
    Doubly_Linked_List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    l1.push_back(6);

    EXPECT_FALSE(l1.is_empty());
    EXPECT_NE(l1.tail(), nullptr);
    EXPECT_NE(l1.head(), nullptr);
    EXPECT_EQ(l1.head(), l1.tail());
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 6);

}

TEST(TestDoublyLinkedList, push_back_work_correctly) {
    Doubly_Linked_List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    l1.push_back(6);
    EXPECT_FALSE(l1.is_empty());
    l1.push_back(3);
    EXPECT_FALSE(l1.is_empty());

    EXPECT_NE(l1.tail(), nullptr);
    EXPECT_NE(l1.head(), nullptr);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 6);
    EXPECT_EQ(l1.tail()->value, 3);
    EXPECT_EQ(l1.tail()->next, nullptr);
    EXPECT_EQ(l1.tail()->prev->value, 6);

    l1.push_back(9);

    EXPECT_NE(l1.tail(), nullptr);
    EXPECT_NE(l1.head(), nullptr);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 6);
    EXPECT_EQ(l1.tail()->value, 9);
    EXPECT_EQ(l1.tail()->next, nullptr);
    EXPECT_EQ(l1.tail()->prev->value, 3);
}

TEST(TestDoublyLinkedList, push_front_work_correctly) {
    Doubly_Linked_List<int> l1;
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
    EXPECT_EQ(l1.tail()->value, 6);
    EXPECT_EQ(l1.tail()->prev->value, 8);
}

TEST(TestDoublyLinkedList, insert_with_node_throw_exception_in_empty_list) {
    Doubly_Linked_List<int> l1;
    EXPECT_TRUE(l1.is_empty());
    ASSERT_THROW(l1.insert(nullptr, 10), std::logic_error);
}


TEST(TestDoublyLinkedList, insert_with_node_work_correctly) {
    Doubly_Linked_List<int> l1;
    l1.push_back(3);
    l1.push_back(6);
    Node<int>* first_node = l1.head();
    ASSERT_NO_THROW(l1.insert(first_node, 10));

    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 3);
    EXPECT_EQ(l1.head()->next->value, 10);
    EXPECT_EQ(l1.head()->next->next->value, 6);
    EXPECT_EQ(l1.tail()->prev->value, 10);
    EXPECT_EQ(l1.tail()->value, 6);

    Node<int>* second_node = l1.head()->next;
    l1.insert(second_node, 5);

    EXPECT_EQ(l1.size(), 4);
    EXPECT_EQ(l1.head()->value, 3);
    EXPECT_EQ(l1.head()->next->value, 10);
    EXPECT_EQ(l1.head()->next->next->value, 5);
    EXPECT_EQ(l1.tail()->prev->value, 5);
    EXPECT_EQ(l1.head()->next->next->next->value, 6);
    EXPECT_EQ(l1.tail()->value, 6);


}

TEST(TestDoublyLinkedList, insert_with_pos_throw_exception_when_pos_is_negative) {
    Doubly_Linked_List<int> l1;
    ASSERT_THROW(l1.insert(-1, 10), std::logic_error);
}


TEST(TestDoublyLinkedList, insert_with_pos_throw_exception_when_pos_is_greater_size_list) {
    Doubly_Linked_List<int> l1;
    ASSERT_THROW(l1.insert(1, 10), std::logic_error);
}

TEST(TestDoublyLinkedList, insert_with_pos_work_correctly) {
    Doubly_Linked_List<int> l1;
    l1.insert(0, 5);
    EXPECT_EQ(l1.size(), 1);
    EXPECT_EQ(l1.head()->value, 5);
    EXPECT_EQ(l1.tail()->value, 5);

    l1.insert(1, 4);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 5);
    EXPECT_EQ(l1.head()->next->value, 4);
    EXPECT_EQ(l1.tail()->prev->value, 5);
    EXPECT_EQ(l1.tail()->value, 4);


    l1.insert(1, 3);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 5);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->prev->value, 3);
    EXPECT_EQ(l1.tail()->value, 4);

}


TEST(TestDoublyLinkedList, pop_front_throw_exception_when_list_is_empty) {
    Doubly_Linked_List<int> l1;
    ASSERT_THROW(l1.pop_front(), std::logic_error);
}
TEST(TestDoublyLinkedList, pop_front_work_correctly) {
    Doubly_Linked_List<int> l1;
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

    l1.push_front(8);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 8);
    EXPECT_EQ(l1.tail()->value, 5);
}

TEST(TestDoublyLinkedList, pop_back_throw_exception_when_list_is_empty) {
    Doubly_Linked_List<int> l1;
    ASSERT_THROW(l1.pop_back(), std::logic_error);
}
TEST(TestDoublyLinkedList, pop_back_work_correctly) {
    Doubly_Linked_List<int> l1;
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

    l1.push_front(7);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 7);
    EXPECT_EQ(l1.tail()->value, 5);
    EXPECT_EQ(l1.tail()->prev->value, 7);

}

TEST(TestDoublyLinkedList, erase_with_node_throw_exception_when_node_indicates_nullptr) {
    Doubly_Linked_List<int> l1;
    Node<int>* node = nullptr;
    ASSERT_THROW(l1.erase(node), std::logic_error);
}


TEST(TestDoublyLinkedList, erase_with_node_work_correctly) {
    Doubly_Linked_List<int> l1;
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
    EXPECT_EQ(l1.tail()->prev->value, 4);
    EXPECT_EQ(l1.tail()->value, 5);

    Node<int>* last_node = l1.tail();
    l1.erase(last_node);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->prev->value, 3);
    EXPECT_EQ(l1.tail()->value, 4);

    Node<int>* second_node = l1.head()->next;
    l1.erase(second_node);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 4);
    EXPECT_EQ(l1.tail()->prev->value, 2);
    EXPECT_EQ(l1.tail()->value, 4);

    l1.pop_back();

    Node<int>* remaining_node = l1.head();
    l1.erase(remaining_node);
    EXPECT_EQ(l1.size(), 0);
    EXPECT_EQ(l1.head(), nullptr);
    EXPECT_EQ(l1.tail(), nullptr);
}

TEST(TestDoublyLinkedList, erase_with_pos_throw_exception_when_pos_is_negative) {
    Doubly_Linked_List<int> l1;
    ASSERT_THROW(l1.erase(-1), std::logic_error);
}

TEST(TestDoublyLinkedList, erase_with_pos_throw_exception_when_pos_is_greater_size_list) {
    Doubly_Linked_List<int> l1;
    ASSERT_THROW(l1.erase(1), std::logic_error);
}

TEST(TestDoublyLinkedList, erase_with_pos_work_correctly) {
    Doubly_Linked_List<int> l1;
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
    EXPECT_EQ(l1.tail()->prev->value, 4);
    EXPECT_EQ(l1.tail()->value, 5);

    l1.erase(3);
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.head()->next->value, 3);
    EXPECT_EQ(l1.head()->next->next->value, 4);
    EXPECT_EQ(l1.tail()->prev->value, 3);
    EXPECT_EQ(l1.tail()->value, 4);

    l1.erase(1);
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l1.head()->value, 2);
    EXPECT_EQ(l1.tail()->prev->value, 2);
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

TEST(TestDoublyLinkedListIterator, can_read_correctly) {
    Doubly_Linked_List<int> list;
    for (int i = 0;i < 10;i++) {
        list.push_back(i + 1);
    }

    int expected_val = 1;
    for (Doubly_Linked_List<int>::Iterator it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }

    expected_val = 10;
    Node<int>* tail_node = list.tail();
    Doubly_Linked_List<int>::Iterator it(tail_node);

    //while (true) {
    //    EXPECT_EQ(*it, expected_val);
    //    if (!(it != list.begin())) break;
    //    expected_val--;
    //    --it;
    //}

    for (auto  it = list.rbegin(); it != list.rend(); it--) {
        EXPECT_EQ(*it, expected_val);
        expected_val--;
    }

}

TEST(TestDoublyLinkedListIterator, can_write_correctly) {
    Doubly_Linked_List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(0);
    }

    int val = 1;
    for (Doubly_Linked_List<int>::Iterator it = list.begin(); it != list.end(); it++) {
        *it = val;
        val++;
    }

    int expected_val = 5;
    Doubly_Linked_List<int>::Iterator it = list.tail();
    while (true) {
        EXPECT_EQ(*it, expected_val);
        expected_val--;

        if (!(it != list.begin())) break;
        --it;
    }
    EXPECT_EQ(expected_val, 0);
}

TEST(TestDoublyLinkedListIterator, empty_list_work_correctly) {
    Doubly_Linked_List<int> list;

    EXPECT_NO_THROW({
        for (Doubly_Linked_List<int>::Iterator it = list.begin(); it != list.end(); it++) {
            *it = 0;
        }
        });

    EXPECT_NO_THROW({
        Doubly_Linked_List<int>::Iterator it = list.end();
        --it;
        it--;
        EXPECT_EQ(it, list.end());
        });
}