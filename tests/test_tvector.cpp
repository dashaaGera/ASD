#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

TEST(TestTVector, can_create_with_defuault_constructor) {
    ASSERT_NO_THROW(TVector<int> v1);
}

TEST(TestTVector, can_create_with_init_constructor_correctly) {
    TVector<int> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.data(), nullptr);
}

TEST(TestTVector, can_create_with_constructor_capacity_correctly) {
    TVector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_NE(vec.data(), nullptr);
}

TEST(TestTVector, throw_when_try_create_vector_with_great_maxcapacity) {
    ASSERT_ANY_THROW(TVector<int> vec(MAX_CAPACITY + 1));
}

TEST(TestTVector, can_create_with_initializer_list_constructor) {
    TVector<int> v = { 1,4,6,7,9 };
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 15);
    EXPECT_NE(v.data(), nullptr);
}

TEST(TestTVector, can_create_with_constructor_with_size_and_data) {
    int test_data[] = { 1, 2, 3, 4, 5 };
    TVector<int> v(test_data, 5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 15);
    EXPECT_NE(v.data(), nullptr);
}


TEST(TestTVector, can_copy_vector) {
    TVector<int> original = { 1, 2, 3 };
    TVector<int> copy(original);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.capacity(), 15);
    for (size_t i = 0; i < 3; i++) {
        EXPECT_EQ(copy.data()[i], original.data()[i]);
    }
}

TEST(TestTVector, is_empty_return_true_for_empty_vector) {
    TVector<int> v;
    EXPECT_TRUE(v.is_empty());
}

TEST(TestTVector, is_empty_return_false_for_non_empty_vector) {
    int data[] = { 1, 2, 3 };
    TVector<int> v(data, 3);
    EXPECT_FALSE(v.is_empty());
}

TEST(TestTVector, is_full_return_false_when_size_equals_capacity) {
    int data[] = { 1, 2, 3 };
    TVector<int> v(data, 3); // size = 3, capacity = 15
    EXPECT_FALSE(v.is_full());
}

TEST(TestTVector, empty_vector_is_empty_but_not_full) {
    TVector<int> v;
    EXPECT_TRUE(v.is_empty());
    EXPECT_FALSE(v.is_full()); // capacity = 0, size = 0
}


TEST(TestTVector, can_increase_capacity) {
    TVector<int> v;
    v.resize(5);
    EXPECT_EQ(v.capacity(), 15);
    EXPECT_EQ(v.size(), 5);

}

TEST(TestTVector, can_increase_capacity_multiple_15) {
    TVector<int> v;
    v.resize(30);
    EXPECT_EQ(v.capacity(), 45);
    EXPECT_EQ(v.size(), 30);
}



TEST(TestTVector, throw_when_try_increase_capacity_vector_with_great_maxcapacity) {
    TVector<int> v(MAX_CAPACITY);
    ASSERT_THROW(v.resize(MAX_CAPACITY + 1), std::logic_error);
}

TEST(TestTVector, can_push_back_val_correctly) {
    int data[] = { 1, 2, 3 };
    TVector<int> v(data, 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 15);
    v.push_back(6);
    EXPECT_EQ(v[3], 6);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v.capacity(), 15);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(TestTVector, can_push_back_val_to_vector_with_size_multiple_15_correctly) {
    int data[] = { 1, 2, 3,4,5,6,7,8,9,10,11,12,13,14,15 };
    TVector<int> v(data, 15);
    EXPECT_EQ(v.size(), 15);
    EXPECT_EQ(v.capacity(), 30);
    v.push_back(6);
    EXPECT_EQ(v[15], 6);
    EXPECT_EQ(v.size(), 16);
    EXPECT_EQ(v.capacity(), 30);

}

TEST(TestTVector, can_push_front_val_correctly) {
    int data[] = { 1, 2, 3 };
    TVector<int> v(data, 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 15);
    v.push_front(6);
    EXPECT_EQ(v[0], 6);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v.capacity(), 15);

    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 3);
}

TEST(TestTVector, can_push_front_val_to_vector_with_size_multiple_15_correctly) {
    int data[] = { 1, 2, 3,4,5,6,7,8,9,10,11,12,13,14,15 };
    TVector<int> v(data, 15);
    EXPECT_EQ(v.size(), 15);
    EXPECT_EQ(v.capacity(), 30);
    v.push_front(6);
    EXPECT_EQ(v[0], 6);
    EXPECT_EQ(v.size(), 16);
    EXPECT_EQ(v.capacity(), 30);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[15], 15);
}

