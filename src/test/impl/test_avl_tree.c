static inline struct avl_tree *
test_avl_tree_sample(uint64 range, uint32 node_count)
{
    struct avl_tree *retval;
    struct avl_tree *tmp;
    sint64 nice;
    uint32 i;

    retval = avl_tree_create();
    avl_tree_node_initial(retval, retval, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = avl_tree_node_create(NULL, 0x0);
        avl_tree_node_initial(tmp, tmp, nice);
        if (tmp != avl_tree_node_insert(retval, tmp)) {
            avl_tree_destroy(&tmp);
        }
        i++;
    }

    return (struct avl_tree *)retval;
}

static void
test_avl_tree_create(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_create), is_passed);
    return;
}

static void
test_avl_tree_node_create(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_node_create(&is_passed, 0xdead);

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0xdead != tmp->b_node.chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_node_create), is_passed);
    return;
}

static void
test_avl_tree_initial(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_initial(tmp);
    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    } else if (0 != tmp->b_node.height) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_initial), is_passed);
    return;
}

static void
test_avl_tree_node_initial(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0 != tmp->b_node.chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    }

    avl_tree_node_initial(tmp, &is_passed, 0xdead);
    if (NULL != tmp->b_node.left || NULL != tmp->b_node.right) {
        is_passed = false;
    } else if (0xdead != tmp->b_node.chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->b_node.chain.link)) {
        is_passed = false;
    } else if (0 != tmp->b_node.height) {
        is_passed = false;
    }

    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_node_initial), is_passed);
    return;
}

static void
test_avl_tree_destroy(void)
{
    bool is_passed;
    struct avl_tree *tmp;

    is_passed = true;
    tmp = avl_tree_create();

    avl_tree_destroy(&tmp);
    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = test_avl_tree_sample(0xABDE8, 0x327EF);
    avl_tree_destroy(&tmp);
    if (NULL != tmp) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(avl_tree_destroy), is_passed);
    return;
}

static void
test_avl_tree_node_find(void)
{
    bool is_passed;
    struct avl_tree *root;
    struct avl_tree *tmp;

    is_passed = true;
    root = test_avl_tree_sample(0x7F28A, 0x87D21);

    if (root != avl_tree_node_find(root, root->b_node.chain.nice)) {
        is_passed = false;
    }

    if (NULL != avl_tree_node_find(root, 0x7FFFFFFF)) {
        is_passed = false;
    }

    tmp = avl_tree_node_find_min(root);
    if (tmp != avl_tree_node_find(root, tmp->b_node.chain.nice)) {
        is_passed = false;
    }

    tmp = avl_tree_node_create(&is_passed, 0x7FFFFFFF);
    if (NULL != avl_tree_node_find(root, tmp->b_node.chain.nice)) {
        is_passed = false;
    }

    avl_tree_destroy(&root);
    avl_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(avl_tree_node_find), is_passed);
    return;
}

static void
test_avl_tree_node_find_min(void)
{
    bool is_passed;
    struct avl_tree *root;
    struct avl_tree *tmp;

    is_passed = true;
    root = test_avl_tree_sample(0x39131, 0x264DC);

    if (NULL != avl_tree_node_find_min(NULL)) {
        is_passed = false;
    }

    tmp = avl_tree_node_find_min(root);
    if (NULL != tmp->b_node.left) {
        is_passed = false;
    }

    avl_tree_destroy(&root);

    test_result_print(SYM_2_STR(avl_tree_node_find_min), is_passed);
    return;
}

static void
test_avl_tree_node_find_max(void)
{
    bool is_passed;
    struct avl_tree *root;
    struct avl_tree *tmp;

    is_passed = true;
    root = test_avl_tree_sample(0x3F1A1, 0x2E494);

    if (NULL != avl_tree_node_find_max(NULL)) {
        is_passed = false;
    }

    tmp = avl_tree_node_find_max(root);
    if (NULL != tmp->b_node.right) {
        is_passed = false;
    }

    avl_tree_destroy(&root);

    test_result_print(SYM_2_STR(avl_tree_node_find_max), is_passed);
    return;
}

