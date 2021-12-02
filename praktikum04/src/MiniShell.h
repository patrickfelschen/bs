/**
 * MiniShell.h
 *
 * Implementierung einer Art mini Shell, welche Eingaben vom Benutzer
 * einlesen kann, Prozesse ausfuehren kann und Variablen speichern kann.
 *
 * Autor(en): Patrick Felschen, Julian Voss
 */

#ifndef BETRIEBSSYSTEME_MINISHELL_H
#define BETRIEBSSYSTEME_MINISHELL_H

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;
/**
 * Implementierung einer Art mini Shell, welche Eingaben vom Benutzer
 * einlesen kann, Prozesse ausfuehren kann und Variablen speichern kann.
 */
class MiniShell {
public:
    MiniShell();
    virtual ~MiniShell();
    void loop();
    char* readLine();
    char** splitArgs(char *line);
    void replaceEnv(char** args);
    void execute(char* line);
    void launch(char** args);
};


#endif //BETRIEBSSYSTEME_MINISHELL_H
