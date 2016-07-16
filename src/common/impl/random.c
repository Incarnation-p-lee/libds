uint32
random_uint32_with_limit(uint32 lmt)
{
    assert_exit(0 != lmt);

    return (uint32)dp_rand() % lmt;
}

sint64
random_sint64(void)
{
    return (sint64)dp_rand() - (sint64)dp_rand();
}

