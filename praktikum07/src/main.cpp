//
// Created by pfelsche@id.hsos.de on 17.12.21.
//
#include <unistd.h>
#include <iostream>
#include "ListDir.h"

using namespace std;

int main(int argc, char** argv) {
    cout << argv[1] << endl;

    ListDir listDir(argv[1]);
    listDir.printDir();

    while (true) {
        switch(getopt(argc,argv, "aglo")) {
            case 'a':
                //// Alle Verzeichnisse und Dateien inkl. versteckte
                cout << "Parameter -a" << endl;
                continue;
            case 'g':
                ////
                cout << "Parameter -g" << endl;
                continue;
            case 'l':
                cout << "Parameter -l" << endl;
                continue;
            case 'o':
                cout << "Parameter -o" << endl;
                continue;
            case -1:
                break;
        }
        return 0;
    }
}