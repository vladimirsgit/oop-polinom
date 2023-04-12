#ifndef POLINOMOOP_USERINTERFACE_H
#define POLINOMOOP_USERINTERFACE_H
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Complex.h"
#include "Polinom.h"
class UserInterface {
private:
    const string firstChoices;

public:
    UserInterface();
    void start();
private:
    int getFirstOption();
    void goToSecondMenu(int selectedOption);
    void goToComplexMenu();
    void goToPolinomMenu();
    static void simulateExiting();

};


#endif //POLINOMOOP_USERINTERFACE_H
