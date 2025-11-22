#include "../lib_parser_arithmetic_expr/parser_arithmetic_expr.h"
#include "../lib_my_math/my_math.h"
#include <gtest/gtest.h>

TEST(TestLexem, init_constructor_work_corretly) {
    Lexem constant("42", LexemeType::Constant, 42.0);
    EXPECT_EQ(constant.name, "42");
    EXPECT_EQ(constant.type, LexemeType::Constant);
    EXPECT_EQ(constant.value, 42.0);

    Lexem variable("x", LexemeType::Variable);
    EXPECT_EQ(variable.name, "x");
    EXPECT_EQ(variable.type, LexemeType::Variable);

    Lexem variable1("x_1", LexemeType::Variable);
    EXPECT_EQ(variable1.name, "x_1");
    EXPECT_EQ(variable1.type, LexemeType::Variable);


    Lexem op("+", LexemeType::Operator, DBL_MAX, 1);
    EXPECT_EQ(op.name, "+");
    EXPECT_EQ(op.type, LexemeType::Operator);
    EXPECT_EQ(op.priority, 1);

    Lexem bracket("{", LexemeType::OpenBracket);
    EXPECT_EQ(bracket.name, "{");
    EXPECT_EQ(bracket.type, LexemeType::OpenBracket);

    Lexem func("sin", LexemeType::Function, DBL_MAX, 5, my_sin);
    EXPECT_EQ(func.name, "sin");
    EXPECT_EQ(func.type, LexemeType::Function);
    EXPECT_EQ(func.value, DBL_MAX);
    EXPECT_EQ(func.priority, 5);
    EXPECT_NE(func.function, nullptr);

    Lexem abs_bracket("|", LexemeType::OpenedAbs, DBL_MAX, 5);
    EXPECT_EQ(abs_bracket.name, "|");
    EXPECT_EQ(abs_bracket.type, LexemeType::OpenedAbs);
    EXPECT_EQ(abs_bracket.priority, 5);

    Lexem un_sub("~", LexemeType::UnOperator, DBL_MAX, 4);
    EXPECT_EQ(un_sub.name, "~");
    EXPECT_EQ(un_sub.type, LexemeType::UnOperator);
    EXPECT_EQ(un_sub.priority, 4);
}

TEST(TestParser, is_alpha_work_corretly) {
    EXPECT_TRUE(Parser::is_alpha('a'));
    EXPECT_TRUE(Parser::is_alpha('Z'));
    EXPECT_FALSE(Parser::is_alpha('9'));
    EXPECT_FALSE(Parser::is_alpha('-'));
    EXPECT_FALSE(Parser::is_alpha('('));
}

TEST(TestParser, is_digit_work_corretly) {
    EXPECT_TRUE(Parser::is_digit('9'));
    EXPECT_TRUE(Parser::is_digit('0'));
    EXPECT_FALSE(Parser::is_digit('e'));
    EXPECT_FALSE(Parser::is_digit('-'));
    EXPECT_FALSE(Parser::is_digit('('));
}

TEST(TestParser, is_variable_char_work_corretly) {
    EXPECT_TRUE(Parser::is_variable_char('9'));
    EXPECT_TRUE(Parser::is_variable_char('_'));
    EXPECT_TRUE(Parser::is_variable_char('e'));
    EXPECT_TRUE(Parser::is_variable_char('A'));
    EXPECT_FALSE(Parser::is_variable_char('-'));
    EXPECT_FALSE(Parser::is_variable_char('('));
}

TEST(TestParser, is_number_work_corretly) {
    EXPECT_TRUE(Parser::is_number("6"));
    EXPECT_TRUE(Parser::is_number("134"));
    EXPECT_FALSE(Parser::is_number("a"));
    EXPECT_FALSE(Parser::is_number("-"));
    EXPECT_FALSE(Parser::is_number("("));
}

TEST(TestParser, is_function_work_corretly) {
    EXPECT_TRUE(Parser::is_function("sin"));
    EXPECT_TRUE(Parser::is_function("cos"));
    EXPECT_TRUE(Parser::is_function("tg"));
    EXPECT_FALSE(Parser::is_function("Sin"));
}


