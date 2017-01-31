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
        disjoint_set_element_set(disjoint_set, i++, DISJOINT_SET_TOP);
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

static inline uint32
disjoint_set_size(s_disjoint_set_t *disjoint_set)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));

    return disjoint_set->size;
}

static inline bool
disjoint_set_element_top_p(sint32 value)
{
    if (value < 0) {
        return true;
    } else {
        return false;
    }
}

sint32
disjoint_set_find(s_disjoint_set_t *disjoint_set, uint32 index)
{
    sint32 element;

    if (disjoint_set_structure_illegal_p(disjoint_set)) {
        return DISJOINT_SET_INVALID;
    } else if (index >= disjoint_set_size(disjoint_set)) {
        return DISJOINT_SET_INVALID;
    } else {
        element = disjoint_set_element(disjoint_set, index);

        while (!disjoint_set_element_top_p(element)) {
            index = element;
            element = disjoint_set_element(disjoint_set, index);
        }

        return index;
    }
}

static inline uint32
disjoint_set_element_size(s_disjoint_set_t *disjoint_set, uint32 index)
{
    sint32 element;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size(disjoint_set));

    element = disjoint_set_element(disjoint_set, index);

    if (element > 0) {
        return DISJOINT_SET_ZERO_SIZE;
    } else {
        return (uint32)(0 - element);
    }
}

static inline sint32
disjoint_set_element(s_disjoint_set_t *disjoint_set, uint32 index)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size(disjoint_set));

    return disjoint_set->set[index];
}

static inline void
disjoint_set_element_set(s_disjoint_set_t *disjoint_set, uint32 index,
    sint32 element)
{
    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index < disjoint_set_size(disjoint_set));

    disjoint_set->set[index] = element;
}

void
disjoint_set_union_by_size(s_disjoint_set_t *disjoint_set, uint32 index_fir,
    uint32 index_sec)
{
    sint32 element;
    uint32 size_fir;
    uint32 size_sec;

    assert_exit(disjoint_set_structure_legal_p(disjoint_set));
    assert_exit(index_fir < disjoint_set_size(disjoint_set));
    assert_exit(index_sec < disjoint_set_size(disjoint_set));

    size_fir = disjoint_set_element_size(disjoint_set, index_fir);
    size_sec = disjoint_set_element_size(disjoint_set, index_sec);

    if (size_fir > size_sec) {
        element = disjoint_set_element(disjoint_set, index_fir);
        disjoint_set_element_set(disjoint_set, index_sec, element);
    } else {
        element = disjoint_set_element(disjoint_set, index_sec);
        disjoint_set_element_set(disjoint_set, index_fir, element);
    }
}

void
disjoint_set_union(s_disjoint_set_t *disjoint_set, uint32 index_fir,
    uint32 index_sec)
{
    if (disjoint_set_structure_illegal_p(disjoint_set)) {
        return;
    } else if (index_fir >= disjoint_set_size(disjoint_set)) {
        return;
    } else if (index_sec >= disjoint_set_size(disjoint_set)) {
        return;
    } else {
        disjoint_set_union_by_size(disjoint_set, index_fir, index_sec);
    }
}

