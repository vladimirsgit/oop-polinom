//
// Created by Vladimir on 11/04/2023.
//

#ifndef POLINOMOOP_COMPLEX_H
#define POLINOMOOP_COMPLEX_H
#include <iostream>
#include <string>
using namespace std;
class Complex {
    int r;
    int i;
public:
    Complex();
    Complex(int r, int i);
    friend ostream & operator<<(ostream &o, const Complex &x);
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
