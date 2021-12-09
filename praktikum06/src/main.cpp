//
// Created by Patrick Felschen on 09.12.21.
//

#include <iostream>
#include <fstream>
#include <cstring>
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
    unsigned int queueSize = stoi(argv[2]);
    unsigned int threadCount = stoi(argv[3]);

    //// Urls aus Datei einlesen
    ifstream inputFile(fileName);

    if(!inputFile.is_open()){
        cerr << "Datei " << fileName << " konnte nicht geöffnet werden." << endl;
        return -1;
    }

    string url;
    char **urls = new char *[20];

    unsigned int position = 0;
    while (getline(inputFile, url)) {
        urls[position] = strdup(url.c_str());
        printf("%s\n", urls[position]);
        position++;
    }

    inputFile.close();

    //// Bot erzeugen
    Bot bot = Bot(urls, queueSize, threadCount);
    bot.start();

    return 0;
}