static void
test_avl_tree_height(void)
{
    bool is_passed;
    sint32 child;
    struct avl_tree *root;

    is_passed = true;
    root = test_avl_tree_sample(0x9E1A2, 0xAB427);

    if (-1 != avl_tree_height(NULL)) {
        is_passed = false;
    }

    child = MAX_S(avl_tree_height(root->b_node.avl_left),
        avl_tree_height(root->b_node.avl_right));
    if (child + 1 != avl_tree_height(root)) {
        is_passed = false;
    }

    avl_tree_destroy(&root);
    test_result_print(SYM_2_STR(avl_tree_height), is_passed);
    return;
}

static void
test_avl_tree_node_contain_p(void)
{
    bool is_passed;
    struct avl_tree *root;
    struct avl_tree *tmp;
    struct avl_tree *fake;

    is_passed = true;
    root = test_avl_tree_sample(0xE28D1, 0xC251F);
    tmp = avl_tree_node_create(&is_passed, 0x1234);

    if (avl_tree_node_contain_p(root, NULL)) {
        is_passed = false;
    }

    if (avl_tree_node_contain_p(root, tmp)) {
        is_passed = false;
    }
    avl_tree_destroy(&tmp);

    tmp = avl_tree_node_find_max(root);
    if (!avl_tree_node_contain_p(root, tmp)) {
        is_passed = false;
    }

    fake = avl_tree_node_create(tmp, tmp->b_node.chain.nice);
    if (avl_tree_node_contain_p(root, fake)) {
        is_passed = false;
    }

    avl_tree_destroy(&fake);
    avl_tree_destroy(&root);

    test_result_print(SYM_2_STR(avl_tree_node_contain_p), is_passed);
    return;
}

static void
test_avl_tree_iterate(void)
{
    bool is_passed;
    struct avl_tree *root;
    struct avl_tree *tmp;
    sint64 nice;

    is_passed = true;
    root = test_avl_tree_sample(0x3813F, 0xAF3EC);

    avl_tree_iterate(root, &tree_iterate_handler, ORDER_PRE);
    if (root->b_node.chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    avl_tree_iterate(root, &tree_iterate_handler, ORDER_IN);
    nice = 0x1;
    while (!(tmp = avl_tree_node_find(root, nice)))
        nice++;
    if (tmp->b_node.chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    avl_tree_iterate(root, &tree_iterate_handler, ORDER_POST);
    tmp = avl_tree_node_find_max(root);
    if (tmp->b_node.chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    tmp = avl_tree_node_find_min(root);
    if (tmp->b_node.chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    avl_tree_destroy(&root);

    test_result_print(SYM_2_STR(avl_tree_iterate), is_passed);
    return;

}

static void
test_avl_tree_balanced_p(void)
{
    bool is_passed;
    struct avl_tree *root;
    struct avl_tree *tmp;

    is_passed = true;
    root = test_avl_tree_sample(0x183EA, 0xED264);
    if (!avl_tree_balanced_p(NULL)) {
        is_passed = false;
    }

    tmp = avl_tree_node_create(&is_passed, 0x1234);
    if (!avl_tree_balanced_p(tmp)) {
        is_passed = false;
    }
    avl_tree_destroy(&tmp);

    tmp = avl_tree_node_create(&is_passed, 0xFFFFE);
    binary_search_tree_node_insert((struct binary_search_tree *)root,
        (struct binary_search_tree *)tmp);
    tmp = avl_tree_node_create(&is_passed, 0xFFFFF);
    binary_search_tree_node_insert((struct binary_search_tree *)root,
        (struct binary_search_tree *)tmp);

    if (avl_tree_balanced_p(root)) {
        is_passed = false;
    }

    avl_tree_destroy(&root);

    test_result_print(SYM_2_STR(avl_tree_balanced_p), is_passed);
    return;
}
