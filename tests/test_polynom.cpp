#include "../lib_polynom/polynom.h"

#include <gtest/gtest.h>
TEST(TestPolynom, can_create_with_default_constructor_correctly) {
    Polynom p;
    EXPECT_TRUE(p.is_empty());
    EXPECT_EQ(p.size(), 0);
}

TEST(TestPolynom, can_create_with_monom_constructor) {
    Monom m{ 2.5, 1, 2, 3 };
    Polynom p(m);
    EXPECT_FALSE(p.is_empty());
    EXPECT_EQ(p.size(), 1);
    EXPECT_EQ(p.get_terms().head()->value.coeff(), 2.5);
}

TEST(TestPolynom, can_create_with_initializer_list_of_monoms) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0}, {-4.0, 0, 0, 0} };
    EXPECT_EQ(p.size(), 3);
}

TEST(TestPolynom, can_create_with_initializer_list_of_numbers) {
    Polynom p{ 2.5, 1, 2, 3 };
    EXPECT_EQ(p.size(), 1);
    EXPECT_EQ(p.get_terms().head()->value.coeff(), 2.5);
}

TEST(TestPolynom, can_create_with_copy_constructor) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2(p1);
    EXPECT_EQ(p1, p2);
}

TEST(TestPolynom, can_add_monom_to_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 4.0, 0, 1, 0 };
    Polynom result = p + m;
    Polynom expected{ {2.0, 1, 0, 0}, {7.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_add_monom_to_polynom_with_new_monom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 4.0, 0, 0, 1 };
    Polynom result = p + m;
    Polynom expected{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0}, {4.0, 0, 0, 1} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_sub_monom_from_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 1.0, 1, 0, 0 };
    Polynom result = p - m;
    Polynom expected{ {1.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_mul_polynom_by_monom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 2.0, 1, 0, 0 };
    Polynom result = p * m;
    Polynom expected{ {4.0, 2, 0, 0}, {6.0, 1, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_add_2_polynoms) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {1.0, 1, 0, 0}, {-2.0, 0, 1, 0} };
    Polynom result = p1 + p2;
    Polynom expected{ {3.0, 1, 0, 0}, {1.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_sub_2_polynoms) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {1.0, 1, 0, 0}, {2.0, 0, 1, 0} };
    Polynom result = p1 - p2;
    Polynom expected{ {1.0, 1, 0, 0}, {1.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_mul_2_polynoms) {
    Polynom p1{ {2.0, 2, 1, 0}, {4.0, 5, 6, 7} }; 
    Polynom p2{ {3.0, 0, 1, 0}, {1.0, 7, 0, 0} };  
    Polynom p3= p1 * p2;

    Polynom expected{
        {4.0, 12, 6, 7},   
        {2.0, 9, 1, 0},    
        {12.0, 5, 7, 7},   
        {6.0, 2, 2, 0}     
    };

    EXPECT_EQ(p3, expected);
}
TEST(TestPolynom, can_mul_polynom_by_scalar) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom result = p * 2.0;
    Polynom expected{ {4.0, 1, 0, 0}, {6.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_mul_scalar_by_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom result = 2.0 * p;
    Polynom expected{ {4.0, 1, 0, 0}, {6.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_div_polynom_by_scalar) {
    Polynom p{ {4.0, 1, 0, 0}, {6.0, 0, 1, 0} };
    Polynom result = p / 2.0;
    Polynom expected{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, can_not_div_polynom_by_zero) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    ASSERT_THROW(p / 0.0, std::logic_error);
}

TEST(TestPolynom, unary_minus_on_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom result = -p;
    Polynom expected{ {-2.0, 1, 0, 0}, {-3.0, 0, 1, 0} };
    EXPECT_EQ(result, expected);
}


TEST(TestPolynom, can_add_assign_polynom) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {1.0, 1, 0, 0}, {-2.0, 0, 1, 0} };
    p1 += p2;
    Polynom expected{ {3.0, 1, 0, 0}, {1.0, 0, 1, 0} };
    EXPECT_EQ(p1, expected);
}

TEST(TestPolynom, can_sub_assign_polynom) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {1.0, 1, 0, 0}, {2.0, 0, 1, 0} };
    p1 -= p2;
    Polynom expected{ {1.0, 1, 0, 0}, {1.0, 0, 1, 0} };
    EXPECT_EQ(p1, expected);
}

TEST(TestPolynom, can_mul_assign_polynom) {
    Polynom p1{ {2.0, 2, 1, 0} ,{4.0,5,6,7} };  
    Polynom p2{ {3.0, 0, 1, 0},{1.0,7,0,0} };  
    p1 *= p2;
    Polynom expected{ {4.0,12,6,7},{2.0,9,1,0} ,{ 12.0,5,7,7 },{6.0,2,2,0} };
    EXPECT_EQ(p1, expected);
}

TEST(TestPolynom, can_mul_assign_scalar) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    p *= 2.0;
    Polynom expected{ {4.0, 1, 0, 0}, {6.0, 0, 1, 0} };
    EXPECT_EQ(p, expected);
}

TEST(TestPolynom, can_div_assign_scalar) {
    Polynom p{ {4.0, 1, 0, 0}, {6.0, 0, 1, 0} };
    p /= 2.0;
    Polynom expected{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    EXPECT_EQ(p, expected);
}

TEST(TestPolynom, can_add_assign_monom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 4.0, 0, 1, 0 };
    p += m;
    Polynom expected{ {2.0, 1, 0, 0}, {7.0, 0, 1, 0} };
    EXPECT_EQ(p, expected);
}

