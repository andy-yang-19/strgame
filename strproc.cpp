#include <algorithm>
#include <functional>
#include <memory>
#include <random>
#include <string>
using namespace std;

random_device rd;
default_random_engine re(rd());

shared_ptr<string> genStr()
{
    static const size_t StrLen(12);
    static const string Charset("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

    uniform_int_distribution<unsigned int> uid(0, Charset.length()-1);
    auto randchar = [&uid]() { return Charset[uid(re)]; };

    shared_ptr<string> str(new string(StrLen, 0));
    generate_n(str->begin(), str->length(), randchar);
    return str;
}

void sortStr(string& str)
{
    sort(str.begin(), str.end());
}

