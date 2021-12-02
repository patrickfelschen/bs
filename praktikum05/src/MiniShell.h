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
    char** splitArgs(char *line);
    char** splitPipe(char *line);
    void replaceEnv(char** args);
    void execute(char* line);
    void launch(char** args);
    void launchPipe(char** args1, char** args2);
};


#endif //BETRIEBSSYSTEME_MINISHELL_H
