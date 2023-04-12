#include "Complex.h"

Complex::Complex() {
    this->r = 0;
    this->i = 0;
}

Complex::Complex(int r, int i) {
    this->r = r;
    this->i = i;
}


ostream &operator<<(ostream &basicOstream, const Complex &x) {
    if(x.r != 0 || x.i == 0) basicOstream << x.r;
    if(x.i > 0 && x.r != 0) basicOstream << "+";
    if(x.i != 0) basicOstream << x.i << "i";
    return basicOstream;
}

istream & operator>>(istream &basicIstream, Complex &x){
    cout << "Introdu partea reala, apoi partea imaginara: ";
    basicIstream >> x.r >> x.i;
    return basicIstream;
}

Complex operator+(const Complex &a, const Complex &b) {
    Complex c;
    c.r = a.r + b.r;
    c.i = a.i + b.i;
    return c;
}

Complex operator-(const Complex &a, const Complex &b) {
    Complex c;
    c.r = a.r - b.r;
    c.i = a.i - b.i;
    return c;
}

Complex operator*(const Complex &a, const Complex &b) {
    Complex c;
    c.r = (a.r * b.r) - (a.i * b.i);
    c.i = (a.r * b.i) + (a.i * b.r);
    return c;
}

bool operator==(const Complex &a, const Complex &b) {
    return a.r == b.r && a.i == b.i;
}

bool operator>(const Complex &a, int value) {
    return a.r > value;
}

bool operator<(const Complex &a, int value) {
    return a.r < value;
}

Complex& Complex::operator=(int value) {
    this->r = this->i = 0;
    return *this;
}

string to_string(const Complex &a) {
    string output = "(" + to_string(a.r) + ((a.i) >= 0 ? "+" : "") + to_string(a.i) + "i" +")";
    return output;
}
