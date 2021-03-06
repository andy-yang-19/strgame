#include <pthread.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <signal.h>
#include "fifo.h"
#include "strproc.h"
#include "err.h"

using namespace std;

static bool run = true;
static size_t prodCnt = 0;
static size_t consCnt = 0;

void sig_handler(int sig)
{
    run = false;
}

static Fifo<string> fifo;

void *producer(void *arg)
{
    while(run) {
        shared_ptr<string> str = genStr();
        fifo.put(str);
        prodCnt++;
    }

    return NULL;
}

void *consumer(void *arg)
{
    while(run) {
        shared_ptr<string> str = fifo.get();
        sortStr(*str);
        consCnt++;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tidp, tidc;
    int e;

    int secs = 2;
    if(argc > 1)
        secs = atoi(argv[1]);

    struct itimerval itv;
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = secs;
    itv.it_value.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &itv, NULL) < 0) {
        perror("setitimer");
        return -1;
    }
    signal(SIGALRM, sig_handler);

    e = pthread_create(&tidp, NULL, &producer, NULL);
    if(e)
        handle_err(e, "pthread_create");

    e = pthread_create(&tidc, NULL, &consumer, NULL);
    if(e)
        handle_err(e, "pthread_create");

    e = pthread_join(tidp, NULL);
    if(e)
        handle_err(e, "pthread_join");

    e = pthread_join(tidc, NULL);
    if(e)
        handle_err(e, "pthread_join");

    cout << "prod: " << prodCnt << ", cons: " << consCnt << endl;

    return 0;
}

