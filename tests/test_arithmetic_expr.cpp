#include "../lib_arithmetic_expr/arithmetic_expr.h"
#include <gtest/gtest.h>

TEST(TestExpression, constructor_with_parser_work_correcty) {
    EXPECT_NO_THROW(Expression expr("x + 5"));
    EXPECT_NO_THROW(Expression expr("sin(x)"));
    EXPECT_NO_THROW(Expression expr("3 * (-x + 5)"));


    Expression expr("x + y * 2");
    const List<Lexem>& lexems = expr.get_expression();

    EXPECT_FALSE(lexems.is_empty());
    EXPECT_EQ(lexems.size(), 5);


    List<Lexem>::Iterator it = lexems.begin();

    EXPECT_EQ((*it).name, "x");
    EXPECT_EQ((*it).type, LexemeType::Variable);
    ++it;

    EXPECT_EQ((*it).name, "+");
    EXPECT_EQ((*it).type, LexemeType::Operator);
    ++it;

    EXPECT_EQ((*it).name, "y");
    EXPECT_EQ((*it).type, LexemeType::Variable);
    ++it;

    EXPECT_EQ((*it).name, "*");
    EXPECT_EQ((*it).type, LexemeType::Operator);
    ++it;

    EXPECT_EQ((*it).name, "2");
    EXPECT_EQ((*it).type, LexemeType::Constant);
    ++it;

}

TEST(TestExpression, constructor_throws_on_no_correct_expression) {
    EXPECT_THROW(Expression expr("x + "), std::logic_error);
    EXPECT_THROW(Expression expr("sin x"), std::logic_error);
    EXPECT_THROW(Expression expr(") x + 5"), std::logic_error);
}

TEST(TestExpression, construct_polish_record_with_add_digits) {
    Expression expr("3 + 4");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 3);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "3");
    EXPECT_EQ((*it).type, LexemeType::Constant);
    ++it;

    EXPECT_EQ((*it).name, "4");
    EXPECT_EQ((*it).type, LexemeType::Constant);
    ++it;

    EXPECT_EQ((*it).name, "+");
    EXPECT_EQ((*it).type, LexemeType::Operator);
    ++it;

    EXPECT_EQ(it, polish.end());
}


TEST(TestExpression, construct_polish_record_with_brakets_and_simple_operators) {
    Expression expr("(x + 4) * 2");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 5);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "x"); ++it;
    EXPECT_EQ((*it).name, "4"); ++it;
    EXPECT_EQ((*it).name, "+"); ++it;
    EXPECT_EQ((*it).name, "2"); ++it;
    EXPECT_EQ((*it).name, "*"); ++it;

    EXPECT_EQ(it, polish.end());
}

TEST(TestExpression, construct_polish_record_with_function) {
    Expression expr("sin(x)");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 2);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "x");
    EXPECT_EQ((*it).type, LexemeType::Variable);
    ++it;

    EXPECT_EQ((*it).name, "sin");
    EXPECT_EQ((*it).type, LexemeType::Function);
    ++it;

    EXPECT_EQ(it, polish.end());
}

TEST(TestExpression, construct_polish_record_abs) {
    Expression expr("|x + -3|");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 5);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "x"); ++it;
    EXPECT_EQ((*it).name, "3"); ++it;
    EXPECT_EQ((*it).name, "~");
    EXPECT_EQ((*it).type, LexemeType::UnOperator);
    ++it;
    EXPECT_EQ((*it).name, "+"); ++it;
    EXPECT_EQ((*it).name, "abs"); ++it;

    EXPECT_EQ(it, polish.end());
}

TEST(TestExpression, construct_polish_record_with_un_operator) {
    Expression expr("-x + -5");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 5);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "x"); ++it;
    EXPECT_EQ((*it).name, "~"); ++it;
    EXPECT_EQ((*it).name, "5"); ++it;
    EXPECT_EQ((*it).name, "~"); ++it;
    EXPECT_EQ((*it).name, "+"); ++it;

    EXPECT_EQ(it, polish.end());
}

TEST(TestExpression, construct_polish_record_with_abs_and_function) {
    Expression expr("x * |cos(9)|");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 5);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "x"); ++it;
    EXPECT_EQ((*it).name, "9"); ++it;
    EXPECT_EQ((*it).name, "cos"); ++it;
    EXPECT_EQ((*it).name, "abs"); ++it;
    EXPECT_EQ((*it).name, "*"); ++it;

    EXPECT_EQ(it, polish.end());
}

