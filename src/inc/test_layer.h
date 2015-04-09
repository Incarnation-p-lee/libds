#ifndef TEST_LAYER_H
#define TEST_LAYER_H

struct test_layer_table {
    char     *name;
    union {
        const void *junior;
        void (*func)(void);
    };
};

#endif
