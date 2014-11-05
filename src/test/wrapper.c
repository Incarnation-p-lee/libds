void *
malloc_wrap(size_t size)
{
    malloc_cnt++;
    return malloc(size);
}

void
free_wrap(void *ptr)
{
    free_cnt++;
    free(ptr);
    return;
}
