#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStack, can_create_with_defuault_constructor) {
    ASSERT_NO_THROW(Stack<int> s);
}

TEST(TestStack, can_create_with_default_constructor_correctly) {
    Stack<int> s;
    EXPECT_EQ(s.size(), 20);
    EXPECT_NE(s.data(), nullptr);
    EXPECT_EQ(s.top_index(), -1);
    EXPECT_TRUE(s.is_empty());
    EXPECT_THROW(s.top(), std::logic_error);
}

TEST(TestStack, copy_empty_stack_correctly) {
    Stack<int> original(10);
    Stack<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.is_empty(), copy.is_empty());
    EXPECT_EQ(original.top_index(), copy.top_index());
    EXPECT_NE(original.data(), copy.data()); 
}

TEST(TestStack, copy_no_empty_stack_correctly) {
    Stack<int> original(5);
    original.push(1);
    original.push(2);
    original.push(3);

    Stack<int> copy(original);
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.top_index(), copy.top_index());
    EXPECT_NE(original.data(), copy.data());
    EXPECT_EQ(original.top(), copy.top());
}

TEST(TestStack, push_pop_work_correctly) {
    Stack<int> s(3);

    s.push(100);
    EXPECT_EQ(s.top_index(), 0);
    EXPECT_EQ(s.top(), 100);

    s.push(200);
    EXPECT_EQ(s.top_index(), 1);
    EXPECT_EQ(s.top(), 200);

    s.push(300);
    EXPECT_EQ(s.top_index(), 2);
    EXPECT_EQ(s.top(), 300);

    s.pop();
    EXPECT_EQ(s.top_index(), 1);
    EXPECT_EQ(s.top(), 200);

    s.pop();
    EXPECT_EQ(s.top_index(), 0);
    EXPECT_EQ(s.top(), 100);

    s.pop();
    EXPECT_EQ(s.top_index(), -1);
    EXPECT_THROW(s.top(), std::logic_error);
}

TEST(TestStack, pop_throws_exception) {
    Stack<int> s;
    EXPECT_ANY_THROW(s.pop());
}

TEST(TestStack, push_throws_exception) {
    Stack<int> s(3);
    s.push(6);
    s.push(1);
    s.push(8);
    EXPECT_ANY_THROW(s.push(5));
}


TEST(TestStack, is_empty_returns_true_for_empty_stack) {
    Stack<int> s;
    EXPECT_TRUE(s.is_empty());

    Stack<int> s2(10);
    EXPECT_TRUE(s2.is_empty());
}

TEST(TestStack, is_empty_returns_false_after_push) {
    Stack<int> s;
    s.push(100);
    EXPECT_FALSE(s.is_empty());
}

TEST(TestStack, is_empty_returns_true_after_clear) {
    Stack<int> s;
    s.push(7);
    EXPECT_FALSE(s.is_empty());

    s.clear();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStack, is_empty_returns_true_after_pop_all) {
    Stack<int> s(5);
    s.push(7);
    s.push(9);
    EXPECT_FALSE(s.is_empty());
    s.pop();
    s.pop();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStack, is_full_returns_false_for_empty_stack) {
    Stack<int> s(3);
    EXPECT_FALSE(s.is_full());
}

TEST(TestStack, is_full_returns_false_for_partially_filled_stack) {
    Stack<int> s(3);
    s.push(10);
    EXPECT_FALSE(s.is_full());

    s.push(20);
    EXPECT_FALSE(s.is_full());
}

TEST(TestStack, is_full_returns_true_when_stack_full) {
    Stack<int> s(3);
    s.push(10);
    s.push(20);
    s.push(30);
    EXPECT_TRUE(s.is_full());
}


TEST(TestStack, can_clear_correctly) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.top_index(), 1);
    s.clear();
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.top_index(), -1);
    EXPECT_THROW(s.top(), std::logic_error);
}



TEST(TestStack, top_returns_correct_value) {
    Stack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(TestStack, top_throws_exception_when_empty_stack) {
    Stack<int> s;
    EXPECT_THROW(s.top(), std::logic_error);

    Stack<int> s1;
    s1.push(3);
    s1.pop();
    EXPECT_THROW(s1.top(), std::logic_error);
}

TEST(TestStack, top_after_clear_throws_exception) {
    Stack<int> s;
    s.push(1);
    s.clear();
    EXPECT_THROW(s.top(), std::logic_error);
}
