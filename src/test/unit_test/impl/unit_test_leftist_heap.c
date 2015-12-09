static void
unit_test_leftist_heap_struct_field(void)
{
    bool pass;
    sint32 npl;
    sint64 nice;
    struct leftist_heap *heap;

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
    struct leftist_heap *heap;

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
    struct leftist_heap *heap;

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
    struct leftist_heap *heap;

    pass = true;
    heap = NULL;

    leftist_heap_destroy(&heap);

    heap = test_leftist_heap_sample(0x3742, 0x2134);
    leftist_heap_destroy(&heap);
    RESULT_CHECK_pointer(NULL, heap, &pass);

    UNIT_TEST_RESULT(leftist_heap_destroy, pass);
}

