#include "Complex.h"


//constructor, creeaza un nr complex si initializeaza partea reala si imaginara cu 0
Complex::Complex() {
    this->realPart = 0;
    this->imaginaryPart = 0;
}

//constrcutor unde primeste ca argument valoarea partii reale si valoarea partii imaginare
Complex::Complex(int r, int i) {
    this->realPart = r;
    this->imaginaryPart = i;
}
//supraincarcarea operatorului de afisare, care are diferite reguli de afisare corecta

ostream &operator<<(ostream &basicOstream, const Complex &x) {
    if(x.realPart != 0 || x.imaginaryPart == 0) basicOstream << x.realPart;
    if(x.imaginaryPart > 0 && x.realPart != 0) basicOstream << "+";
    if(x.imaginaryPart != 0) basicOstream << x.imaginaryPart << "i";
    return basicOstream;
}

//supraincarcarea operatorului de input, in care validam ca acestea sa fie de tip intreg
istream & operator>>(istream &basicIstream, Complex &x){
    string realPart, imaginaryPart;
    do{
        cout << "Partea reala: ";
        realPart = x.validateInteger();
        cout << "Partea imaginara: ";
        imaginaryPart = x.validateInteger();
    }while(realPart == "error" || imaginaryPart == "error");

    x.realPart = stoi(realPart);
    x.imaginaryPart = stoi(imaginaryPart);
    return basicIstream;
}

//supraincarcarea operatorului de adunare, unde facem adunare normala intre doua numere complexe primite ca argument
Complex operator+(const Complex &a, const Complex &b) {
    Complex c;
    c.realPart = a.realPart + b.realPart;
    c.imaginaryPart = a.imaginaryPart + b.imaginaryPart;
    return c;
}

//idem pentru operatorul de scadere -
Complex operator-(const Complex &a, const Complex &b) {
    Complex c;
    c.realPart = a.realPart - b.realPart;
    c.imaginaryPart = a.imaginaryPart - b.imaginaryPart;
    return c;
}


//supraincarcarea operatorului pentru inmultire *, folosim formula pentru inmultirea a doua numere complexe
Complex operator*(const Complex &a, const Complex &b) {
    Complex c;
    c.realPart = (a.realPart * b.realPart) - (a.imaginaryPart * b.imaginaryPart);
    c.imaginaryPart = (a.realPart * b.imaginaryPart) + (a.imaginaryPart * b.realPart);
    return c;
}


//verificam daca doua nr complexe sunt egale, supraincarcarea operatorului ==
bool operator==(const Complex &a, const Complex &b) {
    return a.realPart == b.realPart && a.imaginaryPart == b.imaginaryPart;
}


//verificam daca un nr complex are semnul - sau +, pt a stii ce semne va trebui sa afisam
bool operator>(const Complex &a, int value) {
    return a.realPart > value;
}

bool operator<(const Complex &a, int value) {
    return a.realPart < value;
}

//metoda pt a ne asigura ca inputul userului este de tip integer
string Complex::validateInteger(){
    string input;
    cin >> input;
    int inputToInteger;
    try{
        inputToInteger = stoi(input);
        return input;
    } catch(const invalid_argument& invalidArgument){ //numarul contine litere
        cout << "Incearca sa introduci un numar valid.\n";
        return "error";
    } catch(const out_of_range& outOfRange){ //numarul este prea mare
        cout << "Incearca sa introduci un numar valid.\n";
        return "error";
    }
}



//supraincarcarea operatorului de atribuire, care primeste valoarea si seteaza partea reala si partea imaginara sa fie acea valoare
Complex& Complex::operator=(int value) {
    this->realPart = this->imaginaryPart = value;
    return *this;
}

string to_string(const Complex &a) {
    string output = "(" + to_string(a.realPart) + ((a.imaginaryPart) >= 0 ? "+" : "") + to_string(a.imaginaryPart) + "i" + ")";
    return output;

}
