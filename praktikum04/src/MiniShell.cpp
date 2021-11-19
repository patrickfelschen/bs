/**************************************************************
* MiniShell.cpp
* Funktion:
*
Ausgabe aus.
* Autor: Julian Voss, Patrick Felschen
* Historie:
*
2021/11/12:
*
2021/11/13:
* To Do:
* -
* -
*************************************************************/

#include "MiniShell.h"

using namespace std;

MiniShell::MiniShell() {

}

MiniShell::~MiniShell() {

}

string MiniShell::getUserInput() {
    string input;
    string currentUser = string(getenv("USER"));
    string currentDir = get_current_dir_name();

    cout << currentUser << "@" << currentDir << "$ ";
    cin >> input;

    return input;
}
