#include <gtest/gtest.h>
#include "../lib_monom/monom.h"


TEST(TestMonom, can_create_with_default_constructor_correctly) {
    Monom m1;
    EXPECT_EQ(m1.coeff(), 0);
    EXPECT_EQ(m1.power_x(), 0);
    EXPECT_EQ(m1.power_y(), 0);
    EXPECT_EQ(m1.power_z(), 0);
}

TEST(TestMonom, can_create_with_init_constructor_correctly) {
    int powers[VARS_COUNT] = { 7, 2, 3 };
    Monom m1(2.0, powers);
    EXPECT_EQ(m1.coeff(), 2.0);
    EXPECT_EQ(m1.power_x(), 7);
    EXPECT_EQ(m1.power_y(), 2);
    EXPECT_EQ(m1.power_z(), 3);
}

TEST(TestMonom, can_create_with_initializer_list_constructor_correctly) {
    Monom m1{ 0.5 };                    
    EXPECT_EQ(m1.coeff(), 0.5);

    Monom m2{ 2.5, 1 };                
    EXPECT_EQ(m2.coeff(), 2.5);
    EXPECT_EQ(m2.power_x(), 1);

    Monom m3{ 2.5, 1, 2 };            
    EXPECT_EQ(m3.coeff(), 2.5);
    EXPECT_EQ(m3.power_x(), 1);
    EXPECT_EQ(m3.power_y(), 2);

    Monom m4{ 2.5, 1, 2, 3 };          
    EXPECT_EQ(m4.coeff(), 2.5);
    EXPECT_EQ(m4.power_x(), 1);
    EXPECT_EQ(m4.power_y(), 2);
    EXPECT_EQ(m4.power_z(), 3);
}

TEST(TestMonom, can_create_with_copy_constructor) {
    Monom m{ 2.5, 1, 2, 3 };
    Monom m1(m);
    EXPECT_EQ(m.coeff(), 2.5);
    EXPECT_EQ(m.power_x(), 1);
    EXPECT_EQ(m.power_y(), 2);
    EXPECT_EQ(m.power_z(), 3);
    
}

