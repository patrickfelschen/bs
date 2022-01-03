//
// Created by patrickfelschen on 17.12.21.
//
#ifndef BETRIEBSSYSTEME_LISTDIR_H
#define BETRIEBSSYSTEME_LISTDIR_H

#include <dirent.h>
#include "cstdio"
#include <sys/stat.h>

class ListDir {
private:
    char* dir;
    bool showAll;
    bool showOwner;
    bool showLongFormat;
    bool showGroup;

public:
    ListDir();
    virtual ~ListDir();
    void printResult();
    void setDir(char *dir);
    void setShowAll(bool showAll);
    void setShowOwner(bool showOwner);
    void setShowLongFormat(bool showLongFormat);
    void setShowGroup(bool showGroup);
};


#endif //BETRIEBSSYSTEME_LISTDIR_H
