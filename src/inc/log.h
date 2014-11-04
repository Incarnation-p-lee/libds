#ifndef LOG_OF_LIBDS_H
#define LOG_OF_LIBDS_H

int
libds_log_initial(void);
void
libds_log_close(void);
void
libds_log_print(enum log_level lvl, const char *msg);

#endif
