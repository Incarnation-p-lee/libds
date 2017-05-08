static inline void
utest_directed_graph_create(void)
{
    bool pass;
    s_graph_t *graph;

    pass = true;
    graph = directed_graph_create();
    UNIT_TEST_BEGIN(directed_graph_create);

    RESULT_CHECK_bool(true, directed_graph_structure_legal_p(graph), &pass);

    directed_graph_destroy(&graph);
    UNIT_TEST_RESULT(directed_graph_create, pass);
}