TEST(TestParser, get_priority_work_corretly) {
    EXPECT_EQ(Parser::get_priority("+"), 1);
    EXPECT_EQ(Parser::get_priority("/"), 2);
    EXPECT_EQ(Parser::get_priority("^"), 3);
    EXPECT_EQ(Parser::get_priority("~"), 4);
    EXPECT_EQ(Parser::get_priority("sin"), 5);
    EXPECT_EQ(Parser::get_priority("2"), -1);
}

TEST(TestParser, parse_number_work_corretly) {
    List<Lexem> lexems1;
    size_t pos;

    std::string expr1 = "123";
    pos = 0;
    EXPECT_TRUE(Parser::parse_number(expr1, pos, lexems1, LexemeType::OpenedAbs));
    EXPECT_EQ(pos, 3);
    EXPECT_EQ(lexems1.size(), 1);
    EXPECT_EQ(lexems1.tail()->value.name, "123");
    EXPECT_EQ(lexems1.tail()->value.type, LexemeType::Constant);
    EXPECT_EQ(lexems1.tail()->value.value, 123);

    List<Lexem> lexems2;
    std::string expr2 = "-456";
    pos = 0;
    EXPECT_TRUE(Parser::parse_operator(expr2, pos, lexems2, LexemeType::OpenBracket));
    EXPECT_EQ(pos, 1);
    EXPECT_EQ(lexems2.tail()->value.type, LexemeType::UnOperator);
    EXPECT_EQ(lexems2.tail()->value.name, "~");

    EXPECT_TRUE(Parser::parse_number(expr2, pos, lexems2, LexemeType::UnOperator));
    EXPECT_EQ(pos, 4);
    EXPECT_EQ(lexems2.tail()->value.type, LexemeType::Constant);
    EXPECT_EQ(lexems2.tail()->value.name, "456");
    EXPECT_EQ(lexems2.tail()->value.value, 456);

    List<Lexem> lexems3;
    std::string expr3 = "a";
    pos = 0;
    EXPECT_FALSE(Parser::parse_number(expr3, pos, lexems3, LexemeType::OpenBracket));

    List<Lexem> lexems4;
    std::string expr4 = "-";
    pos = 0;
    EXPECT_FALSE(Parser::parse_number(expr4, pos, lexems4, LexemeType::OpenBracket));


    List<Lexem> lexems;
    pos = 0;
    std::string expr = "123 -456";
    EXPECT_TRUE(Parser::parse_number(expr, pos, lexems, LexemeType::OpenBracket));
    EXPECT_EQ(lexems.tail()->value.name, "123");
    EXPECT_EQ(pos, 3);

    pos++;

    EXPECT_TRUE(Parser::parse_operator(expr, pos, lexems, LexemeType::Constant));
    EXPECT_EQ(pos, 5);
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Operator);
    EXPECT_EQ(lexems.tail()->value.name, "-");

    EXPECT_TRUE(Parser::parse_number(expr, pos, lexems, LexemeType::Operator));
    EXPECT_EQ(pos, 8);
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Constant);
    EXPECT_EQ(lexems.tail()->value.name, "456");
    EXPECT_EQ(lexems.tail()->value.value, 456);
}

TEST(TestParser, parse_variable_or_function_work_corretly) {
    List<Lexem> lexems;
    size_t pos;

    std::string expr1 = "x";
    pos = 0;
    EXPECT_TRUE(Parser::parse_variable_or_function(expr1, pos, lexems));
    EXPECT_EQ(pos, 1);
    EXPECT_EQ(lexems.tail()->value.name, "x");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Variable);

    lexems = List<Lexem>();
    std::string expr2 = "_x1_";
    pos = 0;
    EXPECT_TRUE(Parser::parse_variable_or_function(expr2, pos, lexems));
    EXPECT_EQ(lexems.tail()->value.name, "_x1_");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Variable);

    lexems = List<Lexem>();
    std::string expr3 = "Cos";
    pos = 0;
    EXPECT_TRUE(Parser::parse_variable_or_function(expr3, pos, lexems));
    EXPECT_EQ(lexems.tail()->value.name, "Cos");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Variable);

    lexems = List<Lexem>();
    std::string expr4 = "tg(5)";
    pos = 0;
    EXPECT_TRUE(Parser::parse_variable_or_function(expr4, pos, lexems));
    EXPECT_EQ(lexems.tail()->value.name, "tg");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Function);
    EXPECT_EQ(lexems.tail()->value.priority, 5);

    lexems = List<Lexem>();
    std::string expr5 = "1var";
    pos = 0;
    EXPECT_FALSE(Parser::parse_variable_or_function(expr5, pos, lexems));

}

