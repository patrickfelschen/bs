//
// Created by Patrick Felschen on 09.12.21.
//

#ifndef BETRIEBSSYSTEME_BOT_H
#define BETRIEBSSYSTEME_BOT_H

#include <thread>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <sys/time.h>

#include "Queue.h"


#ifdef __linux__
#include "include/web_request.h"
#endif


class Bot {
public:
    Bot();
    virtual ~Bot();
    void start(char* fileName, int queueSize, int threadCount);
};


#endif //BETRIEBSSYSTEME_BOT_H
