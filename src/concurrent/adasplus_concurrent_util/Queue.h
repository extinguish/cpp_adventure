//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_QUEUE_H
#define CPPADVENTURE_QUEUE_H

#include <sys/types.h>
#include <pthread.h>
#include "list.h"

typedef void (*release_data_fn)(void *data, void *user_data);

typedef bool (*match_fn)(void *data, void *user_data);

class QCameraQueue {
public:
    QCameraQueue();

    QCameraQueue(release_data_fn data_rel_fn, void *user_data);

    virtual ~QCameraQueue();

    void init();

    bool enqueue(void *data);

    bool enqueueWithPriority(void *data);

    /* This call will put queue into uninitialized state.
     * Need to call init() in order to use the queue again */
    void flush();

    void flushNodes(match_fn match);

    void *dequeue(bool bFromHead = true);

    bool isEmpty();

private:
    typedef struct {
        struct cam_list list;
        void *data;
    } camera_q_node;

    camera_q_node m_head; // dummy head
    int m_size;
    bool m_active;
    pthread_mutex_t m_lock;
    release_data_fn m_dataFn;
    void *m_userData;
};


#endif //CPPADVENTURE_QUEUE_H