TEST(TestParser, parse_operator_work_corretly) {
    List<Lexem> lexems;
    size_t pos;

    std::string expr1 = "+";
    pos = 0;
    EXPECT_TRUE(Parser::parse_operator(expr1, pos, lexems, LexemeType::Constant));
    EXPECT_EQ(pos, 1);
    EXPECT_EQ(lexems.tail()->value.name, "+");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Operator);
    EXPECT_EQ(lexems.tail()->value.priority, 1);


    lexems = List<Lexem>();
    std::string expr2 = "-";
    pos = 0;
    EXPECT_TRUE(Parser::parse_operator(expr2, pos, lexems, LexemeType::OpenBracket));
    EXPECT_EQ(lexems.tail()->value.name, "~");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::UnOperator);
    EXPECT_EQ(lexems.tail()->value.priority, 4);

    lexems = List<Lexem>();
    lexems.push_back(Lexem("+", LexemeType::Operator, 0, 1));
    std::string expr3 = "-";
    pos = 0;
    EXPECT_TRUE(Parser::parse_operator(expr3, pos, lexems, LexemeType::Operator));
    EXPECT_EQ(lexems.tail()->value.name, "~");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::UnOperator);


    lexems = List<Lexem>();
    std::string expr4 = "^";
    pos = 0;
    EXPECT_TRUE(Parser::parse_operator(expr4, pos, lexems, LexemeType::Constant));
    EXPECT_EQ(lexems.tail()->value.name, "^");
    EXPECT_EQ(lexems.tail()->value.priority, 3);

    lexems = List<Lexem>();
    std::string expr5 = "(";
    pos = 0;
    EXPECT_FALSE(Parser::parse_operator(expr5, pos, lexems, LexemeType::Constant));
}

TEST(TestParser, parse_brackets_and_abs_work_corretly) {
    List<Lexem> lexems;
    size_t pos;

    std::string expr1 = "(";
    pos = 0;
    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr1, pos, lexems, LexemeType::OpenBracket));
    EXPECT_EQ(pos, 1);
    EXPECT_EQ(lexems.tail()->value.name, "(");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::OpenBracket);

    lexems = List<Lexem>();
    std::string expr2 = "]";
    pos = 0;
    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr2, pos, lexems, LexemeType::Constant));
    EXPECT_EQ(lexems.tail()->value.name, "]");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::CloseBracket);

    lexems = List<Lexem>();
    std::string expr3 = "|";
    pos = 0;
    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr3, pos, lexems, LexemeType::OpenBracket));
    EXPECT_EQ(pos, 1);
    EXPECT_EQ(lexems.tail()->value.name, "|");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::OpenedAbs);
    EXPECT_EQ(lexems.tail()->value.priority, 5);

    lexems = List<Lexem>();
    lexems.push_back(Lexem("+", LexemeType::Operator, DBL_MAX, 1));
    std::string expr4 = "|";
    pos = 0;
    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr4, pos, lexems, LexemeType::Operator));
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::OpenedAbs);

    lexems = List<Lexem>();
    pos = 0;
    std::string expr = "{ | x | }";

    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr, pos, lexems, LexemeType::OpenBracket));
    EXPECT_EQ(lexems.tail()->value.name, "{");
    EXPECT_EQ(pos, 1);

    Parser::skip_spaces(expr, pos);

    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr, pos, lexems, LexemeType::OpenBracket));
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::OpenedAbs);
    EXPECT_EQ(pos, 3);

    Parser::skip_spaces(expr, pos);

    EXPECT_TRUE(Parser::parse_variable_or_function(expr, pos, lexems));
    EXPECT_EQ(lexems.tail()->value.name, "x");
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::Variable);
    EXPECT_EQ(pos, 5);

    Parser::skip_spaces(expr, pos);

    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr, pos, lexems, LexemeType::Variable));
    EXPECT_EQ(lexems.tail()->value.type, LexemeType::ClosedAbs);
    EXPECT_EQ(pos, 7);

    Parser::skip_spaces(expr, pos);

    EXPECT_TRUE(Parser::parse_brackets_and_brackets_of_abs(expr, pos, lexems, LexemeType::ClosedAbs));
    EXPECT_EQ(lexems.tail()->value.name, "}");
    EXPECT_EQ(pos, 9);
    EXPECT_EQ(lexems.size(), 5);
}


