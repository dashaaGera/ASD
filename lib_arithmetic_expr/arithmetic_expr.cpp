#include "../lib_arithmetic_expr/arithmetic_expr.h"
#include <stdexcept>
#include <iostream>

Expression::Expression(const std::string& str) : original_expr(str), variables_are_set(false) {
    expression = Parser::parse(str);

    List<Lexem>::Iterator it = expression.begin();
    while (it != expression.end()) {
        if ((*it).type == LexemeType::Variable) {
            std::string name = (*it).name;

            bool found = false;
            List<std::string>::Iterator name_it = variable_names.begin();
            while (name_it != variable_names.end()) {
                if ((*name_it) == name) {
                    found = true;
                    break;
                }
                ++name_it;
            }

            if (!found) {
                variable_names.push_back(name);
                variable_values.push_back(0);
            }
        }
        ++it;
    }
}
std::string Expression::get_variables_info() const {
    if (variable_names.is_empty()) {
        return "No variables";
    }

    std::string result;
    List<std::string>::Iterator name_it = variable_names.begin();
    List<double>::Iterator value_it = variable_values.begin();

    while (name_it != variable_names.end() && value_it != variable_values.end()) {
        if (!result.empty()) {
            result += ", ";
        }

        if (variables_are_set) {
            result += (*name_it) + " = " + std::to_string(static_cast<int>(*value_it));
        }
        else {
            result += (*name_it) + " = ?";
        }
        ++name_it;
        ++value_it;
    }
    return result;
}


void Expression::set_variables() {
    if (variable_names.is_empty()) {
        std::cout << "No variables in expression" << std::endl;
        return;
    }

    variable_values = List<double>();

    std::cout << "Set variables for: " << original_expr << std::endl;

    List<std::string>::Iterator it = variable_names.begin();
    while (it != variable_names.end()) {
        double value;
        std::cout << (*it) << " = ";
        std::cin >> value;
        variable_values.push_back(value);
        ++it;
    }

    variables_are_set = true;
    expression = Parser::parse(original_expr);

    List<Lexem>::Iterator lex_it = expression.begin();
    while (lex_it != expression.end()) {
        if ((*lex_it).type == LexemeType::Variable) {
            List<std::string>::Iterator name_it = variable_names.begin();
            List<double>::Iterator value_it = variable_values.begin();

            while (name_it != variable_names.end() && value_it != variable_values.end()) {
                if ((*name_it) == (*lex_it).name) {
                    (*lex_it).type = LexemeType::Constant;
                    (*lex_it).value = *value_it;
                    (*lex_it).name = std::to_string(static_cast<int>(*value_it));
                    break;
                }
                ++name_it;
                ++value_it;
            }
        }
        ++lex_it;
    }
    polish_record = List<Lexem>();
    construct_polish_record();

    std::cout << "Variables set successfully!" << std::endl;
}

std::string Expression::get_original_expression() const { return original_expr; }

const List<Lexem>& Expression::get_expression()   const { return expression; }
const List<Lexem>& Expression::get_polish_record() const { return polish_record; }


void Expression::construct_polish_record() {
    List<Lexem> output;
    Stack<Lexem> operators;

    List<Lexem>::Iterator it = expression.begin();
    while (it != expression.end()) {
        const Lexem& lexem = *it;
        ++it;

        switch (lexem.type) {
        case LexemeType::Constant:
        case LexemeType::Variable:
            output.push_back(lexem);
            break;

        case LexemeType::Function:
            operators.push(lexem);
            break;

        case LexemeType::OpenedAbs:
            operators.push(lexem);
            break;

        case LexemeType::Operator:
        case LexemeType::UnOperator:
        { //push out with the highest or equal priority
            while (!operators.is_empty() &&
                operators.top().type != LexemeType::OpenBracket &&
                operators.top().type != LexemeType::OpenedAbs &&
                operators.top().priority >= lexem.priority) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(lexem);
            break;
        }

        case LexemeType::OpenBracket:
            operators.push(lexem);
            break;

            // push out before open bracket
        case LexemeType::CloseBracket:
            while (!operators.is_empty() &&
                operators.top().type != LexemeType::OpenBracket) {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.is_empty() && operators.top().type == LexemeType::OpenBracket) {
                operators.pop();// delete open bracket
            }
            // top=function->push out
            if (!operators.is_empty() && operators.top().type == LexemeType::Function) {
                output.push_back(operators.top());
                operators.pop();
            }
            break;

            // push out before open abs
        case LexemeType::ClosedAbs:
            while (!operators.is_empty() &&
                operators.top().type != LexemeType::OpenedAbs) {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.is_empty() && operators.top().type == LexemeType::OpenedAbs) {
                operators.pop();
                Lexem abs_lexem("abs", LexemeType::Function, 0, 5);
                output.push_back(abs_lexem);
            }
            break;
        }
    }

    // push out remaining operators
    while (!operators.is_empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    polish_record = output;
}

double Expression::calculate() {
    if (polish_record.is_empty() || variables_are_set) {
        construct_polish_record();
    }

    if (!variable_names.is_empty() && !variables_are_set) {
        std::cout << "Variables are not set. Please set variables first." << std::endl;
        set_variables();
    }

    Stack<double> values(100);

    List<Lexem>::Iterator it = polish_record.begin();
    while (it != polish_record.end()) {
        const Lexem& lexem = *it;
        ++it;

        switch (lexem.type) {
        case LexemeType::Constant:
            values.push(lexem.value);
            break;

        case LexemeType::Operator: {
            if (values.top_index() < 1) {
                throw std::logic_error("Not enough operands for operator " + lexem.name);
            }
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();
            double result;

            if (lexem.name == "+") {
                result = a + b;
                values.push(result);
            }
            else if (lexem.name == "-") {
                result = a - b;
                values.push(result);
            }
            else if (lexem.name == "*") {
                result = a * b;
                values.push(result);
            }
            else if (lexem.name == "/") {
                if (b == 0)
                    throw std::logic_error("Division by zero");
                result = a / b;
                values.push(result);
            }
            else if (lexem.name == "^") {
                values.push(power(a, static_cast<int>(b)));
            }
            break;
        }

        case LexemeType::UnOperator:
            if (values.top_index() < 0) {
                throw std::logic_error("Not enough operands for unary operator");
            }
            if (lexem.name == "~") {
                double a = values.top();
                values.pop();
                values.push(-a);
            }
            break;

        case LexemeType::Function: {
            if (values.top_index() < 0) {
                throw std::logic_error("Not enough operands for function " + lexem.name);
            }
            double a = values.top();
            values.pop();

            if (lexem.name == "abs")
                values.push(my_abs(a));
            else if (lexem.name == "sin")
                values.push(my_sin(a));
            else if (lexem.name == "cos")
                values.push(my_cos(a));
            else if (lexem.name == "tg")
                values.push(my_tg(a));
            else throw std::logic_error("Unknown function: " + lexem.name);
            break;
        }

        default:
            throw std::logic_error("Unexpected lexem type in polish notation");
        }
    }

    if (values.top_index() != 0) {
        throw std::logic_error("Invalid expression - multiple values left");
    }

    return values.top();
}