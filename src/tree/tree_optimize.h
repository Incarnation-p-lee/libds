#ifndef HAVE_TREE_OPTIMIZE_H
#define HAVE_TREE_OPTIMIZE_H

#if defined X86_64
    /*
     * if (!node) {
     *     return -1;
     * } else {
     *     return node->height;
     * }
     */
    #define avl_tree_height_internal_optimize(node, height) \
        asm volatile (                                      \
            "mov $0xffffffff, %0\n\t"                       \
            "cmp        $0x0, %1\n\t"                       \
            "cmovz     %%rsp, %1\n\t"                       \
            "cmovne  0x0(%1), %0\n\t"                       \
            :"=&r"(height)                                  \
            :"r"(node))
            /*
             * &: means earlyclobber operand, will be modified before
             *    instruction finished. Therefore, this operand cannot
             *    be lie in an input operand.
             */

    /*
     * 1. Compute height of left node and put it to edi
     * 2. Compute height of right node and put it to esi
     * 3. Compute abs(edi - esi), and write back to eax
     */
    #define avl_tree_node_balanced_optimize(node, balanced) \
        asm volatile (                                      \
            "mov $0xffffffff, %%ecx\n\t"                    \
            /* left node height */                          \
            "mov 0x18(%0), %%rdi\n\t"                       \
            "cmp $0x0, %%rdi\n\t"                           \
            "cmove %1, %%rdi\n\t"                           \
            "cmovne -0x8(%%rdi), %%edi\n\t"                 \
            "cmove %%ecx, %%edi\n\t"                        \
            /* left node height */                          \
            "mov 0x20(%0), %%rsi\n\t"                       \
            "cmp $0x0, %%rsi\n\t"                           \
            "cmove %1, %%rsi\n\t"                           \
            "cmovne -0x8(%%rsi), %%esi\n\t"                 \
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

    /*
     * 1. If NULL == node, avl = NULL
     * 2. Or avl = node - 0x8
     */
    #define avl_tree_ptr_binary_to_avl_optimize(node, avl) \
        asm volatile (                                     \
            "mov $0x0, %%rdx\n\t"                          \
            "lea -0x8(%1), %1\n\t"                         \
            "cmp $0x8, %1\n\t"                             \
            "cmovl %%rdx, %1\n\t"                          \
            "mov %1, %0\n\t"                               \
            :"=r"(avl)                                     \
            :"r"(node)                                     \
            :"rdx")

    /*
     * assert node should be (struct avl_tree *)
     * 1. load node->alias.left to %1
     * 2. If NULL == %1, left = NULL
     * 3. Or left = %1 - 8
     */
    #define avl_tree_left_optimize(node, left) \
        asm volatile (                         \
            "mov $0x0, %%rdx\n\t"              \
            "mov 0x18(%1), %1\n\t"             \
            "lea -0x8(%1), %1\n\t"             \
            "cmp $0x8, %1\n\t"                 \
            "cmovl %%rdx, %1\n\t"              \
            "mov %1, %0\n\t"                   \
            :"=r"(left)                        \
            :"r"(node)                         \
            :"rdx")

    /*
     * the same as left
     */
    #define avl_tree_right_optimize(node, right) \
        asm volatile (                           \
            "mov $0x0, %%rdx\n\t"                \
            "mov 0x20(%1), %1\n\t"               \
            "lea -0x8(%1), %1\n\t"               \
            "cmp $0x8, %1\n\t"                   \
            "cmovl %%rdx, %1\n\t"                \
            "mov %1, %0\n\t"                     \
            :"=r"(right)                         \
            :"r"(node)                           \
            :"rdx")

    /*
     * 1. node->nice => rbx, *iter => rcx.
     * 2. compare rbx, and 0x8(rcx).
     * 3. update iter.
     * slower than gcc -O3 build, disable this macro for now.
     */
    #define binary_search_tree_insert_path_go_through(node, iter) \
        asm volatile (                                            \
            "mov $0x18, %%rax\n\t"                                \
            "mov $0x20, %%rdx\n\t"                                \
            "loop1:\n\t" \
            "mov 0x8(%1), %%rbx\n\t"                              \
            "mov (%0), %%rcx\n\t"                                 \
            "cmp 0x8(%%rcx), %%rbx\n\t"                           \
            "jz BREAK\n\t" \
            "cmovg %%rdx, %%rax\n\t"                              \
            "lea (%%rcx, %%rax), %0\n\t"                          \
            "mov (%0), %%rcx\n\t" \
            "cmp $0x0, %%rcx\n\t"                           \
            "jnz loop1\n\t" \
            "BREAK:\n\t" \
            :"+r"(iter)                                           \
            :"r"(node)                                            \
            :"rax", "rbx", "rcx", "rdx")
#endif

#if defined X86_32
    /*
     * if (!node) {
     *     return -1;
     * } else {
     *     return node->height;
     * }
     */
    #define avl_tree_height_internal_optimize(node, height) \
        asm volatile (                                      \
            "mov $0xffffffff, %0\n\t"                       \
            "cmp        $0x0, %1\n\t"                       \
            "cmovz     %%esp, %1\n\t"                       \
            "cmovne  0x0(%1), %0\n\t"                       \
            :"=&r"(height)                                  \
            :"r"(node))

    /*
     * 1. Compute height of left node and put it to edi
     * 2. Compute height of right node and put it to esi
     * 3. Compute abs(edi - esi), and write back to eax
     */
    #define avl_tree_node_balanced_optimize(node, balanced) \
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
    /*
     * 1. If NULL == node, avl = NULL
     * 2. Or avl = node - 0x8
     */
    #define avl_tree_ptr_binary_to_avl_optimize(node, avl) \
        asm volatile (                                     \
            "mov $0x0, %%edx\n\t"                          \
            "lea -0x4(%1), %1\n\t"                         \
            "cmp $0x4, %1\n\t"                             \
            "cmovl %%edx, %1\n\t"                          \
            "mov %1, %0\n\t"                               \
            :"=r"(avl)                                     \
            :"r"(node)                                     \
            :"edx")

#endif

#endif
