//
// Created by Patrick Felschen on 09.12.21.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include "Bot.h"

using namespace std;

int main(int argc, char **argv) {

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

    string url;
    char **urls = new char *[20];

    //TODO: unsigned int queueSize = ((unsigned int)argv[2]);

    ifstream inputFile(argv[1]);

    if(!inputFile.is_open()){
        cerr << "Datei " << argv[1] << " konnte nicht geöffnet werden." << endl;
        return -1;
    }

    unsigned int i = 0;

    while (getline(inputFile, url)) {
        urls[i] = strdup(url.c_str());
        printf("%s\n", urls[i]);
        i++;
    }

    //TODO:: Bot bot = Bot(urls, argv[2], argv[3]);
    //TODO:: bot.start();

    inputFile.close();

    return 0;
}