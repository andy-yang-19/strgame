#include <pthread.h>
#include <iostream>
#include <string>
#include "fifo.h"
#include "strproc.h"
#include "err.h"

using namespace std;

struct ThreadArg
{
    int cnt;
};

Fifo<string> fifo;

void *producer(void *arg)
{
    int cnt = ((ThreadArg*)arg)->cnt;

    while(cnt-- > 0) {
        shared_ptr<string> str = genStr();
        //cout << "p: " << *str << endl;
        fifo.put(str);
    }

    return NULL;
}

void *consumer(void *arg)
{
    int cnt = ((ThreadArg*)arg)->cnt;

    while(cnt-- > 0) {
        shared_ptr<string> str = fifo.get();
        sortStr(*str);
        //cout << "c: " << *str << endl;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tidp, tidc;
    ThreadArg threadArgs[2];
    int e;

    int cnt = 10;
    if(argc > 1) {
        cnt = atoi(argv[1]);
    }

    threadArgs[0].cnt = cnt;
    threadArgs[1].cnt = cnt;

    e = pthread_create(&tidp, NULL, &producer, &threadArgs[0]);
    if(e)
        handle_err(e, "pthread_create");

    e = pthread_create(&tidc, NULL, &consumer, &threadArgs[1]);
    if(e)
        handle_err(e, "pthread_create");

    e = pthread_join(tidp, NULL);
    if(e)
        handle_err(e, "pthread_join");

    e = pthread_join(tidc, NULL);
    if(e)
        handle_err(e, "pthread_join");

    return 0;
}

