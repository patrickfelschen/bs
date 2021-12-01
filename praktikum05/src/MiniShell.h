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
private:
    char *line;
    char **args;
    int pipeFlag;
public:
    MiniShell();
    virtual ~MiniShell();
    void loop();
    void readLine();
    void setPipeFlag();
    void splitLine();
    void queryEnv();
    void execute();
    void launch();
};


#endif //BETRIEBSSYSTEME_MINISHELL_H
