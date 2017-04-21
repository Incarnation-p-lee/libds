#ifndef HAVE_DEFINED_UNIT_TEST_GRAPH_H
#define HAVE_DEFINED_UNIT_TEST_GRAPH_H

#define UT_GRAPH_create(name)                                  \
static void                                                    \
utest_##name##_graph_create(void)                              \
{                                                              \
    bool pass;                                                 \
    GRAPH *graph;                                              \
                                                               \
    pass = true;                                               \
    graph = GRAPH_create();                                    \
    UNIT_TEST_BEGIN(name##_graph_create);                      \
                                                               \
    RESULT_CHECK_bool(true, TEST_graph_legal_p(graph), &pass); \
                                                               \
    GRAPH_destroy(&graph);                                     \
    UNIT_TEST_RESULT(name##_graph_create, pass);               \
}

#endif

