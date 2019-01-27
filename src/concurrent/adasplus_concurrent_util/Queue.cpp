//
// Created by guoshichao on 19-1-24.
//
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "log.h"

/*===========================================================================
 * FUNCTION   : QCameraQueue
 *
 * DESCRIPTION: default constructor of QCameraQueue
 *
 * PARAMETERS : None
 *
 * RETURN     : None
 *==========================================================================*/
QCameraQueue::QCameraQueue() {
    pthread_mutex_init(&m_lock, NULL);
    cam_list_init(&m_head.list);
    m_size = 0;
    m_dataFn = NULL;
    m_userData = NULL;
    m_active = true;
}

/*===========================================================================
 * FUNCTION   : QCameraQueue
 *
 * DESCRIPTION: constructor of QCameraQueue
 *
 * PARAMETERS :
 *   @data_rel_fn : function ptr to release node data internal resource
 *   @user_data   : user data ptr
 *
 * RETURN     : None
 *==========================================================================*/
QCameraQueue::QCameraQueue(release_data_fn data_rel_fn, void *user_data) {
    pthread_mutex_init(&m_lock, NULL);
    cam_list_init(&m_head.list);
    m_size = 0;
    m_dataFn = data_rel_fn;
    m_userData = user_data;
    m_active = true;
}

/*===========================================================================
 * FUNCTION   : ~QCameraQueue
 *
 * DESCRIPTION: deconstructor of QCameraQueue
 *
 * PARAMETERS : None
 *
 * RETURN     : None
 *==========================================================================*/
QCameraQueue::~QCameraQueue() {
    flush();
    pthread_mutex_destroy(&m_lock);
}

/*===========================================================================
 * FUNCTION   : init
 *
 * DESCRIPTION: Put the queue to active state (ready to enqueue and dequeue)
 *
 * PARAMETERS : None
 *
 * RETURN     : None
 *==========================================================================*/
void QCameraQueue::init() {
    pthread_mutex_lock(&m_lock);
    m_active = true;
    pthread_mutex_unlock(&m_lock);
}

/*===========================================================================
 * FUNCTION   : isEmpty
 *
 * DESCRIPTION: return if the queue is empty or not
 *
 * PARAMETERS : None
 *
 * RETURN     : true -- queue is empty; false -- not empty
 *==========================================================================*/
bool QCameraQueue::isEmpty() {
    bool flag = true;
    pthread_mutex_lock(&m_lock);
    if (m_size > 0) {
        flag = false;
    }
    pthread_mutex_unlock(&m_lock);
    return flag;
}

/*===========================================================================
 * FUNCTION   : enqueue
 *
 * DESCRIPTION: enqueue data into the queue
 *
 * PARAMETERS :
 *   @data    : data to be enqueued
 *
 * RETURN     : true -- success; false -- failed
 *==========================================================================*/
bool QCameraQueue::enqueue(void *data) {
    LOGD("enqueue new data\n");
    bool rc;
    camera_q_node *node =
            (camera_q_node *) malloc(sizeof(camera_q_node));
    if (NULL == node) {
        LOGD("the data are null, so just return\n");
        return false;
    }

    memset(node, 0, sizeof(camera_q_node));
    node->data = data;

    pthread_mutex_lock(&m_lock);
    if (m_active) {
        cam_list_add_tail_node(&node->list, &m_head.list);
        m_size++;
        rc = true;
        LOGD("is active\n");
    } else {
        free(node);
        rc = false;
        LOGD("free node\n");
    }

    pthread_mutex_unlock(&m_lock);
    return rc;
}

/*===========================================================================
 * FUNCTION   : enqueueWithPriority
 *
 * DESCRIPTION: enqueue data into queue with priority, will insert into the
 *              head of the queue
 *
 * PARAMETERS :
 *   @data    : data to be enqueued
 *
 * RETURN     : true -- success; false -- failed
 *==========================================================================*/
bool QCameraQueue::enqueueWithPriority(void *data) {
    bool rc;
    camera_q_node *node =
            (camera_q_node *) malloc(sizeof(camera_q_node));
    if (NULL == node) {
        return false;
    }

    memset(node, 0, sizeof(camera_q_node));
    node->data = data;

    pthread_mutex_lock(&m_lock);
    if (m_active) {
        struct cam_list *p_next = m_head.list.next;

        m_head.list.next = &node->list;
        p_next->prev = &node->list;
        node->list.next = p_next;
        node->list.prev = &m_head.list;

        m_size++;
        rc = true;
    } else {
        free(node);
        rc = false;
    }
    pthread_mutex_unlock(&m_lock);
    return rc;
}

/*===========================================================================
 * FUNCTION   : dequeue
 *
 * DESCRIPTION: dequeue data from the queue
 *
 * PARAMETERS :
 *   @bFromHead : if true, dequeue from the head
 *                if false, dequeue from the tail
 *
 * RETURN     : data ptr. NULL if not any data in the queue.
 *==========================================================================*/
void *QCameraQueue::dequeue(bool bFromHead) {
    camera_q_node *node = NULL;
    void *data = NULL;
    struct cam_list *head = NULL;
    struct cam_list *pos = NULL;

    pthread_mutex_lock(&m_lock);
    if (m_active) {
        head = &m_head.list;
        if (bFromHead) {
            pos = head->next;
        } else {
            pos = head->prev;
        }
        if (pos != head) {
            node = member_of(pos, camera_q_node, list);
            cam_list_del_node(&node->list);
            m_size--;
        }
    }
    pthread_mutex_unlock(&m_lock);

    if (NULL != node) {
        data = node->data;
        free(node);
    }

    return data;
}

/*===========================================================================
 * FUNCTION   : flush
 *
 * DESCRIPTION: flush all nodes from the queue, queue will be empty after this
 *              operation.
 *
 * PARAMETERS : None
 *
 * RETURN     : None
 *==========================================================================*/
void QCameraQueue::flush() {
    camera_q_node *node = NULL;
    struct cam_list *head = NULL;
    struct cam_list *pos = NULL;

    pthread_mutex_lock(&m_lock);
    if (m_active) {
        head = &m_head.list;
        pos = head->next;

        while (pos != head) {
            node = member_of(pos, camera_q_node, list);
            pos = pos->next;
            cam_list_del_node(&node->list);
            m_size--;

            if (NULL != node->data) {
                if (m_dataFn) {
                    m_dataFn(node->data, m_userData);
                }
                free(node->data);
            }
            free(node);

        }
        m_size = 0;
        m_active = false;
    }
    pthread_mutex_unlock(&m_lock);
}

/*===========================================================================
 * FUNCTION   : flushNodes
 *
 * DESCRIPTION: flush only specific nodes, depending on
 *              the given matching function.
 *
 * PARAMETERS :
 *   @match   : matching function
 *
 * RETURN     : None
 *==========================================================================*/
void QCameraQueue::flushNodes(match_fn match) {
    camera_q_node *node = NULL;
    struct cam_list *head = NULL;
    struct cam_list *pos = NULL;

    if (NULL == match) {
        return;
    }

    pthread_mutex_lock(&m_lock);
    if (m_active) {
        head = &m_head.list;
        pos = head->next;

        while (pos != head) {
            node = member_of(pos, camera_q_node, list);
            pos = pos->next;
            if (match(node->data, m_userData)) {
                cam_list_del_node(&node->list);
                m_size--;

                if (NULL != node->data) {
                    if (m_dataFn) {
                        m_dataFn(node->data, m_userData);
                    }
                    free(node->data);
                }
                free(node);
            }
        }
    }
    pthread_mutex_unlock(&m_lock);
}


