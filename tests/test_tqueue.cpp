#include <gtest/gtest.h>
#include "../lib_tqueue/tqueue.h"


TEST(TestQueue, copy_queue_work_correctly) {
    Queue<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    Queue<int> copy(original);
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.head(), copy.head());
}

TEST(TestQueue, push_pop_work_correctly) {
    Queue<int> q;

    q.push(100);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.size(), 1);

    q.push(200);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.size(), 2);

    q.push(300);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.size(), 3);

    q.pop();
    EXPECT_EQ(q.head(), 200);
    EXPECT_EQ(q.size(), 2);

    q.pop();
    EXPECT_EQ(q.head(), 300);
    EXPECT_EQ(q.size(), 1);

    q.pop();
    EXPECT_THROW(q.head(), std::logic_error);
    EXPECT_EQ(q.size(), 0);

}

TEST(TestQueue, pop_throws_exception) {
    Queue<int> q;
    EXPECT_ANY_THROW(q.pop());
}


TEST(TestQueue, is_empty_returns_true_for_empty_queue) {
    Queue<int> q;
    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, is_empty_returns_false_after_push) {
    Queue<int> q;
    q.push(100);
    EXPECT_FALSE(q.is_empty());
}

TEST(TestQueue, is_empty_returns_true_after_clear) {
    Queue<int> q;
    q.push(7);
    EXPECT_FALSE(q.is_empty());

    q.clear();
    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, is_empty_returns_true_after_pop_all) {
    Queue<int> q;
    q.push(7);
    q.push(9);
    EXPECT_FALSE(q.is_empty());
    q.pop();
    q.pop();
    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, can_clear_correctly) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.head(), 1);
    EXPECT_EQ(q.size(), 2);
    q.clear();
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_THROW(q.head(), std::logic_error);

    q.push(7);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.head(), 7);
}

TEST(TestQueue, head_returns_correct_value) {
    Queue<int> q;
    q.push(10);
    EXPECT_EQ(q.head(), 10);
    q.push(20);
    EXPECT_EQ(q.head(), 10);
    q.push(30);
    EXPECT_EQ(q.head(), 10);
    q.pop();
    EXPECT_EQ(q.head(), 20);
    q.pop();
    EXPECT_EQ(q.head(), 30);
}

TEST(TestQueue, head_throws_exception_when_empty_queue) {
    Queue<int> q;
    EXPECT_THROW(q.head(), std::logic_error);

    Queue<int> q1;
    q1.push(3);
    q1.pop();
    EXPECT_THROW(q1.head(), std::logic_error);
}

TEST(TestQueue, head_after_clear_throws_exception) {
    Queue<int> q;
    q.push(1);
    q.clear();
    EXPECT_THROW(q.head(), std::logic_error);
}
