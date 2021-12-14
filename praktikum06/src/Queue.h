//
// Created by Patrick Felschen on 09.12.21.
//

#ifndef BETRIEBSSYSTEME_QUEUE_H
#define BETRIEBSSYSTEME_QUEUE_H

#include <mutex>
#include <condition_variable>

class Queue {
private:
    char** buf;
    int size;
    long head, tail;
    bool full, empty, end;
public:
    std::mutex mutex;
    std::condition_variable notEmpty, notFull;
public:
    Queue(int queueSize);
    virtual ~Queue();
    void addItem(char* in);
    void delItem(char** out);
    void setEnd(bool end);
    bool isEnd() const;
    bool isFull() const;
    bool isEmpty() const;
};

#endif //BETRIEBSSYSTEME_QUEUE_H
