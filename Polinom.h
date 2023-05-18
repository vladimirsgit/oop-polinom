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
    Polinom(Polinom const& p);
    ~Polinom();
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
    bool checkTypeInt() const;
    string validateInteger(bool degree);

};

template<class T>
Polinom<T>::Polinom(const Polinom &p) {
    grad = p.grad;
    polinomValues = new T[grad + 1];
    for(int i = grad; i >= 0; i--){
        this->polinomValues[i] = p.polinomValues[i];
    }

}

template<class T>
Polinom<T>::~Polinom() {
    if(this->polinomValues != nullptr){
        delete[] this->polinomValues;
        this->polinomValues = nullptr;

    }
}

template<class T>
bool Polinom<T>::checkIfComplex() const {
    return is_same<T, Complex>::value;
}

template<class T>
bool Polinom<T>::checkTypeInt() const {
    return is_same<T, int>::value;
}

template<class T>
Polinom<T>::Polinom(int g, T value ...) {
    this->polinomValues = new T[g+1];
    T aux;
    for (int i = 0; i <= g; i++)
        polinomValues[i] = aux;

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
    this->polinomValues = new T[1];
    grad = 0;
    this->polinomValues[0] = value;
}

template<class T>
Polinom<T>::Polinom() {
    grad = 0;
    this->polinomValues = new T[1];
    polinomValues[0] = 0;
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
    string grad;
    do{
        cout << "Introdu gradul polinomului prima data, apoi coeficientii:\nGrad: ";
        grad = x.validateInteger(true);
    }while(grad == "error");
    x.grad = stoi(grad);
    x.polinomValues = new T[x.grad+1];
    for(int i = x.grad; i >= 0; i--){
        T coefficient;
        string coefficientString;
        cout << "x^" << i << ": ";
        if(x.checkTypeInt()) {
            do {
                coefficientString = x.validateInteger(false);
            } while (coefficientString == "error");
            int coefficientInt = stoi(coefficientString);
            x.polinomValues[i] = coefficientInt;
        }
    }
    return basicIstream;
}
template<class T>
Polinom<T> operator+(const Polinom<T> &a, const Polinom<T> &b) {
    int gradMax = max(a.grad, b.grad);
    T arg;
    Polinom<T> c(gradMax, arg);
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
    T arg;
    Polinom<T> c(gradMax, arg);

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
    T arg;
    Polinom<T> c(gradMax+gradMin, arg);

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
template<class T>
string Polinom<T>::validateInteger(bool degree) {
    string input;
    cin >> input;
    int inputToInteger;
    try{
        inputToInteger = stoi(input);
        if((inputToInteger > 100 || inputToInteger < 0) && degree) {
            cout << "Gradul nu poate fi mai mare decat 100 sau negativ.\n";
            return "error";
        }
        return input;
    } catch(const invalid_argument& invalidArgument){ //numarul contine litere
        cout << "Incearca sa introduci un numar valid.\n";
        return "error";
    } catch(const out_of_range& outOfRange){ //numarul este prea mare
        cout << "Incearca sa introduci un numar valid.\n";
        return "error";
    }
}

#endif //POLINOMOOP_POLINOM_H