TEST(TestTVector, can_pop_back_from_non_empty_vector_correctly) {
    int data[] = { 1, 2, 3 };
    TVector<int> v(data, 3);
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(TestTVector, pop_back_decreases_size_but_not_capacity_correctly) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    size_t original_capacity = v.capacity();
    v.pop_back();
    v.pop_back();
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), original_capacity);
}

TEST(TestTVector, pop_back_from_empty_vector_throws) {
    TVector<int> v;
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(TestTVector, reset_memory_work_correctly_when_deleting_elements) {
    int* data = new int[30];
    TVector<int> v(data, 30);
    EXPECT_EQ(v.size(), 30);
    EXPECT_EQ(v.capacity(), 45);
    v.pop_back();
    EXPECT_EQ(v.size(), 29);
    EXPECT_EQ(v.capacity(), 30);

}

TEST(TestTVector, can_pop_front_from_no_empty_vector_correctly) {
    int data[] = { 1, 2, 3 };
    TVector<int> v(data, 3);

    v.pop_front();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 3);
}

TEST(TestTVector, pop_front_from_empty_vector_throws) {
    TVector<int> v;
    EXPECT_THROW(v.pop_front(), std::out_of_range);
}

TEST(TestTVector, pop_front_decreases_size_but_not_capacity_correctly) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    size_t original_capacity = v.capacity();
    v.pop_front();
    v.pop_front();
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), original_capacity);
}

TEST(TestTVector, can_erase_middle_item_correctly) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    v.erase(2, 1);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 5);
}

TEST(TestTVector, can_erase_first_item_correctly) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    v.erase(0, 1);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 5);
}

TEST(TestTVector, can_erase_last_item_correctly) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    v.erase(4, 1);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(TestTVector, can_erase_many_items_correctly) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    v.erase(2, 2);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 5);
}

TEST(TestTVector, erase_out_of_range_throws) {
    TVector<int> v = { 1, 2, 3 };
    EXPECT_THROW(v.erase(3), std::logic_error);
}

TEST(TestTVector, erase_not_decrease_capacity) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    size_t original_capacity = v.capacity();
    v.erase(2);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v.capacity(), original_capacity);
}

TEST(TestTVector, can_insert_at_beginning_correctly) {
    TVector<int> v = { 2, 3, 4 };
    v.insert(0, 1);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(TestTVector, can_insert_in_middle_correctly) {
    TVector<int> v = { 1, 2, 4, 5 };
    v.insert(2, 3);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(TestTVector, can_insert_at_end_correctly) {
    TVector<int> v = { 1, 2, 3 };
    v.insert(3, 4);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(TestTVector, insert_out_of_range_throws) {
    TVector<int> v = { 1, 2, 3 };
    EXPECT_THROW(v.insert(10, 5), std::out_of_range);
}

TEST(TestTVector, front_return_first_element_correctly) {
    TVector<int> v = { 10, 20, 30 };
    EXPECT_EQ(v.front(), 10);

}

TEST(TestTVector, front_on_empty_vector_throws) {
    TVector<int> v;
    EXPECT_THROW(v.front(), std::out_of_range);
}

TEST(TestTVector, back_return_last_element_correctly) {
    TVector<int> v = { 10, 20, 30 };
    EXPECT_EQ(v.back(), 30);
}

TEST(TestTVector, back_on_empty_vector_throws) {
    TVector<int> v;
    EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(TestTVector, find_return_correct_index) {
    TVector<int> v = { 10, 20, 30, 40, 50 };
    EXPECT_EQ(v.find_pos(10), 0);
    EXPECT_EQ(v.find_pos(30), 2);
    EXPECT_EQ(v.find_pos(50), 4);

}

TEST(TestTVector, find_pos_out_of_range_throws) {
    TVector<int> v = { 1, 2, 3 };
    EXPECT_THROW(v.find_pos(4), std::out_of_range);
}


TEST(TestTVector, find_return_correct_val) {
    TVector<int> v = { 10, 20, 30, 40, 50 };
    EXPECT_EQ(v.find_val(0), 10);
    EXPECT_EQ(v.find_val(1), 20);
    EXPECT_EQ(v.find_val(4), 50);

}

TEST(TestTVector, find_val_out_of_range_throws) {
    TVector<int> v = { 1, 2, 3 };
    EXPECT_THROW(v.find_val(4), std::out_of_range);
}

TEST(TestTVector, output_operator) {
    TVector<int> v = { 1, 2, 3, 4, 5 };
    std::stringstream os;
    os << v;
    EXPECT_EQ(os.str(), "1 2 3 4 5 ");
}

