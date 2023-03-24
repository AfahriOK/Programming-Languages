#include <iostream>
#include "InvestData.h"
#include <stdexcept>
using namespace std;

//Clears the screen
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    auto userData = new InvestData;
    bool keepGoing = true; // Bool to keep program going
    char key = 'a'; //Sentinel key to close program and continue
    *userData = InvestData(); //Instance of InvestData

    while (keepGoing) {
        clearScreen();
        userData->printScreen();

        //Try to get the data and if incorrect start over
        try {
            userData->gatherData();
        }
        catch (runtime_error& excpt) {
            cin.clear();
            cin.ignore();
            cout << excpt.what() << endl;
            userData->resetData();
            cout << "Press any key to start over..." << endl;
            cin >> key;
            continue;
        }
        clearScreen();
        userData->printScreen();

        cout << "Press any key to continue..." << endl;
        cin >> key;

        userData->printData();

        cout << "Press any key to continue ('q' or 'Q' to quit)..." << endl;
        cin >> key;
        if (key == 'q' || key == 'Q') {
            keepGoing = false;
        }

        userData->resetData();
    }

    return 0;
}