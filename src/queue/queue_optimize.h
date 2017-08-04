#ifndef HAVE_DEFINED_QUEUE_OPTIMIZE_H
#define HAVE_DEFINED_QUEUE_OPTIMIZE_H

#if defined X86_64
    #define ARRAY_QUEUE_ENTER_I(queue, member)                             \
        asm volatile (                                                     \
            "mov          0x10(%0), %%rcx\n\t"   /* rear => %%rcx */       \
            "mov                %1, (%%rcx)\n\t" /* *rear = member */      \
            "lea        0x8(%%rcx), %%rcx\n\t"   /* rear++ */              \
            "mov           0x4(%0), %%ebx\n\t"                             \
            "mov             %%ebx, %%edx\n\t"   /* dim => %%edx */        \
            "mov          0x18(%0), %%rbx\n\t"   /* base => %%rbx */       \
            "lea (%%rbx, %%rdx, 8), %%rdx\n\t"   /* base + dim => %%rdx */ \
            "cmp             %%rdx, %%rcx\n\t"   /* rear == base +dim ? */ \
            "cmove           %%rbx, %%rcx\n\t"                             \
            "mov             %%rcx, 0x10(%0)\n\t"                          \
            "decl             (%0)\n\t"          /* rest-- */              \
            :                                                              \
            :"r"(queue), "r"(member)                                       \
            :"rbx", "rcx", "rdx")

    #define ARRAY_QUEUE_LEAVE_I(queue, val)                                 \
        asm volatile (                                                      \
            "mov           0x8(%1), %%rcx\n\t"   /* front => %%rcx */       \
            "mov           (%%rcx), %0\n\t"      /* val = *front */         \
            "lea        0x8(%%rcx), %%rcx\n\t"   /* front++ */              \
            "mov           0x4(%1), %%ebx\n\t"                              \
            "mov             %%ebx, %%edx\n\t"   /* dim => %%edx */         \
            "mov          0x18(%1), %%rbx\n\t"   /* base => %%rbx */        \
            "lea (%%rbx, %%rdx, 8), %%rdx\n\t"   /* base + dim => %%rdx */  \
            "cmp             %%rdx, %%rcx\n\t"   /* front == base +dim ? */ \
            "cmove           %%rbx, %%rcx\n\t"                              \
            "mov             %%rcx, 0x8(%1)\n\t" /* %%rcx => front */       \
            "incl             (%1)\n\t"          /* rest++ */               \
            :"=&r"(val)                                                     \
            :"r"(queue)                                                     \
            :"rbx", "rcx", "rdx")

#endif

#endif
