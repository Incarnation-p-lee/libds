#ifndef HAVE_DEFINED_sort_H
#define HAVE_DEFINED_sort_H

bool sort_data_sorted_p(void *data, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline bool sort_parameters_legal_p(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline uint32 shell_sort_exponet_get(uint32 size);
static inline uint32 shell_sort_hibbard_increment_seq(uint32 k);
static inline void * quick_sort_obtain_median(void *base, uint32 left, uint32 right, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline void heap_sort_build_heap(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline void heap_sort_percolate_down(void *base, uint32 size, uint32 csize, uint32 index, sint32 (*compare)(const void *, const void *));
static inline void merge_sort_divide_merge(void *base, void *tmp, uint32 left, uint32 med, uint32 right, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline void merge_sort_recursive(void *base, void *tmp, uint32 left, uint32 right, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline void quick_sort_recursive(void *base, uint32 left, uint32 right, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline void sort_cell_copy(void *to, void *from, uint32 size);
static inline void sort_cell_swap(void *a, void *b, uint32 size);
void heap_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
void insertion_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
void merge_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
void quick_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
void shell_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));

#endif