TEST(TestMonom, can_add_2_similar_monoms) {
    Monom m1{ 2.5, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    Monom result = { 5.5,1,2,3 };
    EXPECT_EQ(m1+m2, result);
}


TEST(TestMonom, can_add_2_not_similar_monoms) {
    Monom m1{ 2.5, 1, 4, 3 };
    Monom m2{ 3,1,2,3 };
    ASSERT_THROW(m1+m2, std::logic_error);
}

TEST(TestMonom, can_sub_2_similar_monoms) {
    Monom m1{ 2.5, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    Monom result = { -0.5,1,2,3 };
    EXPECT_EQ(m1 + m2, result);
}


TEST(TestMonom, can_sub_2_not_similar_monoms) {
    Monom m1{ 2.5, 1, 4, 3 };
    Monom m2{ 3,1,2,3 };
    ASSERT_THROW(m1 - m2, std::logic_error);
}

TEST(TestMonom, can_mul_2_monoms) {
    Monom m1{ 6, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    Monom result = { 18,2,4,6 };
    EXPECT_EQ(m1 * m2, result);

    Monom m3{ 0, 1, 2, 3 };
    Monom result1 = { 0,0,0,0 };
    EXPECT_EQ(m3* m2, result1);
}

TEST(TestMonom, can_div_2_monoms) {
    Monom m1{ 6, 1, 2, 6 };
    Monom m2{ 3,1,2,3 };
    Monom result = { 2,0,0,3 };
    EXPECT_EQ(m1 / m2, result);

    Monom m3{ 0, 1, 2, 3 };
    ASSERT_THROW(m1 /m3, std::logic_error);
}


TEST(TestMonom, can_mul_monom_on_scalar) {
    Monom m1{ 6, 1, 2, 6 };
    Monom result = { 30,1,2,6 };
    EXPECT_EQ(m1*5, result);
    EXPECT_EQ(5* m1 , result);
    EXPECT_EQ(m1 * 5, 5*m1);
}

TEST(TestMonom, can_div_monom_on_scalar) {
    Monom m1{ 6, 1, 2, 6 };
    Monom result = { 1,1,2,6 };
    EXPECT_EQ(m1 / 6, result);
}

TEST(TestMonom, can_add_equal_2_similar_monoms) {
    Monom m1{ 2.5, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    Monom result = { 5.5,1,2,3 };
    EXPECT_EQ(m1 += m2, result);
}


TEST(TestMonom, can_add_equal_2_not_similar_monoms) {
    Monom m1{ 2.5, 1, 4, 3 };
    Monom m2{ 3,1,2,3 };
    ASSERT_THROW(m1 += m2, std::logic_error);
}

TEST(TestMonom, can_sub_equal_2_similar_monoms) {
    Monom m1{ 2.5, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    Monom result = { -0.5,1,2,3 };
    EXPECT_EQ(m1 += m2, result);
}


TEST(TestMonom, can_sub_equal_2_not_similar_monoms) {
    Monom m1{ 2.5, 1, 4, 3 };
    Monom m2{ 3,1,2,3 };
    ASSERT_THROW(m1 -= m2, std::logic_error);
}

TEST(TestMonom, can_mul_equal_2_monoms) {
    Monom m1{ 6, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    Monom result = { 18,2,4,6 };
    EXPECT_EQ(m1 *= m2, result);

    Monom m3{ 0, 1, 2, 3 };
    Monom result1 = { 0,0,0,0 };
    EXPECT_EQ(m3 *= m2, result1);
}

TEST(TestMonom, can_div_equal_2_monoms) {
    Monom m1{ 6, 1, 2, 6 };
    Monom m2{ 3,1,2,3 };
    Monom result = { 2,0,0,3 };
    EXPECT_EQ(m1 /= m2, result);

    Monom m3{ 0, 1, 2, 3 };
    ASSERT_THROW(m2 /= m3, std::logic_error);
}

TEST(TestMonom, 2_monoms_is_similar) {
    Monom m1{ 6, 1, 2, 3 };
    Monom m2{ 3,1,2,3 };
    EXPECT_EQ(m1 == m2, true);
    EXPECT_EQ(m1 == m1, true);
}

TEST(TestMonom, 2_monoms_is_not_similar) {
    Monom m1{ 6, 1, 2, 3 };
    Monom m2{ 3,1,7,3 };
    EXPECT_EQ(m1 != m2, true);

}

TEST(TestMonom, output_operator) {
    Monom m = { 1.5, 2, 3, 4 };
    std::stringstream os;
    os << m;
    EXPECT_EQ(os.str(), "1.5x^2y^3z^4");
}

TEST(TestMonom, input_operator) {
    Monom m;
    std::stringstream is1("-.5x^2y^3z^4");
    is1 >> m;
    EXPECT_EQ(m.coeff(), -0.5);
    EXPECT_EQ(m.power_x(), 2);
    EXPECT_EQ(m.power_y(), 3);
    EXPECT_EQ(m.power_z(), 4);

}

TEST(TestMonom, comparison_operators) {
    Monom m1{ 1.0, 2, 0, 0 };
    Monom m2{ 1.0, 1, 0, 0 };  
    EXPECT_TRUE(m1 > m2);    
    EXPECT_TRUE(m2 < m1);

    Monom m3{ 1.0, 1, 2, 0 };  
    Monom m4{ 1.0, 1, 1, 0 };  
    EXPECT_TRUE(m3 > m4);
    EXPECT_TRUE(m4 < m3);

    Monom m5{ 1.0, 1, 1, 3 };  
    Monom m6{ 1.0, 1, 1, 2 };  
    EXPECT_TRUE(m5 > m6);   
    EXPECT_TRUE(m6 < m5);

    Monom m7{ 2.0, 1, 2, 3 };  
    Monom m8{ 3.0, 1, 2, 3 };  
    EXPECT_TRUE(m7 < m8);   
    EXPECT_TRUE(m8 >m7);   
   
}

TEST(TestMonom, parse_monom){
    Monom m1("2x^2");
    EXPECT_DOUBLE_EQ(m1.coeff(), 2.0);
    EXPECT_EQ(m1.power_x(), 2);
    EXPECT_EQ(m1.power_y(), 0);
    EXPECT_EQ(m1.power_z(), 0);

    Monom m2("-3.5y^3");
    EXPECT_DOUBLE_EQ(m2.coeff(), -3.5);
    EXPECT_EQ(m2.power_x(), 0);
    EXPECT_EQ(m2.power_y(), 3);
    EXPECT_EQ(m2.power_z(), 0);


    Monom m3(".5x^2y^3z");
    EXPECT_DOUBLE_EQ(m3.coeff(), 0.5);
    EXPECT_EQ(m3.power_x(), 2);
    EXPECT_EQ(m3.power_y(), 3);
    EXPECT_EQ(m3.power_z(), 1);

    Monom m4("5");
    EXPECT_DOUBLE_EQ(m4.coeff(), 5.0);
    EXPECT_EQ(m4.power_x(), 0);
    EXPECT_EQ(m4.power_x(), 0);
    EXPECT_EQ(m4.power_x(), 0);

    Monom m5("0");
    EXPECT_DOUBLE_EQ(m5.coeff(), 0.0);

    
}
