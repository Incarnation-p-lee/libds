void
memory_maps_obtain(void)
{
    FILE *maps;

    maps = memory_maps_proc_read();
    memory_maps_filter_process(maps);
    fclose(maps);

    return;
}

struct memory_maps *
memory_maps_entry_find(char *name)
{
    struct memory_maps *iter;

    iter = NULL;
    if (!name) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        iter = mmaps;
        while (iter < mmaps + MAP_ENTRY_MAX) {
            if (!strncmp(name, iter->name, strlen(name))) {
                break;
            }
            iter++;
        }
    }

    return iter;
}

static inline FILE *
memory_maps_proc_read(void)
{
    char ffname[NAME_LEN];
    FILE *maps;

    sprintf(ffname, "/proc/%u/maps", (uint32)getpid());
    maps = fopen(ffname, "r");

    return maps;
}

static inline void
memory_maps_filter_process(FILE *maps)
{
    char line[NAME_LEN];

    while (fgets(line, NAME_LEN, maps)) {
        memory_maps_one_line_process(line, strlen(line));
        memset(line, 0, sizeof(line));
    }
}

static inline void
memory_maps_one_line_process(char *line, uint32 len)
{
    static struct memory_maps *start = mmaps;
    char *name;

    assert(len <= NAME_LEN);
    if ((uint32)(start - mmaps) == MAP_ENTRY_MAX) {
        pr_log_err("Touch the end of the array, may override.\n");
    }

    name = memory_maps_one_line_map_name(line);
    if (name) {
        strncpy(start->name, name, strlen(name));
        start->authority = memory_maps_one_line_map_authority(line);
        memory_maps_one_line_map_boundary(line, start);
    }
    start++;

    return;
}

static inline char *
memory_maps_one_line_map_name(char *line)
{
    char *tmp;

    tmp = strchr(line, '/');
    if (!tmp) { /* For [stack] */
        tmp = strchr(line, '[');
    }

    return tmp;
}

static inline uint32
memory_maps_one_line_map_authority(char *line)
{
    char *tmp;
    uint32 retval;

    tmp = strchr(line, ' ');
    tmp++;

    retval = 0u;
    while (' ' != *tmp) {
        switch ((uint32)*tmp) {
            case 'r':
                 retval += M_READ;
                 break;
            case 'w':
                 retval += M_WRITE;
                 break;
            case 'x':
                 retval += M_EXECUTE;
                 break;
            case 's':
                 retval += M_SHARED;
                 break;
            case 'p':
                 retval += M_PRIVATE;
                 break;
            default:
                 break;
        }
        tmp++;
    }

    return retval;
}

static inline void
memory_maps_one_line_map_boundary(char *line, struct memory_maps *map)
{
   /* %lx can handle both 32 adn 64 bits with long type */
   sscanf(line, "%lx-%lx ", &map->b_val, &map->e_val);
}
