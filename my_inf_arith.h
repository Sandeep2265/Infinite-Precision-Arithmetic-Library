#include <iostream>

#include <string>

namespace InfiniteArithmetic {
    class Integer {
    private:
    std::string value;
    friend class Float;
    public:
         Integer() : value("0") {}
    Integer(std::string s) : value(s) {}
    Integer(const Integer& o) : value(o.value) {}
    ~Integer() {}
        Integer operator+( Integer o);
        Integer operator-( Integer o);
        Integer operator*( Integer o);

        friend std::ostream& operator<<(std::ostream& os, const Integer& o);
        friend std::istream& operator>>(std::istream& input, Integer& o);
        };

    class Float {
 private:
        std::string value;
    public:
       Float() : value("0") {}
    Float(std::string s) : value(s) {}
    Float(const Float& o) : value(o.value) {}

    ~Float() {}
       
        Float operator+( Float o);
        Float operator-( Float o);
        Float operator*( Float o);
      

        friend std::ostream& operator<<(std::ostream& os, const Float& o);
        friend std::istream& operator>>(std::istream& input, Float& o);
     
    };
}

