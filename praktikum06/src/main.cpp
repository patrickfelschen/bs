//
// Created by Patrick Felschen on 09.12.21.
//


#include <iostream>
#include <fstream>
#include <cstring>

using std::ifstream;

int main (int argc, char **argv) {
    std::string url;
    const char* urls[20];
    if(argv[1] != nullptr) {
        ifstream input_file(argv[1]);

        if(input_file.is_open()) {
            unsigned int i = 0;
            while(std::getline(input_file, url)) {
                urls[i] = strdup(url.c_str());
                printf("%s\n", urls[i]);
                i++;
            }
        }else {
            std::cerr << "Datei " << argv[1] << " konnte nicht geöffnet werden." << std::endl;
        }
        input_file.close();
    }else {
        std::cerr << "Bitte Steuerdatei angeben." << std::endl;
    }


    return 0;
}