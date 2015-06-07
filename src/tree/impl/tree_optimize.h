#ifndef HAVE_TREE_OPTIMIZE_H
#define HAVE_TREE_OPTIMIZE_H

#if defined X86_64
    /*
     * 1. If node == NULL, fake a valid address for cmovne with edx unchanged
     * 2. If node != NULL, %0 unchanged, will load correct value tp edx
     * 3. TAKE care of 0x10 offset, changed structure avl_tree may effect on this value.
     */
    #define avl_tree_height_internal_optimize(node, height) \
        asm volatile (                                      \
            "mov $0xffffffff, %%edx\n\t"                    \
            "cmp $0x0, %0\n\t"                              \
            "cmovz %1, %0\n\t"                              \
            "cmovne 0x10(%0), %%edx\n\t"                    \
            "mov %%edx, (%1)\n\t"                           \
            :                                               \
            :"r"(node), "r"(height)                         \
            :"edx")

    /*
     * 1. Compute height of left node and put it to edi
     * 2. Compute height of right node and put it to esi
     * 3. Compute abs(edi - esi), and write back to eax
     */
    #define avl_tree_balanced_on_height_internal_optimize(node, balanced) \
        asm volatile (                                      \
            "mov $0xffffffff, %%ecx\n\t"                    \
            /* left node height */                          \
            "mov 0x18(%0), %%rdi\n\t"                       \
            "cmp $0x0, %%rdi\n\t"                           \
            "cmove %1, %%rdi\n\t"                           \
            "cmovne 0x10(%%rdi), %%edi\n\t"                 \
            "cmove %%ecx, %%edi\n\t"                        \
            /* left node height */                          \
            "mov 0x20(%0), %%rsi\n\t"                       \
            "cmp $0x0, %%rsi\n\t"                           \
            "cmove %1, %%rsi\n\t"                           \
            "cmovne 0x10(%%rsi), %%esi\n\t"                 \
            "cmove %%ecx, %%esi\n\t"                        \
            /* initial const variable */                    \
            "mov $0x0, %%ebx\n\t"                           \
            "mov $0x1, %%eax\n\t"                           \
            /* compute abs of (left - right) */             \
            "sub %%esi, %%edi\n\t"                          \
            "mov %%edi, %%esi\n\t"                          \
            "and $0x80000000, %%esi\n\t"                    \
            "cmovz %%ebx, %%ecx\n\t"                        \
            "xor %%ecx, %%edi\n\t"                          \
            "shr $0x1f, %%ecx\n\t"                          \
            "add %%ecx, %%edi\n\t"                          \
            "cmp %%eax, %%edi\n\t"                          \
            "cmovg %%ebx, %%eax\n\t"                        \
            "mov %%eax, (%1)\n\t"                           \
            :                                               \
            :"r"(node), "r"(balanced)                       \
            :"edx", "eax", "rsi", "rdi", "ecx", "ebx")

#endif

#if defined X86
    /*
     * If node == NULL, fake a valid address for cmovne with edx unchanged
     * If node != NULL, %0 unchanged, will load correct value tp edx
     * TAKE care of 0x10 offset, changed structure avl_tree may effect on this value.
     */
    #define avl_tree_height_internal_optimize(node, height) \
        asm volatile (                                      \
            "mov $0xffffffff, %%edx\n\t"                    \
            "cmp $0x0, %0\n\t"                              \
            "cmovz %1, %0\n\t"                              \
            "cmovne 0x10(%0), %%edx\n\t"                    \
            "mov %%edx, (%1)\n\t"                           \
            :                                               \
            :"r"(node), "r"(height)                         \
            :"edx")

    /*
     * 1. Compute height of left node and put it to edi
     * 2. Compute height of right node and put it to esi
     * 3. Compute abs(edi - esi), and write back to eax
     */
    #define avl_tree_balanced_on_height_internal_optimize(node, balanced) \
        asm volatile (                                      \
            "mov $0xffffffff, %%ecx\n\t"                    \
            /* left node height */                          \
            "mov 0x18(%0), %%edi\n\t"                       \
            "cmp $0x0, %%edi\n\t"                           \
            "cmove %1, %%edi\n\t"                           \
            "cmovne 0x10(%%edi), %%edi\n\t"                 \
            "cmove %%ecx, %%edi\n\t"                        \
            /* left node height */                          \
            "mov 0x1c(%0), %%esi\n\t"                       \
            "cmp $0x0, %%esi\n\t"                           \
            "cmove %1, %%esi\n\t"                           \
            "cmovne 0x10(%%esi), %%esi\n\t"                 \
            "cmove %%ecx, %%esi\n\t"                        \
            /* initial const variable */                    \
            "mov $0x0, %%ebx\n\t"                           \
            "mov $0x1, %%eax\n\t"                           \
            /* compute abs of (left - right) */             \
            "sub %%esi, %%edi\n\t"                          \
            "mov %%edi, %%esi\n\t"                          \
            "and $0x80000000, %%esi\n\t"                    \
            "cmovz %%ebx, %%ecx\n\t"                        \
            "xor %%ecx, %%edi\n\t"                          \
            "shr $0x1f, %%ecx\n\t"                          \
            "add %%ecx, %%edi\n\t"                          \
            "cmp %%eax, %%edi\n\t"                          \
            "cmovg %%ebx, %%eax\n\t"                        \
            "mov %%eax, (%1)\n\t"                           \
            :                                               \
            :"r"(node), "r"(balanced)                       \
            :"edx", "eax", "esi", "edi", "ecx", "ebx")

#endif

#if defined OPT_HOT
    #define avl_tree_height_internal(node, height) \
         avl_tree_height_internal_optimize(node, height)

    #define avl_tree_child_height_sync(root, left, right)

    #define avl_tree_balanced_on_height_internal(node, b) \
        avl_tree_balanced_on_height_internal_optimize(node, b)
#else
    #define avl_tree_height_internal(node, height) \
        avl_tree_height_internal_default(node, height)

    #define avl_tree_child_height_sync(root, left, right) \
        avl_tree_child_height_sync_with_calculated(root, left, right)

    #define avl_tree_balanced_on_height_internal(node, b) \
        avl_tree_balanced_on_height_internal_default(node, b)
#endif

#endif
