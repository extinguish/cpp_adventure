//
// Created by guoshichao on 19-2-14.
//

#ifndef C_ADVENTURE_ATOMIC_X86_H
#define C_ADVENTURE_ATOMIC_X86_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


extern inline int32_t android_atomic_add(int32_t increment,
                                         volatile int32_t *ptr) {
    __asm__ __volatile__ ("lock; xaddl %0, %1"
    : "+r" (increment), "+m" (*ptr)
    : : "memory");
    /* increment now holds the old value of *ptr */
    return increment;
}

extern inline int android_atomic_cas(int32_t old_value, int32_t new_value,
                                     volatile int32_t *ptr) {
    int32_t prev;
    __asm__ __volatile__ ("lock; cmpxchgl %1, %2"
    : "=a" (prev)
    : "q" (new_value), "m" (*ptr), "0" (old_value)
    : "memory");
    return prev != old_value;
}

extern inline int32_t android_atomic_inc(volatile int32_t *addr) {
    return android_atomic_add(1, addr);
}

extern inline int32_t android_atomic_dec(volatile int32_t *addr) {
    return android_atomic_add(-1, addr);
}

extern inline int android_atomic_release_cas(int32_t old_value,
                                             int32_t new_value,
                                             volatile int32_t *ptr) {
    /* Stores are not reordered with other stores. */
    return android_atomic_cas(old_value, new_value, ptr);
}

extern inline int32_t android_atomic_or(int32_t value, volatile int32_t *ptr) {
    int32_t prev, status;
    do {
        prev = *ptr;
        status = android_atomic_cas(prev, prev | value, ptr);
    } while (__builtin_expect(status != 0, 0));
    return prev;
}

#define android_atomic_cmpxchg android_atomic_release_cas

#ifdef __cplusplus
} // extern "C"
#endif

#endif //C_ADVENTURE_ATOMIC_X86_H
