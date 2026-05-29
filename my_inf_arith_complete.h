#ifndef MY_INF_ARITH_H
#define MY_INF_ARITH_H

#include <iostream>
#include <string>

namespace InfiniteArithmetic {

class Integer {
private:
    std::string value;

public:
    Integer();
    Integer(std::string s);

    Integer operator+(const Integer& o) const;
    Integer operator-(const Integer& o) const;
    Integer operator*(const Integer& o) const;
    Integer operator/(const Integer& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Integer& o);
    friend std::istream& operator>>(std::istream& is, Integer& o);
};

class Float {
private:
    std::string value;

public:
    Float();
    Float(std::string s);

    Float operator+(const Float& o) const;
    Float operator-(const Float& o) const;
    Float operator*(const Float& o) const;
    Float operator/(const Float& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Float& o);
    friend std::istream& operator>>(std::istream& is, Float& o);
};

}

#endif
