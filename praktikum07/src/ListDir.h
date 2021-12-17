//
// Created by pfelsche@id.hsos.de on 17.12.21.
//

#ifndef BETRIEBSSYSTEME_LISTDIR_H
#define BETRIEBSSYSTEME_LISTDIR_H

#include <dirent.h>
#include "cstdio"
#include <sys/stat.h>

class ListDir {
private:
    char* dir;
public:
    ListDir(char* dir);
    virtual ~ListDir();
    void printDir();
};


#endif //BETRIEBSSYSTEME_LISTDIR_H
