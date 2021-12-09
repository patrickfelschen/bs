//
// Created by Patrick Felschen on 09.12.21.
//

#include "Bot.h"

Bot::Bot(char** urls) {
    this->urls = urls;
}

Bot::~Bot() {

}

void do_produce(int item, int r)
{
    printf("producer: produced %d (round %d).\n", item, r);
    usleep(100000 + r * 100000);
}

/* Producer */
void *producer(void *q) {
    Queue * queue = (Queue *) q;

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < LOOP; i++) {
            unique_lock<std::mutex> lck(queue->mut);
            // while -> spinlock
            if (queue->isFull()) {
                printf("producer: queue FULL.\n");
                queue->notFull.wait(lck);
            }
            TODO: queue->addItem (i);
            queue->notEmpty.notify_one();
        }
    }
    return nullptr;
}

void do_consume(int item, int r)
{
    printf("consumer: consumed %d.\n", item);
    usleep(200000 + r * 300000);
}

/* Consumer */
void *consumer(void *q) {
    Queue *fifo;
    int i, d;
    int j;

    fifo = (Queue *) q;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < LOOP; i++) {
            unique_lock<std::mutex> lck(fifo->mut);
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
    return nullptr;
}

void Bot::start() {
    Queue queue(queueSize);

    thread pro(producer, &queue);
    thread con(consumer, &queue);

    pro.join();
    con.join();
}
