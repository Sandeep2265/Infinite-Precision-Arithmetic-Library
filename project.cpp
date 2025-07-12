

#include <algorithm>
#include "my_inf_arith.h"
using namespace std;
namespace InfiniteArithmetic
{

    /*Implementation of addition operator for Integer class*/
    Integer Integer::operator+(Integer o)
    {
        /*if both numbers are positive*/
        if (this->value[0] != '-' && o.value[0] != '-')
        {
            int len1 = this->value.size() - 1;
            int len2 = o.value.size() - 1;
            int extra = 0;
            int add;
            string sum;
            /*loop through digit by digit of both numbers*/
            while (len1 >= 0 || len2 >= 0 || extra > 0)
            {
                add = 0;
                /*adding digits of both numbers*/
                if (len1 >= len2)
                {
                    if (len1 >= 0)
                    {
                        add = value[len1] - '0';
                        len1--;
                    }
                    if (len2 >= 0)
                    {
                        add += o.value[len2] - '0';
                        len2--;
                    }
                }
                else
                {
                    if (len2 >= 0)
                    {
                        add = o.value[len2] - '0';
                        len2--;
                    }
                    if (len1 >= 0)
                    {
                        add += this->value[len1] - '0';
                        len1--;
                    }
                }
                /*adding the carrying value*/
                add += extra;
                sum = char(add % 10 + '0') + sum;
                /*updating the extra*/
                extra = add / 10;
            }

            return Integer(sum);
        }
        /*if first number is negative and second one is positive*/
        if (this->value[0] == '-' && o.value[0] != '-')
        {
            this->value.erase(0, 1); /*removing - sign form first number*/
            Integer result = Integer(o.value) - Integer(this->value);
            return result;
        }
        /*if first number is positive and second number is negative*/
        if (value[0] != '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1); /*removing - sign form second number*/
            Integer result = Integer(this->value) - Integer(o.value);
            return result;
        }
        if (this->value[0] == '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1);
            this->value.erase(0, 1); /*removing - sign form both numbers*/
            Integer result = Integer(this->value) + Integer(o.value);
            result.value.insert(0, 1, '-'); /*inserting - at the first of result*/
            return result;
        }
    }
    /*Implementation of subtraction operator for Integer class*/
    Integer Integer::operator-(Integer o)
    {
        /*if both numbers are positive*/
        if (this->value[0] != '-' && o.value[0] != '-')
        {
            int len1 = this->value.size() - 1;
            int len2 = o.value.size() - 1;
            int borrow = 0;
            int sub;
            string result;
            /*subtracting digits of both numbers*/
            if (len1 > len2)
            {
                while (len1 >= 0 || len2 >= 0)
                {
                    if (len1 >= 0)
                    {
                        sub = this->value[len1] - '0' - borrow;
                        len1--;
                    }
                    else
                    {
                        sub = -borrow;
                    }

                    if (len2 >= 0)
                    {
                        sub -= o.value[len2] - '0';
                        len2--;
                    }
                    /*updating borrow and result*/

                    if (sub >= 0)
                    {
                        borrow = 0;
                    }
                    else
                    {
                        if (len1 >= 0 && len2 >= 0)
                        {
                            sub += 10;
                        }
                        else
                        {
                            sub = sub;
                        }
                        borrow = 1;
                    }

                    result = char(sub + '0') + result;
                }
                /*removing leading zeroes*/
                while (result.size() > 1 && result[0] == '0')
                {
                    result = result.substr(1);
                }

                return Integer(result);
            }

            if (len2 > len1)
            {
                while (len1 >= 0 || len2 >= 0)
                {
                    if (len2 >= 0)
                    {
                        sub = o.value[len2] - '0' - borrow;
                        len2--;
                    }
                    else
                    {
                        sub = -borrow;
                    }

                    if (len1 >= 0)
                    {
                        sub -= this->value[len1] - '0';
                        len1--;
                    }

                    if (sub >= 0)
                    {
                        borrow = 0;
                    }
                    else
                    {
                        sub += 10;
                        borrow = 1;
                    }

                    result = char(sub + '0') + result;
                }

                while (result.size() > 1 && result[0] == '0')
                {
                    result = result.substr(1);
                }
                result.insert(0, 1, '-');

                return Integer(result);
            }

            if (len1 == len2)
            {
                int u = 0;
                for (int i = 0; i < len1; i++)
                {
                    if (this->value[i] < o.value[i])
                    {
                        u = 1;
                        break;
                    }
                    else if (this->value[i] > o.value[i])
                    {
                        break;
                    }
                }
                if (u == 0)
                {
                    while (len1 >= 0 || len2 >= 0)
                    {
                        if (len1 >= 0)
                        {
                            sub = this->value[len1] - '0' - borrow;
                            len1--;
                        }
                        else
                        {
                            sub = -borrow;
                        }

                        if (len2 >= 0)
                        {
                            sub -= o.value[len2] - '0';
                            len2--;
                        }

                        if (sub >= 0)
                        {
                            borrow = 0;
                        }
                        else
                        {
                            sub += 10;
                            borrow = 1;
                        }

                        result = char(sub + '0') + result;
                    }

                    while (result.size() > 1 && result[0] == '0')
                    {
                        result = result.substr(1);
                    }
                    return Integer(result);
                }

                if (u == 1)
                {
                    while (len1 >= 0 || len2 >= 0)
                    {
                        if (len2 >= 0)
                        {
                            sub = o.value[len2] - '0' - borrow;
                            len2--;
                        }
                        else
                        {
                            sub = -borrow;
                        }

                        if (len1 >= 0)
                        {
                            sub -= this->value[len1] - '0';
                            len1--;
                        }

                        if (sub >= 0)
                        {
                            borrow = 0;
                        }
                        else
                        {
                            sub += 10;
                            borrow = 1;
                        }

                        result = char(sub + '0') + result;
                    }
                    /*removing leading zeroes*/
                    while (result.size() > 1 && result[0] == '0')
                    {
                        result = result.substr(1);
                    }
                    result.insert(0, 1, '-');

                    return Integer(result);
                }
            }
        }
        /*if first number is negative and second one is positive*/
        if (this->value[0] == '-' && o.value[0] != '-')
        {
            this->value.erase(0, 1); /*removing - sign form first number*/
            Integer result = Integer(this->value) + Integer(o.value);
            result.value.insert(0, 1, '-'); /*inserting - statring of result*/
            return result;
        }
        /*if first number is negative and second one is negative*/
        if (this->value[0] == '-' && o.value[0] == '-')
        {
            this->value.erase(0, 1); /*removing - sign form first number*/
            o.value.erase(0, 1);     /*removing - sign form second number*/
            Integer result = Integer(o.value) - Integer(this->value);
            return result;
        }
        /*if second number is negative and first one is positive*/
        if (this->value[0] != '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1); /*removing - sign form first number*/
            Integer result = Integer(this->value) + Integer(o.value);
            return result;
        }
    }
    /*Implementation of multiplication operator for Integer class*/
    Integer Integer::operator*(Integer o)
    {
        /*if first number is positive and second one is positive*/
        if (this->value[0] != '-' && o.value[0] != '-')
        {

            int len1 = this->value.size() - 1;

            int len2 = o.value.size() - 1;

            int extra = 0;

            int mul;

            string result;

            Integer final_result("0");

            int u = 0;
            /*Loop through digits of the first number*/
            for (int i = len1; i >= 0; i--)
            {
                /*reset result everytime*/

                result = "";

                extra = 0;

                /*Loop through digits of the second number*/
                for (int j = len2; j >= 0; j--)
                {

                    if (j > 0)
                    {

                        mul = (this->value[i] - '0') * (o.value[j] - '0') + extra;

                        extra = mul / 10;

                        result = result + char(mul % 10 + '0');
                    }
                    else
                    {

                        mul = (this->value[i] - '0') * (o.value[j] - '0') + extra;

                        if (mul >= 10)
                        {

                            result = result + char(mul % 10 + '0') +

                                     char(mul / 10 + '0');
                        }
                        else
                        {

                            result = result + char(mul + '0');
                        }

                        extra = 0;
                    }
                }

                if (extra > 0)
                {

                    result = result + char(extra + '0');
                }
                /*Reverse the result*/

                reverse(result.begin(), result.end());

                result += std::string(u, '0');

                u++;

                Integer add = result;

                /*Adding result to the final result*/
                final_result = add + final_result;
            }

            return Integer(final_result);
        }
        /*if first number is negative and second one is positive*/
        if (this->value[0] == '-' && o.value[0] != '-')
        {
            this->value.erase(0, 1); /*removing - from first one*/
            Integer result = Integer(this->value) * Integer(o.value);
            result.value.insert(0, 1, '-'); /*inserting - before result*/
            return result;
        }
        /*if first number is positive and second one is negative*/
        if (this->value[0] != '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1); /*removing - from first one*/
            Integer result = Integer(this->value) * Integer(o.value);
            result.value.insert(0, 1, '-'); /*inserting - before result*/
            return result;
        }
        /*if first number is negative and second one is negative*/
        if (this->value[0] == '-' && o.value[0] == '-')
        {
            this->value.erase(0, 1); /*removing - from first one*/
            o.value.erase(0, 1);     /*removing - from first one*/
            Integer result = Integer(this->value) * Integer(o.value);
            return result;
        }
    }

