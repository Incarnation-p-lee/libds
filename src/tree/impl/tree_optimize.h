#ifndef HAVE_TREE_OPTIMIZE_H
#define HAVE_TREE_OPTIMIZE_H


#if defined X86_64
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
#endif

#if defined OPT_HOT
    #define avl_tree_height_internal(node, height) \
         avl_tree_height_internal_optimize(node, height)
#else
    #define avl_tree_height_internal(node, height) \
        avl_tree_height_internal_default(node, height)
#endif

#endif
