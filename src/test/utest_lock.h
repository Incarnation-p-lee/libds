#ifndef HAVE_UTEST_LOCK_H
#define HAVE_UTEST_LOCK_H

#define LOCK_THREAD_MAX        100
#define LOOP_COUNT             1000000
#define LOCK_MARK              1

typedef struct spin_lock_sample s_spin_lock_sample_t;
typedef struct semaphore_sample s_semaphore_sample_t;
typedef struct mutex_sample     s_mutex_sample_t;

struct spin_lock_sample {
    uint32        idx;
    s_spin_lock_t *lock;
};

struct semaphore_sample {
    uint32        idx;
    s_semaphore_t *semaphore;
};

struct mutex_sample {
    uint32    idx;
    s_mutex_t *mutex;
};

static uint32 critical_section[LOCK_THREAD_MAX];

#endif

