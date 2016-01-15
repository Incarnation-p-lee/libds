#ifndef HAVE_LINKED_LIST_OPTIMIZE_H
#define HAVE_LINKED_LIST_OPTIMIZE_H

#if defined OPT_HOT
    #define single_linked_list_remove_internal(node)      \
        single_linked_list_remove_internal_optimize(node)
#else
    #define single_linked_list_remove_internal(node)      \
        single_linked_list_remove_internal_default(node)
#endif

#endif
