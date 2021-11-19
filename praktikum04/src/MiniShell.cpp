#include <iostream>
#include <unistd.h>

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

using namespace std;

int main() {
    int test;

    while(true) {
        cout << get_current_dir_name() << ":";
        cin >> test;
        cout << to_string(test) << endl;
    }
    return 0;
}

