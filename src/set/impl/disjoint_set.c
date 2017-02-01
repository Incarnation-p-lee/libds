s_disjoint_set_t *
disjoint_set_create(uint32 size)
{
    uint32 bytes_count;
    s_disjoint_set_t *disjoint_set;

    if (size == 0) {
        return PTR_INVALID;
    } else {
        disjoint_set = memory_cache_allocate(sizeof(*disjoint_set));
        disjoint_set->size = size;
        bytes_count = sizeof(*disjoint_set->set) * size;
        disjoint_set->set = memory_cache_allocate(bytes_count);

        disjoint_set_initial(disjoint_set);

        return disjoint_set;
    }
}

static inline bool
disjoint_set_structure_legal_p(s_disjoint_set_t *disjoint_set)
{
    if (complain_null_pointer_p(disjoint_set)) {
        return false;
    } else if (complain_null_pointer_p(disjoint_set->set)) {
        return false;
    } else if (complain_zero_size_p(disjoint_set->size)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disjoint_set_structure_illegal_p(s_disjoint_set_t *disjoint_set)
{
    return !disjoint_set_structure_legal_p(disjoint_set);
}

static inline void
disjoint_set_initial(s_disjoint_set_t *disjoint_set)
{
    uint32 i;
    uint32 limit;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));

    i = 0;
    limit = disjoint_set->size;

    while (i < limit) {
        disjoint_set_element_set(disjoint_set, i++, DISJOINT_TOP);
    }
}

void
disjoint_set_destroy(s_disjoint_set_t **disjoint_set)
{
    if (disjoint_set && disjoint_set_structure_legal_p(*disjoint_set)) {
        memory_cache_free((*disjoint_set)->set);
        memory_cache_free(*disjoint_set);

        *disjoint_set = NULL;
    }
}

uint32
disjoint_set_size(s_disjoint_set_t *disjoint_set)
{
    if (DISJOINT_SET_ILLEGAL_P(disjoint_set)) {
        return DISJOINT_SIZE_INVALID;
    } else {
        return disjoint_set_size_i(disjoint_set);
    }
}

static inline uint32
disjoint_set_size_i(s_disjoint_set_t *disjoint_set)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));

    return disjoint_set->size;
}

static inline bool
disjoint_set_element_value_top_p(sint32 element)
{
    return element < 0 ? true : false;
}

static inline bool
disjoint_set_element_top_p(s_disjoint_set_t *disjoint_set, uint32 index)
{
    sint32 element;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size_i(disjoint_set));

    element = disjoint_set_element(disjoint_set, index);

    return disjoint_set_element_value_top_p(element);
}

static inline void
disjoint_set_path_compression(s_disjoint_set_t *disjoint_set,
    s_array_stack_t *stack, uint32 index_top)
{
    uint32 index_father;

    assert_exit(array_stack_structure_legal_p(stack));
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index_top < disjoint_set_size_i(disjoint_set));
    assert_exit(disjoint_set_element_top_p(disjoint_set, index_top));

    while (!array_stack_empty_p(stack)) {
        index_father = (ptr_t)array_stack_pop(stack);
        disjoint_set_element_set(disjoint_set, index_father, index_top);
    }
}

static inline uint32
disjoint_set_find_i(s_disjoint_set_t *disjoint_set, uint32 index)
{
    void *father;
    sint32 element;
    s_array_stack_t *stack_father;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size_i(disjoint_set));

    element = disjoint_set_element(disjoint_set, index);

    if (disjoint_set_element_value_top_p(element)) {
        return index;
    } else {
        stack_father = array_stack_create();

        while (!disjoint_set_element_value_top_p(element)) {
            index = element;
            father = (void *)(ptr_t)index;
            array_stack_push(stack_father, father);
            element = disjoint_set_element(disjoint_set, index);
        }

        array_stack_pop(stack_father); /* skip top node */
        disjoint_set_path_compression(disjoint_set, stack_father, index);
        array_stack_destroy(&stack_father);
    }

    return index;
}