TEST(TestLexemSequence, after_open_bracket_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::Variable, "(", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::Constant, "(", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::Function, "(", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::OpenBracket, "(", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::UnOperator, "(", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::OpenedAbs, "(", 1));
}

TEST(TestLexemSequence, after_open_bracket_no_correct_sequences) {
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::Operator, "(", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::CloseBracket, "(", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::OpenBracket, LexemeType::ClosedAbs, "(", 1), std::logic_error);
}

TEST(TestLexemSequence, after_variable_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::Operator, "x", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::CloseBracket, "x", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::ClosedAbs, "x", 1));
}

TEST(TestLexemSequence, after_variable_no_correct_sequences) {
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::Variable, "x", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::Constant, "x", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::Function, "x", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::OpenBracket, "x", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Variable, LexemeType::OpenedAbs, "x", 1), std::logic_error);
}

TEST(TestLexemSequence, after_ñonstant_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::Operator, "5", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::CloseBracket, "5", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::ClosedAbs, "5", 1));
}

TEST(TestLexemSequence, after_ñonstant_no_correct_sequences) {
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::Variable, "8", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::Constant, "8", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::Function, "8", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::OpenBracket, "8", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Constant, LexemeType::OpenedAbs, "8", 1), std::logic_error);
}

TEST(TestLexemSequence, after_function_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Function, LexemeType::OpenBracket, "sin", 3));
}

TEST(TestLexemSequence, after_function_no_correct_sequences) {
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Function, LexemeType::Variable, "sin", 3), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Function, LexemeType::Constant, "sin", 3), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Function, LexemeType::Operator, "sin", 3), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Function, LexemeType::CloseBracket, "sin", 3), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Function, LexemeType::ClosedAbs, "sin", 3), std::logic_error);
}

TEST(TestLexemSequence, after_operator_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::Variable, "+", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::Constant, "+", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::Function, "+", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::OpenBracket, "+", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::OpenedAbs, "+", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::UnOperator, "+", 1));
}

TEST(TestLexemSequence, after_operator_no_correct_sequences) {
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::Operator, "+", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::CloseBracket, "+", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::Operator, LexemeType::ClosedAbs, "+", 1), std::logic_error);
}

TEST(TestLexemSequence, after_ñlose_bracket_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::Operator, ")", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::CloseBracket, ")", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::ClosedAbs, ")", 1));
}

TEST(TestLexemSequence, after_ñlose_bracket_no_correct_sequences) {
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::Variable, ")", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::Constant, ")", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::Function, ")", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::OpenBracket, ")", 1), std::logic_error);
    EXPECT_THROW(Parser::check_lexem_sequence(LexemeType::CloseBracket, LexemeType::OpenedAbs, ")", 1), std::logic_error);
}

TEST(TestLexemSequence, after_unoperator_correct_sequences) {
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::Variable, "~", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::Constant, "~", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::Function, "~", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::OpenBracket, "~", 1));
    EXPECT_NO_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::OpenedAbs, "~", 1));
}

TEST(TestLexemSequence, after_unoperator_no_correct_sequences) {
    EXPECT_ANY_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::Operator, "~", 1));
    EXPECT_ANY_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::CloseBracket, "~", 1));
    EXPECT_ANY_THROW(Parser::check_lexem_sequence(LexemeType::UnOperator, LexemeType::ClosedAbs, "~", 1));
}

