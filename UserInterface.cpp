#include "UserInterface.h"

UserInterface::UserInterface(): firstChoices("1: Creeaza un polinom sau mai multe.\n2: Creeaza un numar complex sau mai multe.\n3: Paraseste programul.\n"){
}

void UserInterface::start() {
    cout << "Salut!\nAcesta este un program unde vei crea polinoame de diferite tipuri, sau numere complexe.\n\n" <<
            "Te rog sa alegi o optiune:\n\n";
    while(true){
        cout << firstChoices;
        int chosenOption;
        do {
            cout << "Optiunea aleasa trebuie sa fie 1, 2 sau 3.\n";
            chosenOption = getFirstOption();
        } while (chosenOption < 1 || chosenOption > 3);
        goToSecondMenu(chosenOption);
    }

}

int UserInterface::getFirstOption() {
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
            goToPolinomMenu();
            break;
        case 2:
            goToComplexMenu();
            break;
        default:
        {
           simulateExiting();
            exit(0);
        }
    }
}

void UserInterface::goToPolinomMenu() {

}

void UserInterface::goToComplexMenu() {

}

void UserInterface::simulateExiting() {
    cout << "Sper ca te-ai simtit bine!\n";
    cout << "Exiting";
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << ".";
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << ".";
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << ".";

}