TEST(TestPolynom, can_sub_assign_monom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 1.0, 1, 0, 0 };
    p -= m;
    Polynom expected{ {1.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    EXPECT_EQ(p, expected);
}

TEST(TestPolynom, can_mul_assign_monom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 2.0, 1, 0, 0 };
    p *= m;
    Polynom expected{ {4.0, 2, 0, 0}, {6.0, 1, 1, 0} };
    EXPECT_EQ(p, expected);
}

TEST(TestPolynom, 2_polynoms_are_equal) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(TestPolynom, 2_polynoms_are_not_equal) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {2.0, 1, 0, 0}, {4.0, 0, 2, 0} };
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 == p2);
}

TEST(TestPolynom, polynoms_with_different_order_are_equal_after_simplify) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2{ {3.0, 0, 1, 0}, {2.0, 1, 0, 0} };
    EXPECT_EQ(p1, p2);
}


TEST(TestPolynom, can_evaluate_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} }; 
    double result = p.evaluate(2.0, 3.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 2.0 * 2.0 + 3.0 * 3.0); 
}

TEST(TestPolynom, can_evaluate_empty_polynom) {
    Polynom p;
    double result = p.evaluate(2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(TestPolynom, can_evaluate_polynom_with_all_variables) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0}, {4.0, 0, 0, 1} }; 
    double result = p.evaluate(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(result, 2.0 * 1.0 + 3.0 * 2.0 + 4.0 * 3.0); 
}

TEST(TestPolynom, output_operator) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0}, {-4.0, 0, 0, 0} };
    std::stringstream os;
    os << p;
    EXPECT_EQ(os.str(), "2x^1 + 3y^1 - 4");
}

TEST(TestPolynom, output_operator_for_empty_polynom) {
    Polynom p;
    std::stringstream os;
    os << p;
    EXPECT_EQ(os.str(), "0");
}

TEST(TestPolynom, input_operator) {
    Polynom p;
    std::stringstream is1("3y+ 2x  - 4");
    is1 >> p;
    Polynom expected1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0}, {-4.0, 0, 0, 0} };
    EXPECT_EQ(p, expected1);

    std::stringstream is2("x^2 + 2xy + y^2");
    is2 >> p;
    Polynom expected2{ {1.0, 2, 0, 0}, {2.0, 1, 1, 0}, {1.0, 0, 2, 0} };
    EXPECT_EQ(p, expected2);

    std::stringstream is3("-3.5x^2y^3 + 2z - 1");
    is3 >> p;
    Polynom expected3{ {-3.5, 2, 3, 0}, {2.0, 0, 0, 1}, {-1.0, 0, 0, 0} };
    EXPECT_EQ(p, expected3);
}

TEST(TestPolynom, monoms_are_sorted_correctly) {
    std::stringstream is("6 + x^1y^1 + 2y^2 + 1y^2z^3");
    Polynom p;
    is >> p;

    std::stringstream os;
    os << p;
    std::string result = os.str();

    size_t xy_pos = result.find("x^1y^1");
    size_t y2z3_pos = result.find("y^2z^3");
    size_t y2_pos = result.find("2y^2");
    size_t const_pos = result.find("6");
    EXPECT_TRUE(xy_pos != std::string::npos);
    EXPECT_TRUE(y2z3_pos != std::string::npos);
    EXPECT_TRUE(y2_pos != std::string::npos);
    EXPECT_TRUE(const_pos != std::string::npos);

    if (xy_pos != std::string::npos && y2z3_pos != std::string::npos) {
        EXPECT_TRUE(y2z3_pos > xy_pos);
    }

    if (const_pos != std::string::npos && xy_pos != std::string::npos) {
        EXPECT_TRUE(const_pos > xy_pos);
    }
}

TEST(TestPolynom, left_addition_monom_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 4.0, 0, 0, 1 };
    Polynom result = m + p;
    Polynom expected = p + m;
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, left_subtraction_monom_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 4.0, 0, 0, 1 };
    Polynom result = m - p;
    Polynom expected{  {-2.0, 1, 0, 0}, {-3.0, 0, 1, 0} ,{4.0, 0, 0, 1}};
    EXPECT_EQ(result, expected);
}

TEST(TestPolynom, left_multiplication_monom_polynom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 2.0, 1, 0, 0 };
    Polynom result = m * p;
    Polynom expected = p * m;
    EXPECT_EQ(result, expected);
}


TEST(TestPolynom, addition_with_empty_polynom) {
    Polynom p1{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom p2;
    Polynom result = p1 + p2;
    EXPECT_EQ(result, p1);
}

TEST(TestPolynom, multiplication_by_zero_scalar) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Polynom result = p * 0.0;
    EXPECT_TRUE(result.is_empty());
    p *= 0.0;
    EXPECT_TRUE(p.is_empty());
}

TEST(TestPolynom, multiplication_by_zero_monom) {
    Polynom p{ {2.0, 1, 0, 0}, {3.0, 0, 1, 0} };
    Monom m{ 0.0, 1, 0, 0 };
    Polynom result = p * m;
    EXPECT_TRUE(result.is_empty());

    p *= m;
    EXPECT_TRUE(p.is_empty());
}


TEST(PolynomParseTest, three_monoms_with_spaces_no_iterators) {
    Polynom p = Polynom::parse("-3z+yx^2+2y");
    Monom m1(1.0, 2, 1, 0);   
    Monom m2(2.0, 0, 1, 0);  
    Monom m3(-3.0, 0, 0, 1);  
    Polynom expected;
    expected += m1;
    expected += m2;
    expected += m3;

    EXPECT_TRUE(p == expected);


    Polynom p1 = Polynom::parse(".5");
    Monom m(0.5, 0, 0, 0);
    Polynom expected1;
    expected1 += m;
    EXPECT_TRUE(p1 == expected1);
}
