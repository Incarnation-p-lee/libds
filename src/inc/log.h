#ifndef LOG_OF_LIBDS_H
#define LOG_OF_LIBDS_H

#define DEFAULT_LOG_FILE    "./ds.log"
#define SYM_2_STR(symbol)   (#symbol)
#define pr_log_info(msg)    libds_log_print(INFO, msg);
#define pr_log_warn(msg)    libds_log_print(WARN, msg);
#define pr_log_debug(msg)   libds_log_print(DEBUG, msg);
#define pr_log_err(msg)     \
  do {                           \
    libds_log_print(ERROR, msg); \
    exit(1);                     \
  } while (0);

enum log_level {
  INFO,
  WARN,
  ERROR,
  DEBUG,
};

static FILE *ds_log = NULL;


#endif
