/*
 * Index = SUM(key[size - i - 1] * (32 ^ i)), 0 <= i <= size - 1
 *     0x0 <= key[size - i - 1] <= 0xF
 */
uint32
hashing_function_polynomial(void *key, uint32 size)
{
    uint64 raw;
    uint64 retval;

    raw = (uint64)key;

    retval = 0x0ull;
    while (0ull != raw) {
        retval = ((raw & 0xfull) << 5) + retval;
        raw = raw >> 4;
    }

    return retval % size;
}

