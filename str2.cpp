#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include "strproc.h"
using namespace std;

static bool run = true;

void sig_handler(int sig)
{
    run = false;
}

int main(int argc, char* argv[])
{
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

    int cnt = 0;
    while(run) {
        shared_ptr<string> s = genStr();
        string ss = *s;
        sortStr(ss);
        cnt++;
        //cout << *s << "," << ss << endl;
    }
    cout << "cnt: " << cnt << endl;
}

