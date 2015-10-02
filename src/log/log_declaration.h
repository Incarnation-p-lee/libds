#ifndef LOG_DECLARATION_H
#define LOG_DECLARATION_H


void libds_log_file_close(void);
void libds_log_file_create(void);
void libds_log_print(enum log_level lvl, const char *msg);

#endif