    Integer Integer::operator/(Integer o)
    {
        if (o.value == "0")
        {
            throw std::invalid_argument("Division by zero");
        }
        bool neg = false;
        string a = this->value;
        string b = o.value;
        if (a[0] == '-' && b[0] != '-')
        {
            neg = true;
            a.erase(0, 1);
        }
        else if (a[0] != '-' && b[0] == '-')
        {
            neg = true;
            b.erase(0, 1);
        }
        else if (a[0] == '-' && b[0] == '-')
        {
            a.erase(0, 1);
            b.erase(0, 1);
        }

        string result;
        string curr = "";
        for (size_t i = 0; i < a.size(); ++i)
        {
            curr += a[i];
            int count = 0;
            while (curr.size() > 1 && curr[0] == '0')
                curr.erase(0, 1);
            while (Integer(curr) >= Integer(b))
            {
                curr = (Integer(curr) - Integer(b)).value;
                count++;
            }
            result += char(count + '0');
        }
        while (result.size() > 1 && result[0] == '0')
            result.erase(0, 1);
        if (neg)
            result.insert(0, 1, '-');
        return Integer(result);
    }

    ostream &operator<<(ostream &os, const Integer &o)
    {
        os << o.value;

        return os;
    }

    istream &operator>>(istream &input, Integer &o)
    {
        input >> o.value;

        return input;
    }

