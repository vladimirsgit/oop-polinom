//
// Created by Vladimir on 11/04/2023.
//

#include <cstdarg>
#include "Polinom.h"

template<class T>
Polinom<T>::Polinom(int g, ...) {
    va_list arg;    /// creez lista cu argumente
    grad = g;
    va_start(arg, g+1); /// punem in lista g+1 argumente
    for(int i=g; i>=0; i--)
        c[i]=va_arg(arg, T);
    va_end(arg);   /// elibereaza memoria alocata
}

template<class T>
Polinom<T>::Polinom() {
    grad = 0;
    for(int i = 0; i < 100; i++){
        c[i] = 0;
    }
}

template<class T>
int Polinom<T>::getGrad() const{
    return this->grad;
}

template<class T>
ostream & operator<<(ostream &o, const Polinom<T> &x) {
    for(int i=x.grad; i>=0; i--)
    {   string output = to_string(x.c[i]) + "x^" + to_string(i) + " ";
        if(i == 0){
            output = output.substr(0, output.size() - 4);
        }
        if(i == x.grad)
        {
            o <<  output;
        }
        else {
            if(x.c[i] < 0)
                o << output;
            else o << "+"s << output; //aici a trebuit sa pun s ca sa mearga
        }
    }
    return o;
}
template<class T>
Polinom<T> operator+(const Polinom<T> &a, const Polinom<T> &b) {

    int gradMax = max(a.grad, b.grad);
    Polinom<T> c(gradMax);

    for(int i = gradMax; i >= 0; i--){
        c.c[i] = a.c[i] + b.c[i];
    }

    return c;
}
template<class T>
Polinom<T> operator-(const Polinom<T> &a, const Polinom<T> &b) {

    int gradMax = max(a.grad, b.grad);
    Polinom<T> c(gradMax);

    for(int i = gradMax; i >= 0; i--){
        c.c[i] = a.c[i] - b.c[i];
    }
    return c;
}

template<class T>
Polinom<T> operator*(const Polinom<T> &a, const Polinom<T> &b) {
    int gradMax = max(a.grad, b.grad);
    int gradMin = min(a.grad, b.grad);
    Polinom<T> c(gradMax+gradMin);
    for(int i = 0; i <= gradMax + gradMin; i++){
        c.c[i] = 0;
    }
    for(int i = gradMax; i >= 0; i--){
        for(int j = gradMin; j >= 0; j--){
            c.c[i+j] = c.c[i+j] + (a.c[i] * b.c[j]);
        }
    }
    return c;
}
template<class T>
bool operator==(const Polinom<T> &a, const Polinom<T> &b) {
    if(a.grad != b.grad)
        return false;
    for(int i = a.grad; i >= 0; i--){
        if(a.c[i] != b.c[i])
            return false;
    }
    return true;
}

