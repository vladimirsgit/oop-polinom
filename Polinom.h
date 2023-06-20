#ifndef POLINOMOOP_POLINOM_H
#define POLINOMOOP_POLINOM_H
#include <string>
#include <type_traits>
#include "Complex.h"
using namespace std;
template <class T>
class Polinom {
    T* polinomValues; //Pointer catre inceputul unui array
    int grad; //gradul polinomului
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



/*Aici am creat constructorul de copiere
Copiaza prima data gradul polinomului primit ca parametru, aloca memorie pentru un nou vector de marimea gradului + 1*/
template<class T>
Polinom<T>::Polinom(const Polinom &p) { //constructor de copiere, pentru a crea un nou obiect, nu doar sa salveze adresa
    grad = p.grad;
    polinomValues = new T[grad + 1];
    for(int i = grad; i >= 0; i--){
        this->polinomValues[i] = p.polinomValues[i];
    }

}
//Am creat destructorul, in care verificam daca pointerul catre inceputul polinomValues este null, daca nu este, il sterge
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

/*Constructor care primeste ca argument pe primul loc gradul polinomului, iar apoi coeficientii, de la cel mai mare
la cel mai mic*/
template<class T>
Polinom<T>::Polinom(int g, initializer_list<T> values) {
    this->polinomValues = new T[g+1];
    grad = g;
    int i = g;

    for(auto value : values) {
        polinomValues[i] = value;
        i--;
    }
}

//creeaza un polinom de gradul 0
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


//getter pentru gradul unui polinom
template<class T>
int Polinom<T>::getGrad() const{
    return this->grad;
}

// supraincarcarea operatorului de afisare

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
            else basicOstream << "+"s << output;
        }
    }
    return basicOstream;
}


//supraincarcarea operatorului de input
template<class T>
istream & operator>>(istream &basicIstream, Polinom<T> &x){ //operatorul de input
    string grad;
    //aici cat timp userul nu introduce un tip de date INT pentru grad, nu va fi acceptat inputul
    do{
        cout << "Introdu gradul polinomului prima data, apoi coeficientii:\nGrad: ";
        grad = x.validateInteger(true); //aici dau degree sa vada daca verificam gradul sau nu
    }while(grad == "error");

    //transformam gradul in integer
    x.grad = stoi(grad);
    x.polinomValues = new T[x.grad+1];

    for(int i = x.grad; i >= 0; i--){
        string coefficientString;
        cout << "x^" << i << ": ";
    //pentru fiecare tip de data a coeficientilor polinomului, verificam sa fie corespunzator: integer, float sau Complex
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

/* supraincarcarea operatorului de adunare +
 * Verificam care este gradul maxim dintre cele 2 polinoame, pentru a stii cum sa cream noul polinom
 * Acesta va primi ca argument gradul maxim, si o lista de argumente care ar reprezenta primul coeficient. acesta este utilizat doar pt a initializa noul polinom
 * Pe urma,ii vor fi atribuite elementele necesare
 * */
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
//supraincarcarea operatorului de scadere -, asemanator cu operatorul +
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

//supraincarcarea operatorului de inmultire *, crearea polinomului este asemanatoare ca in cazul primelor 2 operatori.
//inmultim toate valorile din primul polinom cu toate din al doilea polinom
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
//supraincarcarea operatorului ==. daca gradele sunt diferite, atunci clar nu sunt egale, altfel verifica daca vreun coeficient este diferit, returneaza fals, altfel la final returneaza true, inseamna ca polinoamele
//sunt egale
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
//conversia de tip, trasnforma de exemplu un polinom de tip integer intr un integer care este reprezentat de coeficientul x^0.
template<class T>
Polinom<T>::operator T() { //type conversion
    return this->polinomValues[0];
}

//metoda pt a valida inputurile de tip integer
//primeste ca argument degree, pt a stii daca verifica sa fie gradul polinomului sau doar coeficient.
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

//asemenator pentru inputuri de tip float
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
