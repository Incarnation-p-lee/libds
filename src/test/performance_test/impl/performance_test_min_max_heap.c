static inline void
performance_test_min_max_heap_create(uint32 count)
{
    struct min_max_heap *heap;

    PERFORMANCE_TEST_CHECKPOINT;

    while (count--) {
        heap = min_max_heap_create(0x1e3);
        min_max_heap_destroy(&heap);
    }

    PERFORMANCE_TEST_ENDPOINT;

    performance_test_result_print(SYM_2_STR(min_max_heap_create),
        performance_test_time_stamp_period());
}


