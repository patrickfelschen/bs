//
// Created by Patrick Felschen on 09.12.21.
//

#ifndef BETRIEBSSYSTEME_BOT_H
#define BETRIEBSSYSTEME_BOT_H

#define LOOP 20

#include "Queue.h"
#include "include/web_request.h"
#include <cstring>

class Bot {
public:
    Bot(char** urls);
    virtual ~Bot();
    void start();
private:
    char** urls;
};


#endif //BETRIEBSSYSTEME_BOT_H
