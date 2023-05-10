#ifndef POLINOMOOP_POLINOM_H
#define POLINOMOOP_POLINOM_H
#include <string>
#include <cstdarg>
#include <type_traits>
#include "Complex.h"
using namespace std;
template <class T>
class Polinom {
    T* polinomValues;
    int grad;
public:
    Polinom(int g, T value...);
    Polinom();
    explicit Polinom(T value);
    int getGrad() const;
    template <class A>
    friend ostream & operator<<(ostream &basicOstream, const Polinom<A> &x);
    template <class B>
    friend istream & operator>>(istream &basicIstream, Polinom<B> &x);
    template <class C>
    friend Polinom<C> operator+(const Polinom<C> &a, const Polinom<C> &b);
    template <class D>
    friend Polinom<D> operator-(const Polinom<D> &a, const Polinom<D> &b);
    template <class E>
    friend Polinom<E> operator*(const Polinom<E> &a, const Polinom<E> &b);
    template <class F>
    friend bool operator==(const Polinom<F> &a, const Polinom<F> &b);
    explicit operator T();

private:
    bool checkIfComplex() const;


};

template<class T>
bool Polinom<T>::checkIfComplex() const {
    return is_same<T, Complex>::value;
}


template<class T>
Polinom<T>::Polinom(int g, T value ...) {
    this->polinomValues = new T[g+1];
    va_list arg;    /// creez lista cu argumente
    grad = g;
    va_start(arg, g); /// punem in lista g+1 argumente
    polinomValues[g] = value;
    for(int i=g-1; i>=0; i--)
        polinomValues[i]=va_arg(arg, T);
    va_end(arg);   /// elibereaza memoria alocata
}

template<class T>
Polinom<T>::Polinom(T value){
        grad = 0;
        this->polinomValues[0] = value;
}

template<class T>
Polinom<T>::Polinom() {
    grad = 0;
}

template<class T>
int Polinom<T>::getGrad() const{
    return this->grad;
}

template<class T>
ostream & operator<<(ostream &basicOstream, const Polinom<T> &x) {

    for(int i=x.grad; i>=0; i--)
    {   string output = to_string(x.polinomValues[i]) + "x^" + to_string(i) + " ";
        if(i == 0){
            output = output.substr(0, output.size() - 4);
        }
        if(i == x.grad){
            basicOstream << output;
        }
        else {
            if(x.polinomValues[i] < 0)
                basicOstream << output;
            else basicOstream << "+"s << output; //aici a trebuit sa pun s ca sa mearga
        }
    }
    return basicOstream;
}
template<class T>
istream & operator>>(istream &basicIstream, Polinom<T> &x){
    cout << "Introdu gradul polinomului prima data, apoi coeficientii: ";
    basicIstream >> x.grad;
    for(int i = x.grad; i >= 0; i--){
        basicIstream >> x.polinomValues[i];
    }
    return basicIstream;
}
template<class T>
Polinom<T> operator+(const Polinom<T> &a, const Polinom<T> &b) {
    int gradMax = max(a.grad, b.grad);
    Polinom<T> c;
    if(c.checkIfComplex()){
        Complex z(0, 0);
        Polinom<T> aux(gradMax, z);
        c = aux;
    }
    else {
        T arg;
        Polinom<T> aux(gradMax, arg);
        c = aux;
    }
    for(int i = gradMax; i >= 0; i--){
        if(i > a.grad){
            c.polinomValues[i] = b.polinomValues[i];
        }
        else if(i > b.grad){
            c.polinomValues[i] = a.polinomValues[i];
        }
        else{
            c.polinomValues[i] = a.polinomValues[i] + b.polinomValues[i];
        }
    }
    return c;
}
template<class T>
Polinom<T> operator-(const Polinom<T> &a, const Polinom<T> &b) {
    int gradMax = max(a.grad, b.grad);
    Polinom<T> c;
    if(c.checkIfComplex()){
        Complex z(0, 0);
        Polinom<T> aux(gradMax, z);
        c = aux;
    }
    else {
        T arg;
        Polinom<T> aux(gradMax, arg);
        c = aux;
    }

    for(int i = gradMax; i >= 0; i--){
        if(i > a.grad){
            c.polinomValues[i] = b.polinomValues[i];
        }
        else if(i > b.grad){
            c.polinomValues[i] = a.polinomValues[i];
        }
        else{
            c.polinomValues[i] = a.polinomValues[i] - b.polinomValues[i];
        }
    }
    return c;
}

template<class T>
Polinom<T> operator*(const Polinom<T> &a, const Polinom<T> &b) {
    int gradMax = max(a.grad, b.grad);
    int gradMin = min(a.grad, b.grad);
    Polinom<T> c;
    if(c.checkIfComplex()){
        Complex z(0, 0);
        Polinom<T> aux(gradMax + gradMin, z);
        c = aux;
    }
    else {
        T arg;
        Polinom<T> aux(gradMax + gradMin, arg);
        c = aux;
    }
    for(int i = 0; i <= gradMax + gradMin; i++){
        c.polinomValues[i] = 0;
    }
    for(int i = gradMax; i >= 0; i--){
        for(int j = gradMin; j >= 0; j--){
            c.polinomValues[i + j] = c.polinomValues[i + j] + (a.polinomValues[i] * b.polinomValues[j]);
        }
    }
    return c;
}
template<class T>
bool operator==(const Polinom<T> &a, const Polinom<T> &b) {
    if(a.grad != b.grad)
        return false;
    for(int i = a.grad; i >= 0; i--){
        if(a.polinomValues[i] != b.polinomValues[i])
            return false;
    }
    return true;
}
template<class T>
Polinom<T>::operator T() {
    return this->polinomValues[0];
}


#endif //POLINOMOOP_POLINOM_H
