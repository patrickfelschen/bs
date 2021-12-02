/**
 * main.cpp
 *
 * Erstellt eine Instanz der MiniShell und fuehrt diese aus.
 *
 * Autor(en): Patrick Felschen, Julian Voss
 */

#include "MiniShell.h"

int main(int argc, char *argv[]){
    MiniShell miniShell;
    miniShell.loop();
    return 0;
}

