uint32
dp_random_uint32_with_limit(uint32 lmt)
{
    dp_assert(0 != lmt);

    return (uint32)dp_rand() % lmt;
}

sint64
dp_random_sint64(void)
{
    return (sint64)dp_rand() - (sint64)dp_rand();
}

