//
// Created by pfelsche@id.hsos.de on 17.12.21.
//
#include <unistd.h>
#include <iostream>
#include "ListDir.h"

using namespace std;

int main(int argc, char **argv) {
    ListDir listDir;
    int c;
    while ((c = getopt(argc, argv, "aglo")) != -1) {
        switch (c) {
            case 'a':
                listDir.setShowAll(true);
                break;
            case 'g':
                listDir.setShowLongFormat(true);
                listDir.setShowGroup(true);
                listDir.setShowOwner(false);
                break;
            case 'l':
                listDir.setShowLongFormat(true);
                listDir.setShowGroup(true);
                listDir.setShowOwner(true);
                break;
            case 'o':
                listDir.setShowLongFormat(true);
                listDir.setShowGroup(false);
                break;
            default:
                cout << "-a\tEintraege, die mit . beginnen nicht verstecken" << endl;
                cout << "-g\twie -l aber Eigentuemer nicht auflisten" << endl;
                cout << "-l\tlanges Listenformat verwenden" << endl;
                cout << "-o\twie -l aber ohne Gruppen-Informationen" << endl;
                break;
        }
    }
    char *directory;
    if (optind < argc) {
        directory = argv[optind];
    } else {
        directory = ".";
    }
    listDir.setDir(directory);
    listDir.printResult();
    return 0;
}