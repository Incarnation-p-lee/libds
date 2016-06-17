void *
malloc_wrap(uint32 size)
{
    malloc_cnt++;

    return dp_malloc(size);
}

void *
realloc_wrap(void *ptr, uint32 size)
{
    realloc_cnt++;

    return dp_realloc(ptr, size);
}

void
free_wrap(void *ptr)
{
    free_cnt++;
    dp_free(ptr);
}

