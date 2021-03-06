//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_LIST_H
#define CPPADVENTURE_LIST_H

#include <stddef.h>

#define member_of(ptr, type, member) ({ \
  const typeof(((type *)0)->member) *__mptr = (ptr); \
  (type *)((char *)__mptr - offsetof(type,member));})

struct cam_list {
    struct cam_list *next, *prev;
};

static inline void cam_list_init(struct cam_list *ptr) {
    ptr->next = ptr;
    ptr->prev = ptr;
}

static inline void cam_list_add_tail_node(struct cam_list *item,
                                          struct cam_list *head) {
    struct cam_list *prev = head->prev;

    head->prev = item;
    item->next = head;
    item->prev = prev;
    prev->next = item;
}

static inline void cam_list_insert_before_node(struct cam_list *item,
                                               struct cam_list *node) {
    item->next = node;
    item->prev = node->prev;
    item->prev->next = item;
    node->prev = item;
}

static inline void cam_list_del_node(struct cam_list *ptr) {
    struct cam_list *prev = ptr->prev;
    struct cam_list *next = ptr->next;

    next->prev = ptr->prev;
    prev->next = ptr->next;
    ptr->next = ptr;
    ptr->prev = ptr;
}

#endif //CPPADVENTURE_LIST_H
