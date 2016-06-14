#if defined X86_64

static inline sint32 attr_always_inline
avl_tree_height_opt(struct avl_tree *tree)
{
    sint32 height;

    asm volatile (
        "mov    $0xffffffff, %0\n\t" \
        "cmp    $0x0,        %1\n\t" \
        "cmovz  %%rsp,       %1\n\t" \
        // cmov can tell invalid memory
        "cmovne 0x0(%1),     %0\n\t"
        :"=&r"(height)
        :"r"(tree));
        /*
         * &: means earlyclobber operand, will be modified before
         *    instruction finished. Therefore, this operand cannot
         *    be lie in an input operand.
         */

    assert(avl_tree_height_opt_validity_p(tree, height));

    return height;
}

#endif

#if defined X86_32

static inline sint32 attr_always_inline
avl_tree_height_opt(struct avl_tree *tree)
{
    sint32 height;

    asm volatile (
        "mov    $0xffffffff, %0\n\t" \
        "cmp    $0x0,        %1\n\t" \
        "cmovz  %%esp,       %1\n\t" \
        // cmov can tell invalid memory
        "cmovne 0x0(%1),     %0\n\t"
        :"=&r"(height)
        :"r"(tree));
        /*
         * &: means earlyclobber operand, will be modified before
         *    instruction finished. Therefore, this operand cannot
         *    be lie in an input operand.
         */

    assert(avl_tree_height_opt_validity_p(tree, height));

    return height;
}

#endif

