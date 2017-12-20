#ifndef HAVE_LOCK_H
#define HAVE_LOCK_H

#define SPIN_LOCK_VAL_MAX      1
#define SPIN_LOCK_UNLOCKED     0
#define SPIN_LOCK_LOCKED       1

#if defined(DEBUG)
    #define SPIN_LOCK_LEGAL_P(s)       spin_lock_legal_ip(s)
    #define SPIN_LOCK_ILLEGAL_P(s)     spin_lock_illegal_ip(s)
#else
    #define SPIN_LOCK_LEGAL_P(s)       NON_NULL_PTR_P(s)
    #define SPIN_LOCK_ILLEGAL_P(s)     NULL_PTR_P(s)
#endif

#if defined(X86_64)
    #define SPIN_LOCK_TRY(spin_lock)     SPIN_LOCK_TRY_X64(spin_lock)

    #define SPIN_LOCK_TRY_X64(spin_lock)    \
        asm volatile (                      \
            "mov           $0x1, %%edx\n\t" \
            "LOOP:                    \n\t" \
            "mov           $0x0, %%eax\n\t" \
            "lock;cmpxchg %%edx, %0\n\t"    \
            "jz END                \n\t"    \
            "pause                 \n\t"    \
            "jmp LOOP              \n\t"    \
            "END:                  \n\t"    \
            :"+m"(spin_lock->shared_lock)   \
            :                               \
            :"eax", "edx")

#endif

#endif

