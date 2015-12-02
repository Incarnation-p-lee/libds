#ifndef HAVE_DEFINED_HEAP_OPTIMIZE_H
#define HAVE_DEFINED_HEAP_OPTIMIZE_H

#if defined X86_64
    /*
     * if (NULL = node) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(node, struct leftist_heap, alias);
     * }
     */
    #define leftist_heap_ptr_binary_to_leftist_optimize(node, leftist) \
        asm volatile (                                                 \
            "mov       $0, %0\n\t"                                     \
            "lea -0x8(%1), %%rbx\n\t"                                  \
            "cmp     $0x8, %%rbx\n\t"                                  \
            "cmovl  %%rbx, %0\n\t"                                     \
            :"=&r"(leftist)                                            \
            :"r"(node)                                                 \
            :"rbx")

    /*
     * struct binary_search_tree *left = node->alias.left;
     *
     * if (NULL == left) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(left, struct leftist_heap, alias);
     * }
     */
    #define leftist_heap_left_optimize(node, left) \
        asm volatile (                             \
            "mov          $0,    %0\n\t"           \
            "mov    0x18(%1), %%rdx\n\t"           \
            "lea -0x8(%%rdx), %%rdx\n\t"           \
            "cmp        $0x8, %%rdx\n\t"           \
            "cmovl     %%rdx,    %0\n\t"           \
            :"=&r"(left)                           \
            :"r"(node)                             \
            :"rdx")

    /*
     * struct binary_search_tree *right = node->alias.right;
     *
     * if (NULL == right) {
     *     return NULL;
     * } else {
     *     return CONTAINER_OF(left, struct leftist_heap, alias);
     * }
     */
    #define leftist_heap_right_optimize(node, left) \
        asm volatile (                              \
            "mov          $0,    %0\n\t"            \
            "mov    0x20(%1), %%rdx\n\t"            \
            "lea -0x8(%%rdx), %%rdx\n\t"            \
            "cmp        $0x8, %%rdx\n\t"            \
            "cmovl     %%rdx,    %0\n\t"            \
            :"=&r"(left)                            \
            :"r"(node)                              \
            :"rdx")

    /*
     * if (NULL == node) {
     *     return -1;
     * } else {
     *     return node->npl;
     * }
     */
    #define leftist_heap_npl_optimize(node, npl) \
        asm volatile (                           \
            "mov   $0xffffffff, %0\n\t"          \
            "cmp          $0x0, %1\n\t"          \
            "cmovz       %%rsp, %%rdx\n\t"       \
            "cmovnz 0x0(%%rdx), %0\n\t"          \
            :"=&r"(npl)                          \
            :"r"(node)                           \
            :"rdx")

#endif


#endif

