uint32
binary_indexed_tree_size(struct binary_indexed_tree *tree)
{
    return tree->size;
}

sint64
binary_indexed_tree_value(struct binary_indexed_tree *tree, uint32 number)
{
    return tree->data[number];
}

/*
 * Generate tree->data with DP.
 * For example: number 24 = 11000B
 *     24 = 11000B
 *        = 10111B
 *        + 10110B
 *        + 10100B
 * Iteration:
 * msk 1111110B
 * raw XXX1000B
 * b   XXX0111B
 * ...
 * e   XXX0100B
 */
struct binary_indexed_tree *
binary_indexed_tree_create(sint64 *data, uint32 size)
{
    uint32 i;
    uint32 base;
    uint32 mask;
    struct binary_indexed_tree *tree;

    if (complain_null_pointer_p(data)) {
        return NULL;
    } else if (complain_zero_size_p(size)) {
        return NULL;
    } else {
        tree = memory_cache_allocate(sizeof(*tree));
        tree->size = size;
        tree->data = memory_cache_allocate(sizeof(*tree->data) * (size + 1));
        memset(tree->data, 0, sizeof(*tree->data) * (size + 1));

        i = 2;
        tree->data[1] = data[0];

        while (i <= size) {
            tree->data[i] = data[i - 1];
            if (0 == i % 2) {
                base = i - 1;
                mask = 0xfffffffe;

                while (0 == (i & ~mask)) {
                    tree->data[i] += tree->data[base];
                    base = base & mask;
                    mask = mask << 1;
                }
            }
            i++;
        }

        return tree;
    }
}

void
binary_indexed_tree_destroy(struct binary_indexed_tree **tree)
{
    struct binary_indexed_tree *tmp;

    if (complain_null_pointer_p(tree)) {
        return;
    } else if (binary_indexed_tree_structure_legal_p(*tree)) {
        tmp = *tree;
        *tree = NULL;

        memory_cache_dp_free(tmp->data);
        memory_cache_dp_free(tmp);
    }
}

static inline bool
binary_indexed_tree_number_legal_p(struct binary_indexed_tree *tree, uint32 number)
{
    dp_assert(!complain_null_pointer_p(tree));

    if (number == BIN_IDXED_NMBR_INVALID) {
        return false;
    } else if (number > tree->size) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_indexed_tree_structure_legal_p(struct binary_indexed_tree *tree)
{
    if (complain_null_pointer_p(tree)) {
        return false;
    } else if (complain_null_pointer_p(tree->data)) {
        return false;
    } else if (complain_zero_size_p(tree->size)) {
        return false;
    } else {
        return true;
    }
}

static inline void
binary_indexed_tree_add_internal(struct binary_indexed_tree *tree,
    uint32 number, sint64 val)
{
    uint32 base;

    dp_assert(!complain_null_pointer_p(tree));
    dp_assert(binary_indexed_tree_number_legal_p(tree, number));
    dp_assert(binary_indexed_tree_structure_legal_p(tree));

    base = ((number - 1) ^ number) & number;
    tree->data[number] += val;

    /*
     * Update the all the parent node of tree.
     * For example: number 10 = 1010B
     *     Should update from 
     *     1. 01010B
     *     2. 01100B = 1010B + 10B
     *     3. 10000B = 1100B + 100B ...
     *     to the limit of size. 
     */
    while (number + base <= tree->size) {
        number = number + base;
        tree->data[number] += val;
        base = base << 1;
    }
}


void
binary_indexed_tree_add(struct binary_indexed_tree *tree,
    uint32 number, sint64 val)
{

    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return;
    } else if (!binary_indexed_tree_number_legal_p(tree, number)) {
        return;
    } else {
        binary_indexed_tree_add_internal(tree, number, val);
    }
}

void
binary_indexed_tree_sub(struct binary_indexed_tree *tree,
    uint32 number, sint64 val)
{

    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return;
    } else if (!binary_indexed_tree_number_legal_p(tree, number)) {
        return;
    } else {
        binary_indexed_tree_add_internal(tree, number, -val);
    }
}

static inline sint64
binary_indexed_tree_sum_internal(struct binary_indexed_tree *tree,
    uint32 number)
{
    sint64 retval;
    uint32 base;

    dp_assert(binary_indexed_tree_structure_legal_p(tree));
    dp_assert(binary_indexed_tree_number_legal_p(tree, number));

    retval = 0;
    base = number;

    while (base) {
        retval += tree->data[base];
        base = base & (base - 1);
    }

    return retval;
}

sint64
binary_indexed_tree_sum(struct binary_indexed_tree *tree, uint32 number)
{
    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (!binary_indexed_tree_number_legal_p(tree, number)) {
        return 0;
    } else {
        return binary_indexed_tree_sum_internal(tree, number);
    }
}

sint64
binary_indexed_tree_range_sum(struct binary_indexed_tree *tree,
    uint32 nmbr_s, uint32 nmbr_e)
{
    sint64 retval;
    sint64 tmp;

    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (!binary_indexed_tree_number_legal_p(tree, nmbr_s)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (!binary_indexed_tree_number_legal_p(tree, nmbr_e)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (nmbr_s > nmbr_e) {
        pr_log_warn("Invalid start number and end number of range.\n");
        return BIN_IDXED_SUM_INVALID;
    } else {
        retval = binary_indexed_tree_sum_internal(tree, nmbr_e);
        if (nmbr_s == 1) {
            tmp = 0;
        } else {
            tmp = binary_indexed_tree_sum_internal(tree, nmbr_s - 1);
        }

        return retval - tmp;
    }
}

