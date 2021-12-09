//
// Created by Patrick Felschen on 09.12.21.
//

#include "Bot.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"

Bot::Bot(char **urls) {
    this->urls = urls;
}

Bot::~Bot() {

}

void do_produce(char *url) {
    printf(GRN"producer: produced %s.\n", url);
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
            printf(YEL"producer: queue FULL.\n");
            queue->notFull.wait(lck);
        }

        queue->addItem(urls[pos]);
        queue->notEmpty.notify_one();

        do_produce(urls[pos]);

        pos++;
    }

    return nullptr;
}

void do_consume(char *url, int id) {
    printf(RED"consumer (%i): consumed %s.\n", id, url);

    webreq_download(url, url);

    usleep(random()/1000);
}

/* Consumer */
void *consumer(void *q) {
    Queue *queue = (Queue *) q;
    char *url;

    for (int i = 0; i < LOOP; i++) {
        unique_lock<mutex> lck(queue->mut);
        // while -> spinlock
        if (queue->isEmpty()) {
            printf(YEL"consumer: queue EMPTY.\n");
            queue->notEmpty.wait(lck);
        }
        queue->delItem(&url);
        queue->notFull.notify_one();
        do_consume(url, i);
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
