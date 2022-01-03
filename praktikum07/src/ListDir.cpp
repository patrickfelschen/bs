//
// Created by patrickfelschen on 17.12.21.
//
#include "ListDir.h"
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <grp.h>
#include <pwd.h>

ListDir::ListDir() {
    showAll = false;
    showOwner = false;
    showLongFormat = false;
    showGroup = false;
}

ListDir::~ListDir() {}

void ListDir::printResult() {
    DIR *currentDir;
    struct dirent *files;
    currentDir = opendir(dir);
    files = readdir(currentDir);
    struct stat buf;
    while (files) {
        char *path = files->d_name;
        stat(path, &buf);
        // Ueberspringe Datei, wenn -a nicht angegeben ist und Datei versteckt
        if(!showAll && path[0] == '.'){
            files = readdir(currentDir);
            continue;
        }
        if (showLongFormat) {
            // Dateityp
            printf((S_ISDIR(buf.st_mode)) ? "d" : "-");
            // Rechte
            printf((buf.st_mode & S_IRUSR) ? "r" : "-");
            printf((buf.st_mode & S_IWUSR) ? "w" : "-");
            printf((buf.st_mode & S_IXUSR) ? "x" : "-");
            printf((buf.st_mode & S_IRGRP) ? "r" : "-");
            printf((buf.st_mode & S_IWGRP) ? "w" : "-");
            printf((buf.st_mode & S_IXGRP) ? "x" : "-");
            printf((buf.st_mode & S_IROTH) ? "r" : "-");
            printf((buf.st_mode & S_IWOTH) ? "w" : "-");
            printf((buf.st_mode & S_IXOTH) ? "x" : "-");
            // Anzahl Hardlinks
            printf(" %i ", buf.st_nlink);
            // Eigentuemer
            if (showOwner) {
#ifdef __linux__
                struct passwd *pw = getpwuid(buf.st_uid);
                printf("%-10s ", pw->pw_name);
#else
                printf("%-2i ", buf.st_uid);
#endif
            }
            // Eigentuemer Gruppe
            if (showGroup) {
#ifdef __linux__
                struct group *gr = getgrgid(buf.st_gid);
                printf("%-10s ", gr->gr_name);
#else
                printf("%-2i ", buf.st_gid);
#endif

            }
            // Dateigroeße
            printf("%-10i ", buf.st_size);
            // Aenderungszeit
            char *time = strtok(ctime(&buf.st_mtime), "\n");
            printf("%s ", time);
            // Name
            printf("%-10s \n", files->d_name);
        } else {
            printf("%s ", files->d_name);
        }
        files = readdir(currentDir);
    }
    closedir(currentDir);
}

void ListDir::setShowAll(bool showAll) {
    this->showAll = showAll;
}

void ListDir::setShowOwner(bool showOwner) {
    this->showOwner = showOwner;
}

void ListDir::setShowLongFormat(bool showLongFormat) {
    this->showLongFormat = showLongFormat;
}

void ListDir::setShowGroup(bool showGroup) {
    ListDir::showGroup = showGroup;
}

void ListDir::setDir(char *dir) {
    this->dir = dir;
}
