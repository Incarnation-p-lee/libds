void *
malloc_wrap(size_t size)
{
    malloc_cnt++;

    return malloc(size);
}

void *
realloc_wrap(void *ptr, size_t size)
{
    realloc_cnt++;

    return realloc(ptr, size);
}

void
free_wrap(void *ptr)
{
    free_cnt++;
    free(ptr);

    return;
}
