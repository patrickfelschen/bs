//
// Created by Patrick Felschen on 30.11.21.
//

#include "MiniShell.h"

using namespace std;

MiniShell::MiniShell() {}

MiniShell::~MiniShell() {}

void MiniShell::loop() {
    while (true) {
        char *user = getenv("USER");
        char dir[256];
        getcwd(dir, 256);

        cout << user << "@" << dir << "$ ";

        readLine();
        splitLine();
        queryEnv();
        execute();

        free(line);
        free(args);
    }
}

void MiniShell::readLine() {
    int bufsize = 1024;
    line = new char[bufsize];

    cin.getline(line, bufsize);
}

void MiniShell::splitLine() {
    char sep[] = " ";
    int bufsize = 64;
    int position = 0;
    args = new char *[bufsize];
    char *token;

    token = strtok(line, sep);

    while (token != nullptr) {
        args[position] = token;

        position++;

        token = strtok(nullptr, sep);
    }

    args[position] = nullptr;
}

void MiniShell::queryEnv() {
    int position = 0;
    while (args[position] != nullptr) {

        if (args[position][0] == '$') {
            char *env = getenv(args[position] + 1);
            if (env != nullptr) {
                args[position] = env;
            } else {
                cout << "Nicht gefunden!" << endl;
            }
        }

        position++;
    }
}

void MiniShell::execute() {
    if (args[0] == nullptr) {

        return;

    } else if (strcmp(args[0], "exit") == 0) {

        exit(0);

    } else if (strcmp(args[0], "cd") == 0) {

        chdir(args[1]);

    } else if (strcmp(args[0], "showenv") == 0) {
        char *env = getenv(args[1]);

        if (env != nullptr) {
            cout << env << endl;
        } else {
            cout << "Nicht gefunden!" << endl;
        }

    } else if (strcmp(args[0], "export") == 0) {

        int err = putenv(args[1]);

        if (err != 0) {
            cout << "Fehler beim setzen!" << endl;
        }

    } else {

        launch();

    }
}

void MiniShell::launch() {
    pid_t pid = fork();
    int status;
    int childStatus;
    if (pid == 0) {
        childStatus = execvp(args[0], args);

        if (childStatus < 0) {
            cout << "Fehlerhafte Eingabe!" << endl;
        }

        exit(0);
    } else if (pid < 0) {
        cout << "Etwas ist schiefgelaufen!" << endl;
    } else {
        waitpid(pid, &status, 0);
    }
}



