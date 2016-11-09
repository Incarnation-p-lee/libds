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
s_binary_indexed_tree_t *
binary_indexed_tree_create(sint64 *data, uint32 size)
{
    uint32 i;
    uint32 mask;
    uint32 iterator;
    s_binary_indexed_tree_t *tree;

    if (complain_null_pointer_p(data)) {
        return NULL;
    } else if (complain_zero_size_p(size)) {
        return NULL;
    } else {
        tree = memory_cache_allocate(sizeof(*tree));

        tree->size = size;
        tree->data = memory_cache_allocate(sizeof(*tree->data) * (size + 1));
        dp_memset(tree->data, 0, sizeof(*tree->data) * (size + 1));

        tree->data[1] = data[0];

        i = 2;
        while (i <= size) {
            tree->data[i] = data[i - 1];
            if (0 == i % 2) {
                iterator = i - 1;
                mask = 0xfffffffe;

                while (0 == (i & ~mask)) {
                    tree->data[i] += tree->data[iterator];
                    iterator = iterator & mask;
                    mask = mask << 1;
                }
            }
            i++;
        }

        return tree;
    }
}

void
binary_indexed_tree_destroy(s_binary_indexed_tree_t **tree)
{
    if (complain_null_pointer_p(tree)) {
        return;
    } else if (binary_indexed_tree_structure_legal_p(*tree)) {
        memory_cache_free((*tree)->data);
        memory_cache_free(*tree);
        *tree = NULL;
    }
}

static inline bool
binary_indexed_tree_number_legal_p(s_binary_indexed_tree_t *tree, uint32 number)
{
    assert_exit(!complain_null_pointer_p(tree));

    if (number == BIN_IDXED_NMBR_INVALID) {
        return false;
    } else if (number > tree->size) {
        return false;
    } else {
        return true;
    }
}

static inline bool
binary_indexed_tree_structure_legal_p(s_binary_indexed_tree_t *tree)
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
binary_indexed_tree_add_i(s_binary_indexed_tree_t *tree,
    uint32 number, sint64 val)
{
    uint32 iterator;

    assert_exit(!complain_null_pointer_p(tree));
    assert_exit(binary_indexed_tree_number_legal_p(tree, number));
    assert_exit(binary_indexed_tree_structure_legal_p(tree));

    iterator = ((number - 1) ^ number) & number;
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
    while (number + iterator <= tree->size) {
        number = number + iterator;
        tree->data[number] += val;
        iterator = iterator << 1;
    }
}


void
binary_indexed_tree_add(s_binary_indexed_tree_t *tree,
    uint32 number, sint64 val)
{

    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return;
    } else if (!binary_indexed_tree_number_legal_p(tree, number)) {
        return;
    } else {
        binary_indexed_tree_add_i(tree, number, val);
    }
}

void
binary_indexed_tree_sub(s_binary_indexed_tree_t *tree,
    uint32 number, sint64 val)
{
    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return;
    } else if (!binary_indexed_tree_number_legal_p(tree, number)) {
        return;
    } else {
        binary_indexed_tree_add_i(tree, number, -val);
    }
}

static inline sint64
binary_indexed_tree_sum_i(s_binary_indexed_tree_t *tree,
    uint32 number)
{
    sint64 sum;
    uint32 iterator;

    assert_exit(binary_indexed_tree_structure_legal_p(tree));
    assert_exit(binary_indexed_tree_number_legal_p(tree, number));

    sum = 0;
    iterator = number;

    while (iterator) {
        sum += tree->data[iterator];
        iterator = iterator & (iterator - 1);
    }

    return sum;
}

sint64
binary_indexed_tree_sum(s_binary_indexed_tree_t *tree, uint32 number)
{
    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (!binary_indexed_tree_number_legal_p(tree, number)) {
        return BIN_IDXED_SUM_INVALID;
    } else {
        return binary_indexed_tree_sum_i(tree, number);
    }
}

sint64
binary_indexed_tree_range_sum(s_binary_indexed_tree_t *tree,
    uint32 nmbr_s, uint32 nmbr_e)
{
    sint64 sum_head;
    sint64 sum_range;

    if (!binary_indexed_tree_structure_legal_p(tree)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (!binary_indexed_tree_number_legal_p(tree, nmbr_s)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (!binary_indexed_tree_number_legal_p(tree, nmbr_e)) {
        return BIN_IDXED_SUM_INVALID;
    } else if (nmbr_s > nmbr_e) {
        pr_log_warn("Invalid start number and end number of range.\n");
        return BIN_IDXED_SUM_INVALID;
    } else if (nmbr_s == 1) {
        return binary_indexed_tree_sum_i(tree, nmbr_e);
    } else {
        sum_head = binary_indexed_tree_sum_i(tree, nmbr_s - 1);
        sum_range = binary_indexed_tree_sum_i(tree, nmbr_e) - sum_head;
        return sum_range;
    }
}

