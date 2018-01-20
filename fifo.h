#pragma once

#include <deque>
#include <memory>
#include <pthread.h>
#include "err.h"

template<typename T>
class Fifo
{
public:
    Fifo()
    {
        pthread_mutex_init(&mMut, NULL);
        pthread_cond_init(&mCond, NULL);
    }

    ~Fifo()
    {
        pthread_mutex_destroy(&mMut);
        pthread_cond_destroy(&mCond);
    }

    bool put(const std::shared_ptr<T>& item)
    {
        int e = pthread_mutex_lock(&mMut);
        if(e)
            handle_err(e, "pthread_mutex_lock");

        mItems.push_back(item);
        if(mItems.size() == 1)
            pthread_cond_signal(&mCond);

        pthread_mutex_unlock(&mMut);
        if(e)
            handle_err(e, "pthread_mutex_unlock");

        return true;
    }

    std::shared_ptr<T> get()
    {
        int e = pthread_mutex_lock(&mMut);
        if(e)
            handle_err(e, "pthread_mutex_lock");

        while(mItems.empty())
            pthread_cond_wait(&mCond, &mMut);

        std::shared_ptr<T> item = mItems.front();
        mItems.pop_front();

        pthread_mutex_unlock(&mMut);
        if(e)
            handle_err(e, "pthread_mutex_unlock");

        return item;
    }

private:
    std::deque<std::shared_ptr<T>> mItems;
    pthread_mutex_t mMut;
    pthread_cond_t mCond;
};

