//
// Created by Patrick Felschen on 09.12.21.
//

#include "Bot.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"

Bot::Bot() {}

Bot::~Bot() {}

/* Producer */
void *producer(void *q, char* fileName) {
    Queue *queue = (Queue *) q;
    //// Urls aus Datei einlesen
    std::ifstream file(fileName);
    std::string str;
    while (std::getline(file, str)) {
        std::unique_lock<std::mutex> lock(queue->mutex);
        while(queue->isFull()){
            queue->notFull.wait(lock);
        }
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
        queue->addItem(cstr);
        printf(GRN"producer: %s\n", cstr);
        queue->notEmpty.notify_all();
    }
    queue->setEnd(true);
    return nullptr;
}

void do_consume(char *url, int id) {
#ifdef __APPLE__
    usleep(random() / 1000);
#endif

#ifdef __linux__
    // get domain for filename
    char *urlCopy = strdup(url);
    strtok(urlCopy, "/");
    char *domain = strtok(nullptr, "/");

    char filename[64];
    snprintf(filename, sizeof(filename), "%i_%s.html", id, domain);

    int res = webreq_download(url, filename);

    if(res != 200) {
        printf("%s", webreq_error(res));
    }
#endif
    printf(RED"consumer (%i): consumed %s\n", id, url);
}

/* Consumer */
void *consumer(void *q, int id) {
    Queue *queue = (Queue *) q;
    while(true) {
        std::unique_lock<std::mutex> lock(queue->mutex);
        //// Queue erreicht das Ende und ist leer
        if(queue->isEnd() && queue->isEmpty()){
            printf(YEL"consumer (%i): isEnd\n", id);
            exit(0);
        }
        while(queue->isEmpty()){
            printf(YEL"consumer (%i): isEmpty\n", id);
            queue->notEmpty.wait(lock);
        }
        char* url;
        queue->delItem(&url);
        queue->notFull.notify_all();
        do_consume(url, id);
    }
    return nullptr;
}

void Bot::start(char* fileName, int queueSize, int threadCount) {
    std::thread threads[threadCount];
    Queue queue(queueSize);

#ifdef __linux__
    webreq_set_output_path("./output");
#endif
    //// Reader Thread
    std::thread pro(producer, &queue, fileName);
    //// Client Threads
    for (int i = 0; i < threadCount; i++) {
        threads[i] = std::thread(consumer, &queue, i);
    }
    pro.join();
    for (std::thread &con: threads) {
        con.join();
    }
#ifdef __linux__
    webreq_cleanup();
#endif
}
