//
// Created by pfelsche@id.hsos.de on 17.12.21.
//
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    cout << argv[1] << endl;
    while (true) {
        switch(getopt(argc,argv, "aglo")) {
            case 'a':
                cout << "Parameter -a" << endl;
                continue;
            case 'g':
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