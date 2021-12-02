//
// Created by Patrick Felschen on 30.11.21.
//

#include "MiniShell.h"

using namespace std;

MiniShell::MiniShell() {}

MiniShell::~MiniShell() {}

/***
 *
 */
void MiniShell::loop() {
    while (true) {
        char *user = getenv("USER");
        char dir[256];
        getcwd(dir, 256);

        cout << user << "@" << dir << "$ ";

        char *line = readLine();
        execute(line);
    }
}

/***
 * Benutzereingaben werden eingelesen (maximal 1024 Zeichen).
 * @return Eingegebene Zeile des Benutzers als Zeichenkette.
 */
char *MiniShell::readLine() {
    int bufsize = 1024;
    char *line = new char[bufsize];
    cin.getline(line, bufsize);

    return line;
}
/***
 * Teilt eine Zeile in einzelne Argumente auf und gibt diese zurueck.
 * Jeweils bei einem Leerzeichen wird die Zeile unterteilt.
 * (maximal 64 Argumente)
 * @param line Eingabezeile, bspw. vom Benutzer
 * @return Unterteilte Zeile (Argumente) als Array von Zeichenketten.
 */
char **MiniShell::splitArgs(char *line) {
    char sep[] = " ";
    int bufsize = 64;
    int position = 0;
    char **args = new char *[bufsize];
    char *token;

    token = strtok(line, sep);

    while (token != nullptr) {
        args[position] = token;
        position++;
        token = strtok(nullptr, sep);
    }

    args[position] = nullptr;

    replaceEnv(args);

    return args;
}

/***
 * Teilt eine Zeile in einzelne (zwei) Pipes auf und gibt diese zurueck.
 * @param line Eingegebene Zeile des Benutzers als Zeichenkette.
 * @return Unterteilte Zeile (Pipes) als Array von Zeichenketten.
 */
char **MiniShell::splitPipe(char *line) {
    char sep[] = "|";
    int bufsize = 64;
    int position = 0;
    char **pipes = new char *[bufsize];
    char *token;

    token = strtok(line, sep);

    while (token != nullptr) {
        pipes[position] = token;
        position++;
        token = strtok(nullptr, sep);
    }

    pipes[position] = nullptr;

    return pipes;
}

/***
 *
 * @param args
 */
void MiniShell::replaceEnv(char **args) {
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
/***
 *
 * @param line
 */
void MiniShell::execute(char *line) {
    if (strstr(line, "|") != nullptr) {

        char **pipes = splitPipe(line);
        char **args1 = splitArgs(pipes[0]);
        char **args2 = splitArgs(pipes[1]);

        launchPipe(args1, args2);

    } else {
        char **args = splitArgs(line);

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
            launch(args);
        }

    }
}

/***
 *
 * @param args
 */
void MiniShell::launch(char **args) {
    // Forking a child
    pid_t pid = fork();

    if (pid == -1) {
        printf("Fork fehlgeschlagen!\n");
        return;
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            printf("Befehl konnte nicht ausgefuert werden!\n");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(nullptr);
        return;
    }
}

/***
 *
 * @param args1
 * @param args2
 */
void MiniShell::launchPipe(char **args1, char **args2) {
    // 0 is read end, 1 is write end
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        printf("Pipe konnte nicht erstellt werden!\n");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        printf("Fork fehlgeschlagen!\n");
        return;
    }

    if (p1 == 0) {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(args1[0], args1) < 0) {
            printf("Befehl 1 konnte nicht ausgefuert werden!\n");
            exit(0);
        }
    } else {
        // Parent executing
        p2 = fork();

        if (p2 < 0) {
            printf("Fork fehlgeschlagen\n");
            return;
        }

        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (execvp(args2[0], args2) < 0) {
                printf("Befehl 2 konnte nicht ausgefuert werden\n");
                exit(0);
            }
        } else {
            // parent executing, waiting for two children
            wait(nullptr);
            return;
        }
    }


}
