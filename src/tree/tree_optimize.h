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
             * &: means earlyclobber opedp_rand, will be modified before
             *    instruction finished. Therefore, this opedp_rand cannot
             *    be lie in an input operand.
             */

    /*
     * sint32 left;
     * sint32 right;
     *
     * left = avl_tree_height_internal(avl_tree_left(node));
     * right = avl_tree_height_internal(avl_tree_right(node));
     *
     * if (abs_sint32(left - right) > 1) {
     *     return false;
     * } else {
     *     return true;
     * }
     */
    #define avl_tree_node_balanced_optimize(node, balanced) \
        asm volatile (                                      \
            /* left node height in %%edx */                 \
            "mov       0x18(%1), %%rbx\n\t"                 \
            "cmp           $0x0, %%rbx\n\t"                 \
            "mov    $0xffffffff, %%edx\n\t"                 \
            "cmove        %%rsp, %%rbx\n\t"                 \
            "cmovne -0x8(%%rbx), %%edx\n\t"                 \
            /* right node height in %%ecx */                \
            "mov       0x20(%1), %%rbx\n\t"                 \
            "cmp           $0x0, %%rbx\n\t"                 \
            "mov    $0xffffffff, %%ecx\n\t"                 \
            "cmove        %%rsp, %%rbx\n\t"                 \
            "cmovne -0x8(%%rbx), %%ecx\n\t"                 \
            /* abs(left - right) */                         \
            "sub          %%ecx, %%edx\n\t"                 \
            "mov          %%edx, %%ecx\n\t"                 \
            "sar          $0x1f, %%ecx\n\t"                 \
            "add          %%ecx, %%edx\n\t"                 \
            "xor          %%ecx, %%edx\n\t"                 \
            /* return true or false */                      \
            "cmp           $0x1, %%edx\n\t"                 \
            "mov           $0x0, %%ecx\n\t"                 \
            "mov           $0x1, %0\n\t"                    \
            "cmovg        %%ecx, %0\n\t"                    \
            :"=r"(balanced)                                 \
            :"r"(node)                                      \
            :"rbx", "edx", "ecx")

    /*
     * if (NULL == node) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(node, struct avl_tree, alias);
     * }
     */
    #define avl_tree_ptr_binary_to_avl_optimize(node, avl) \
        asm volatile (                                     \
            "lea -0x8(%1), %%rdx\n\t"                      \
            "cmp     $0x8, %%rdx\n\t"                      \
            "mov     $0x0, %0\n\t"                         \
            "cmovg  %%rdx, %0\n\t"                         \
            :"=r"(avl)                                     \
            :"r"(node)                                     \
            :"rdx")

    /*
     * struct binary_search_tree *left = node->alias.left;
     *
     * if (NULL == left) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(left, struct avl_tree, alias);
     * }
     */
    #define avl_tree_left_optimize(node, left) \
        asm volatile (                         \
            "mov    0x18(%1), %%rdx\n\t"       \
            "lea -0x8(%%rdx), %%rdx\n\t"       \
            "mov        $0x0, %0\n\t"          \
            "cmp        $0x8, %%rdx\n\t"       \
            "cmovg     %%rdx, %0\n\t"          \
            :"=r"(left)                        \
            :"r"(node)                         \
            :"rdx")

    /*
     * the same as left
     */
    #define avl_tree_right_optimize(node, right) \
        asm volatile (                           \
            "mov    0x20(%1), %%rdx\n\t"         \
            "lea -0x8(%%rdx), %%rdx\n\t"         \
            "mov        $0x0, %0\n\t"            \
            "cmp        $0x8, %%rdx\n\t"         \
            "cmovg     %%rdx, %0\n\t"            \
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
     * sint32 left;
     * sint32 right;
     *
     * left = avl_tree_height_internal(avl_tree_left(node));
     * right = avl_tree_height_internal(avl_tree_right(node));
     *
     * if (abs_sint32(left - right) > 1) {
     *     return false;
     * } else {
     *     return true;
     * }
     */
    #define avl_tree_node_balanced_optimize(node, balanced) \
        asm volatile (                                      \
            /* left node height in %%edx */                 \
            "mov       0x10(%1), %%ebx\n\t"                 \
            "cmp           $0x0, %%ebx\n\t"                 \
            "mov    $0xffffffff, %%edx\n\t"                 \
            "cmove        %%esp, %%ebx\n\t"                 \
            "cmovne -0x4(%%ebx), %%edx\n\t"                 \
            /* right node height in %%ecx */                \
            "mov       0x14(%1), %%ebx\n\t"                 \
            "cmp           $0x0, %%ebx\n\t"                 \
            "mov    $0xffffffff, %%ecx\n\t"                 \
            "cmove        %%esp, %%ebx\n\t"                 \
            "cmovne -0x4(%%ebx), %%ecx\n\t"                 \
            /* abs(left - right) */                         \
            "sub          %%ecx, %%edx\n\t"                 \
            "mov          %%edx, %%ecx\n\t"                 \
            "sar          $0x1f, %%ecx\n\t"                 \
            "add          %%ecx, %%edx\n\t"                 \
            "xor          %%ecx, %%edx\n\t"                 \
            /* return true or false */                      \
            "cmp           $0x1, %%edx\n\t"                 \
            "mov           $0x0, %%ecx\n\t"                 \
            "mov           $0x1, %0\n\t"                    \
            "cmovg        %%ecx, %0\n\t"                    \
            :"=r"(balanced)                                 \
            :"r"(node)                                      \
            :"ebx", "edx", "ecx")

    /*
     * if (NULL == node) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(node, struct avl_tree, alias);
     * }
     */
    #define avl_tree_ptr_binary_to_avl_optimize(node, avl) \
        asm volatile (                                     \
            "lea -0x4(%1), %%edx\n\t"                      \
            "cmp     $0x4, %%edx\n\t"                      \
            "mov     $0x0, %0\n\t"                         \
            "cmovg  %%rdx, %0\n\t"                         \
            :"=r"(avl)                                     \
            :"r"(node)                                     \
            :"edx")

    /*
     * struct binary_search_tree *left = node->alias.left;
     *
     * if (NULL == left) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(left, struct avl_tree, alias);
     * }
     */
    #define avl_tree_left_optimize(node, left) \
        asm volatile (                         \
            "mov    0x10(%1), %%edx\n\t"       \
            "lea -0x4(%%edx), %%edx\n\t"       \
            "mov        $0x0, %0\n\t"          \
            "cmp        $0x4, %%edx\n\t"       \
            "cmovg     %%edx, %0\n\t"          \
            :"=r"(left)                        \
            :"r"(node)                         \
            :"edx")

    /*
     * the same as left
     */
    #define avl_tree_right_optimize(node, right) \
        asm volatile (                           \
            "mov    0x14(%1), %%edx\n\t"         \
            "lea -0x4(%%edx), %%edx\n\t"         \
            "mov        $0x0, %0\n\t"            \
            "cmp        $0x4, %%edx\n\t"         \
            "cmovg     %%edx, %0\n\t"            \
            :"=r"(right)                         \
            :"r"(node)                           \
            :"edx")

#endif

#endif
