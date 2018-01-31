#ifndef HAVE_LOCK_H
#define HAVE_LOCK_H

#define SPIN_LOCK_VAL_MAX      1
#define SPIN_LOCK_UNLOCKED     0
#define SPIN_LOCK_LOCKED       1

#define SPIN_LOCK_SUCCESS      0
#define SPIN_LOCK_FAIL         1

#define SPIN_SHARED_LOCK(s)            (s)->shared_lock
#define SEMAPHORE_VAL(s)               (s)->val
#define SEMAPHORE_LOCK(s)              (&(s)->lock)
#define SEMAPHORE_SLEEP_QUEUE(s)       (s)->sleep_queue
#define SEMAPHORE_ACT_NEW(s)           (&(s)->act_new)
#define SEMAPHORE_ACT_OLD(s)           (&(s)->act_old)
#define MUTEX_SEMAPHORE(m)             ((m)->semaphore)

#if defined(DEBUG)
    #define SPIN_LOCK_LEGAL_P(s)       spin_lock_legal_ip(s)
    #define SPIN_LOCK_ILLEGAL_P(s)     spin_lock_illegal_ip(s)
    #define SEMAPHORE_LEGAL_P(s)       semaphore_legal_ip(s)
    #define SEMAPHORE_ILLEGAL_P(s)     semaphore_illegal_ip(s)
    #define MUTEX_LEGAL_P(s)           mutex_legal_ip(s)
    #define MUTEX_ILLEGAL_P(s)         mutex_illegal_ip(s)
#else
    #define SPIN_LOCK_LEGAL_P(s)       NON_NULL_PTR_P(s)
    #define SPIN_LOCK_ILLEGAL_P(s)     NULL_PTR_P(s)
    #define SEMAPHORE_LEGAL_P(s)       NON_NULL_PTR_P(s)
    #define SEMAPHORE_ILLEGAL_P(s)     NULL_PTR_P(s)
    #define MUTEX_LEGAL_P(s)           NON_NULL_PTR_P(s)
    #define MUTEX_ILLEGAL_P(s)         NULL_PTR_P(s)
#endif

#if defined(X86_64)
    #define SPIN_LOCK(l)               SPIN_LOCK_X64(l)
    #define SPIN_LOCK_TRY(l, s)        SPIN_LOCK_TRY_X64(l, s)

    #define SPIN_LOCK_X64(lock)             \
        asm volatile (                      \
            "mov           $0x1, %%edx\n\t" \
            "LOOP:                    \n\t" \
            "mov           $0x0, %%eax\n\t" \
            "lock;cmpxchg %%edx, %0\n\t"    \
            "jz END                \n\t"    \
            "pause                 \n\t"    \
            "jmp LOOP              \n\t"    \
            "END:                  \n\t"    \
            :"+m"(lock->shared_lock)        \
            :                               \
            :"eax", "edx")

    /* The status is a stack variable, for thread safy */
    #define SPIN_LOCK_TRY_X64(lock, status)        \
        asm volatile (                             \
            "mov           $0x1, %%edx\n\t"        \
            "mov           $0x0, %%eax\n\t"        \
            "lock;cmpxchg %%edx, %0\n\t"           \
            "mov          %%eax, %1\n\t"           \
            :"+m"(lock->shared_lock), "=m"(status) \
            :                                      \
            :"eax", "edx")

    #define SEMAPHORE_DOWN(semaphore)    SEMAPHORE_DOWN_X64(semaphore)

    #define SEMAPHORE_DOWN_X64(lock) \
        asm volatile (               \
            "lock;decl %0\n\t"       \
            :"+m"(semaphore->val)    \
            :                        \
            :)

    #define SEMAPHORE_UP(semaphore)      SEMAPHORE_UP_X64(semaphore)

    #define SEMAPHORE_UP_X64(lock) \
        asm volatile (             \
            "lock;incl %0\n\t"     \
            :"+m"(semaphore->val)  \
            :                      \
            :)

#endif

extern s_array_queue_t * array_queue_create(void);
extern void array_queue_enter(s_array_queue_t *queue, void *member);
extern void array_queue_destroy(s_array_queue_t **queue);
extern void * array_queue_leave(s_array_queue_t *queue);
extern bool array_queue_structure_illegal_p(s_array_queue_t *queue);

#endif

