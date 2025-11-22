#include "../lib_parser_arithmetic_expr/parser_arithmetic_expr.h"
#include "../lib_my_math/my_math.h"
class Expression {
    std::string original_expr;
    List<Lexem> expression;
    List<Lexem> polish_record;

    List<std::string> variable_names;
    List<double> variable_values;
    bool variables_are_set;

public:
    Expression() = default;
    Expression(const std::string& str);

    std::string get_original_expression() const;
    std::string get_variables_info() const;


    void construct_polish_record();
    void set_variables();
    double calculate();

    const List<Lexem>& get_expression()  const;
    const List<Lexem>& get_polish_record()  const;
};