TEST(TestParser, correct_sequence_transitions_to_parse) {
    EXPECT_NO_THROW(Parser::parse("7 + -5"));
    EXPECT_NO_THROW(Parser::parse("x + 5"));
    EXPECT_NO_THROW(Parser::parse("sin(x)"));
    EXPECT_NO_THROW(Parser::parse("x * |cos(9)|"));
    EXPECT_NO_THROW(Parser::parse("-sin(8) * x"));
    EXPECT_NO_THROW(Parser::parse("x *5/y+ |a*-6+ cos(9)|"));
    EXPECT_NO_THROW(Parser::parse("x"));
    EXPECT_NO_THROW(Parser::parse("5"));
    EXPECT_NO_THROW(Parser::parse("((x))"));
    EXPECT_NO_THROW(Parser::parse("-x"));
    EXPECT_NO_THROW(Parser::parse("sin*5"));
    EXPECT_NO_THROW(Parser::parse("x"));

    List<Lexem> lexems1 = Parser::parse("sin*5");
    EXPECT_EQ(lexems1.head()->value.type, LexemeType::Variable);
    EXPECT_EQ(lexems1.head()->value.name, "sin");

    List<Lexem> lexems2 = Parser::parse("sin(y)");
    EXPECT_EQ(lexems2.head()->value.type, LexemeType::Function);
    EXPECT_EQ(lexems2.head()->value.name, "sin");
}

TEST(TestParser, no_correct_sequence_transitions_to_parse) {
    EXPECT_THROW(Parser::parse("x y"), std::logic_error);
    EXPECT_THROW(Parser::parse("5 10"), std::logic_error);
    EXPECT_THROW(Parser::parse("sin x"), std::logic_error);
    EXPECT_THROW(Parser::parse("+ *"), std::logic_error);
    EXPECT_THROW(Parser::parse("} x"), std::logic_error);
    EXPECT_THROW(Parser::parse("x + "), std::logic_error);
    EXPECT_THROW(Parser::parse("()"), std::logic_error);
    EXPECT_THROW(Parser::parse("Sin(y) "), std::logic_error);
    EXPECT_THROW(Parser::parse("(x+ y+5})"), std::logic_error);
    EXPECT_THROW(Parser::parse("(x+ y+5}"), std::logic_error);
    EXPECT_THROW(Parser::parse("x * ||-7|+ cos(-9)-100||"), std::logic_error);
}

TEST(TestParser, difficult_expression_parse_corretly) {
    List<Lexem> lexems = Parser::parse("X_124 * |||-7|+ cos(-9)-100||");

    EXPECT_EQ(lexems.size(), 18);

    List<Lexem>::Iterator it = lexems.begin();

    EXPECT_EQ((*it).type, LexemeType::Variable);
    EXPECT_EQ((*it).name, "X_124");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Operator);
    EXPECT_EQ((*it).name, "*");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::OpenedAbs);
    EXPECT_EQ((*it).name, "|");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::OpenedAbs);
    EXPECT_EQ((*it).name, "|");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::OpenedAbs);
    EXPECT_EQ((*it).name, "|");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::UnOperator);
    EXPECT_EQ((*it).name, "~");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Constant);
    EXPECT_EQ((*it).name, "7");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::ClosedAbs);
    EXPECT_EQ((*it).name, "|");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Operator);
    EXPECT_EQ((*it).name, "+");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Function);
    EXPECT_EQ((*it).name, "cos");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::OpenBracket);
    EXPECT_EQ((*it).name, "(");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::UnOperator);
    EXPECT_EQ((*it).name, "~");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Constant);
    EXPECT_EQ((*it).name, "9");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::CloseBracket);
    EXPECT_EQ((*it).name, ")");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Operator);
    EXPECT_EQ((*it).name, "-");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::Constant);
    EXPECT_EQ((*it).name, "100");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::ClosedAbs);
    EXPECT_EQ((*it).name, "|");
    ++it;

    EXPECT_EQ((*it).type, LexemeType::ClosedAbs);
    EXPECT_EQ((*it).name, "|");
    ++it;

    EXPECT_EQ(it, lexems.end());
}

