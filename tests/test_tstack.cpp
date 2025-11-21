#include <gtest/gtest.h>
#include "../lib_tstack/tstack.h"

TEST(TestTStack, copy_tstack_correctly) {
    TStack<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    TStack<int> copy(original);
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.top(), copy.top());
}

TEST(TestTStack, push_pop_work_correctly_in_tstack) {
    TStack<int> s;

    s.push(100);
    EXPECT_EQ(s.top(), 100);
    EXPECT_EQ(s.size(), 1);

    s.push(200);
    EXPECT_EQ(s.top(), 200);
    EXPECT_EQ(s.size(), 2);

    s.push(300);
    EXPECT_EQ(s.top(), 300);
    EXPECT_EQ(s.size(), 3);

    s.pop();
    EXPECT_EQ(s.top(), 200);
    EXPECT_EQ(s.size(), 2);

    s.pop();
    EXPECT_EQ(s.top(), 100);
    EXPECT_EQ(s.size(), 1);

    s.pop();
    EXPECT_THROW(s.top(), std::logic_error);
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(TestTStack, pop_throws_exception_in_tstack) {
    TStack<int> s;
    EXPECT_ANY_THROW(s.pop());
}


TEST(TestTStack, is_empty_returns_true_for_empty_tstack) {
    TStack<int> s;
    EXPECT_TRUE(s.is_empty());

}

TEST(TestTStack, is_empty_returns_false_after_push) {
    TStack<int> s;
    s.push(100);
    EXPECT_FALSE(s.is_empty());
}

TEST(TestTStack, is_empty_returns_true_after_clear) {
    TStack<int> s;
    s.push(7);
    EXPECT_FALSE(s.is_empty());

    s.clear();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestTStack, is_empty_returns_true_after_pop_all) {
    TStack<int> s;
    s.push(7);
    s.push(9);
    EXPECT_FALSE(s.is_empty());
    s.pop();
    s.pop();
    EXPECT_TRUE(s.is_empty());
}


TEST(TestTStack, can_clear_correctly) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.top(), 2);
    s.clear();
    EXPECT_TRUE(s.is_empty());
    EXPECT_THROW(s.top(), std::logic_error);
}

TEST(TestTStack, top_returns_correct_value) {
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(TestTStack, top_throws_exception_when_empty_stack) {
    TStack<int> s;
    EXPECT_THROW(s.top(), std::logic_error);

    TStack<int> s1;
    s1.push(3);
    s1.pop();
    EXPECT_THROW(s1.top(), std::logic_error);
}

TEST(TestTStack, top_after_clear_throws_exception) {
    TStack<int> s;
    s.push(1);
    s.clear();
    EXPECT_THROW(s.top(), std::logic_error);
    s.push(1);
    EXPECT_EQ(s.top(), 1);
}