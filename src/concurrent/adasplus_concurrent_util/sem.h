//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_SEM_H
#define CPPADVENTURE_SEM_H

#include <sys/types.h>
#include <pthread.h>

namespace util {
#ifdef __cplusplus
    extern "C" {
#endif
    typedef struct {
        int val;
        pthread_mutex_t mutex;
        pthread_cond_t cond;
    } semaphore_t;

    static inline void sem_init(semaphore_t *s, int n) {
        pthread_mutex_init(&(s->mutex), NULL);
        pthread_cond_init(&(s->cond), NULL);
        s->val = n;
    }

    static inline void sem_post(semaphore_t *s) {
        pthread_mutex_lock(&(s->mutex));
        s->val++;
        pthread_cond_signal(&(s->cond));
        pthread_mutex_unlock(&(s->mutex));
    }

    static inline int sem_wait(semaphore_t *s) {
        int rc = 0;
        pthread_mutex_lock(&(s->mutex));
        while (s->val == 0) {
            rc = pthread_cond_wait(&(s->cond), &(s->mutex));
        }
        s->val--;
        pthread_mutex_unlock(&(s->mutex));
        return rc;
    }

    static inline void sem_destroy(semaphore_t *s) {
        pthread_mutex_destroy(&(s->mutex));
        pthread_cond_destroy(&(s->cond));
        s->val = 0;
    }
#ifdef __cplusplus
    }
#endif
}

#endif //CPPADVENTURE_SEM_H
