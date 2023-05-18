#include <iostream>
#include "Polinom.h"
#include "Complex.h"
#include "UserInterface.h"
using namespace std;
int main() {

//    UserInterface userInterface;
//    userInterface.start();
    Complex complex1(2, 3);
    Complex complex2(2, 3);
    Polinom<Complex> a(2, complex1, complex2);
    cout << a + a;
    return 0;
}
