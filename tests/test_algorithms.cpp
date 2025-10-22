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



