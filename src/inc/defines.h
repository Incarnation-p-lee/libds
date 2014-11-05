#ifndef HAVE_DEFINES_H
#define HAVE_DEFINES_H


#define true        1
#define false       0

#define DEFAULT_LOG_FILE    "./ds.log"
#define SYM_2_STR(symbol)   (#symbol)
#define pr_log_info(msg)    libds_log_print(INFO, msg);
#define pr_log_warn(msg)    libds_log_print(WARN, msg);
#define pr_log_debug(msg)   libds_log_print(DEBUG, msg);
#define pr_log_err(msg)     \
    do {                             \
        libds_log_print(ERROR, msg); \
        exit(1);                     \
    } while (0);

#endif
