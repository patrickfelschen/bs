//
// Created by Patrick Felschen on 09.12.21.
//

#include <iostream>
#include "Bot.h"

using namespace std;

int main(int argc, char **argv) {

    //// Argumente prüfen
    if (argv[1] == nullptr) {
        cerr << "Bitte Steuerdatei angeben." << endl;
        return -1;
    }

    if (argv[2] == nullptr) {
        cerr << "Bitte Queuegröße angeben." << endl;
        return -1;
    }

    if (argv[3] == nullptr) {
        cerr << "Bitte Threadanzahl angeben." << endl;
        return -1;
    }

    //// Argumente zwischenspeichern
    char* fileName = argv[1];
    int queueSize = stoi(argv[2]);
    int threadCount = stoi(argv[3]);

    //// Bot erzeugen
    #ifdef __linux__
        webreq_init(argc, argv);
    #endif

    Bot bot = Bot();
    bot.start(fileName, queueSize, threadCount);

    return 0;
}