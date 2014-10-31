int
libds_log_initial(void)
{
  char *logfile = DEFAULT_LOG_FILE;
  int retval;

  retval = 0;

  if (!ds_log) {
    ds_log = fopen(logfile, "w");
    if (!ds_log) {
      retval = -1;
    }
  }

  return retval;
}

void
libds_log_close(void)
{
  if (ds_log) {
    fclose(ds_log);
  }

  return;
}

void
libds_log_print(enum log_level lvl, const char *msg)
{
  if (msg) {
    switch (lvl) {
      case INFO:
        fprintf(ds_log, "%5s >%s", SYM_2_STR(INFO), msg);
        break;
      case WARN:
        fprintf(ds_log, "%5s >%s", SYM_2_STR(WARN), msg);
        break;
      case ERROR:
        fprintf(stdout, "%5s >%s", SYM_2_STR(ERROR), msg);
        break;
      case DEBUG:
        fprintf(ds_log, "%5s >%s", SYM_2_STR(DEBUG), msg);
        break;
      default:
        msg = "Unknown enum value of enum log_level.\n";
        fprintf(ds_log , "%5s >%s", SYM_2_STR(WARN), msg);
        break;
    }
  }

  return;
}