    /*Implementation of addition operator for Float class*/
    Float Float::operator+(Float o)
    {
        /*If both numbers are positive*/
        if (this->value[0] != '-' && o.value[0] != '-')
        {
            int dot_pos1 = this->value.find('.');
            int dot_pos2 = o.value.find('.');

            int int1_len = dot_pos1;
            int frac1_len = this->value.size() - dot_pos1 - 1;
            int int2_len = dot_pos2;
            int frac2_len = o.value.size() - dot_pos2 - 1;
            /*extracting integer parts and float parts*/
            std::string ip1 = this->value.substr(0, dot_pos1);
            std::string ip2 = o.value.substr(0, dot_pos2);
            std::string fp1 = this->value.substr(dot_pos1 + 1);
            std::string fp2 = o.value.substr(dot_pos2 + 1);
            /*equalizing both intger parts and float parts*/
            if (int1_len > int2_len)
            {
                for (int i = 0; i < int1_len - int2_len; i++)
                {
                    ip2.insert(0, 1, '0');
                }
            }
            else
            {
                for (int i = 0; i < int2_len - int1_len; i++)
                {
                    ip1.insert(0, 1, '0');
                }
            }

            if (frac1_len > frac2_len)
            {
                for (int i = 0; i < frac1_len - frac2_len; i++)
                {
                    fp2.push_back('0');
                }
            }
            else
            {
                for (int i = 0; i < frac2_len - frac1_len; i++)
                {
                    fp1.push_back('0');
                }
            }
            /*adding separately integer parts and float parts*/
            int z = fp1.size();
            Integer add1 = Integer(ip1) + Integer(ip2);
            Integer add2 = Integer(fp1) + Integer(fp2);
            add2.value.insert(add2.value.size() - z, 1, '.');
            Integer add3;
            add3.value = add2.value.substr(0, add2.value.size() - z - 1);
            string add4 = add2.value.substr(add2.value.size() - z);
            Integer a = add3 + add1;
            string result = a.value + "." + add4;
            return (Float(result));
        } /*if second number is positive and first one is negative*/
        if (this->value[0] == '-' && o.value[0] != '-')
        {
            this->value.erase(0, 1);
            Float result = Float(o.value) - Float(this->value);
            return result;
        }
        /*if first number is positive and second one is negative*/
        if (this->value[0] != '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1);
            Float result = Float(this->value) - Float(o.value);
            return result;
        }
        /*if first number is negative and second one is negative*/
        if (this->value[0] == '-' && o.value[0] == '-')
        {
            this->value.erase(0, 1);
            o.value.erase(0, 1);
            Float result = Float(this->value) + Float(o.value);
            result.value.insert(0, 1, '-');
            return result;
        }
    }

