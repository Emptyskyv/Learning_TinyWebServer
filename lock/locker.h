//
// Created by Emptyskyv-Private on 2023/5/8.
//

#ifndef LEARNING_TINYWEBSERVER_LOCKER_H
#define LEARNING_TINYWEBSERVER_LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>
#include <semaphore>

class sem {
private:
    sem_t m_sem;
public:
    sem() {
        if (sem_open("m_sem", O_CREAT|O_EXCL, S_IRWXU, 0) != 0) {
            throw std::exception();
        }
    }

    sem(int num) {
        if (sem_open("m_sem", O_CREAT|O_EXCL, S_IRWXU, num) != 0) {
            throw std::exception();
        }
    }

    ~sem() {
        sem_unlink("m_sem");
    }

    bool wait() {
        return sem_wait(&m_sem) == 0;
    }

    bool post() {
        return sem_post(&m_sem) == 0;
    }
};

class locker{
private:
    pthread_mutex_t m_mutex;

public:
    locker() {
        if (pthread_mutex_init(&m_mutex, nullptr) != 0) {
            throw std::exception();
        }
    }
    ~locker() {
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock() {
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock() {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

    pthread_mutex_t* get() {
        return &m_mutex;
    }
};

class cond {
private:
    pthread_cond_t m_cond;

public:
    cond() {
        if (pthread_cond_init(&m_cond, nullptr) != 0) {
            throw std::exception();
        }
    }

    ~cond() {
        pthread_cond_destroy(&m_cond);
    }

    bool wait(pthread_mutex_t* m_mutex) {
        int ret = pthread_cond_wait(&m_cond, m_mutex);

        return ret == 0;
    }

    bool signal() {
        return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast() {
        return pthread_cond_broadcast(&m_cond) == 0;
    }
};

#endif //LEARNING_TINYWEBSERVER_LOCKER_H
