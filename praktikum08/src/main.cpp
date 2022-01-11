//
// Created by patrickfelschen on 17.12.21.
//

#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include "tar.h"
#include <string>
#include <ctime>

long octalToDecimal(long octalNumber);
void printConsole(const char* s);

int main(int argc, char **argv) {
    //// OPEN FILE ////
    errno = 0;
    int fd = open(argv[1], O_RDONLY);
    if (errno != 0) {
        printConsole(strerror(errno));
        return EXIT_FAILURE;
    }
    TARHeader tarBuf;
    //// LOOP FILE CONTENT SEGMENTS ////
    while (read(fd, &tarBuf, sizeof(tarBuf)) > 0) {
        if(strlen(tarBuf.name) == 0) continue;
        //// CHECK FILE HEADER ////
        if (memcmp(tarBuf.magic, TMAGIC, strlen(TMAGIC)) != 0) {
            printConsole("Not a TAR-Archive.");
            return EXIT_FAILURE;
        }
        long sizeOct = atol(tarBuf.size);
        long sizeDec = octalToDecimal(sizeOct);
        long segCount = ceil((double)sizeDec / 512);
        long segSize = segCount * 512;
        long modeOct = atol(tarBuf.mode);
        long modeDec = octalToDecimal(modeOct);
        long mtimeOct = atol(tarBuf.mtime);
        time_t mTimeDec = octalToDecimal(mtimeOct);
        char* date = strtok(ctime(&mTimeDec), "\n");
        //// PRINT FILE HEADER ////
        printConsole(tarBuf.typeflag == DIRTYPE ? "d" : "-");
        printConsole(modeDec & TUREAD ? "r" : "-");
        printConsole(modeDec & TUWRITE ? "w" : "-");
        printConsole(modeDec & TUEXEC ? "x" : "-");
        printConsole(modeDec & TGREAD ? "r" : "-");
        printConsole(modeDec & TGWRITE ? "w" : "-");
        printConsole(modeDec & TGEXEC ? "x" : "-");
        printConsole(modeDec & TOREAD ? "r" : "-");
        printConsole(modeDec & TOWRITE ? "w" : "-");
        printConsole(modeDec & TOEXEC ? "x" : "-");
        printConsole("\t");
        printConsole(tarBuf.uname);
        printConsole("/");
        printConsole(tarBuf.gname);
        printConsole("\t");
        printConsole(std::to_string(sizeDec).c_str());
        printConsole("\t");
        printConsole(date);
        printConsole("\t");
        printConsole(tarBuf.name);
        printConsole("\n");
        errno = 0;
        //// REPOSITION THE FILE OFFSET ////
        lseek(fd, segSize, SEEK_CUR);
        if (errno != 0) {
            printf("%s \n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    //// CLOSE FILE ////
    errno = 0;
    close(fd);
    if (errno != 0) {
        printConsole(strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

long octalToDecimal(long octalNumber) {
    // https://www.programiz.com/cpp-programming/examples/octal-decimal-convert
    long decimalNumber = 0, i = 0, rem;
    while (octalNumber != 0) {
        rem = octalNumber % 10;
        octalNumber /= 10;
        decimalNumber += rem * pow(8, i);
        ++i;
    }
    return decimalNumber;
}

void printConsole(const char* s) {
    write(STDOUT_FILENO, s, strlen(s));
}
