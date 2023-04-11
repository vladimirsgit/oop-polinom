//
// Created by Vladimir on 11/04/2023.
//

#ifndef POLINOMOOP_POLINOM_H
#define POLINOMOOP_POLINOM_H
#include <string>
#include <cstdarg>
using namespace std;
template <class T>
class Polinom {
    T c[100];
    int grad;
public:
    Polinom(int g, ...);
    Polinom();
    int getGrad() const;
    template <class A>
    friend ostream & operator<<(ostream &o, const Polinom<A> &x);
    template <class B>
    friend Polinom<B> operator+(const Polinom<B> &a, const Polinom<B> &b);
    template <class C>
    friend Polinom<C> operator-(const Polinom<C> &a, const Polinom<C> &b);
    template <class D>
    friend Polinom<D> operator*(const Polinom<D> &a, const Polinom<D> &b);
    template <class E>
    friend bool operator==(const Polinom<E> &a, const Polinom<E> &b);
    operator T();


};

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
    for(auto & i : c){
        i = 0;
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
    Polinom<T> c(gradMax + gradMin);
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
template<class T>
Polinom<T>::operator T() {
    return this->c[0];
}


#endif //POLINOMOOP_POLINOM_H
