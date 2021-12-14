//
// Created by Patrick Felschen on 09.12.21.
//

#include "Queue.h"

Queue::Queue(int queueSize) {
    buf = new char*[queueSize];
    size = queueSize;

    empty = true;
    full = false;
    end = false;

    head = 0;
    tail = 0;
}

Queue::~Queue() {}

void Queue::addItem(char *in) {
    buf[tail] = in;
    tail++;
    if (tail == size) {
        tail = 0;
    }
    if (tail == head) {
        full = true;
    }
    empty = false;
}

void Queue::delItem(char **out) {
    *out = buf[head];
    head++;
    if (head == size) {
        head = 0;
    }
    if (head == tail) {
        empty = true;
    }
    full = false;
}

void Queue::setEnd(bool end) {
    this->end = end;
}

bool Queue::isFull() const {
    return full;
}

bool Queue::isEmpty() const {
    return empty;
}

bool Queue::isEnd() const {
    return end;
}
