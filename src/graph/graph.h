#ifndef HAVE_DEFINED_GRAPH_H
#define HAVE_DEFINED_GRAPH_H

#define GRAPH_VERTEX_INVALID     (void *)PTR_INVALID
#define GRAPH_VERTEX_DEFAULT     128
#define GRAPH_VERTEX_MAX_DEFAULT 1024
/* Open addressing hash need at least (2 * n + 1) space */
#define GRAPH_VERTEX_HASH_SIZE   (GRAPH_VERTEX_MAX_DEFAULT * 2 + 1)

#define GRAPH_LABEL_INVALID      0
#define GRAPH_LABEL_FIRST        1

#define GRAPH_ADJACENT_DEFAULT   GRAPH_VERTEX_DEFAULT
#define GRAPH_EDGE_DEFAULT       1024


extern bool array_queue_structure_illegal_p(s_array_queue_t *queue);
extern bool array_queue_empty_p(s_array_queue_t *queue);
extern s_array_queue_t * array_queue_create(void);
extern s_open_addressing_hash_t * open_addressing_hash_create(uint32 size);
extern void array_queue_destroy(s_array_queue_t **queue);
extern void open_addressing_hash_destroy(s_open_addressing_hash_t **hash);
extern void * open_addressing_hash_find(s_open_addressing_hash_t *hash, void *key);
extern void * array_queue_leave(s_array_queue_t *queue);

#endif

