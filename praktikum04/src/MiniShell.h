//
// Created by juliavos@id.hsos.de on 19.11.21.
//

#ifndef BETRIEBSSYSTEME_MINISHELL_H
#define BETRIEBSSYSTEME_MINISHELL_H

#include <string>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class MiniShell {
private:
    vector<string> arguments;
public:
    MiniShell();
    ~MiniShell();
    string getUserInput();
    void splitInput(string userInput);
    bool builtInCommand();
    void posixCommand();
    void start();
};


#endif //BETRIEBSSYSTEME_MINISHELL_H
