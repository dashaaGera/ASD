#include <iostream>
#include <iomanip>
#include "../lib_polynom/polynom.h"
#include "../lib_monom/monom.h"


void print_menu() {
    std::cout << "\nMenu\n";
    std::cout << "1. Enter polynom\n";
    std::cout << "2. Print polynom\n";
    std::cout << "3. Calculate value at point\n";
    std::cout << "4. Add two polynoms\n";
    std::cout << "5. Sub two polynoms\n";
    std::cout << "6. Mul two polynoms\n";
    std::cout << "7. Mul polynom by scalar\n";
    std::cout << "8. Div polynom by scalar\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}


int main() {

    Polynom current_poly;
    Polynom second_poly;

    int choice = -1;

    while (choice != 0) {
        print_menu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::cout << "Enter polynom: ";
            std::string input;
            std::getline(std::cin, input);

            try {
                current_poly = Polynom::parse(input);
                std::cout << "Your polynom: " << current_poly << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 2: {
            std::cout << "\nPolynom:\n";
            std::cout << "P = " << current_poly << std::endl;
            break;
        }

        case 3: {
            std::cout << "Current polynom: " << current_poly << std::endl;
            std::cout << "Enter x y z (separated by space): ";

            double x, y, z;
            std::cin >> x >> y >> z;
            std::cin.ignore();

            try {
                double result = current_poly.evaluate(x, y, z);
                std::cout << "P(" << x << "," << y << "," << z << ") = "
                    << std::fixed << std::setprecision(6)
                    << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 4: {
            std::cout << "Curremt polynom: " << current_poly << std::endl;
            std::cout << "Enter second polynom: ";

            std::string input;
            std::getline(std::cin, input);

            try {
                second_poly = Polynom::parse(input);
                Polynom sum = current_poly + second_poly;
                std::cout << "Result: " << current_poly << " + "
                    << second_poly << " = " << sum << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 5: {
            std::cout << "Current polynom: " << current_poly << std::endl;
            std::cout << "Enter second polynom:  ";

            std::string input;
            std::getline(std::cin, input);

            try {
                second_poly = Polynom::parse(input);
                Polynom diff = current_poly - second_poly;
                std::cout << "Result: " << current_poly << " - "
                    << second_poly << " = " << diff << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 6: {
            std::cout << "Current polynom: " << current_poly << std::endl;
            std::cout << "Enter second polynom:  ";

            std::string input;
            std::getline(std::cin, input);

            try {
                second_poly = Polynom::parse(input);
                Polynom prod = current_poly * second_poly;
                std::cout << "Result: " << current_poly << " * "
                    << second_poly << " = " << prod << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 7: {
            std::cout << "Current polynom: " << current_poly << std::endl;
            std::cout << "Enter scalar: ";

            double scalar;
            std::cin >> scalar;
            std::cin.ignore();

            try {
                Polynom result = current_poly * scalar;
                std::cout << "Result: " << current_poly << " * "
                    << scalar << " = " << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 8: {
            std::cout << "Current polynom: " << current_poly << std::endl;
            std::cout << "Enter scalar: ";

            double scalar;
            std::cin >> scalar;
            std::cin.ignore();

            try {
                Polynom result = current_poly / scalar;
                std::cout << "Result: " << current_poly << " * "
                    << scalar << " = " << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }


        case 0: {
            std::cout << "\nExit\n";
            break;
        }

        default: {
            std::cout << "Wrong choice!\n";
            break;
        }
        }
    }

    return 0;
} 