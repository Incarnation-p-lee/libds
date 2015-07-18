uint32
random_uint32_with_limit(uint32 lmt)
{
    assert(0 != lmt);

    return (uint32)rand() % lmt;
}
