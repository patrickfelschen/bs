//
// Created by pfelsche@id.hsos.de on 17.12.21.
//

#include <unistd.h>

#include <string.h>

int main(int argc, char** argv) {
    int opt = getopt(argc, argv, ":goal");

    if(strcmp(optarg, "g") != 0){

    }
}