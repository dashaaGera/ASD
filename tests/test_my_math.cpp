#include <gtest/gtest.h>
#include "../lib_my_math/my_math.h"
#include <cmath>

TEST(TestMath, my_abs_work_corretly) {
    EXPECT_EQ(my_abs(5), 5);
    EXPECT_EQ(my_abs(0), 0);
    EXPECT_EQ(my_abs(-5), 5);
}

TEST(TestMath, my_pow_work_corretly) {
    EXPECT_EQ(power(5, 3), 125);
    EXPECT_EQ(power(0, 5), 0);
}
TEST(TestMath, my_sin_work_corretly) {

    EXPECT_NEAR(my_sin(0), 0.0, 1e-5);
    EXPECT_NEAR(my_sin(1), std::sin(1.0), 0.1);
    EXPECT_NEAR(my_sin(-1), std::sin(-1.0), 0.1);
    EXPECT_NEAR(my_sin(2), std::sin(2.0), 0.1);
    EXPECT_NEAR(my_sin(145), std::sin(145.0), 0.1);
}

TEST(TestMath, my_cos_work_corretly) {
    EXPECT_NEAR(my_cos(0), 1.0, 1e-5);
    EXPECT_NEAR(my_cos(1), std::cos(1.0), 0.1);
    EXPECT_NEAR(my_cos(-1), std::cos(-1.0), 0.1);
    EXPECT_NEAR(my_cos(3), std::cos(3.0), 0.1);
    EXPECT_NEAR(my_cos(234), std::cos(234.0), 0.1);
}

TEST(TestMath, my_tg_work_corretly) {
    EXPECT_NEAR(my_tg(0), 0.0, 1e-5);
    EXPECT_NEAR(my_tg(1), std::tan(1.0), 0.1);
    EXPECT_NEAR(my_tg(56), std::tan(56.0), 0.1);
}