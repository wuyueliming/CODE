#pragma once
#include<semaphore.h>

namespace ThreadModule{
    class Semaphore{
    public:
        Semaphore(int value = 0){
            sem_init(&_sem, 0, value);
        }

        ~Semaphore(){
            sem_destroy(&_sem);
        }

        void P(){
            wait();
        }
        void V(){
            signal();
        }

    private:
        void wait(){
            sem_wait(&_sem);
        }

        void signal(){
            sem_post(&_sem);
        }

    private:
        sem_t _sem;
    };
}
