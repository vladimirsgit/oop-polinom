#ifndef POLINOMOOP_COMPLEX_H
#define POLINOMOOP_COMPLEX_H
#include <iostream>
#include <string>
using namespace std;
class Complex {
    int realPart;
    int imaginaryPart;
public:
    Complex();
    Complex(int r, int i);
    friend ostream & operator<<(ostream &basicOstream, const Complex &x);
    friend istream & operator>>(istream &basicIstream, Complex &x);
    friend Complex operator+(const Complex& a, const Complex& b);
    friend Complex operator-(const Complex& a, const Complex& b);
    friend Complex operator*(const Complex& a, const Complex& b);
    friend bool operator==(const Complex& a, const Complex& b);
    friend bool operator>(const Complex& a, int value);
    friend bool operator<(const Complex& a, int value);
    Complex& operator=(int value);
    friend string to_string(const Complex &a);
};


#endif //POLINOMOOP_COMPLEX_H
