#ifndef POLINOMOOP_POLINOM_H
#define POLINOMOOP_POLINOM_H
#include <string>
#include <type_traits>
#include "Complex.h"
using namespace std;
template <class T>
class Polinom {
    T* polinomValues;
    int grad;
public:
    Polinom(int g, initializer_list<T> values);
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
    bool checkTypeComplex() const;
    bool checkTypeInt() const;
    bool checkTypeFloat() const;
    string validateInteger(bool degree);
    string validateFloat();

};

template<class T>
Polinom<T>::Polinom(const Polinom &p) { //constructor de copiere, pentru a crea un nou obiect, nu doar sa salveze adresa
    grad = p.grad;
    polinomValues = new T[grad + 1];
    for(int i = grad; i >= 0; i--){
        this->polinomValues[i] = p.polinomValues[i];
    }

}

template<class T>
Polinom<T>::~Polinom() { //destructor
    if(this->polinomValues != nullptr){ //verificam sa nu fie null pointerul catre vectorul coeficientilor
        delete[] this->polinomValues;
        this->polinomValues = nullptr;

    }
}

//functii pentru a verifica tipul coeficientilor
template<class T>
bool Polinom<T>::checkTypeComplex() const {
    return is_same<T, Complex>::value;
}

template<class T>
bool Polinom<T>::checkTypeInt() const {
    return is_same<T, int>::value;
}

template<class T>
bool Polinom<T>::checkTypeFloat() const {
    return is_same<T, float>::value;
}

template<class T>
Polinom<T>::Polinom(int g, initializer_list<T> values) { //constructor, folosim lista de initializare pt argumente
    this->polinomValues = new T[g+1];
    grad = g;
    int i = g;

    for(auto value : values) {
        polinomValues[i] = value;
        i--;
    }
}

template<class T>
Polinom<T>::Polinom(T value){
    this->polinomValues = new T[1];
    grad = 0;
    this->polinomValues[0] = value;
}

template<class T>
Polinom<T>::Polinom() { //constructor default
    grad = 0;
    this->polinomValues = new T[1];
    polinomValues[0] = 0;
}

template<class T>
int Polinom<T>::getGrad() const{
    return this->grad;
}

template<class T>
ostream & operator<<(ostream &basicOstream, const Polinom<T> &x) { //operatorul de afisare

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
istream & operator>>(istream &basicIstream, Polinom<T> &x){ //operatorul de input
    string grad;
    do{
        cout << "Introdu gradul polinomului prima data, apoi coeficientii:\nGrad: ";
        grad = x.validateInteger(true); //aici dau degree sa vada daca verificam gradul sau nu
    }while(grad == "error");

    x.grad = stoi(grad);
    x.polinomValues = new T[x.grad+1];

    for(int i = x.grad; i >= 0; i--){
        string coefficientString;
        cout << "x^" << i << ": ";

        if(x.checkTypeInt()) {
            do {
                coefficientString = x.validateInteger(false); //aici ii zicem ca nu verificam grad, deci verificam un coeficient
            } while (coefficientString == "error");
            int coefficientInt = stoi(coefficientString);
            x.polinomValues[i] = coefficientInt;
        }
        else if(x.checkTypeFloat()) {
            do {
                coefficientString = x.validateFloat();
            }while(coefficientString == "error");
            float coefficientFloat = stof(coefficientString);
            x.polinomValues[i] = coefficientFloat;
        }
        else if(x.checkTypeComplex()){
            T coefficientComplex;
            basicIstream >> coefficientComplex;
            x.polinomValues[i] = coefficientComplex;
        }
    }
    return basicIstream;
}
template<class T>
Polinom<T> operator+(const Polinom<T> &a, const Polinom<T> &b) {
    int gradMax = max(a.grad, b.grad);
    T arg;
    Polinom<T> c(gradMax, {arg});
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
    Polinom<T> c(gradMax, {arg});

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
    Polinom<T> c(gradMax+gradMin, {arg});

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
Polinom<T>::operator T() { //type conversion
    return this->polinomValues[0];
}
template<class T>
string Polinom<T>::validateInteger(bool degree) { //validam inputurile de tip integer
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

template <class T>
string Polinom<T>::validateFloat() { //validam inputurile de tip float
    string input;
    cin >> input;
    float inputToFloat;
    try{
        inputToFloat = stof(input);
        if(inputToFloat > 100 || inputToFloat < 0) {
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
