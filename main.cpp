#include <iostream>
#include "Polinom.h"
#include "Complex.h"
#include "Polinom.cpp"
//#include "Complex.cpp"

using namespace std;
int main() {

    Polinom <int> x(3, 1, 2, 3, 4);
    Complex a(3, 5), b(3, 4), c(2, 6);
    Polinom <Complex> z(2, a, b, c);
    cout << z << " ";

    return 0;
}
