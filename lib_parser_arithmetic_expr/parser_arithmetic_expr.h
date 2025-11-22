#ifndef PARSER_ARITHMETIC_EXPR_H
#define PARSER_ARITHMETIC_EXPR_H
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include <string>

enum class LexemeType {
    Constant, Variable, OpenBracket, CloseBracket,
    Function, Operator, UnOperator, OpenedAbs, ClosedAbs
};
struct Lexem {
    std::string name;
    LexemeType type;
    double value;
    int priority;
    double (*function)(double);

    Lexem(std::string _name = "", LexemeType _type = LexemeType::Variable, double _value = DBL_MAX, int _priority = -1, double(*_function)(double) = nullptr);
};

namespace Parser {

    bool is_digit(char c);
    bool is_alpha(char c);
    bool is_variable_char(char c);
    void skip_spaces(const std::string& expr, size_t& pos);
    bool is_number(const std::string& str);
    bool is_function(const std::string& str);
    int get_priority(const std::string& op);
    int string_to_int(const std::string& str);

    std::string create_error(const std::string& expr, size_t pos, const std::string& message);

    bool parse_number(const std::string& expr, size_t& pos, List<Lexem>& lexems, LexemeType lastType);
    bool parse_variable_or_function(const std::string& expr, size_t& pos, List<Lexem>& lexems);
    bool parse_operator(const std::string& expr, size_t& pos, List<Lexem>& lexems, LexemeType lastType);
    bool parse_brackets_and_brackets_of_abs(const std::string& expr, size_t& pos, List<Lexem>& lexems, LexemeType lastType);

    void check_lexem_sequence(LexemeType prevType, LexemeType currentType, const std::string& expr, size_t pos);
    List<Lexem> parse(const std::string& expression);

}
#endif