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

        char* line = readLine();
        char** commands = splitCommand(line);
        replaceEnv(commands);
        execute(commands);
    }
}

char* MiniShell::readLine() {
    int bufsize = 1024;

    char* inputLine = new char[bufsize];

    cin.getline(inputLine, bufsize);

    return inputLine;
}

char **MiniShell::splitCommand(char* line) {
    char sep[] = " ";
    int bufsize = 64;
    int position = 0;
    char **tokens = new char *[bufsize];
    char *token;

    token = strtok(line, sep);

    while (token != nullptr) {
        tokens[position] = token;

        position++;

        token = strtok(nullptr, sep);
    }

    tokens[position] = nullptr;

    return tokens;
}

void MiniShell::replaceEnv(char** commands) {
    int position = 0;
    while (commands[position] != nullptr) {

        if (commands[position][0] == '$') {
            char *env = getenv(commands[position] + 1);
            if (env != nullptr) {
                commands[position] = env;
            } else {
                cout << "Nicht gefunden!" << endl;
            }
        }

        position++;
    }
}

void MiniShell::execute(char** commands) {
    if (commands[0] == nullptr) {

        return;

    } else if (strcmp(commands[0], "exit") == 0) {

        exit(0);

    } else if (strcmp(commands[0], "cd") == 0) {

        chdir(commands[1]);

    } else if (strcmp(commands[0], "showenv") == 0) {
        char *env = getenv(commands[1]);

        if (env != nullptr) {
            cout << env << endl;
        } else {
            cout << "Nicht gefunden!" << endl;
        }

    } else if (strcmp(commands[0], "export") == 0) {

        int err = putenv(commands[1]);

        if (err != 0) {
            cout << "Fehler beim setzen!" << endl;
        }

    } else {

        launch(commands);

    }
}

void MiniShell::launch(char** commands) {
    pid_t pid = fork();
    int status;
    int childStatus;
    if (pid == 0) {
        // Child process
        childStatus = execvp(commands[0], commands);
        if (childStatus < 0) {
            cout << "Fehlerhafte Eingabe!" << endl;
        }
        exit(0);
    } else if (pid < 0) {
        // Error forking
        cout << "Etwas ist schiefgelaufen!" << endl;
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void MiniShell::launchPipe() {

}
