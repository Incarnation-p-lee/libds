static inline struct binary_search_tree *
test_binary_search_tree_sample(uint64 range, uint32 node_count)
{
    struct binary_search_tree *retval;
    struct binary_search_tree *tmp;
    sint64 nice;
    uint32 i;

    retval = binary_search_tree_create();
    binary_search_tree_node_initial(retval, retval, 0);
    i = 1;

    while (i < node_count) {
        nice = (sint64)((rand() % range) - (range / 2));
        tmp = binary_search_tree_node_create(NULL, 0x0);
        binary_search_tree_node_initial(tmp, tmp, nice);
        binary_search_tree_node_insert(retval, &tmp);
        i++;
    }

    return retval;
}


static void
test_binary_search_tree_create(void)
{
    bool is_passed;
    struct binary_search_tree *tmp;

    is_passed = true;
    tmp = binary_search_tree_create();

    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0 != tmp->chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(binary_search_tree_create), is_passed);
    return;
}

static void
test_binary_search_tree_node_create(void)
{
    bool is_passed;
    struct binary_search_tree *tmp;

    is_passed = true;
    tmp = binary_search_tree_node_create(&is_passed, 0xdead);

    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0xdead != tmp->chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(binary_search_tree_node_create), is_passed);
    return;
}

static void
test_binary_search_tree_initial(void)
{
    bool is_passed;
    struct binary_search_tree *tmp;

    is_passed = true;
    tmp = binary_search_tree_node_create(&is_passed, 0xdead);
    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0xdead != tmp->chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_initial(tmp);
    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0 != tmp->chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(binary_search_tree_initial), is_passed);
    return;
}


static void
test_binary_search_tree_node_initial(void)
{
    bool is_passed;
    struct binary_search_tree *tmp;

    is_passed = true;
    tmp = binary_search_tree_create();
    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0 != tmp->chain.nice
        || NULL != doubly_linked_list_node_get_val(tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_node_initial(tmp, &is_passed, 0xdead);
    if (NULL != tmp->left || NULL != tmp->right) {
        is_passed = false;
    } else if (0xdead != tmp->chain.nice
        || &is_passed != doubly_linked_list_node_get_val(tmp->chain.link)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&tmp);

    test_result_print(SYM_2_STR(binary_search_tree_node_initial), is_passed);
    return;
}

static void
test_binary_search_tree_destroy(void)
{
    bool is_passed;
    struct binary_search_tree *tmp;

    is_passed = true;
    tmp = binary_search_tree_create();
    binary_search_tree_destroy(&tmp);

    if (NULL != tmp) {
        is_passed = false;
    }

    tmp = test_binary_search_tree_sample(0x12345, 0xABCDE);
    binary_search_tree_destroy(&tmp);

    if (NULL != tmp) {
        is_passed = false;
    }

    test_result_print(SYM_2_STR(binary_search_tree_destroy), is_passed);
    return;
}

static void
test_binary_search_tree_node_find(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;

    is_passed = true;
    root = test_binary_search_tree_sample(0x21234, 0xBCDEF);

    if (root != binary_search_tree_node_find(root, root->chain.nice)) {
        is_passed = false;
    }

    if (NULL != binary_search_tree_node_find(root, 0xFFFFFFF)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_min(root);
    if (tmp != binary_search_tree_node_find(root, tmp->chain.nice)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_max(root);
    if (tmp != binary_search_tree_node_find(root, tmp->chain.nice)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_node_find), is_passed);
    return;
}


static void
test_binary_search_tree_node_find_min(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;

    is_passed = true;
    root = test_binary_search_tree_sample(0x31234, 0x9ABCD);

    if (NULL != binary_search_tree_node_find_min(NULL)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_min(root);
    if (NULL != tmp->left) {
        is_passed = false;
    }

    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_node_find_min), is_passed);
    return;
}


static void
test_binary_search_tree_node_find_max(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;

    is_passed = true;
    root = test_binary_search_tree_sample(0x71234, 0x2ABCD);

    if (NULL != binary_search_tree_node_find_max(NULL)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_max(root);
    if (NULL != tmp->right) {
        is_passed = false;
    }

    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_node_find_max), is_passed);
    return;
}

