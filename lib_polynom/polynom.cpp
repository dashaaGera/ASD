#include "../lib_polynom/polynom.h"
#include <sstream>
#include <stdexcept>

int Polynom::_counter = 1;
Polynom::Polynom() { _name = "pol" + std::to_string(_counter++); }

Polynom::Polynom(const Monom& m)
{
    *this = *this + m;
    _name = "pol" + std::to_string(_counter++);
}

Polynom::Polynom(const std::string& str) {
    *this = Polynom::parse(str);
}


Polynom::Polynom(std::initializer_list<Monom> list)
{
    for (const auto& m : list)
        *this = *this + m;
    _name = "pol" + std::to_string(_counter++);
}

Polynom::Polynom(std::initializer_list<double> list)
{
    *this = *this + Monom(list);
    _name = "pol" + std::to_string(_counter++);
}

Polynom::Polynom(const Polynom& other) : _terms(other._terms), _name("pol" + std::to_string(_counter++)) {}


Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _terms = other._terms;
        _name = "pol" + std::to_string(_counter++);
    }
    return *this;
}

Polynom Polynom::operator+(const Monom& m) const
{
    if (m.coeff() == 0)
        return *this;

    Polynom result = *this;
    Node<Monom>* current = result._terms.head();
    Node<Monom>* prev = nullptr;

    while (current) {
        if (current->value == m) {
            current->value += m;
            if (current->value.coeff() == 0)
                result._terms.erase(current);
            return result;
        }

        if (current->value < m) {
            if (!prev)
                result._terms.push_front(m);
            else
                result._terms.insert(prev, m);

            return result;
        }

        prev = current;
        current = current->next;
    }

    result._terms.push_back(m);
    return result;
}

Polynom Polynom::operator-(const Monom& m) const
{
    return *this + (-m);
}

Polynom Polynom::operator*(const Monom& m) const
{
    if (m.coeff() == 0)
        return Polynom();

    Polynom result;
    for (auto it = _terms.begin(); it != _terms.end(); ++it)
        result += ((*it) * m);

    return result;
}


Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this; 
    for (auto it = other._terms.begin(); it != other._terms.end(); ++it) {
        result +=(*it); 
    }
    return result; 
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result = *this;  
    for (auto it = other._terms.begin(); it != other._terms.end(); ++it) {
        result -= (*it);  
    }
    return result;
}


Polynom Polynom::operator*(const Polynom& other) const
{
    Polynom result;
    for (auto it = _terms.begin(); it != _terms.end(); ++it)
        result += other * (*it);

    return result;
}

Polynom Polynom::operator*(double scalar) const
{
    if (scalar == 0)
        return Polynom();
    Polynom result;
    for (auto it = _terms.begin(); it != _terms.end(); ++it)
        result += ((*it) * scalar);
    return result;
}

Polynom Polynom::operator/(double scalar) const
{
    if (scalar == 0)
        throw std::logic_error("Division by zero");
    Polynom result;
    for (auto it = _terms.begin(); it != _terms.end(); ++it)
        result+= ((*it) / scalar);

    return result;
}

Polynom Polynom::operator-() const {
    Polynom result = *this;  
    for (auto it = result._terms.begin(); it != result._terms.end(); ++it) {
        *it = -(*it);  
    }
    return result;  
}

Polynom& Polynom::operator+=(const Polynom& other) {
    *this = *this + other;  
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    *this = *this - other; 
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;  
    return *this;
}

Polynom& Polynom::operator*=(double scalar)
{
    *this = *this * scalar;
    return *this;
}

Polynom& Polynom::operator/=(double scalar)
{
    *this = *this / scalar;
    return *this;
}

Polynom& Polynom::operator+=(const Monom& m) {
    *this = *this + m; 
    return *this;
}

Polynom& Polynom::operator-=(const Monom& m) {
    *this = *this - m; 
    return *this;
}

Polynom& Polynom::operator*=(const Monom& m)
{
    *this = *this * m;
    return *this;
}

bool Polynom::operator==(const Polynom& other) const {
    if (_terms.size() != other._terms.size()) return false;

    auto it1 = _terms.begin();
    auto it2 = other._terms.begin();

    while( !(it1 == _terms.end()) ){
        if (!(*it1 == *it2)) return false;  
        ++it1;
        ++it2;
    }

    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}


double Polynom::evaluate(double x, double y, double z) const {
    double result = 0;
    for (auto it = _terms.begin(); it != _terms.end(); ++it) {
        result += (*it).evaluate(x, y, z); 
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    if (p._terms.is_empty()) {
        os << "0";
        return os;
    }

    bool first = true;
    for (auto it = p._terms.begin(); it != p._terms.end(); ++it) {
        if (!first) {
            if ((*it).coeff() > 0) {
                os << " + ";
            }
            else {
                os << " - ";
                Monom positive = -(*it);
                os << positive;
                continue;
            }
        }
        os << *it;  
        first = false;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynom& p) {
    std::string line;
    if (std::getline(is, line)) 
        p = Polynom::parse(line);
    return is;
}


Polynom operator*(double scalar, const Polynom& p) {
    return p * scalar;  
}

Polynom operator+(const Monom& m, const Polynom& p) {
    return p + m; 
}

Polynom operator-(const Monom& m, const Polynom& p) {
    return -p+m;
}

Polynom operator*(const Monom& m, const Polynom& p) {
    return p * m;  
}

std::string remove_spaces(const std::string& s) {
    std::string result;
     for (char c : s) 
         if (!std::isspace(c)) result += c;
        return result;
 }


Polynom Polynom::parse(const std::string& str)
{
    std::string s = remove_spaces(str);
    if (s.empty() || s == "0")
        return Polynom();
    //sign first monom
    if (s[0] != '+' && s[0] != '-')
        s = "+" + s;

    Polynom result;
    size_t start = 0;

    for (size_t i = 1; i < s.size(); ++i)
    {
        if (s[i] == '+' || s[i] == '-')
        {
            std::string token = s.substr(start, i - start);
            result += Monom(token);
            start = i;
        }
    }

    result += Monom(s.substr(start));

    return result;
}