TEST(TestExpression, construct_polish_record_with_different_operators_brackets_and_functions) {
    Expression expr("{(x_1^5) * |cos(5^{-9+z})|}+[5*y]");
    expr.construct_polish_record();
    const List<Lexem>& polish = expr.get_polish_record();

    EXPECT_EQ(polish.size(), 16);

    List<Lexem>::Iterator it = polish.begin();
    EXPECT_EQ((*it).name, "x_1");
    EXPECT_EQ((*it).type, LexemeType::Variable);
    ++it;
    EXPECT_EQ((*it).name, "5"); ++it;
    EXPECT_EQ((*it).name, "^"); ++it;
    EXPECT_EQ((*it).name, "5"); ++it;
    EXPECT_EQ((*it).name, "9"); ++it;
    EXPECT_EQ((*it).name, "~"); ++it;
    EXPECT_EQ((*it).name, "z"); ++it;
    EXPECT_EQ((*it).name, "+"); ++it;
    EXPECT_EQ((*it).name, "^"); ++it;
    EXPECT_EQ((*it).name, "cos"); ++it;
    EXPECT_EQ((*it).name, "abs"); ++it;
    EXPECT_EQ((*it).name, "*"); ++it;
    EXPECT_EQ((*it).name, "5"); ++it;
    EXPECT_EQ((*it).name, "y"); ++it;
    EXPECT_EQ((*it).name, "*"); ++it;
    EXPECT_EQ((*it).name, "+"); ++it;

    EXPECT_EQ(it, polish.end());

    Expression expr1("(5+x*3)*y^3+sin(x)*5");
    expr1.construct_polish_record();
    const List<Lexem>& polish1 = expr1.get_polish_record();

    EXPECT_EQ(polish1.size(), 14);

    List<Lexem>::Iterator it1 = polish1.begin();
    EXPECT_EQ((*it1).name, "5");++it1;
    EXPECT_EQ((*it1).name, "x"); ++it1;
    EXPECT_EQ((*it1).name, "3"); ++it1;
    EXPECT_EQ((*it1).name, "*"); ++it1;
    EXPECT_EQ((*it1).name, "+"); ++it1;
    EXPECT_EQ((*it1).name, "y"); ++it1;
    EXPECT_EQ((*it1).name, "3"); ++it1;
    EXPECT_EQ((*it1).name, "^"); ++it1;
    EXPECT_EQ((*it1).name, "*"); ++it1;
    EXPECT_EQ((*it1).name, "x"); ++it1;
    EXPECT_EQ((*it1).name, "sin"); ++it1;
    EXPECT_EQ((*it1).name, "5"); ++it1;
    EXPECT_EQ((*it1).name, "*"); ++it1;
    EXPECT_EQ((*it1).name, "+"); ++it1;

    EXPECT_EQ(it1, polish.end());
}

TEST(TestExpression, calculate_expr_with_add_digits_work_corretly) {
    Expression expr("3 + 4");
    int result = expr.calculate();
    EXPECT_EQ(result, 7);

}

TEST(TestExpression, calculate_expr_with_mul_digits_corretly) {
    Expression expr("5 * 3");
    int result = expr.calculate();
    EXPECT_EQ(result, 15);
}

TEST(TestExpression, calculate_expr_with_div_digits_corretly) {
    Expression expr("10 / 2");
    int result = expr.calculate();
    EXPECT_EQ(result, 5);
}

TEST(TestExpression, calculate_expr_with_pow_digits_corretly) {
    Expression expr("2 ^ 3");
    int result = expr.calculate();
    EXPECT_EQ(result, 8);

    Expression expr1("3 ^ (3 ^ 2)");
    int result1 = expr1.calculate();
    EXPECT_EQ(result1, 19683);
}

TEST(TestExpression, calculate_expr_with_brakets_and_digits_corretly) {
    Expression expr("(3 + 4) * 2");
    int result = expr.calculate();
    EXPECT_EQ(result, 14);

    Expression expr1("3 + 4 * 2");
    int result1 = expr1.calculate();
    EXPECT_EQ(result1, 11);

}

TEST(TestExpression, calculate_expr_with_un_operator_corretly) {
    Expression expr("-5 + 3");
    int result = expr.calculate();
    EXPECT_EQ(result, -2);

    Expression expr1("-(-5)");
    int result1 = expr1.calculate();
    EXPECT_EQ(result1, 5);
}

TEST(TestExpression, calculate_expr_with_abs_corretly) {
    Expression expr("|-5|");
    int result = expr.calculate();
    EXPECT_EQ(result, 5);

    Expression expr1("|-5 + 3|");
    int result1 = expr1.calculate();
    EXPECT_EQ(result1, 2);
}


TEST(TestExpression, calculate_expr_with_sin_corretly) {
    Expression expr("sin(0)");
    int result = expr.calculate();
    EXPECT_EQ(result, 0);
}

TEST(TestExpression, calculate_expr_with_cos_corretly) {
    Expression expr("cos(0)");
    int result = expr.calculate();
    EXPECT_EQ(result, 1);
}

TEST(TestExpression, calculate_expr_with_functions_and_operators_corretly) {
    Expression expr("sin(0) + cos(0) * 2");
    int result = expr.calculate();
    EXPECT_EQ(result, 2);
}

TEST(TestExpression, calculate_expr_with_div_by_zero_corretly) {
    Expression expr("5 / 0");
    EXPECT_THROW(expr.calculate(), std::logic_error);
}

TEST(TestExpression, calculate_difficult_expr_corretly) {
    Expression expr("sin(-50)-3*-9+||-5| + 3|/2^6+tg(50)");
    double result = expr.calculate();
    EXPECT_NEAR(result, 27.115, 0.1);
}
