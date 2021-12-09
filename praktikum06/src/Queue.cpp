//
// Created by Patrick Felschen on 09.12.21.
//

#include "Queue.h"

Queue::Queue() {
    empty = true;
    full = false;
    head = 0;
    tail = 0;
}

Queue::~Queue() {}

void Queue::addItem(char *in) {
    buf[tail] = in;
    tail++;
    if (tail == size)
        tail = 0;
    if (tail == head)
        full = true;
    empty = false;
}

void Queue::delItem(char **out) {
    *out = buf[head];
    head++;
    if (head == size)
        head = 0;
    if (head == tail)
        empty = true;
    full = false;
}
