//
// Created by Vladimir on 11/04/2023.
//

#ifndef POLINOMOOP_POLINOM_H
#define POLINOMOOP_POLINOM_H
#include <string>
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
};


#endif //POLINOMOOP_POLINOM_H
