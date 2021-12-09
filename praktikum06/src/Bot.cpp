//
// Created by Patrick Felschen on 09.12.21.
//

#include "Bot.h"

Bot::Bot(char **urls) {
    this->urls = urls;
}

Bot::~Bot() {

}

void do_produce(char *url) {
    printf("producer: produced %s.\n", url);
    usleep(100000 + 100000);
}

/* Producer */
void *producer(void *q, char **urls) {
    Queue *queue = (Queue *) q;

    unsigned int pos = 0;
    while (urls[pos] != nullptr) {

        unique_lock<mutex> lck(queue->mut);
        // while -> spinlock
        if (queue->isFull()) {
            printf("producer: queue FULL.\n");
            queue->notFull.wait(lck);
        }

        queue->addItem(urls[pos]);
        queue->notEmpty.notify_one();

        do_produce(urls[pos]);

        pos++;
    }

    return nullptr;
}

void do_consume(char *url) {
    printf("consumer: consumed %s.\n", url);
    usleep(200000 + 300000);
}

/* Consumer */
void *consumer(void *q) {
    Queue *queue = (Queue *) q;
    char *url;
    int i;

    for (i = 0; i < LOOP; i++) {
        unique_lock<mutex> lck(queue->mut);
        // while -> spinlock
        if (queue->isEmpty()) {
            printf("consumer: queue EMPTY.\n");
            queue->notEmpty.wait(lck);
        }
        queue->delItem(&url);
        queue->notFull.notify_one();
        do_consume(url);
    }

    return nullptr;
}

void Bot::start() {
    Queue queue;

    // Reader Thread
    thread pro(producer, &queue, urls);

    // Client Threads
    thread con(consumer, &queue);

    pro.join();
    con.join();
}
