#ifndef SORT_DECLARATION_H
#define SORT_DECLARATION_H


bool sort_data_sorted_p(void *data, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));
static inline void sort_cell_copy(void *to, void *from, uint32 size);
void insertion_sort(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));

#endif
