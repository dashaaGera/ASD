#include "../lib_my_math/my_math.h"
#include <stdexcept>
long long factorial(int n) {
    if (n == 0) return 1;
    long long result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}

double power(double base, int exponent) {
    double result = 1.0;

    if (exponent < 0) {
        base = 1.0 / base;
        exponent = -exponent;
    }

    for (int i = 0; i < exponent; i++)
        result *= base;

    return result;
}

double sign(double x) {
    if (x > 0) return 1.0;
    else if (x < 0) return -1.0;
    return 0.0;
}


double my_abs(double x) {
    return (x < 0) ? -x : x;
}

double my_sin(double x) {
    // [-2pi, 2pi]
    while (my_abs(x) >= 2 * M_PI)
        x -= sign(x) * 2 * M_PI;


    double result = x;
    for (int i = 1; i <= 10; i++) {
        int n = 2 * i + 1;
        double term = power(x, n) / factorial(n);
        if (i % 2 == 1)
            result -= term;
        else
            result += term;
    }
    return result;
}

double my_cos(double x) {
    //   [-2pi, 2pi]
    while (my_abs(x) >= 2 * M_PI)
        x -= sign(x) * 2 * M_PI;

    double result = 1.0;
    for (int i = 1; i <= 10; i++) {
        int n = 2 * i;
        double term = power(x, n) / factorial(n);

        if (i % 2 == 1)
            result -= term;
        else
            result += term;
    }
    return result;
}

double my_tg(double x) {
    //  [-pi/2, pi/2]
    while (my_abs(x) >= M_PI / 2)
        x -= sign(x) * M_PI;

    if (my_abs(my_abs(x) - M_PI / 2) < 1e-10)
        throw std::logic_error("Tangent undefined for this angle");
    double sin_val = my_sin(x);
    double cos_val = my_cos(x);

    if (my_abs(cos_val) < 1e-10)
        throw std::logic_error("Tangent undefined for this angle");

    return sin_val / cos_val;
}