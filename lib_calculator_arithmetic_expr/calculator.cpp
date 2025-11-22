#include <iostream>
#include <string>
#include "../lib_my_math/my_math.h"
#include "../lib_parser_arithmetic_expr/parser_arithmetic_expr.h"
#include "../lib_arithmetic_expr/arithmetic_expr.h"
#include "../lib_tvector/tvector.h"

int main() {
    TVector<Expression> expressions;
    int choice;

    do {
        std::cout << "\n=== Calculator ===" << std::endl;
        std::cout << "1. Create expression" << std::endl;
        std::cout << "2. Delete expression" << std::endl;
        std::cout << "3. Set variables" << std::endl;
        std::cout << "4. Calculate expression" << std::endl;
        std::cout << "5. Show all expessions" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Your choice: ";

        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
            case 1: {
                std::string expr;
                std::cout << "Expression: ";
                std::getline(std::cin, expr);
                expressions.push_back(Expression(expr));
                std::cout << "Added (ID: " << expressions.size() << ")" << std::endl;
                break;
            }
            case 2: {
                if (expressions.is_empty()) {
                    std::cout << "No expressions" << std::endl;
                    break;
                }
                std::cout << "ID expression for delete: ";
                size_t id;
                std::cin >> id;
                if (id >= 1 && id <= expressions.size()) {
                    expressions.erase(id - 1);
                    std::cout << "Deleted" << std::endl;
                }
                else
                    std::cout << "Wrong ID" << std::endl;
                break;
            }
            case 3: {
                if (expressions.is_empty()) {
                    std::cout << "No expressions" << std::endl;
                    break;
                }
                std::cout << "ID expression: ";
                size_t id;
                std::cin >> id;
                if (id >= 1 && id <= expressions.size()) {
                    expressions[id - 1].construct_polish_record();
                    expressions[id - 1].set_variables();
                }
                else
                    std::cout << "Wrong ID" << std::endl;
                break;
            }
            case 4: {
                if (expressions.is_empty()) {
                    std::cout << "No expessions" << std::endl;
                    break;
                }
                std::cout << "ID expession: ";
                size_t id;
                std::cin >> id;
                if (id >= 1 && id <= expressions.size()) {
                    double result = expressions[id - 1].calculate();
                    std::cout << "Result: " << result << std::endl;
                }
                else
                    std::cout << "Wrong ID" << std::endl;
                break;
            }
            case 5: {
                if (expressions.is_empty()) {
                    std::cout << "No expressions" << std::endl;
                }
                else {
                    std::cout << "+-----+----------------------------------------------+--------------------------+" << std::endl;
                    std::cout << "| ID  | EXPRESSION                                   | VARIABLES VALUES         |" << std::endl;
                    std::cout << "+-----+----------------------------------------------+--------------------------+" << std::endl;

                    for (size_t i = 0; i < expressions.size(); i++) {
                        std::string expr_str = expressions[i].get_original_expression();
                        std::string vars_info = expressions[i].get_variables_info();

                        if (expr_str.length() > 45) {
                            expr_str = expr_str.substr(0, 42) + "...";
                        }
                        if (vars_info.length() > 24) {
                            vars_info = vars_info.substr(0, 21) + "...";
                        }

                        std::cout << "| " << (i + 1);

                        if (i + 1 < 10)
                            std::cout << "   | ";
                        else
                            std::cout << "  | ";

                        std::cout << expr_str;
                        for (size_t j = expr_str.length(); j < 45; j++) {
                            std::cout << " ";
                        }

                        std::cout << "| " << vars_info;
                        for (size_t j = vars_info.length(); j < 24; j++) {
                            std::cout << " ";
                        }
                        std::cout << " |" << std::endl;
                    }
                    std::cout << "+-----+----------------------------------------------+--------------------------+" << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Exit......" << std::endl;
                break;
            default:
                std::cout << "Wrong choice" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << std::endl << e.what() << std::endl;
        }

    } while (choice != 0);

    return 0;
}