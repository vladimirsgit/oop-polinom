#include "UserInterface.h"

UserInterface::UserInterface(): firstChoices("1: Creeaza un polinom sau mai multe.\n2: Creeaza un numar complex sau mai multe.\n3: Paraseste programul.\n"),
                                polinomTypeChoices("Alege tipul coeficientilor:\n1: Integer\n2: Float\n3:Complex\n4:Meniul anterior.\n5:Paraseste programul.\n"){

}

void UserInterface::start() {
    cout << "Salut!\nAcesta este un program unde vei crea polinoame de diferite tipuri, sau numere complexe.\n\n" <<
            "Te rog sa alegi o optiune:\n\n";
    while(true){
        cout << this->firstChoices;
        int chosenOption;
        do {
            cout << "Optiunea aleasa trebuie sa fie 1, 2 sau 3.\n";
            chosenOption = getOption();
        } while (chosenOption < 1 || chosenOption > 3);
        goToSecondMenu(chosenOption);
    }

}

int UserInterface::getOption() {
    string optionInput;
    cin >> optionInput; //userul introduce optiunea
    try{
        return stoi(optionInput);
    } catch(const invalid_argument& invalidArgument){ //numarul contine litere
        cout << "Incearca sa introduci un numar valid.\n";
        return -1;
    } catch(const out_of_range& outOfRange){ //numarul este prea mare
        cout << "Incearca sa introduci un numar valid.\n";
        return -1;
    }
}

void UserInterface::goToSecondMenu(int selectedOption) {

    switch(selectedOption){
        case 1:
            polinomMenu();
            break;
        case 2:
            complexMenu();
            break;
        default:
        {
           simulateExiting();
            exit(0);
        }
    }
}

void UserInterface::polinomMenu() {

    while(true){
        cout << this->polinomTypeChoices;
        int chosenOption;
        do {
            cout << "Optiunea aleasa trebuie sa fie 1, 2, 3, 4 sau 5.\n";
            chosenOption = getOption();
        } while (chosenOption < 1 || chosenOption > 5);
        if(chosenOption == 4)
            return;
        goToPolinomSubmenu(chosenOption);

    }
}

void UserInterface::goToPolinomSubmenu(int selectedOption) {
    switch(selectedOption){
        case 1:
        case 2:
        case 3:
            checkTypeOfPolinom(selectedOption);
            break;
        default:
        {
            simulateExiting();
            exit(0);
        }
    }
}

void UserInterface::checkTypeOfPolinom(int selectedOption) {
    switch (selectedOption) {
        case 1:
            createPolynom<int>();
            break;
        case 2:
            createPolynom<float>();
            break;
        case 3:
            createPolynom<Complex>();
            break;
    }
}
template <class T>
void UserInterface::createPolynom() {
    cout << "Cate polinoame vrei sa creezi?";
    int numberOfPolinoms;
    cin >> numberOfPolinoms;
    vector<Polinom<T>> polinoms;
    for(int i = 0; i < numberOfPolinoms; i++){
        Polinom<T> a;
        cin >> a;
        polinoms.emplace_back(a);
    }

}

//TODO: CREATE POLINOM OPERATIONS FUNCTIONS


void UserInterface::complexMenu() {

}


void UserInterface::simulateExiting() {
    cout << "Sper ca te-ai simtit bine!\n";
    cout << "Exiting";
    for(int i = 0; i < 3; i++){
        this_thread::sleep_for(chrono::milliseconds(400));
        cout << ".";
    }
}
