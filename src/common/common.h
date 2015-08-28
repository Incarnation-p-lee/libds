#ifndef HAVE_COMMON_H
#define HAVE_COMMON_H

#define MAP_ENTRY_MAX 128

#define M_UKNW        0x1u << 0
#define M_READ        0x1u << 1
#define M_WRITE       0x1u << 2
#define M_EXECUTE     0x1u << 3
#define M_SHARED      0x1u << 4
#define M_PRIVATE     0x1u << 5

const uint32 fixed_prime[] = {
    3,             7,      11,      17,      23,      29,      37,      47,
    59,           71,      89,     107,     131,     163,     197,     239,
    293,         353,     431,     521,     631,     761,     919,    1103,
    1327,       1597,    1931,    2333,    2801,    3371,    4049,    4861,
    5839,       7013,    8419,   10103,   12143,   14591,   17519,   21023,
    25229,     30293,   36353,   43627,   52361,   62851,   75431,   90523,
    108631,   130363,  156437,  187751,  225307,  270371,  324449,  389357,
    467237,   560689,  672827,  807403,  968897, 1162687, 1395263, 1674319,
    2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369,
};

#define FIXED_PRIME_MAX fixed_prime[array_sizeof(fixed_prime) - 1]

/*
 * section info of binary
 */
static struct memory_maps mmaps[MAP_ENTRY_MAX] = {
    {},
};

static struct option_set opt_set = {
};


#endif
