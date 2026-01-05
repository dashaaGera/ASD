#include "../lib_polynom/polynom.h"
#include <sstream>
#include <stdexcept>


Polynom::Polynom() {}

Polynom::Polynom(const Monom& m) {
    if (m.coeff() != 0) {
        _terms.push_back(m);
    }
}

Polynom::Polynom(const std::string& str) {
    *this = Polynom::parse(str);
}


Polynom::Polynom(std::initializer_list<Monom> list) {
    for (const auto& m : list) {
        if (m.coeff() != 0) {
            _terms.push_back(m);
        }
    }
    _simplify();
}

//1 monom
Polynom::Polynom(std::initializer_list<double> list) {
    Monom m(list);
    if (m.coeff() != 0) {
        _terms.push_back(m);
    }
}

Polynom::Polynom(const Polynom& other) : _terms(other._terms) {}


Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _terms = other._terms;
    }
    return *this;
}

void Polynom::_simplify() {
    if (_terms.is_empty()) return;

    _sort_terms();

    Node<Monom>* current = _terms.head();
    while (current != nullptr) {
        // check all next monoms by similar
        Node<Monom>* runner = current->next;
        while (runner != nullptr) {
            if (current->value == runner->value) {
                try {
                    current->value = current->value + runner->value;
                    Node<Monom>* to_delete = runner;
                    runner = runner->next; // remember next before delete
                    _terms.erase(to_delete);
                }
                catch (...) {
                    runner = runner->next;
                }
            }
            else {
                runner = runner->next;
            }
        }

        // if currenr is null
        if (current->value.coeff() == 0) {
            Node<Monom>* to_delete = current;
            current = current->next;
            _terms.erase(to_delete);
        }
        else {
            current = current->next;
        }
    }
}
void Polynom::_sort_terms() {
    if (_terms.size() <= 1) return;

    bool swapped;
    do {
        swapped = false;
        Node<Monom>* current = _terms.head();

        while (current != nullptr && current->next != nullptr) {
            if (current->value < current->next->value) {
                Monom temp = current->value;
                current->value = current->next->value;
                current->next->value = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}


Polynom Polynom::operator+(const Monom& m) const {
    Polynom result = *this;  

    bool found_similar = false;
    // find similar monom in polynom
    for (auto it = result._terms.begin(); it != result._terms.end(); ++it) {
        if (*it == m) {  
            try {
                *it = (*it) + m;  
                found_similar = true;
                break;
            }
            catch (const std::exception&) {}
        }
    }

    //else
    if (!found_similar) {
        result._terms.push_back(m);
    }

    result._simplify();
    return result;
}


Polynom Polynom::operator-(const Monom& m) const {
    Polynom result = *this;  
    bool found_similar = false;
    for (auto it = result._terms.begin(); it != result._terms.end(); ++it) {
        if (*it == m) {
            try {
                *it = (*it) - m;  
                found_similar = true;
                break;
            }
            catch (const std::exception&) {
            }
        }
    }

    if (!found_similar) {
        result._terms.push_back(-m);  
    }

    result._simplify();
    return result;
}


Polynom Polynom::operator*(const Monom& m) const {
    if (m.coeff() == 0) {
        return Polynom(); 
    }
    Polynom result = *this;  

    for (auto it = result._terms.begin(); it != result._terms.end(); ++it) {
        *it = (*it) * m;  
    }
    result._simplify();
    return result;
}


Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this; 
    for (auto it = other._terms.begin(); it != other._terms.end(); ++it) {
        result = result + (*it); 
    }

    return result; 
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result = *this;  

    for (auto it = other._terms.begin(); it != other._terms.end(); ++it) {
        result = result - (*it);  
    }

    return result;
}


Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result;
    for (const auto& monom : _terms) {
        result += (other * monom);
    }
    result._simplify();
    return result;
}

Polynom Polynom::operator*(double scalar) const {
    if (scalar == 0) {
        return Polynom();  
    }
    Polynom result = *this;
    for (auto it = result._terms.begin(); it != result._terms.end(); ++it) {
        *it = (*it) * scalar;
    }
    result._simplify();
    return result;
}

Polynom Polynom::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::logic_error("Division by zero");
    }
    Polynom result = *this;  

    for (auto it = result._terms.begin(); it != result._terms.end(); ++it) {
        *it = (*it) / scalar; 
    }

    result._simplify();
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

Polynom& Polynom::operator*=(double scalar) {
    if (scalar == 0) {
        _terms = List<Monom>();  
        return *this;  
    }

    for (auto it = _terms.begin(); it != _terms.end(); ++it) {
        *it = (*it) * scalar;
    }
    _simplify();
    return *this;
}

Polynom& Polynom::operator/=(double scalar) {
    if (scalar == 0) {
        throw std::logic_error("Division by zero");
    }
    for (auto it = _terms.begin(); it != _terms.end(); ++it) {
        *it = (*it) / scalar;
    }
    _simplify();
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

Polynom& Polynom::operator*=(const Monom& m) {
    if (m.coeff() == 0) {
        _terms = List<Monom>();  
        return *this;
    }
    for (auto it = _terms.begin(); it != _terms.end(); ++it) {
        *it = (*it) * m;
    }
    _simplify();
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
    int num_monoms;
    is >> num_monoms;

    p = Polynom();  
    for (int i = 0; i < num_monoms; i++) {
        Monom m;
        is >> m; 
        p._terms.push_back(m);
    }

    p._simplify();
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


Polynom Polynom::parse(const std::string& str) {
    if (str.empty()) {
        return Polynom();
    }

    std::string s = remove_spaces(str);
    if (s.empty() || s == "0") {
        return Polynom();
    }

    Polynom result;
    std::string current_monom;

    if (s[0] != '+' && s[0] != '-') {
        current_monom = "+";
    }

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];

        // start new monom
        if ((c == '+' || c == '-') && i > 0) {
            if (!current_monom.empty()) {
                Monom m(current_monom);
                if (std::abs(m.coeff()) > 1e-12) {
                    result = result + m;
                }
            }
            current_monom = std::string(1, c); 
        }
        else {
            current_monom += c;
        }
    }

    // last monom
    if (!current_monom.empty()) {
        Monom m(current_monom);
        if (std::abs(m.coeff()) > 1e-12) {
            result = result + m;
        }
    }

    result._simplify();
    return result;
}


