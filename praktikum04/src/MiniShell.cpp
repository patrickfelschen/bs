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
 * Die Nutzereingabe wird in einzelne Argumente zerlegt.
 * Die Argumente werden auf Built-In Kommandos geprueft, welche entsprechend ausgefuehrt werden.
 * Beinhaltet die Eingabe kein Built-In Kommando werden die Argumente an die launch() Funktion uebergeben.
 * @param line Eingegebene Zeile des Nutzers als Zeichenkette.
 */
void MiniShell::execute(char *line) {

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


