uint32
prime_numeral_next(uint32 prime)
{
    uint32 *iter;

    if (prime < FIXED_PRIME_MAX) {
        iter = (uint32 *)fixed_prime;
        while (iter < fixed_prime + array_sizeof(fixed_prime)) {
            if (prime < *iter++) {
                break;
            }
        }
        return *iter;
    } else {
        return prime_numeral_calculate_next(prime);
    }
}

static inline uint32
prime_numeral_calculate_next(uint32 prime)
{
    uint32 start;
    uint32 next;
    uint32 limit;
    uint32 retval;

    assert(1u == (prime & 0x1u));

    retval = 0;
    next = prime + 2;
    while (next != UINT_MAX - 1) {
        start = 3;
        limit = (uint32)sqrt(next);
        while (start < limit) {
            if (0u == next % start) {
                break;
            }
            start += 2;
        }

        if (start < limit) {
            /* If next is not PRIME */
            next += 2;
        } else {
            retval = next;
            break;
        }
    }

    if (0 == retval) {
        pr_log_warn("Failed to find next PRIME numeral less than UINT_MAX.\n");
    }

    return retval;
}

