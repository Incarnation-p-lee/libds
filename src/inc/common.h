#ifndef HAVE_COMMON_H
#define HAVE_COMMON_H

void memory_maps_obtain(void);
struct memory_maps * memory_maps_entry_find(char *name);

static inline FILE * memory_maps_proc_read(void);
static inline void memory_maps_filter_process(FILE *maps);
static inline void memory_maps_one_line_process(char *line, uint32 len);
static inline char * memory_maps_one_line_map_name(char *line);
static inline uint32 memory_maps_one_line_map_authority(char *line);
static inline void memory_maps_one_line_map_boundary(char *line, struct memory_maps *map);

/*
 * section info of binary
 */
struct memory_maps mmaps[MAP_ENTRY_MAX] = {
    {},
};

#endif
