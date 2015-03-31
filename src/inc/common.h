#ifndef HAVE_COMMON_H
#define HAVE_COMMON_H

#define NAME_LEN 128
#define MAP_ENTRY_MAX 128

#define M_UKNW      0x1u
#define M_READ      0x1u << 1
#define M_WRITE     0x1u << 2
#define M_EXECUTE   0x1u << 3
#define M_SHARED    0x1u << 4
#define M_PRIVATE   0x1u << 5


struct memory_maps {
    char        name[NAME_LEN];
    uint32      authority;
    union {
        void    *begin;
        NUMERAL b_val;
    };
    union {
        void    *end;
        NUMERAL e_val;
    };
};

extern void libds_log_print(enum log_level lvl, const char *msg);

void memory_maps_obtain(void);

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
