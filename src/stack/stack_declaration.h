#ifndef HAVE_DEFINED_stack_H
#define HAVE_DEFINED_stack_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

#if defined DEBUG


#endif

bool array_stack_empty_p(s_array_stack_t *stack);
bool array_stack_full_p(s_array_stack_t *stack);
bool array_stack_space_structure_legal_p(s_array_stack_space_t *space);
bool array_stack_structure_legal_p(s_array_stack_t *stack);
bool linked_stack_empty_p(s_linked_stack_t *stack);
bool linked_stack_full_p(s_linked_stack_t *stack);
bool linked_stack_structure_legal_p(s_linked_stack_t *stack);
s_array_stack_t * array_stack_create(void);
s_linked_stack_t * linked_stack_create(void);
static inline bool array_stack_empty_ip(s_array_stack_t *stack);
static inline bool array_stack_full_ip(s_array_stack_t *stack);
static inline bool array_stack_structure_legal_ip(s_array_stack_t *stack);
static inline bool linked_stack_empty_ip(s_linked_stack_t *stack);
static inline bool linked_stack_full_ip(s_linked_stack_t *stack);
static inline bool linked_stack_space_empty_p(s_linked_stack_space_t *space);
static inline bool linked_stack_space_full_p(s_linked_stack_space_t *space);
static inline bool linked_stack_space_structure_legal_p(s_linked_stack_space_t *space);
static inline bool linked_stack_structure_legal_ip(s_linked_stack_t *stack);
static inline s_linked_stack_space_t * linked_stack_ptr_to_space(s_doubly_linked_list_t *link);
static inline s_linked_stack_space_t * linked_stack_space_create(uint32 dim);
static inline s_linked_stack_space_t * linked_stack_space_next(s_linked_stack_space_t *node);
static inline s_linked_stack_space_t * linked_stack_space_previous(s_linked_stack_space_t *node);
static inline s_linked_stack_space_t * linked_stack_space_remove(s_linked_stack_space_t *node);
static inline uint32 array_stack_rest_i(s_array_stack_t *stack);
static inline uint32 array_stack_size_i(s_array_stack_t *stack);
static inline uint32 linked_stack_capacity_i(s_linked_stack_t *stack);
static inline uint32 linked_stack_rest_i(s_linked_stack_t *stack);
static inline uint32 linked_stack_space_rest(s_linked_stack_space_t *space);
static inline void array_stack_resize_i(s_array_stack_t *stack, uint32 dim);
static inline void linked_stack_resize_i(s_linked_stack_t *stack, uint32 dim);
static inline void linked_stack_space_initial(s_linked_stack_space_t *space, uint32 dim);
static inline void linked_stack_space_iterate(s_linked_stack_space_t *space, void (*handler)(void *));
uint32 array_stack_capacity(s_array_stack_t *stack);
uint32 array_stack_rest(s_array_stack_t *stack);
uint32 array_stack_size(s_array_stack_t *stack);
uint32 linked_stack_capacity(s_linked_stack_t *stack);
uint32 linked_stack_rest(s_linked_stack_t *stack);
void * array_stack_pop(s_array_stack_t *stack);
void * array_stack_top(s_array_stack_t *stack);
void * linked_stack_pop(s_linked_stack_t *stack);
void * linked_stack_top(s_linked_stack_t *stack);
void array_stack_cleanup(s_array_stack_t *stack);
void array_stack_destroy(s_array_stack_t **stack);
void array_stack_iterate(s_array_stack_t *stack, void (*handler)(void *));
void array_stack_push(s_array_stack_t *stack, void *member);
void array_stack_resize(s_array_stack_t *stack, uint32 dim);
void linked_stack_cleanup(s_linked_stack_t *stack);
void linked_stack_destroy(s_linked_stack_t **stack);
void linked_stack_iterate(s_linked_stack_t *stack, void (*handler)(void *));
void linked_stack_push(s_linked_stack_t *stack, void *member);
void linked_stack_resize(s_linked_stack_t *stack, uint32 dim);

#endif

