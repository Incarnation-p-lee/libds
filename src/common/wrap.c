void *
malloc_wrap(size_t size)
{
    return malloc(size);
}

void
free_wrap(void *ptr)
{
    free(ptr);
    return;
}
