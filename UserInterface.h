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
    const string polinomOpChoices;


public:
    UserInterface();
    void start();
private:
    int getOption();
    void goToSecondMenu(int selectedOption);
    void polinomMenu();
    void goToPolinomSubmenu(int selectedOption);
    void checkTypeOfPolinom(int selectedOption);
    template <class A>
    void createPolynom();
    template <class B>
    void chooseOperation(vector <Polinom<B>> &vectorPolinom);
    template <class C>
    void doPolinomOperations(const vector<Polinom<C>> &vectorPolinom, int operation, int selectedOption1, int selectedOption2);
    template <class D>
    void choosePolinom(const vector<Polinom<D>> &vectorPolinom, int operation);
//    void complexMenu();
    static void simulateExiting();

};



#endif //POLINOMOOP_USERINTERFACE_H
