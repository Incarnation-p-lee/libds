#ifndef COMMON_DECLARATION_H
#define COMMON_DECLARATION_H


static inline FILE * memory_maps_proc_read(void);
static inline char * memory_maps_one_line_map_name(char *line);
static inline uint32 memory_maps_one_line_map_authority(char *line);
static inline uint32 prime_numeral_calculate_next(uint32 prime);
static inline void memory_maps_filter_process(FILE *maps);
static inline void memory_maps_one_line_map_boundary(char *line, struct memory_maps *map);
static inline void memory_maps_one_line_process(char *line, uint32 len);
static inline void option_one_parameter_process(struct option_set *opt, char *arg);
struct memory_maps * memory_maps_entry_find(char *name);
struct option_set * option_process(uint32 argc, char **argv);
uint32 prime_numeral_next(uint32 prime);
uint32 random_uint32_with_limit(uint32 lmt);
void memory_maps_obtain(void);

#endif