#ifndef HAVE_HASH_H
#define HAVE_HASH_H

extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern struct doubly_linked_list * doubly_linked_list_create(void);
extern void doubly_linked_list_insert_after(struct doubly_linked_list *list, void *val);
extern s_doubly_linked_list_t * doubly_linked_list_remove(s_doubly_linked_list_t **list);
extern void doubly_linked_list_initial(s_doubly_linked_list_t *list);
extern bool doubly_linked_list_structure_legal_p(s_doubly_linked_list_t *list);

#define HASHING_TABLE_LOAD_FACTOR(table) ((table)->load.amount * 100 / (table)->load.size)
#define BITMAP_NATIVE_BYTES              sizeof(native_wide_t)
#define BITMAP_NATIVE_BITS               (BITMAP_NATIVE_BYTES * 8)

#if defined DEBUG
    #define BITMAP_LEGAL_P(bitmap)       bitmap_structure_legal_ip(bitmap)
    #define BITMAP_ILLEGAL_P(bitmap)     bitmap_structure_illegal_ip(bitmap)
#else
    #define BITMAP_LEGAL_P(bitmap)       NON_NULL_PTR_P(bitmap)
    #define BITMAP_ILLEGAL_P(bitmap)     NULL_PTR_P(bitmap)
#endif

#endif
