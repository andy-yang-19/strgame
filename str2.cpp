#include <cstdlib>
#include <iostream>
#include "strproc.h"
using namespace std;

int main(int argc, char* argv[])
{
    int loopCnt = 10;
    if(argc > 1)
        loopCnt = atoi(argv[1]);

    while(loopCnt-- > 0) {
        shared_ptr<string> s = genStr();
        string ss = *s;
        sortStr(ss);
        //cout << *s << "," << ss << endl;
    }
}

