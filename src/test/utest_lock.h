#ifndef HAVE_UTEST_LOCK_H
#define HAVE_UTEST_LOCK_H

#define LOCK_THREAD_MAX        1000
#define LOOP_COUNT             10000

typedef struct spin_lock_sample s_spin_lock_sample_t;

struct spin_lock_sample {
    uint32        idx;
    s_spin_lock_t *spin_lock;
};

static uint32 critical_section[LOCK_THREAD_MAX + 1];

#endif

