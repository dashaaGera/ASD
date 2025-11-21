#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

TEST(TestCheckBreckets, check_breckets_return_true_when_the_sequence_of_brackets_correct) {
    EXPECT_EQ(check_breckets("([()]){}"),true);
}

TEST(TestCheckBreckets, check_breckets_return_false_when_the_sequence_of_brackets_not_correct) {
    EXPECT_EQ(check_breckets("([()]){"), false);
}


TEST(TestCheckBreckets, check_breckets_return_false_when_the_amount_brackets_not_equal) {
    EXPECT_EQ(check_breckets("([()])(){"), false);
}

TEST(TestCheckBreckets, check_breckets_return_false_when_one_round_braket) {
    EXPECT_EQ(check_breckets("("), false);
}

TEST(TestCheckBreckets, check_breckets_return_false_when_one_square_braket) {
    EXPECT_EQ(check_breckets("["), false);
}
TEST(TestCheckBreckets, check_breckets_return_false_when_one_curly_braket) {
    EXPECT_EQ(check_breckets("{"), false);
}

TEST(TestCheckBreckets, check_breckets_return_true_when_pair_of_two_identical_brakets) {
    EXPECT_EQ(check_breckets("()"), true);
}

TEST(TestCheckBreckets, check_breckets_return_false_when_pair_of_two_not_identical_brakets) {
    EXPECT_EQ(check_breckets("(]"), false);
}

TEST(TestCycleList, has_cycle_hare_and_turtle_work_correctly_in_empty_list) {
    List<int> l1;
    EXPECT_EQ(has_cycle_hare_and_turtle(l1), false);
}

TEST(TestCycleList, has_cycle_hare_and_turtle_work_correctly_in_no_empty_list_without_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    EXPECT_EQ(has_cycle_hare_and_turtle(l1), false);
}

TEST(TestCycleList, has_cycle_hare_and_turtle_work_correctly_in_no_empty_list_with_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.tail()->next = l1.head()->next->next;
    EXPECT_EQ(has_cycle_hare_and_turtle(l1), true);
    l1.pop_back();

    List<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);
    l2.tail()->next = l2.head();
    EXPECT_EQ(has_cycle_hare_and_turtle(l2), true);
    l2.pop_back();
}

TEST(TestCycleList, has_cycle_reverse_pointers_work_correctly_in_empty_list) {
    List<int> l1;
    EXPECT_EQ(has_cycle_reverse_pointers(l1), false);
}

TEST(TestCycleList, has_cycle_reverse_pointers_work_correctly_in_no_empty_list_without_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    EXPECT_EQ(has_cycle_reverse_pointers(l1), false);
}

TEST(TestCycleList, has_cycle_reverse_pointers_work_correctly_in_no_empty_list_with_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.tail()->next = l1.head()->next->next;
    EXPECT_EQ(has_cycle_reverse_pointers(l1), true);

    List<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);
    l2.tail()->next = l2.head();
    EXPECT_EQ(has_cycle_reverse_pointers(l2), true);

}

