#ifndef HAVE_TREE_H
#define HAVE_TREE_H

enum ITER_ORDER {
    ORDER_START,
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_END,
};

#define TREE_NICE_PLUS_LMT  0x7fffffffffffffff
#define TREE_NICE_MINUS_LMT (-TREE_NICE_PLUS_LMT - 1)

#define LEGAL_ORDER_P(x) ((x) > ORDER_START && (x) < ORDER_END) ? true : false

extern void doubly_linked_list_initial(struct doubly_linked_list *);
extern struct doubly_linked_list * doubly_linked_list_merge(struct doubly_linked_list *m, struct doubly_linked_list *n);
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern void doubly_linked_list_iterate(struct doubly_linked_list *head, void (*handler)(void *));

/* BINARY SEARCH TREE */
static inline void binary_search_tree_node_initial_internal(struct binary_search_tree *node, void *val, sint64 nice);
static inline void binary_search_tree_initial_internal(struct binary_search_tree *tree);
static inline void binary_search_tree_node_destroy(struct binary_search_tree *node);
static inline void binary_search_tree_destroy_internal(struct binary_search_tree **tree);
static inline void binary_search_tree_node_child_lt_doubly_strip(struct binary_search_tree **pre, struct binary_search_tree *node);
static inline void binary_search_tree_node_collision_chain_copy(struct collision_chain *tgt, struct collision_chain *node);
static inline void binary_search_tree_node_collision_chain_swap(struct collision_chain *m_node, struct collision_chain *n_node);
static inline void binary_search_tree_node_child_clean(struct binary_search_tree *node);
static inline void binary_search_tree_iterate_internal(struct binary_search_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
static inline void binary_search_tree_node_chain_copy(struct collision_chain *tgt, struct collision_chain *node);
static inline void binary_search_tree_node_chain_swap(struct collision_chain *m, struct collision_chain *n);
static inline bool binary_search_tree_node_contains_p_internal(struct binary_search_tree *tree, struct binary_search_tree *node);
static inline bool binary_search_tree_node_leaf_p(struct binary_search_tree *node);
static inline bool binary_search_tree_child_doubly_p(struct binary_search_tree *node);
static inline sint32 binary_search_tree_height_internal(struct binary_search_tree *tree);
static inline struct binary_search_tree * binary_search_tree_create_internal(void);
static inline struct binary_search_tree * binary_search_tree_node_create_internal(void *val, sint64 nice);
static inline struct binary_search_tree * binary_search_tree_node_find_internal(struct binary_search_tree *tree, sint64 nice);
static inline struct binary_search_tree * binary_search_tree_node_find_min_internal(struct binary_search_tree *tree);
static inline struct binary_search_tree * binary_search_tree_node_find_max_internal(struct binary_search_tree *tree);
static inline struct binary_search_tree * binary_search_tree_node_insert_internal(struct binary_search_tree *tree, struct binary_search_tree *node);
static inline struct binary_search_tree * binary_search_tree_node_child_doubly_strip(struct binary_search_tree **pre, struct binary_search_tree *node);
static inline struct binary_search_tree * binary_search_tree_node_remove_internal(struct binary_search_tree **tree, sint64 nice);
static inline struct binary_search_tree ** binary_search_tree_node_find_ptr_to_max(struct binary_search_tree **tree);
static inline struct binary_search_tree ** binary_search_tree_node_find_ptr_to_min(struct binary_search_tree **tree);

static inline bool avl_tree_height_sync_with_calculated_p(struct avl_tree *node, sint32 left, sint32 right);

bool binary_search_tree_node_contains_p(struct binary_search_tree *root, struct binary_search_tree *node);
void binary_search_tree_initial(struct binary_search_tree *root);
void binary_search_tree_node_initial(struct binary_search_tree *node, void *val, sint64 nice);
void binary_search_tree_destroy(struct binary_search_tree **root);
void binary_search_tree_iterate(struct binary_search_tree *root, void (*handle)(void *), enum ITER_ORDER order);
void binary_search_tree_node_remove_and_destroy(struct binary_search_tree **tree, sint64 nice);
sint32 binary_search_tree_height(struct binary_search_tree *root);
struct binary_search_tree * binary_search_tree_node_find(struct binary_search_tree *root, sint64 nice);
struct binary_search_tree * binary_search_tree_node_insert(struct binary_search_tree *root, struct binary_search_tree *node);
struct binary_search_tree * binary_search_tree_node_find_min(struct binary_search_tree *root);
struct binary_search_tree * binary_search_tree_node_find_max(struct binary_search_tree *root);
struct binary_search_tree * binary_search_tree_create(void);
struct binary_search_tree * binary_search_tree_node_create(void *val, sint64 nice);
struct binary_search_tree * binary_search_tree_node_remove(struct binary_search_tree **root, sint64 nice);
/* END OF BINARY SEARCH TREE */


/* AVL TREE */
struct avl_tree * avl_tree_create(void);
struct avl_tree * avl_tree_node_create(void *val, sint64 nice);
void avl_tree_initial(struct avl_tree *tree);
void avl_tree_node_initial(struct avl_tree *node, void *val, sint64 nice);
static inline void avl_tree_node_destroy(struct avl_tree *node);
static inline void avl_tree_destroy_internal(struct avl_tree *tree);
void avl_tree_destroy(struct avl_tree **tree);
struct avl_tree * avl_tree_ptr_container_of(struct binary_search_tree *node);
struct avl_tree * avl_tree_node_find(struct avl_tree *tree, sint64 nice);
struct avl_tree * avl_tree_node_find_min(struct avl_tree *tree);
struct avl_tree * avl_tree_node_find_max(struct avl_tree *tree);
bool avl_tree_node_contains_p(struct avl_tree *tree, struct avl_tree *node);
static inline bool avl_tree_balanced_internal_p(struct avl_tree *tree);
bool avl_tree_balanced_p(struct avl_tree *tree);
static inline void avl_tree_height_update(struct avl_tree *tree);
static inline struct binary_search_tree * avl_tree_balance_single_rotate_left(struct binary_search_tree *k1);
static inline struct binary_search_tree * avl_tree_balance_single_rotate_right(struct binary_search_tree *k1);
static inline struct binary_search_tree * avl_tree_balance_doubly_rotate_left(struct binary_search_tree *k1);
static inline struct binary_search_tree * avl_tree_balance_doubly_rotate_right(struct binary_search_tree *k1);
static inline void avl_tree_balanced_on_height_internal_default(struct avl_tree *tree, bool *b);
static inline bool avl_tree_balanced_on_height_p(struct avl_tree *tree);
static inline void avl_tree_balance_remove_rotate_right(struct binary_search_tree **tree, struct binary_search_tree *node);
static inline struct binary_search_tree * avl_tree_node_remove_internal(struct binary_search_tree **tree, sint64 nice);
struct avl_tree * avl_tree_node_remove(struct avl_tree **tree, sint64 nice);
void avl_tree_node_remove_and_destroy(struct avl_tree **tree, sint64 nice);
static inline struct binary_search_tree * avl_tree_node_insert_internal(struct binary_search_tree **tree, struct binary_search_tree *node);
struct avl_tree * avl_tree_node_insert(struct avl_tree **tree, struct avl_tree *node);
void avl_tree_iterate(struct avl_tree *tree, void (*handle)(void *), enum ITER_ORDER order);
static inline void avl_tree_height_internal_default(struct avl_tree *node, sint32 *height);
static inline void avl_tree_balance_remove_rotate_left(struct binary_search_tree **tree, struct binary_search_tree *node);
static inline void avl_tree_balance_insert_rotate_left(struct binary_search_tree **tree, struct binary_search_tree *node);
static inline void avl_tree_balance_insert_rotate_right(struct binary_search_tree **tree, struct binary_search_tree *node);
static inline struct binary_search_tree * avl_tree_balance_child_doubly_strip(struct binary_search_tree *node);
static inline struct binary_search_tree * avl_tree_balance_child_doubly_strip_from_max(struct binary_search_tree *node);
static inline struct binary_search_tree * avl_tree_balance_child_doubly_strip_from_min(struct binary_search_tree *node);
static inline bool avl_tree_balanced_on_height_p_default(struct avl_tree *tree);
static inline void avl_tree_height_update(struct avl_tree *tree);
/* END OF AVL TREE */


/* SPLAY TREE */
/*
struct splay_tree * splay_tree_create(void);
struct splay_tree * splay_tree_node_create(void *val, sint64 nice);
void splay_tree_initial(struct splay_tree *tree);
void splay_tree_node_initial(struct splay_tree *node, void *val, sint64 nice);
void splay_tree_destroy(struct splay_tree **tree);
struct splay_tree * splay_tree_node_find(struct splay_tree **tree, sint64 nice);
struct splay_tree * splay_tree_node_find_max(struct splay_tree **tree);
struct splay_tree * splay_tree_node_find_min(struct splay_tree **tree);
bool splay_tree_node_contains_p(struct splay_tree *tree, struct splay_tree *node);
sint32 splay_tree_height(struct splay_tree *tree);
struct splay_tree * splay_tree_node_insert(struct splay_tree **tree, struct splay_tree *node);
struct splay_tree * splay_tree_node_remove(struct splay_tree **tree, sint64 nice);
void splay_tree_iterate(struct splay_tree *tree, void (*handle)(void *), enum ITER_ORDER order);

static void inline splay_tree_splaying_root_left(struct splay_tree **tree);
static void inline splay_tree_splaying_root_right(struct splay_tree **tree);
static void inline splay_tree_single_splaying_left(struct splay_tree **tree);
static void inline splay_tree_single_splaying_right(struct splay_tree **tree);
static void inline splay_tree_doubly_splaying_left(struct splay_tree **tree);
static void inline splay_tree_doubly_splaying_right(struct splay_tree **tree);
static void inline splay_tree_node_splaying_left(struct splay_tree **tree, sint64 nice, struct splay_tree *root);
static void inline splay_tree_node_splaying_right(struct splay_tree **tree, sint64 nice, struct splay_tree *root);
static inline struct splay_tree * splay_tree_node_find_internal(struct splay_tree **tree, sint64 nice, struct splay_tree *root);
static inline struct splay_tree * splay_tree_node_find_min_internal(struct splay_tree **tree, struct splay_tree *root);
static inline struct splay_tree * splay_tree_node_find_max_internal(struct splay_tree **tree, struct splay_tree *root);
static inline bool splay_tree_child_has_nice_p(struct splay_tree *node, sint64 nice);
static inline bool splay_tree_node_leaf_p(struct splay_tree *node);
*/
/* END OF SPLAY TREE */

#endif
