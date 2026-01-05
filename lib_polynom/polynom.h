#ifndef POLYNOM_H
#define POLYNOM_H
#include "../lib_monom/monom.h"
#include "../lib_list/list.h"
#include <string>
#include <initializer_list>

class Polynom {
private:
    List<Monom> _terms;  
    void _simplify();
    void _sort_terms();

public:
    Polynom();                                  
    Polynom(const Monom& m);                  
    Polynom(const std::string& str);            
    Polynom(std::initializer_list<Monom> list);
    Polynom(std::initializer_list<double> list);
    Polynom(const Polynom& other);              

    Polynom& operator=(const Polynom& other);

    const List<Monom>& get_terms() const { return _terms; }
    bool is_empty() const { return _terms.is_empty(); }
    int size() const { return _terms.size(); }

    Polynom operator+(const Polynom& other) const;  
    Polynom operator-(const Polynom& other) const;  
    Polynom operator*(const Polynom& other) const;  
    Polynom operator*(double scalar) const;         
    Polynom operator/(double scalar) const;        
    Polynom operator-() const;                      

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator*=(double scalar);
    Polynom& operator/=(double scalar);

    Polynom operator+(const Monom& m) const;  
    Polynom operator-(const Monom& m) const;  
    Polynom operator*(const Monom& m) const;  

    Polynom& operator+=(const Monom& m);
    Polynom& operator-=(const Monom& m);
    Polynom& operator*=(const Monom& m);


    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    double evaluate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);

    static Polynom parse(const std::string& str);
};

Polynom operator*(double scalar, const Polynom& p);
Polynom operator+(const Monom& m, const Polynom& p);
Polynom operator-(const Monom& m, const Polynom& p);
Polynom operator*(const Monom& m, const Polynom& p);

#endif