#include "../lib_parser_arithmetic_expr/parser_arithmetic_expr.h"
#include <stdexcept>
#include <cfloat>

Lexem::Lexem(std::string _name, LexemeType _type, double _value, int _priority, double(*_function)(double))
    : name(_name), type(_type), value(_value), priority(_priority), function(_function) {
}


bool Parser::is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool Parser::is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Parser::is_variable_char(char c) {
    return is_alpha(c) || is_digit(c) || c == '_';
}

void Parser::skip_spaces(const std::string& expr, size_t& pos) {
    while (pos < expr.length() && expr[pos] == ' ') {
        pos++;
    }
}

bool Parser::is_number(const std::string& str) {
    if (str.empty()) return false;

    for (size_t i = 0; i < str.length(); i++) {
        if (!is_digit(str[i]))
            return false;
    }
    return true;
}

bool Parser::is_function(const std::string& str) {
    return str == "sin" || str == "cos" || str == "tg" || str == "abs";
}


int Parser::get_priority(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    if (op == "~") return 4;
    if (op == "sin" || op == "cos" || op == "tg" || op == "|" || op == "abs") return 5;
    return -1;
}

int Parser::string_to_int(const std::string& str) {
    int result = 0;
    for (size_t i = 0; i < str.length(); i++) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

std::string Parser::create_error(const std::string& expr, size_t pos, const std::string& message) {
    std::string error_message;

    error_message += expr + "\n";
    error_message += std::string(pos, ' ') + "^\n";
    error_message += std::string(pos, ' ') + "|\n";
    error_message += "Error at position " + std::to_string(pos + 1) + ": " + message;

    return error_message;
}

bool Parser::parse_number(const std::string& expr, size_t& pos, List<Lexem>& lexems, LexemeType lastType) {
    if (!is_digit(expr[pos]))
        return false;
    size_t start_pos = pos;
    std::string number_str;

    while (pos < expr.length() && is_digit(expr[pos])) {
        number_str += expr[pos];
        pos++;
    }

    if (number_str.empty()) {
        throw std::logic_error(create_error(expr, pos - number_str.length(),
            "Invalid number: expected digits"));
    }

    if (pos < expr.length() && (is_alpha(expr[pos]) || expr[pos] == '_')) {
        throw std::logic_error(create_error(expr, pos, "After number expected operator, closing bracket or closing modulus"));
    }

    int value = string_to_int(number_str);
    lexems.push_back(Lexem(number_str, LexemeType::Constant, value));

    return true;
}
bool Parser::parse_variable_or_function(const std::string& expr, size_t& pos, List<Lexem>& lexems) {
    if (!is_alpha(expr[pos]) && expr[pos] != '_') {
        return false;
    }

    std::string name;
    while (pos < expr.length() && is_variable_char(expr[pos])) {
        name += expr[pos];
        pos++;
    }

    if (pos < expr.length() && expr[pos] == '(' && is_function(name))
        lexems.push_back(Lexem(name, LexemeType::Function, DBL_MAX, get_priority(name)));
    else
        lexems.push_back(Lexem(name, LexemeType::Variable));

    return true;
}

bool Parser::parse_operator(const std::string& expr, size_t& pos, List<Lexem>& lexems, LexemeType lastType) {
    char c = expr[pos];
    if (c != '+' && c != '-' && c != '*' && c != '/' && c != '^') {
        return false;
    }

    if (lastType == LexemeType::UnOperator) {
        throw std::logic_error(create_error(expr, pos, "After unary operator expected constant, variable, function, opening bracket or opening modulus"));
    }

    // processing unminus
    if (expr[pos] == '-' && (lastType == LexemeType::Operator ||
        lastType == LexemeType::OpenBracket ||
        lastType == LexemeType::OpenedAbs ||
        lexems.is_empty())) {
        lexems.push_back(Lexem("~", LexemeType::UnOperator, 0, 4));
    }
    else {
        std::string op(1, expr[pos]);
        lexems.push_back(Lexem(op, LexemeType::Operator, 0, get_priority(op)));
    }

    pos++;
    return true;
}


bool Parser::parse_brackets_and_brackets_of_abs(const std::string& expr, size_t& pos, List<Lexem>& lexems, LexemeType lastType) {
    char current = expr[pos];

    if (current == '(' || current == '{' || current == '[') {
        lexems.push_back(Lexem(std::string(1, current), LexemeType::OpenBracket));
        pos++;
        return true;
    }

    if (current == ')' || current == '}' || current == ']') {
        lexems.push_back(Lexem(std::string(1, current), LexemeType::CloseBracket));
        pos++;
        return true;
    }

    // abs 
    if (current == '|') {
        if (lastType == LexemeType::Variable ||
            lastType == LexemeType::Constant ||
            lastType == LexemeType::CloseBracket ||
            lastType == LexemeType::ClosedAbs) {
            lexems.push_back(Lexem("|", LexemeType::ClosedAbs, DBL_MAX, 5));
        }
        else {
            lexems.push_back(Lexem("|", LexemeType::OpenedAbs, DBL_MAX, 5));
        }
        pos++;
        return true;
    }

    return false;
}

void Parser::check_lexem_sequence(LexemeType prevType, LexemeType currentType, const std::string& expr, size_t pos) {
    //after open bracket
    if (prevType == LexemeType::OpenBracket) {
        if (currentType != LexemeType::Variable &&
            currentType != LexemeType::Constant &&
            currentType != LexemeType::Function &&
            currentType != LexemeType::OpenBracket &&
            currentType != LexemeType::UnOperator &&
            currentType != LexemeType::OpenedAbs) {

            size_t error_pos = pos;
            if (currentType == LexemeType::CloseBracket || currentType == LexemeType::ClosedAbs) {
                error_pos = (pos > 0) ? pos - 1 : 0;
            }
            throw std::logic_error(create_error(expr, error_pos, "After opening bracket expected constant, variable, function, unary operator or opening modulus"));
        }
    }
    // after var or const
    else if (prevType == LexemeType::Variable || prevType == LexemeType::Constant) {
        if (currentType != LexemeType::Operator &&
            currentType != LexemeType::CloseBracket &&
            currentType != LexemeType::ClosedAbs) {
            throw std::logic_error(create_error(expr, pos - 1, "After variable/constant expected operator, closing bracket or closing modulus"));
        }
    }
    //after function
    else if (prevType == LexemeType::Function) {
        if (currentType != LexemeType::OpenBracket) {
            throw std::logic_error(create_error(expr, pos - 1, "After function expected opening bracket"));
        }
    }
    // after operator
    else if (prevType == LexemeType::Operator) {
        if (currentType != LexemeType::Variable &&
            currentType != LexemeType::Constant &&
            currentType != LexemeType::Function &&
            currentType != LexemeType::OpenBracket &&
            currentType != LexemeType::OpenedAbs &&
            currentType != LexemeType::UnOperator) {
            throw std::logic_error(create_error(expr, pos, "After operator expected constant, variable, function, opening bracket or opening modulus"));
        }
    }
    // after close bracket
    else if (prevType == LexemeType::CloseBracket) {
        if (currentType != LexemeType::Operator &&
            currentType != LexemeType::CloseBracket &&
            currentType != LexemeType::ClosedAbs) {
            throw std::logic_error(create_error(expr, pos - 1, "After closing bracket expected operator, closing bracket or closing modulus"));
        }
    }
    //after open abs
    else if (prevType == LexemeType::OpenedAbs) {
        if (currentType != LexemeType::Variable &&
            currentType != LexemeType::Constant &&
            currentType != LexemeType::Function &&
            currentType != LexemeType::OpenBracket &&
            currentType != LexemeType::UnOperator &&
            currentType != LexemeType::OpenedAbs) {
            throw std::logic_error(create_error(expr, pos, "After opening modulus expected constant, variable, function, unary operator, opening bracket or opening modulus"));
        }
    }
    // after close abs
    else if (prevType == LexemeType::ClosedAbs) {
        if (currentType != LexemeType::Operator &&
            currentType != LexemeType::CloseBracket &&
            currentType != LexemeType::ClosedAbs) {
            throw std::logic_error(create_error(expr, pos - 1, "After closing modulus expected operator, closing bracket or closing modulus"));
        }
    }
    // after un minus
    else if (prevType == LexemeType::UnOperator) {
        if (currentType != LexemeType::Variable &&
            currentType != LexemeType::Constant &&
            currentType != LexemeType::Function &&
            currentType != LexemeType::OpenBracket &&
            currentType != LexemeType::OpenedAbs) {
            throw std::logic_error(create_error(expr, pos, "After unary operator expected constant, variable, function, opening bracket or opening modulus"));
        }
    }
}


List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    Stack<char> bracket_stack(100);
    size_t pos = 0;
    size_t length = expression.length();
    LexemeType last_type = LexemeType::OpenBracket;

    while (pos < length) {
        skip_spaces(expression, pos);
        if (pos >= length) break;

        bool parsed = false;
        //opened brackets
        if (expression[pos] == '(' || expression[pos] == '{' || expression[pos] == '[') {
            bracket_stack.push(expression[pos]);
            lexems.push_back(Lexem(std::string(1, expression[pos]), LexemeType::OpenBracket));
            pos++;
            parsed = true;
        }
        // closed brackets
        else if (expression[pos] == ')' || expression[pos] == '}' || expression[pos] == ']') {
            if (bracket_stack.is_empty()) {
                throw std::logic_error(create_error(expression, pos, "Unmatched closing bracket"));
            }

            char open_bracket = bracket_stack.top();
            char close_bracket = expression[pos];

            // pairing brackets
            if ((open_bracket == '(' && close_bracket != ')') ||
                (open_bracket == '{' && close_bracket != '}') ||
                (open_bracket == '[' && close_bracket != ']')) {
                throw std::logic_error(create_error(expression, pos, "Mismatched brackets"));
            }

            bracket_stack.pop();
            lexems.push_back(Lexem(std::string(1, expression[pos]), LexemeType::CloseBracket));
            pos++;
            parsed = true;
        }
        // abs
        else if (expression[pos] == '|') {
            parsed = parse_brackets_and_brackets_of_abs(expression, pos, lexems, last_type);
        }
        else {
            parsed =
                parse_operator(expression, pos, lexems, last_type) ||
                parse_number(expression, pos, lexems, last_type) ||
                parse_variable_or_function(expression, pos, lexems);
        }

        if (!parsed) {
            throw std::logic_error(create_error(expression, pos,
                std::string("Unknown character: '") + expression[pos] + "'"));
        }

        // sequence lexems
        if (!lexems.is_empty()) {
            LexemeType current_type = lexems.tail()->value.type;
            check_lexem_sequence(last_type, current_type, expression, pos);
            last_type = current_type;
        }
    }

    // all brackets closed
    if (!bracket_stack.is_empty()) {
        char unmatched_bracket = bracket_stack.top();
        size_t error_pos = expression.find(unmatched_bracket);
        throw std::logic_error(create_error(expression, error_pos, "Unmatched opening bracket"));
    }

    int abs_balance = 0;
    List<Lexem>::Iterator it = lexems.begin();
    while (it != lexems.end()) {
        if ((*it).type == LexemeType::OpenedAbs)
            abs_balance++;

        else if ((*it).type == LexemeType::ClosedAbs)
            abs_balance--;
        ++it;
    }
    if (abs_balance != 0) {
        size_t error_pos = expression.find('|');
        throw std::logic_error(create_error(expression, error_pos, "Unmatched modulus brackets"));
    }

    if (lexems.is_empty())
        throw std::logic_error("Empty expression");

    LexemeType final_type = lexems.tail()->value.type;
    if (final_type == LexemeType::Operator || final_type == LexemeType::UnOperator)
        throw std::logic_error(create_error(expression, length - 1, "Expression ends with operator"));

    return lexems;
}