uint32
disjoint_set_find(s_disjoint_set_t *disjoint_set, uint32 index)
{
    if (disjoint_set_structure_illegal_p(disjoint_set)) {
        return DISJOINT_ELE_INVALID;
    } else if (index >= disjoint_set_size_i(disjoint_set)) {
        return DISJOINT_ELE_INVALID;
    } else {
        return disjoint_set_find_i(disjoint_set, index);
    }
}

static inline bool
disjoint_set_equivalent_ip(s_disjoint_set_t *disjoint_set, uint32 index_fir,
    uint32 index_sec)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index_fir < disjoint_set_size_i(disjoint_set));
    assert_exit(index_sec < disjoint_set_size_i(disjoint_set));

    if (disjoint_set_find(disjoint_set, index_fir)
        == disjoint_set_find(disjoint_set, index_sec)) {
        return true;
    } else {
        return false;
    }
}

bool
disjoint_set_equivalent_p(s_disjoint_set_t *disjoint_set, uint32 index_fir,
    uint32 index_sec)
{
    if (disjoint_set_structure_illegal_p(disjoint_set)) {
        return false;
    } else if (index_fir >= disjoint_set_size_i(disjoint_set)) {
        return false;
    } else if (index_sec >= disjoint_set_size_i(disjoint_set)) {
        return false;
    } else {
        return disjoint_set_equivalent_ip(disjoint_set, index_fir, index_sec);
    }
}

static inline uint32
disjoint_set_element_size(s_disjoint_set_t *disjoint_set, uint32 index)
{
    sint32 element;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size_i(disjoint_set));

    element = disjoint_set_element(disjoint_set, index);

    if (element > 0) {
        return DISJOINT_ZERO_SIZE;
    } else {
        return (uint32)(0 - element);
    }
}

static inline sint32
disjoint_set_element(s_disjoint_set_t *disjoint_set, uint32 index)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size_i(disjoint_set));

    return disjoint_set->set[index];
}

static inline void
disjoint_set_element_set(s_disjoint_set_t *disjoint_set, uint32 index,
    sint32 element)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size_i(disjoint_set));

    disjoint_set->set[index] = element;
}

static inline void
disjoint_set_element_top_increase(s_disjoint_set_t *disjoint_set, uint32 index_top)
{
    sint32 element;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index_top < disjoint_set_size_i(disjoint_set));
    assert_exit(disjoint_set_element_top_p(disjoint_set, index_top));

    element = disjoint_set_element(disjoint_set, index_top);
    disjoint_set_element_set(disjoint_set, index_top, element - 1);
}

static inline void
disjoint_set_union_by_size(s_disjoint_set_t *disjoint_set, uint32 index_fir,
    uint32 index_sec)
{
    uint32 size_fir, size_sec;
    uint32 top_fir, top_sec;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index_fir < disjoint_set_size_i(disjoint_set));
    assert_exit(index_sec < disjoint_set_size_i(disjoint_set));

    top_fir = disjoint_set_find_i(disjoint_set, index_fir);
    top_sec = disjoint_set_find_i(disjoint_set, index_sec);

    size_fir = disjoint_set_element_size(disjoint_set, top_fir);
    size_sec = disjoint_set_element_size(disjoint_set, top_sec);

    if (size_fir > size_sec) {
        disjoint_set_element_set(disjoint_set, top_sec, (sint32)top_fir);
        disjoint_set_element_top_increase(disjoint_set, top_fir);
    } else {
        disjoint_set_element_set(disjoint_set, top_fir, (sint32)top_sec);
        disjoint_set_element_top_increase(disjoint_set, top_sec);
    }
}

void
disjoint_set_union(s_disjoint_set_t *disjoint_set, uint32 index_fir,
    uint32 index_sec)
{
    if (disjoint_set_structure_illegal_p(disjoint_set)) {
        return;
    } else if (index_fir >= disjoint_set_size_i(disjoint_set)) {
        return;
    } else if (index_sec >= disjoint_set_size_i(disjoint_set)) {
        return;
    } else if (disjoint_set_equivalent_ip(disjoint_set, index_fir, index_sec)) {
        return;
    } else {
        disjoint_set_union_by_size(disjoint_set, index_fir, index_sec);
    }
}

