void
swap_pointer(void **ptr_a, void **ptr_b)
{
    void *tmp;

    if (complain_null_pointer_p(ptr_a)) {
        return;
    } else if (complain_null_pointer_p(ptr_b)) {
        return;
    } else if (*ptr_a == *ptr_b) {
        return;
    } else {
        // TODO, CMPXCHG optimization
        tmp = *ptr_a;
        *ptr_a = *ptr_b;
        *ptr_b = tmp;
    }
}

