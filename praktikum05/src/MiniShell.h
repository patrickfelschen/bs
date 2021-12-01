//
// Created by Patrick Felschen on 30.11.21.
//

#ifndef BETRIEBSSYSTEME_MINISHELL_H
#define BETRIEBSSYSTEME_MINISHELL_H

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

class MiniShell {
public:
    MiniShell();
    virtual ~MiniShell();
    void loop();
    char* readLine();
    char** splitCommand(char* line);
    void replaceEnv(char** commands);
    void execute(char** commands);
    void launch(char** commands);
    void launchPipe();
};


#endif //BETRIEBSSYSTEME_MINISHELL_H
