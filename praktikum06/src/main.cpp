//
// Created by Patrick Felschen on 09.12.21.
//


#include <iostream>

int main (int argc, char **argv) {

    for (int i = 0; i < argc; i++) {
        std::cout<< "Argument " << i << ": " << argv[i] << std::endl;
    }

    return 0;
}