static void
test_binary_search_tree_height(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    sint32 child;

    is_passed = true;
    root = test_binary_search_tree_sample(0x183F1, 0x1820C);
    if (-1 != binary_search_tree_height(NULL)) {
        is_passed = false;
    }

    child = MAX_S(binary_search_tree_height(root->left),
                  binary_search_tree_height(root->right));
    if (child + 1 != binary_search_tree_height(root)) {
        is_passed = false;
    }
    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_height), is_passed);
    return;
}

static void
test_binary_search_tree_node_contain_p(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;
    struct binary_search_tree *fake;

    is_passed = true;
    root = test_binary_search_tree_sample(0x37FD7, 0xAD31D);
    tmp = binary_search_tree_node_create(&is_passed, 0x1234);

    if (binary_search_tree_node_contain_p(root, NULL)) {
        is_passed = false;
    }

    if (binary_search_tree_node_contain_p(root, tmp)) {
        is_passed = false;
    }
    binary_search_tree_destroy(&tmp);

    tmp = binary_search_tree_node_find_max(root);
    if (!binary_search_tree_node_contain_p(root, tmp)) {
        is_passed = false;
    }

    fake = binary_search_tree_node_create(tmp, tmp->chain.nice);
    if (binary_search_tree_node_contain_p(root, fake)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&fake);
    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_node_contain_p), is_passed);
    return;
}

static void
test_binary_search_tree_node_insert(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;

    is_passed = true;
    root = test_binary_search_tree_sample(0xB4321, 0x31A2B);
    tmp = binary_search_tree_node_create(&is_passed, 0xFFDEA);

    if (NULL != binary_search_tree_node_find(root, tmp->chain.nice)) {
        is_passed = false;
    }

    binary_search_tree_node_insert(root, &tmp);
    if (tmp != binary_search_tree_node_find(root, tmp->chain.nice)) {
        is_passed = false;
    }

    if (tmp != binary_search_tree_node_insert(root, &tmp)) {
        is_passed = false;
    }

    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_node_insert), is_passed);
    return;
}


static void
test_binary_search_tree_node_remove(void)
{
    bool is_passed;
    sint64 nice;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;

    is_passed = true;
    root = test_binary_search_tree_sample(0xF4321, 0x2ABCD);
    nice = root->chain.nice;

    binary_search_tree_node_remove(&root, nice);
    if (NULL != binary_search_tree_node_find(root, nice)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_min(root);
    nice = tmp->chain.nice;
    binary_search_tree_node_remove(&root, nice);
    if (NULL != binary_search_tree_node_find(root, nice)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_max(root);
    nice = tmp->chain.nice;
    binary_search_tree_node_remove(&root, nice);
    if (NULL != binary_search_tree_node_find(root, nice)) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_create(&is_passed, 0x1A2B);
    binary_search_tree_node_remove(&tmp, tmp->chain.nice);
    if (NULL != tmp) {
        is_passed = false;
    }

    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_node_remove), is_passed);
    return;

}

static void
test_binary_search_tree_iterate(void)
{
    bool is_passed;
    struct binary_search_tree *root;
    struct binary_search_tree *tmp;

    is_passed = true;
    root = test_binary_search_tree_sample(0x312A1, 0x72B7C);

    binary_search_tree_iterate(root, &tree_iterate_handler, ORDER_PRE);
    if (root->chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    binary_search_tree_iterate(root, &tree_iterate_handler, ORDER_IN);
    tmp = binary_search_tree_node_find(root, 0x1234);
    if (tmp->chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    binary_search_tree_iterate(root, &tree_iterate_handler, ORDER_POST);
    tmp = binary_search_tree_node_find_max(root);
    if (tmp->chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    tmp = binary_search_tree_node_find_min(root);
    if (tmp->chain.link->id != 0xDEADu) {
        is_passed = false;
    }

    binary_search_tree_destroy(&root);

    test_result_print(SYM_2_STR(binary_search_tree_iterate), is_passed);
    return;
}
