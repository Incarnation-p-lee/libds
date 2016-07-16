#define HEIGHT_OFFSET          (ptr_t)(&((struct avl_tree *)0)->height)
#define LEFT_OFFSET            (ptr_t)(&((struct avl_tree *)0)->left)
#define RIGHT_OFFSET           (ptr_t)(&((struct avl_tree *)0)->right)

#if defined X86_64

static inline sint32 attr_always_inline
avl_tree_height_opt(struct avl_tree *tree)
{
    sint32 height;

    asm volatile (
        "add          %2, %1\n\t" \
        "mov $0xffffffff, %0\n\t" \
        "cmp          %2, %1\n\t" \
        // cmov can tell invalid memory
        "cmove     %%rsp, %1\n\t" \
        "cmovne     (%1), %0\n\t"
        :"=&r"(height)
        :"r"(tree), "i"(HEIGHT_OFFSET));
        /*
         * &: means earlyclobber operand, will be modified before
         *    instruction finished. Therefore, this operand cannot
         *    be lie in an input operand.
         */

    assert_exit(avl_tree_height_opt_validity_p(tree, height));

    return height;
}

#endif

#if defined X86_32

static inline sint32 attr_always_inline
avl_tree_height_opt(struct avl_tree *tree)
{
    sint32 height;

    asm volatile (
        "add          %2, %1\n\t" \
        "mov $0xffffffff, %0\n\t" \
        "cmp          %2, %1\n\t" \
        // cmov can tell invalid memory
        "cmovz     %%esp, %1\n\t" \
        "cmovne     (%1), %0\n\t"
        :"=&r"(height)
        :"r"(tree), "i"(HEIGHT_OFFSET));
        /*
         * &: means earlyclobber operand, will be modified before
         *    instruction finished. Therefore, this operand cannot
         *    be lie in an input operand.
         */

    assert_exit(avl_tree_height_opt_validity_p(tree, height));

    return height;
}

#endif

static inline sint32 attr_always_inline
avl_tree_height_balanced_opt_p(struct avl_tree *tree)
{
    bool balanced;
    sint32 left;
    sint32 right;

    assert_exit(avl_tree_structure_legal_p(tree));

    left = avl_tree_height_opt(tree->left);
    right = avl_tree_height_opt(tree->right);

    asm volatile (
        // abs(left - right)
        "mov            %1, %%eax\n\t" \
        "mov            %2, %%ecx\n\t" \
        "sub         %%ecx, %%eax\n\t" \
        "mov         %%eax, %%ecx\n\t" \
        "sar         $0x1f, %%ecx\n\t" \
        "add         %%ecx, %%eax\n\t" \
        "xor         %%ecx, %%eax\n\t" \
        // return true or false
        "xor         %%ecx, %%ecx\n\t" \
        "mov          $0x1, %0\n\t"    \
        "cmp          $0x1, %%eax\n\t" \
        "cmovg       %%ecx, %0\n\t"
        :"=r"(balanced)
        :"m"(left), "m"(right)
        :"eax", "ecx");

    assert_exit(avl_tree_balanced_optimize_validity_p(tree, balanced));

    return balanced;
}

#undef HEIGHT_OFFSET
#undef LEFT_OFFSET
#undef RIGHT_OFFSET

