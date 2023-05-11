#ifndef POLINOMOOP_USERINTERFACE_H
#define POLINOMOOP_USERINTERFACE_H
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Complex.h"
#include "Polinom.h"

class UserInterface {
private:
    const string firstChoices;
    const string polinomTypeChoices;


public:
    UserInterface();
    void start();
private:
    int getOption();
    void goToSecondMenu(int selectedOption);
    void complexMenu();
    void polinomMenu();
    void goToPolinomSubmenu(int selectedOption);
    void checkTypeOfPolinom(int selectedOption);
    template <class A>
    void createPolynom();
    static void simulateExiting();

};



#endif //POLINOMOOP_USERINTERFACE_H
