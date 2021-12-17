//
// Created by pfelsche@id.hsos.de on 17.12.21.
//


#include "ListDir.h"

ListDir::ListDir(char* dir): dir(dir) {

}

ListDir::~ListDir() {

}

void ListDir::printDir() {
    DIR *currentDir;
    struct dirent *files;

    currentDir = opendir(dir);
    files = readdir(currentDir);

    struct stat buf;

    while(files)
    {
        char* path = files->d_name;

        //lstat(path, &stat);

        printf("%s ", files->d_name);
        files = readdir(currentDir);
    }
    closedir(currentDir);
}
