#include <gtest/gtest.h>
#include "../lib_queue/queue.h"
TEST(TestQueue, can_create_with_defuault_constructor) {
    ASSERT_NO_THROW(Queue<int> q);
}

TEST(TestQueue, can_create_with_default_constructor_correctly) {
    Queue<int> q;
    EXPECT_EQ(q.size(), 20);
    EXPECT_NE(q.data(), nullptr);
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_EQ(q.count(), 0);
    EXPECT_TRUE(q.is_empty());
    EXPECT_THROW(q.head(), std::logic_error);
}

TEST(TestQueue, push_pop_work_correctly) {
    Queue<int> q(3);

    q.push(100);
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.count(), 1);

    q.push(200);
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.count(), 2);

    q.push(300);
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_EQ(q.head(), 100);
    EXPECT_EQ(q.count(), 3);

    q.pop();
    EXPECT_EQ(q.head_index(), 1);
    EXPECT_EQ(q.head(), 200);
    EXPECT_EQ(q.count(), 2);

    q.pop();
    EXPECT_EQ(q.head_index(), 2);
    EXPECT_EQ(q.head(), 300);
    EXPECT_EQ(q.count(), 1);

    q.pop();
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_THROW(q.head(), std::logic_error);
    EXPECT_EQ(q.count(), 0);

}

TEST(TestQueue, pop_throws_exception) {
    Queue<int> q;
    EXPECT_ANY_THROW(q.pop());
}

TEST(TestQueue, push_throws_exception) {
    Queue<int> q(3);
    q.push(6);
    q.push(1);
    q.push(8);
    EXPECT_ANY_THROW(q.push(5));
}


TEST(TestQueue, is_empty_returns_true_for_empty_queue) {
    Queue<int> q;
    EXPECT_TRUE(q.is_empty());

    Queue<int> q2(10);
    EXPECT_TRUE(q2.is_empty());
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

TEST(TestQueue, is_full_returns_false_for_empty_queue) {
    Queue<int> q(5);
    EXPECT_FALSE(q.is_full());
}

TEST(TestQueue, is_full_returns_false_for_partially_filled_queue) {
    Queue<int> q(3);
    q.push(10);
    EXPECT_FALSE(q.is_full());

    q.push(20);
    EXPECT_FALSE(q.is_full());
}

TEST(TestQueue, is_full_returns_true_when_queue_full) {
    Queue<int> q(3);
    q.push(10);
    q.push(20);
    q.push(30);
    EXPECT_TRUE(q.is_full());
}


TEST(TestQueue, can_clear_correctly) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_EQ(q.count(), 2);
    q.clear();
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.head_index(), 0);
    EXPECT_EQ(q.count(), 0);
    EXPECT_THROW(q.head(), std::logic_error);
}

TEST(TestQueue, head_returns_correct_value) {
    Queue<int> q(3);
    q.push(10);
    q.push(20);
    q.push(30);
    EXPECT_EQ(q.head(), 10);
    q.pop();
    EXPECT_EQ(q.head(), 20);
    q.pop();
    EXPECT_EQ(q.head(), 30);
}

TEST(TestQueue, top_throws_exception_when_empty_queue) {
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



