/**************************************************************
* MiniShell.cpp
* Funktion:
*
Ausgabe aus.
* Autor: Julian Voss, Patrick Felschen
* Historie:
*
2021/11/12:
*
2021/11/13:
* To Do:
* -
* -
*************************************************************/

#include <sstream>
#include <iterator>
#include <sys/wait.h>
#include "MiniShell.h"

using namespace std;

MiniShell::MiniShell() {

}

MiniShell::~MiniShell() {

}

string MiniShell::getUserInput() {
    string input = "";
    string currentUser = string(getenv("USER"));
    string currentDir = get_current_dir_name();

    /* Funktioniert nicht
    cout << currentUser << "@" << currentDir << "$ ";
    cout.flush();
     */
    printf("%s@%s$",currentUser.c_str(),currentDir.c_str());
    getline(cin, input);
    return input;
}

void MiniShell::splitInput(string userInput) {
    arguments.clear();
    string tmp;
    stringstream ss(userInput);
    while(getline(ss, tmp, ' ')) {
        arguments.push_back(tmp);
    }
}

bool MiniShell::builtInCommand() {
    if(arguments[0] == "exit") {
        exit(0);
    }else if(arguments[0] == "cd") {
        chdir(arguments[1].c_str());
        return true;
    }else if(arguments[0] == "showenv") {
        cout << "showenv" << endl;
        return true;
    }else if(arguments[0] == "export") {
        cout << "export" << endl;
        return true;
    }
    return false;
}

void MiniShell::posixCommand() {
    char* args[arguments.size()];
    for(int i = 0; i <= arguments.size(); i++) {
        args[i] = (char *) arguments[i].c_str();
    }

    for(int i = 0; i <= arguments.size(); i++) {
        cout << "Argument: " << arguments[i] << endl;
    }

    pid_t pid = fork();
    if(pid == -1) {
        cout << "Kindprozess konnte nicht gestartet werden" << endl;
    }else if(pid > 0) {
        wait(nullptr);
    }else {
        execvp(args[0], args);
        exit(EXIT_SUCCESS);
    }
    arguments.clear();
    memset(args, 0, sizeof args);
}

void MiniShell::start() {
    setvbuf(stdout, NULL, _IONBF, 0);
    string i = "";
    while(true) {
        i = getUserInput();
        splitInput(i);
        if(!builtInCommand()) {
            posixCommand();
        }
        arguments.clear();
    }
}


