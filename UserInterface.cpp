#include "UserInterface.h"
//constructor in care cream tipuril de alegeri pe care le are userul
UserInterface::UserInterface(): firstChoices("\n\n1: Creeaza un polinom sau mai multe.\n2: Paraseste programul.\n"),
                                polinomTypeChoices("\n\nAlege tipul coeficientilor:\n1: Integer\n2: Float\n3: Complex\n4: Meniul anterior.\n5: Paraseste programul.\n"),
                                polinomOpChoices("\n\nPoti aduna, scadea sau inmulti polinoame.\n1: Adunare\n2: Scadere\n3: Inmultire.\n4: Meniul anterior\n5: Paraseste programul.\n"){

}

//din aceasta metoda porneste totul, este cea apelata in functia main
void UserInterface::start() {
    cout << "Salut!\nAcesta este un program unde vei crea polinoame de diferite tipuri.\n\n" <<
            "Te rog sa alegi o optiune:\n\n";
    while(true){
        cout << this->firstChoices;
        int chosenOption;
        do {
            cout << "Optiunea aleasa trebuie sa fie 1 sau 2.\n";
            chosenOption = getOption();
        } while (chosenOption < 1 || chosenOption > 2);
        goToSecondMenu(chosenOption);
    }

}


//metoda pe care o reutilizam in fiecare meniu si submeniu, pentru a lua optiunea pe care o doreste userul
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


//functie pt a merge la meniul urmatorul, care fie este meniu Polinom, fie iese din program
void UserInterface::goToSecondMenu(int selectedOption) {

    switch(selectedOption){
        case 1:
            polinomMenu();
            break;
//        case 2:
//            complexMenu();
//            break;
        default:
        {
           simulateExiting();
            exit(0);
        }
    }
}

//meniul polinom in care userul alege ce doreste sa faca
//daca alege sa mearga in meniul anterior, pur si simplu dam return, altfel mergem in submeniu

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

//submeniul primeste ca argument optiunea selectata de user, si transmite mai departe daca este cazul ce tip de polinom doreste userul sa creeze
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

//cream polinom in functie de alegerea userului

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

//aici cream cate polinoame doreste userul si cream un vector care sa le contina pe toate, iar acel vector il transmitem prin referinta catre metoda in care alegem ce operatie doreste userul sa faca
template <class T>
void UserInterface::createPolynom() {
    cout << "Cate polinoame vrei sa creezi? ";
    int numberOfPolinoms;
    cin >> numberOfPolinoms;
    vector<Polinom<T>> vectorPolinom;
    for(int i = 0; i < numberOfPolinoms; i++){
        Polinom<T> a;
        cout << "Polinomul #" << i + 1 << ": ";
        cin >> a;
        vectorPolinom.emplace_back(a);
    }
    chooseOperation(vectorPolinom);
}


//aici alegem operatia pe care doreste userul sa o faca
template <class T>
void UserInterface::chooseOperation(vector<Polinom<T>> &vectorPolinom){
    cout << polinomOpChoices;
    int selectedOp;
    do{
        cout << "Optiunea aleasa trebuie sa fie 1, 2, 3, 4 sau 5.\n";
        selectedOp = getOption();
    } while(selectedOp < 1 || selectedOp > 5);

    switch (selectedOp) {
        case 1:
        case 2:
        case 3:
            choosePolinom(vectorPolinom, selectedOp);
            break;
        case 4:
            return;
        case 5:
            simulateExiting(), exit(0);

    }
}


//metoda prin care alegem cele 2 polinoame pe care doreste userul sa le aduna, scada, sau inmulteasca
template <class T>
void UserInterface::choosePolinom(const vector<Polinom<T>> &vectorPolinom, int operation){
    for(int i = 0; i < vectorPolinom.size(); i++){
        cout << i + 1  << " : " << vectorPolinom[i] << "\n";
    }
    int selectedOption1, selectedOption2;
    do{
        cout << "Alege cele 2 polinoame pe care vrei sa le incluzi in operatia ta: ";

        selectedOption1 = getOption();
        selectedOption2 = getOption();

    }while(selectedOption1 < 1 || selectedOption2 > vectorPolinom.size() || selectedOption2 < 1 || selectedOption2 > vectorPolinom.size());

    cout << "Polinoamele alese sunt:\n";
    cout << "Polinom #" << selectedOption1 << ": " << vectorPolinom[selectedOption1-1] << "\n";
    switch (operation) {
        case 1:
            cout << "+\n";
            break;
        case 2:
            cout << "-\n";
            break;
        default:
            cout << "*\n";
    }
    cout << "Polinom #" << selectedOption2 << ": " << vectorPolinom[selectedOption2-1] << "\n";

    doPolinomOperations(vectorPolinom, operation, selectedOption1, selectedOption2);

}

//aici se fac operatiile propriu zise si se afiseaza rezultatul
template <class T>
void UserInterface::doPolinomOperations(const vector<Polinom<T>> &vectorPolinom, int operation, int selectedOption1, int selectedOption2) {

    switch (operation) {
        case 1:
            cout << "Rezultat: " << vectorPolinom[selectedOption1-1] + vectorPolinom[selectedOption2-1] << "\n";
            break;
        case 2:
            cout << "Rezultat: " << vectorPolinom[selectedOption1-1] - vectorPolinom[selectedOption2-1] << "\n";
            break;
        case 3:
            cout << "Rezultat: " << vectorPolinom[selectedOption1-1] * vectorPolinom[selectedOption2-1] << "\n";
            break;
        default:
            return;
    }

}


//functi pt a simula asteptarea sa iasa din program

void UserInterface::simulateExiting() {
    cout << "Sper ca te-ai simtit bine!\n";
    cout << "Exiting";
    for(int i = 0; i < 3; i++){
        this_thread::sleep_for(chrono::milliseconds(400));
        cout << ".";
    }
}

