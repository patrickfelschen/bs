//
// Created by Patrick Felschen on 09.12.21.
//

#ifndef BETRIEBSSYSTEME_BOT_H
#define BETRIEBSSYSTEME_BOT_H

#define LOOP 20

#include "Queue.h"

class Bot {
private:
public:
    Bot(char** urls, unsigned int queueSize, unsigned int threadCount);
    virtual ~Bot();
    void start();
private:
    void do_produce(int item, int r);
    void *producer(void *q);
    void do_consume(int item, int r);
    void *consumer(void *q);
};


#endif //BETRIEBSSYSTEME_BOT_H
