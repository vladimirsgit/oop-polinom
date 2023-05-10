#include "Complex.h"

Complex::Complex() {
    this->realPart = 0;
    this->imaginaryPart = 0;
}

Complex::Complex(int r, int i) {
    this->realPart = r;
    this->imaginaryPart = i;
}


ostream &operator<<(ostream &basicOstream, const Complex &x) {
    if(x.realPart != 0 || x.imaginaryPart == 0) basicOstream << x.realPart;
    if(x.imaginaryPart > 0 && x.realPart != 0) basicOstream << "+";
    if(x.imaginaryPart != 0) basicOstream << x.imaginaryPart << "i";
    return basicOstream;
}

istream & operator>>(istream &basicIstream, Complex &x){
    cout << "Introdu partea reala, apoi partea imaginara: ";
    basicIstream >> x.realPart >> x.imaginaryPart;
    return basicIstream;
}

Complex operator+(const Complex &a, const Complex &b) {
    Complex c;
    c.realPart = a.realPart + b.realPart;
    c.imaginaryPart = a.imaginaryPart + b.imaginaryPart;
    return c;
}

Complex operator-(const Complex &a, const Complex &b) {
    Complex c;
    c.realPart = a.realPart - b.realPart;
    c.imaginaryPart = a.imaginaryPart - b.imaginaryPart;
    return c;
}

Complex operator*(const Complex &a, const Complex &b) {
    Complex c;
    c.realPart = (a.realPart * b.realPart) - (a.imaginaryPart * b.imaginaryPart);
    c.imaginaryPart = (a.realPart * b.imaginaryPart) + (a.imaginaryPart * b.realPart);
    return c;
}

bool operator==(const Complex &a, const Complex &b) {
    return a.realPart == b.realPart && a.imaginaryPart == b.imaginaryPart;
}

bool operator>(const Complex &a, int value) {
    return a.realPart > value;
}

bool operator<(const Complex &a, int value) {
    return a.realPart < value;
}

Complex& Complex::operator=(int value) {
    this->realPart = this->imaginaryPart = 0;
    return *this;
}

string to_string(const Complex &a) {
    string output = "(" + to_string(a.realPart) + ((a.imaginaryPart) >= 0 ? "+" : "") + to_string(a.imaginaryPart) + "i" + ")";
    return output;
}
