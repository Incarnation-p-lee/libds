void
libds_log_print(enum log_level lvl, const char *msg)
{
    if (msg) {
        switch (lvl) {
            case INFO:
                fprintf(logfile, " >> %4s: %s", SYM_2_STR(INFO), msg);
                break;
            case WARN:
                fprintf(logfile, " >> %4s: %s", SYM_2_STR(WARN), msg);
                break;
            case DBUG:
                fprintf(logfile, " >> %4s: %s", SYM_2_STR(DBUG), msg);
                break;
            case ERRR:
                fprintf(stdout,  " >> %4s: %s", SYM_2_STR(ERRR), msg);
                break;
            default:
                msg = "Unknown enum value of enum log_level.\n";
                fprintf(logfile, " >> %4s: %s", SYM_2_STR(WARN), msg);
                break;
        }
    }
}

void
libds_log_file_create(void)
{
    logfile = fopen(LOG_FNAME, "w");

    if (!logfile) {
        pr_log_err("Failed to create logfile.\n");
    }
}

void
libds_log_file_close(void)
{
    if (logfile) {
        fclose(logfile);
    }
}

