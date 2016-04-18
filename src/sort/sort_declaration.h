#ifndef SORT_DECLARATION_H
#define SORT_DECLARATION_H


static inline void sort_cell_copy(void *to, void *from, uint32 size);
void sort_insertion(void *base, uint32 size, uint32 csize, sint32 (*compare)(const void *, const void *));

#endif
