//
// Created by Patrick Felschen on 09.12.21.
//

#include "Bot.h"

void Bot::do_produce(int item, int r)
{
    printf("producer: produced %d (round %d).\n", item, r);
    usleep(100000 + r * 100000);
}

/* Producer */
void *Bot::producer(void *q) {
    Queue * fifo = (Queue *) q;

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < LOOP; i++) {
            std::unique_lock<std::mutex> lck(fifo->mut);
            // while -> spinlock
            if (fifo->isFull()) {
                printf("producer: queue FULL.\n");
                fifo->notFull.wait(lck);
            }
            //TODO: fifo->addItem (i);
            fifo->notEmpty.notify_one();
        }
    }
    return (NULL);
}

void Bot::do_consume(int item, int r)
{
    printf("consumer: consumed %d.\n", item);
    usleep(200000 + r * 300000);
}

/* Consumer */
void *Bot::consumer(void *q) {
    Queue *fifo;
    int i, d;
    int j;

    fifo = (Queue *) q;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < LOOP; i++) {
            std::unique_lock<std::mutex> lck(fifo->mut);
            // while -> spinlock
            if (fifo->isEmpty()) {
                printf("consumer: queue EMPTY.\n");
                fifo->notEmpty.wait(lck);
            }
            //TODO: fifo->delItem (&d);
            fifo->notFull.notify_one();
            do_consume (d, j);
        }
    }
    return (NULL);
}

Bot::Bot(char** urls, unsigned int queueSize, unsigned int threadCount) {}

Bot::~Bot() {

}

void Bot::start() {

}
