static void
unit_test_leftist_heap_struct_field(void)
{
    bool pass;
    sint32 npl;
    sint64 nice;
    s_leftist_heap_t *heap;

    pass = true;
    npl = 0xfead;
    nice = 0xdfea;
    heap = leftist_heap_create();

    RESULT_CHECK_pointer(NULL, leftist_heap_left(heap), &pass);
    RESULT_CHECK_pointer(NULL, leftist_heap_right(heap), &pass);

    leftist_heap_nice_set(heap, nice);
    RESULT_CHECK_sint64(nice, leftist_heap_nice(heap), &pass);

    leftist_heap_npl_set(heap, npl);
    RESULT_CHECK_sint32(npl, leftist_heap_npl(heap), &pass);

    leftist_heap_val_set(heap, &pass);
    RESULT_CHECK_pointer(&pass, leftist_heap_val(heap), &pass);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_struct_field, pass);
}

static void
unit_test_leftist_heap_create(void)
{
    bool pass;
    s_leftist_heap_t *heap;

    pass = true;
    heap = leftist_heap_create();

    RESULT_CHECK_pointer(NULL, leftist_heap_val(heap), &pass);
    RESULT_CHECK_pointer(NULL, leftist_heap_left(heap), &pass);
    RESULT_CHECK_pointer(NULL, leftist_heap_right(heap), &pass);

    RESULT_CHECK_sint64(0, leftist_heap_nice(heap), &pass);
    RESULT_CHECK_sint32(0, leftist_heap_npl(heap), &pass);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_create, pass);
}

static void
unit_test_leftist_heap_node_create(void)
{
    bool pass;
    sint32 npl;
    sint64 nice;
    s_leftist_heap_t *heap;

    pass = true;
    npl = 0x123;
    nice = -0x1e2;
    heap = leftist_heap_node_create(&pass, npl, nice);

    RESULT_CHECK_pointer(NULL, leftist_heap_left(heap), &pass);
    RESULT_CHECK_pointer(NULL, leftist_heap_right(heap), &pass);
    RESULT_CHECK_pointer(&pass, leftist_heap_val(heap), &pass);

    RESULT_CHECK_sint64(nice, leftist_heap_nice(heap), &pass);
    RESULT_CHECK_sint32(npl, leftist_heap_npl(heap), &pass);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_node_create, pass);
}

static void
unit_test_leftist_heap_destroy(void)
{
    bool pass;
    s_leftist_heap_t *heap;

    pass = true;
    heap = NULL;

    leftist_heap_destroy(&heap);

    heap = test_leftist_heap_sample(0x742, 0x134);
    leftist_heap_destroy(&heap);
    RESULT_CHECK_pointer(NULL, heap, &pass);

    UNIT_TEST_RESULT(leftist_heap_destroy, pass);
}

static void
unit_test_leftist_heap_get_min(void)
{
    bool pass;
    s_leftist_heap_t *heap;
    s_leftist_heap_t *tmp;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(PTR_INVALID, leftist_heap_get_min(heap), &pass);

    heap = test_leftist_heap_sample(0xd22, 0xec2);
    tmp = heap;
    RESULT_CHECK_pointer(leftist_heap_val(tmp), leftist_heap_get_min(heap), &pass);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_get_min, pass);
}

static void
unit_test_leftist_heap_insert(void)
{
    bool pass;
    sint64 nice;
    s_leftist_heap_t *heap;

    pass = true;
    heap = NULL;
    nice = -0x893e;

    RESULT_CHECK_pointer(PTR_INVALID, leftist_heap_insert(heap, NULL, 0), &pass);

    heap = test_leftist_heap_sample(0x9b2, 0x2f2);
    heap = leftist_heap_insert(heap, &pass, nice);
    RESULT_CHECK_pointer(&pass, leftist_heap_val(heap), &pass);
    RESULT_CHECK_sint64(nice, leftist_heap_nice(heap), &pass);

    heap = leftist_heap_insert(heap, &pass, 1);
    RESULT_CHECK_pointer(&pass, leftist_heap_val(heap), &pass);
    RESULT_CHECK_sint64(nice, leftist_heap_nice(heap), &pass);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_insert, pass);
}

static void
unit_test_leftist_heap_merge(void)
{
    bool pass;
    sint64 nice;
    void *val;
    s_leftist_heap_t *heap;
    s_leftist_heap_t *tmp;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(PTR_INVALID, leftist_heap_merge(heap, NULL), &pass);

    heap = test_leftist_heap_sample(0x4b2, 0x2f2);
    RESULT_CHECK_pointer(heap, leftist_heap_merge(heap, NULL), &pass);
    RESULT_CHECK_pointer(heap, leftist_heap_merge(NULL, heap), &pass);

    tmp = test_leftist_heap_sample(0x912, 0x3e2);
    nice = leftist_heap_nice(heap) < leftist_heap_nice(tmp)
        ? leftist_heap_nice(heap) : leftist_heap_nice(tmp);
    val = leftist_heap_nice(heap) < leftist_heap_nice(tmp)
        ? leftist_heap_val(heap) : leftist_heap_val(tmp);

    heap = leftist_heap_merge(heap, tmp);
    RESULT_CHECK_sint64(nice, leftist_heap_nice(heap), &pass);
    RESULT_CHECK_pointer(val, leftist_heap_val(heap), &pass);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_merge, pass);
}

static void
unit_test_leftist_heap_remove_min(void)
{
    bool pass;
    void *min;
    s_leftist_heap_t *heap;
    s_leftist_heap_t *removed;

    pass = true;
    heap = NULL;

    RESULT_CHECK_pointer(PTR_INVALID, leftist_heap_remove_min(&heap), &pass);

    heap = test_leftist_heap_sample(0x3b2, 0x1f2);
    min = leftist_heap_get_min(heap);
    removed = leftist_heap_remove_min(&heap);
    RESULT_CHECK_pointer(leftist_heap_val(removed), min, &pass);
    leftist_heap_destroy(&removed);
    leftist_heap_destroy(&heap);

    heap = leftist_heap_create();
    min = leftist_heap_get_min(heap);
    removed = leftist_heap_remove_min(&heap);
    RESULT_CHECK_pointer(leftist_heap_val(removed), min, &pass);
    RESULT_CHECK_pointer(NULL, heap, &pass);
    leftist_heap_destroy(&removed);

    leftist_heap_destroy(&heap);
    UNIT_TEST_RESULT(leftist_heap_remove_min, pass);
}

static void
unit_test_leftist_heap_remove_min_and_destroy(void)
{
    bool pass;
    s_leftist_heap_t *heap;

    pass = true;
    heap = NULL;

    leftist_heap_remove_min_and_destroy(&heap);

    heap = test_leftist_heap_sample(0x392, 0x1f2);
    leftist_heap_remove_min_and_destroy(&heap);
    leftist_heap_destroy(&heap);

    heap = leftist_heap_create();
    leftist_heap_remove_min_and_destroy(&heap);
    RESULT_CHECK_pointer(NULL, heap, &pass);

    UNIT_TEST_RESULT(leftist_heap_remove_min_and_destroy, pass);
}

