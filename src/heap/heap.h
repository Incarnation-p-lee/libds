#ifndef HAVE_HEAP_H
#define HAVE_HEAP_H

#define HEAP_ROOT_INDEX          0x1u
#define DEFAULT_BINARY_HEAP_SIZE 4097

#define INDEX_LEFT_CHILD(index)  (index) * 2
#define INDEX_RIGHT_CHILD(index) ((index) * 2 + 1)
#define INDEX_PARENT(index)      ((index) / 2)
#define INDEX_LAST(heap)         ((heap)->size)

#define HEAP_PARENT_NICE(heap, index)      (heap)->base[INDEX_PARENT(index)]->nice
#define HEAP_LEFT_CHILD_NICE(heap, index)  (heap)->base[INDEX_LEFT_CHILD(index)]->nice
#define HEAP_RIGHT_CHILD_NICE(heap, index) (heap)->base[INDEX_RIGHT_CHILD(index)]->nice
#define HEAP_NICE(heap, index)             (heap)->base[index]->nice
#define HEAP_LINK(heap, index)             (heap)->base[index]->link
#define HEAP_SIZE(heap)                    (heap)->size
#define HEAP_CHAIN(heap, index)            (heap)->base[index]


/* array of base will skip index 0, and started at index 1 */
#define heap_iterate_start(heap)   ((heap)->base + 1)
#define heap_iterate_limit(heap)   ((heap)->base + (heap)->size + 1)

#define u_offset(n, offset) (n + offset)


/* EXTERNAL FUNCTIONS */
extern void doubly_linked_list_destroy(struct doubly_linked_list **head);
extern struct doubly_linked_list * doubly_linked_list_node_create(void *val, uint32 sid);
extern void doubly_linked_list_node_insert_after(struct doubly_linked_list *cur, struct doubly_linked_list *node);
/* END OF EXTERNAL FUNCTIONS */


/* BINARY HEAP INTERNAL */
static inline struct binary_heap * binary_heap_create(uint32 capacity);
static inline void binary_heap_initial(struct binary_heap *heap, uint32 capacity);
static inline void binary_heap_destroy(struct binary_heap **heap);
static inline bool binary_heap_empty_p(struct binary_heap *heap);
static inline bool binary_heap_full_p(struct binary_heap *heap);
static inline void binary_heap_cleanup(struct binary_heap *heap);
static inline struct doubly_linked_list * binary_heap_node_root(struct binary_heap *heap);
static inline struct doubly_linked_list * binary_heap_node_find(struct binary_heap *heap, sint64 nice);
static inline void binary_heap_capacity_extend(struct binary_heap *heap);
static inline uint32 binary_heap_percolate_up(struct binary_heap *heap, uint32 index, sint64 nice);
static inline void binary_heap_percolate_down(struct binary_heap *heap, uint32 index);
static inline struct collision_chain * binary_heap_collision_chain_create(sint64 nice, void *val);
static inline void binary_heap_node_create_by_index(struct binary_heap *heap, uint32 index, sint64 nice, void *val);
static inline struct doubly_linked_list * binary_heap_node_destroy_by_index(struct binary_heap *heap, uint32 index);
static inline uint32 binary_heap_index_get_by_nice(struct binary_heap *heap, sint64 nice);
/* END OF BINARY HEAP INTERNAL */

/* MINIMAL HEAP */
struct minimal_heap * minimal_heap_create(uint32 capacity);
void minimal_heap_destroy(struct minimal_heap **heap);
bool minimal_heap_empty_p(struct minimal_heap *heap);
bool minimal_heap_full_p(struct minimal_heap *heap);
void minimal_heap_cleanup(struct minimal_heap *heap);
struct doubly_linked_list * minimal_heap_node_find(struct minimal_heap *heap, sint64 nice);
struct doubly_linked_list * minimal_heap_node_find_min(struct minimal_heap *heap);
void minimal_heap_node_insert(struct minimal_heap *heap, void *val, sint64 nice);
struct doubly_linked_list * minimal_heap_node_remove_min(struct minimal_heap *heap);
/* END OF MINIMAL HEAP */

#endif