    Float Float::operator-(Float o)
    {
        /*if first number is positive and second one is positive*/
        if (this->value[0] != '-' && o.value[0] != '-')
        {

            int dot_pos1 = this->value.find('.');
            int dot_pos2 = o.value.find('.');
            /*extracting integer parts and float parts*/
            int int1_len = dot_pos1;
            int frac1_len = this->value.size() - dot_pos1 - 1;
            int int2_len = dot_pos2;
            int frac2_len = o.value.size() - dot_pos2 - 1;
            /*equalizing both intger parts and float parts*/
            string ip1 = this->value.substr(0, dot_pos1);
            string ip2 = o.value.substr(0, dot_pos2);
            string fp1 = this->value.substr(dot_pos1 + 1);
            string fp2 = o.value.substr(dot_pos2 + 1);

            if (int1_len > int2_len)
            {
                for (int i = 0; i < int1_len - int2_len; i++)
                {
                    ip2.insert(0, 1, '0');
                }
            }
            else
            {
                for (int i = 0; i < int2_len - int1_len; i++)
                {
                    ip1.insert(0, 1, '0');
                }
            }

            if (frac1_len > frac2_len)
            {
                for (int i = 0; i < frac1_len - frac2_len; i++)
                {
                    fp2.push_back('0');
                }
            }
            else
            {
                for (int i = 0; i < frac2_len - frac1_len; i++)
                {
                    fp1.push_back('0');
                }
            }
            string I = ip1 + fp1;

            string F = ip2 + fp2;
            /*subtracting separately integer parts and float parts*/
            Integer sub = Integer(I) - Integer(F);

            int result_frac_len = std::max(frac1_len, frac2_len);
            int len1 = sub.value.size() - result_frac_len;

            if (len1 <= 0)
            {
                sub.value.insert(0, "0.");
            }
            else
            {
                sub.value.insert(len1, ".");
            }

            return Float(sub.value);
        } /*if second number is positive and first one is negative*/
        if (this->value[0] == '-' && o.value[0] != '-')
        {
            this->value.erase(0, 1);
            Float result = Float(this->value) + Float(o.value);
            result.value.insert(0, 1, '-');
            return result;
        }
        /*if first number is positive and second one is negative*/
        if (this->value[0] != '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1);
            Float result = Float(this->value) + Float(o.value);
            return result;
        }
        /*if both are negative*/
        if (this->value[0] == '-' && o.value[0] == '-')
        {
            this->value.erase(0, 1);
            o.value.erase(0, 1);
            Float result = Float(o.value) - Float(this->value);
            return result;
        }
    }
    /*Implementation of multiplication operator for Float class*/

