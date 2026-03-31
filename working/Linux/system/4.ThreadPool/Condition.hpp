#pragma once
#include<pthread.h>

namespace ThreadModule{
    class Condition{
    public:
        Condition(){
            pthread_cond_init(&_cond, nullptr);
        }

        ~Condition(){
            pthread_cond_destroy(&_cond);
        }

        void wait(Mutex& mutex){
            pthread_cond_wait(&_cond, &mutex.getMutex());
        }

        void signal(){
            pthread_cond_signal(&_cond);
        }

        void broadcast(){
            pthread_cond_broadcast(&_cond);
        }   

    private:
        pthread_cond_t _cond;
    };

}