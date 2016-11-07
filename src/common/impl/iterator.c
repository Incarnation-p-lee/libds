s_array_iterator_t *
array_iterator_create(void)
{
    s_array_iterator_t *iterator;

    iterator = dp_malloc(sizeof(*iterator));

    iterator->fp_index_initial = NULL;
    iterator->fp_next_exist_p = NULL;
    iterator->fp_next_obtain = NULL;

    return iterator;
}

bool
array_iterator_structure_legal_p(s_array_iterator_t *iterator)
{
    return array_iterator_structure_legal_ip(iterator);
}

static inline bool
array_iterator_structure_legal_ip(s_array_iterator_t *iterator)
{
    if (NULL_PTR_P(iterator)) {
        return false;
    } else if (!iterator->fp_index_initial) {
        return false;
    } else if (!iterator->fp_next_exist_p) {
        return false;
    } else if (!iterator->fp_next_obtain) {
        return false;
    } else {
        return true;
    }
}

void
array_iterator_initial(s_array_iterator_t *iterator,
               f_array_iterator_initial_t fp_index_initial,
            f_array_iterator_next_exist_t fp_next_exist_p,
           f_array_iterator_next_obtain_t fp_next_obtain)
{
    if (NULL_PTR_P(iterator)) {
        return;
    }

    // pr_log_err will exit program
    if (NULL_PTR_P(fp_index_initial)) {
        pr_log_err("Function pointer 'fp_index_initial' is NULL.");
    }

    if (NULL_PTR_P(fp_next_exist_p)) {
        pr_log_err("Function pointer 'fp_next_exist_p' is NULL.");
    }

    if (NULL_PTR_P(fp_next_obtain)) {
        pr_log_err("Function pointer 'fp_next_obtain' is NULL.");
    }

    iterator->index = 0;
    iterator->fp_index_initial = fp_index_initial;
    iterator->fp_next_exist_p = fp_next_exist_p;
    iterator->fp_next_obtain = fp_next_obtain;
}

void
array_iterator_destroy(s_array_iterator_t *iterator)
{
    if (array_iterator_structure_legal_ip(iterator)) {
        iterator->fp_index_initial = NULL;
        iterator->fp_next_exist_p = NULL;
        iterator->fp_next_obtain = NULL;

        dp_free(iterator);
    }
}

