#ifndef LIB_MONOM_H_
#define LIB_MONOM_H_

#define VARS_COUNT 3

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Monom {
private:
    double _coeff;
    int _powers[VARS_COUNT];  

public:
    Monom();
    Monom(double coeff, int powers[VARS_COUNT]);
    Monom(double coeff, int px, int py, int pz); 
    Monom(std::initializer_list<double> list);  
    Monom(const Monom& other);
    Monom(const std::string& str);

    double coeff() const { return _coeff; }
    const int* powers() const { return _powers; }
    int power_x() const { return _powers[0]; }
    int power_y() const { return _powers[1]; }
    int power_z() const { return _powers[2]; }

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double scalar) const;
    Monom operator/(double scalar) const;
    Monom operator-() const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);

    Monom& operator=(const Monom& other);

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    double evaluate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Monom& m);
    friend std::istream& operator>>(std::istream& is, Monom& m);

    bool operator>(const Monom& other) const;
    bool operator<(const Monom& other) const;
    static Monom parse(const std::string& str);
};


Monom operator*(double scalar, const Monom& m);

#endif 