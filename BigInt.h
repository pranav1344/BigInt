#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
#include <string>
#include<vector>

#define max(a,b) ((a) > (b) ? (a) : (b))

std::vector<unsigned int> add(std::vector<unsigned int> lhs, std::vector<unsigned int> rhs);
std::vector<unsigned int> subtract(std::vector<unsigned int> lhs, std::vector<unsigned int> rhs);
std::vector<unsigned int> multiply(std::vector<unsigned int> num1, std::vector<unsigned int> num2);

class bigInteger
{
    public :
    std::string representation;
    std::vector <unsigned int> v;
    short int signOfInteger;
    void toInteger();
    void toString();
    void displayNumber();
};

bigInteger multiplyBigInteger( bigInteger a, bigInteger b);
bigInteger addBigInteger( bigInteger a, bigInteger b);
bigInteger subtractBigInteger( bigInteger a, bigInteger b);
bigInteger modulo(bigInteger a, bigInteger b);

#endif