//
// Created by juliavos@id.hsos.de on 19.11.21.
//

#ifndef BETRIEBSSYSTEME_MINISHELL_H
#define BETRIEBSSYSTEME_MINISHELL_H

#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

class MiniShell {
public:
    MiniShell();
    ~MiniShell();
    string getUserInput();
};


#endif //BETRIEBSSYSTEME_MINISHELL_H
