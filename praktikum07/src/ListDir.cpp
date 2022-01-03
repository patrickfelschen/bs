//
// Created by patrickfelschen on 17.12.21.
//
#include "ListDir.h"
#include <ctime>
#include <unistd.h>

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
            if(showOwner){
                printf("%-5i ", buf.st_uid);
            }
            if(showGroup){
                printf("%-5i ", buf.st_gid);
            }
            printf("%-10i ", buf.st_size);
            char* time = strtok(ctime(&buf.st_mtime), "\n");
            printf("%s ", time);
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
