/*
 * Index = SUM(key[size - i - 1] * (32 ^ i)), 0 <= i <= size - 1
 *     0x0 <= key[size - i - 1] <= 0xF
 */
uint32
hashing_function_polynomial(void *key, uint32 size)
{
    uint64 raw;
    uint64 retval;

    if (0 == size) {
        pr_log_err("Hash table should not have zero table size.\n");
    } else {
        raw = (uint64)key;

        retval = 0x0ull;
        while (0ull != raw) {
            retval = ((raw & 0xfull) << 5) + retval;
            raw = raw >> 4;
        }
    }

    return (uint32)retval % size;
}

static inline uint32
hashing_function_square(uint32 iter)
{
    assert(iter < 0x10000);

    return iter * iter;
}

uint32
hashing_function_open_addressing(void *key, uint32 size, uint32 iter)
{
    uint64 retval;

    retval = hashing_function_polynomial(key, size);
    retval = (retval + hashing_function_square(iter)) % size;

    return (uint32)retval;
}
