//
// Created by Patrick Felschen on 09.12.21.
//

#ifndef BETRIEBSSYSTEME_QUEUE_H
#define BETRIEBSSYSTEME_QUEUE_H

#define QUEUESIZE 10

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <cstdio>
#include <unistd.h>
#include <cstdlib>

using namespace std;

class Queue {
private:
    char* buf[QUEUESIZE];
    long head, tail;
    bool full, empty;
    unsigned int size;
public:
    std::mutex mut;
    std::condition_variable notFull, notEmpty;
public:
    Queue();
    virtual ~Queue();
    void addItem(char* in);
    void delItem(char** out);
    bool isFull() const { return full; }
    bool isEmpty() const { return empty; }
};


#endif //BETRIEBSSYSTEME_QUEUE_H
