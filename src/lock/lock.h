#ifndef HAVE_LOCK_H
#define HAVE_LOCK_H

#define SPIN_LOCK_VAL_MAX      1
#define SPIN_LOCK_UNLOCKED     0

#if defined(X86_64)
    #define SPIN_LOCK_TRY(spin_lock)     SPIN_LOCK_TRY_X64(spin_lock)

    #define SPIN_LOCK_TRY_X64(spin_lock) \
        asm volatile (                   \
            "mov        $0x1, %%edx\n\t" \
            "LOOP:                 \n\t" \
            "mov        $0x0, %%eax\n\t" \
            "lock;cmpxchg %0, %%edx\n\t" \
            "jz END                \n\t" \
            "pause                 \n\t" \
            "jmp LOOP              \n\t" \
            "END:                  \n\t" \
            :"+m"(spin_lock->lock)
            :
            :"eax", "edx")

#endif

#endif

