/**
 * MiniShell.cpp
 *
 * Implementierung einer Art mini Shell, welche Eingaben vom Benutzer
 * einlesen kann, Prozesse ausfuehren kann und Variablen speichern kann.
 *
 * Autor(en): Patrick Felschen, Julian Voss
 */

#include "MiniShell.h"

using namespace std;

MiniShell::MiniShell() {}

MiniShell::~MiniShell() {}

/**
 *  Schleife für die durchgehende Konsolen-Aufgabe.
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

/**
 * Benutzereingaben werden eingelesen (maximal 1024 Zeichen).
 * @return Eingegebene Zeile des Benutzers als Zeichenkette.
 */
char *MiniShell::readLine() {
    int bufsize = 1024;
    char *line = new char[bufsize];
    cin.getline(line, bufsize);

    return line;
}
/**
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

/**
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

/**
 * Ersetzt die Variablen ($...) der uebergebenen Argumente.
 * @param args Argumente mit ggf. Variablen
 */
void MiniShell::replaceEnv(char **args) {
    int position = 0;
    while (args[position] != nullptr) {
        if (args[position][0] == '$') {
            char *env = getenv(args[position] + 1);
            if (env != nullptr) {
                args[position] = env;
            } else {
                cerr << "Variable nicht gefunden! ";
            }
        }
        position++;
    }
}
/**
 * Überprüft die uebergebene Zeichenekette auf das Pipe-Symbol "|".
 * Ist dies vorhanden, wird der Input in zwei Pipes zerlegt und mit diesen launchPipe() aufgerufen.
 * Ist kein Pipe-Symbol vorhanden, wird die Nutzereingabe in einzelne Argumente zerlegt.
 * Die Argumente werden auf Built-In Kommandos geprueft, welche entsprechend ausgefuehrt werden.
 * Beinhaltet die Eingabe kein Built-In Kommando werden die Argumente an die launch() Funktion uebergeben.
 * @param line Eingegebene Zeile des Nutzers als Zeichenkette.
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
                cerr << "Variable nicht gefunden!" << endl;
            }
        } else if (strcmp(args[0], "export") == 0) {
            int err = putenv(args[1]);

            if (err != 0) {
                cerr << "Fehler beim setzen!" << endl;
            }
        } else {
            launch(args);
        }

    }
}

/**
 * Es wird ein Duplikat des Prozesses erstellt (Child)
 * Ist das Erstellen erfolgreich (Rueckgabewert 0), wird mit dem uebergebenen Array ein Befehl ausgefuehrt.
 * In args[0] befindet sich der auszufuehrende Befehl, args[n] (n > 0) beinhaltet die Argumente.
 * @param args Pointer-Array mit Befehl und zugehörigen Argumenten
 */
void MiniShell::launch(char **args) {
    // Neuer Kindprozess per fork() erzeugen
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "Fork fehlgeschlagen!" << endl;
        return;
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            cerr << "Befehl konnte nicht ausgefuehrt werden!" << endl;
        }
        exit(0);
    } else {
        // Elternprozess wartet auf Beendigung des Kindprozesses
        wait(nullptr);
        return;
    }
}

/**
 * Es wird eine Kommunikation zwischen zwei Prozessen ueber pipe() hergestellt.
 * Die produzierte Ausgabe des ersten Kindprozesses wird als Eingabe für Kindprozess zwei verwendet.
 * @param args1 Pointer Array mit Befehl und Argumenten links vom Pipe-Symbol
 * @param args2 Pointer Array mit Befehl und Argumenten rechts vom Pipe-Symbol
 */
void MiniShell::launchPipe(char **args1, char **args2) {
    // Deskriptor 0 = lesen
    // Deskriptor 1 = schreiben
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        cerr << "Pipe konnte nicht erstellt werden!" << endl;
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        cerr << "Fork fehlgeschlagen!" << endl;
        return;
    }

    if (p1 == 0) {
        // Kindprozess 1
        close(pipefd[0]); // Nicht verwendeten Deskriptor schliessen
        dup2(pipefd[1], STDOUT_FILENO); // Ausgabe per dup2() in Deskriptor 1 umleiten
        close(pipefd[1]); // Deskriptor schliessen um Terminierung zu kennzeichnen

        if (execvp(args1[0], args1) < 0) {
            cerr << "Befehl 1 konnte nicht ausgefuehrt werden!" << endl;
            exit(0);
        }
    } else {
        // Elternprozess
        p2 = fork();

        if (p2 < 0) {
            cerr << "Fork fehlgeschlagen" << endl;
            return;
        }

        if (p2 == 0) {
            // Kindprozess 2
            close(pipefd[1]); // Nicht verwendeten Deskriptor schliessen
            dup2(pipefd[0], STDIN_FILENO); // Eingabe per dup2() in Deskriptor 0 umleiten
            close(pipefd[0]); // Deskriptor schliessen um Terminierung zu kennzeichnen
            if (execvp(args2[0], args2) < 0) {
                cerr << "Befehl 2 konnte nicht ausgefuehrt werden" << endl;
                exit(0);
            }
        } else {
            // Warten auf Beendigung der Child-Prozesse
            wait(nullptr);
            return;
        }
    }


}
