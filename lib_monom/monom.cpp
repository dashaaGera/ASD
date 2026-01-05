#include <stdexcept>
#include "../lib_monom/monom.h"
#include <cmath>


Monom::Monom(){
    _coeff = 0;
    for (int i = 0; i < VARS_COUNT; i++)
        _powers[i] = 0;
}

Monom::Monom(double coeff, int powers[VARS_COUNT]) : _coeff(coeff) {
    for (int i = 0; i < VARS_COUNT; i++)
        _powers[i] = powers[i];
}

Monom::Monom(double coeff, int px, int py, int pz) : _coeff(coeff) {
    _powers[0] = px;
    _powers[1] = py;
    _powers[2] = pz;
}



Monom::Monom(std::initializer_list<double> list) {
    _coeff = 0.0;
    for (int i = 0; i < VARS_COUNT; i++)
        _powers[i] = 0;

    if (list.size() == 0) return;

    auto it = list.begin();
    _coeff = *it++;

    int i = 0;
    while (it != list.end() && i < VARS_COUNT) {
        _powers[i++] = static_cast<int>(*it++);
    }

}

Monom::Monom(const Monom& other) : _coeff(other._coeff) {
    for (int i = 0; i < VARS_COUNT; i++)
        _powers[i] = other._powers[i];
}

Monom::Monom(const std::string& str) {
    *this = parse(str);
}

bool Monom::operator==(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != other._powers[i])
            return false;
    }
    return true;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coeff = other._coeff;
        for (int i = 0; i < VARS_COUNT; i++) {
            _powers[i] = other._powers[i];
        }
    }
    return *this;
}

Monom Monom::operator+(const Monom& other) const {
    if (*this!=other)
        throw std::logic_error("monomials aren't suitable for add");
    Monom result(*this);
    result._coeff += other._coeff;
    return result;
}

Monom Monom::operator-(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("monomials aren't suitable for sub");
    Monom result(*this);
    result._coeff -= other._coeff;
    return result;
}

Monom Monom::operator*(const Monom& other) const {
    if (_coeff == 0 || other._coeff == 0)
        return Monom();
    Monom result(*this);
    result._coeff *= other._coeff;
    for (int i = 0;i < VARS_COUNT;i++)
        result._powers[i] += other._powers[i];
    return result;
}

Monom Monom::operator/(const Monom& other) const {
    if (other._coeff == 0)
        throw std::logic_error("div on null coeff");

    Monom result(*this);
    result._coeff /= other._coeff;
    for (int i = 0;i < VARS_COUNT;i++) {
        if (other._powers[i] > _powers[i])
            throw std::logic_error("degree of dividor is greater than degree of divindend");
        result._powers[i] -= other._powers[i];
    }
    return result;
}

Monom Monom::operator*(double scalar) const {
    Monom result = *this;         
    result._coeff = _coeff * scalar; 
    return result;
}

Monom operator*(double scalar, const Monom& m) {
    return m * scalar;
}

Monom Monom::operator/(double scalar) const {
    if (scalar == 0)
        throw std::logic_error("div on null coeff");

    Monom result = *this;
    result._coeff = _coeff / scalar;
    return result;
}

Monom Monom::operator-() const {
    Monom result = *this;
    result._coeff = -_coeff;
    return result;
}

Monom& Monom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

double Monom::evaluate(double x, double y, double z) const {
    double vars[VARS_COUNT] = { x, y, z };
    double result = _coeff;

    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != 0) 
            result *= std::pow(vars[i], _powers[i]);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    os << m._coeff;
    if (m._powers[0] > 0) os << "x^" << m._powers[0];
    if (m._powers[1] > 0) os << "y^" << m._powers[1];
    if (m._powers[2] > 0) os << "z^" << m._powers[2];
    return os;
}

std::istream& operator>>(std::istream& is, Monom& m) {
    double coeff;
    int px, py, pz;
    is >> coeff >> px >> py >> pz;
    m = Monom(coeff, px, py, pz);
    return is;
}

bool Monom::operator>(const Monom& other) const {

    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != other._powers[i])
            return _powers[i] > other._powers[i];
    }
    return _coeff > other._coeff;
}

bool Monom::operator<(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != other._powers[i])
            return _powers[i] < other._powers[i];
    }
    return _coeff < other._coeff;
}

Monom Monom::parse(const std::string& str) {
    Monom result;
    result._coeff = 0.0;
    for (int i = 0; i < VARS_COUNT; i++) {
        result._powers[i] = 0;
    }

    if (str.empty() || str == "0") {
        return result;
    }

    //delete spaces
    std::string s;
    for (char c : str) {
        if (!std::isspace(c)) {
            s += c;
        }
    }

    if (s.empty()) {
        return result;
    }

    double coeff = 1.0;
    int px = 0, py = 0, pz = 0;

    // parsing sign
    bool negative = false;
    size_t start = 0;

    if (s[0] == '-') {
        negative = true;
        start = 1;
    }
    else if (s[0] == '+') {
        start = 1;
    }

    std::string coeff_str;
    size_t i = start;

    // start num is num
    bool has_coeff = false;
    while (i < s.size() && (std::isdigit(s[i]) || s[i] == '.' ||
        (i > start && (s[i] == '+' || s[i] == '-')))) {
        coeff_str += s[i];
        i++;
        has_coeff = true;
    }

    if (has_coeff && !coeff_str.empty()) {
        try {
            coeff = std::stod(coeff_str);
        }
        catch (...) {
            coeff = 1.0;
        }
    }

    if (negative) {
        coeff = -coeff;
    }

    while (i < s.size()) {
        char var = s[i];

        if (var >= 'A' && var <= 'Z') {
            var = var + ('a' - 'A');
        }

        if (var == 'x' || var == 'y' || var == 'z') {
            i++;
            int power = 1;

            // check degree
            if (i < s.size() && s[i] == '^') {
                i++;
                std::string power_str;
                while (i < s.size() && std::isdigit(s[i])) {
                    power_str += s[i];
                    i++;
                }
                if (!power_str.empty()) {
                    try {
                        power = std::stoi(power_str);
                    }
                    catch (...) {
                        power = 1;
                    }
                }
            }

            switch (var) {
            case 'x': px = power; break;
            case 'y': py = power; break;
            case 'z': pz = power; break;
            }
        }
        else {
            i++;
        }
    }

    result._coeff = coeff;
    result._powers[0] = px;
    result._powers[1] = py;
    result._powers[2] = pz;

    return result;
}