    Float Float::operator*(Float o)
    {
        /*If both numbers are positive*/
        if (this->value[0] != '-' && o.value[0] != '-')
        {
            int dot_pos1 = this->value.find('.');
            int dot_pos2 = o.value.find('.');
            /*extracting integer parts and float parts*/
            int int1_len = dot_pos1;
            int frac1_len = this->value.size() - dot_pos1 - 1;
            int int2_len = dot_pos2;
            int frac2_len = o.value.size() - dot_pos2 - 1;
            /*equalizing both intger parts and float parts*/
            string ip1 = this->value.substr(0, dot_pos1);
            string ip2 = o.value.substr(0, dot_pos2);
            string fp1 = this->value.substr(dot_pos1 + 1);
            string fp2 = o.value.substr(dot_pos2 + 1);
            string I = ip1 + fp1;
            string F = ip2 + fp2;
            Integer mul = Integer(I) * Integer(F);
            int result_frac_len = frac1_len + frac2_len;
            int len1 = mul.value.size() - result_frac_len;

            if (len1 <= 0)
            {
                mul.value.insert(0, "0.");
            }
            else
            {
                mul.value.insert(len1, ".");
            }

            return Float(mul.value);
        }
        /*if first number is positive and second one is negative*/
        if (this->value[0] != '-' && o.value[0] == '-')
        {
            o.value.erase(0, 1);
            Float result = Float(this->value) * Float(o.value);
            result.value.insert(0, 1, '-');
            return result;
        }
        /*if second number is positive and first one is negative*/
        if (this->value[0] == '-' && o.value[0] != '-')
        {
            this->value.erase(0, 1);
            Float result = Float(this->value) * Float(o.value);
            result.value.insert(0, 1, '-');
            return result;
        }
        /*both are negative*/
        if (this->value[0] == '-' && o.value[0] == '-')
        {
            this->value.erase(0, 1);
            o.value.erase(0, 1);
            Float result = Float(this->value) * Float(o.value);
            return result;
        }
    }

    Float Float::operator/(Float o)
    {
        if (o.value == "0" || o.value == "0.0")
        {
            throw std::invalid_argument("Division by zero");
        }

        int dot1 = this->value.find('.');
        int dot2 = o.value.find('.');

        int frac1_len = this->value.size() - dot1 - 1;
        int frac2_len = o.value.size() - dot2 - 1;

        string n1 = this->value;
        string n2 = o.value;

        n1.erase(dot1, 1);
        n2.erase(dot2, 1);

        int total_frac = frac1_len - frac2_len + 20;
        for (int i = 0; i < total_frac; ++i)
        {
            n1.push_back('0');
        }

        Integer dividend(n1);
        Integer divisor(n2);
        Integer quotient = dividend / divisor;

        string q_str = quotient.value;
        if (q_str.size() <= 20)
        {
            q_str.insert(0, 20 - q_str.size() + 1, '0');
        }
        q_str.insert(q_str.size() - 20, ".");

        return Float(q_str);
    }

    ostream &operator<<(ostream &os, const Float &o)
    {
        os << o.value;

        return os;
    }

    istream &operator>>(istream &input, Float &o)
    {
        input >> o.value;

        return input;
    }

}
/*using command line arguments*/
int main(int argc, char *argv[])
{
    using namespace std;
    using namespace InfiniteArithmetic;
    string data_type = argv[1];
    string oper = argv[2];
    string s1 = argv[3];
    string s2 = argv[4];
    int i;
    if (oper == "add")
        i = 1;
    else if (oper == "sub")
        i = 2;
    else if (oper == "mul")
        i = 3;
    else if (oper == "div")
        i = 4;

    if (data_type == "int")
    {
        Integer num1(s1);
        Integer num2(s2);
        Integer result;
        if (i == 1)
            result = num1 + num2;
        else if (i == 2)
            result = num1 - num2;
        else if (i == 3)
            result = num1 * num2;
        else if (i == 4)
            result = num1 / num2;
        cout << result << endl;
    }
    else if (data_type == "float")
    {
        Float num1(s1);
        Float num2(s2);
        Float result;
        if (i == 1)
            result = num1 + num2;
        else if (i == 2)
            result = num1 - num2;
        else if (i == 3)
            result = num1 * num2;
        else if (i == 4)
            result = num1 / num2;
        cout << result << endl;
    }
    return 0;
}

