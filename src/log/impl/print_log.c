void
libds_log_print(enum log_level lvl, const char *msg)
{
    if (msg) {
        switch (lvl) {
            case INFO:
                fprintf(stdout, "[34m%4s[0m < %s", SYM_2_STR(INFO), msg);
                break;
            case WARN:
                fprintf(stdout, "[35m%4s[0m < %s", SYM_2_STR(WARN), msg);
                break;
            case DBUG:
                fprintf(stdout, "[32m%4s[0m < %s", SYM_2_STR(DBUG), msg);
                break;
            case ERRR:
                fprintf(stdout, "[31m%4s[0m < %s", SYM_2_STR(ERRR), msg);
                break;
            default:
                msg = "Unknown enum value of enum log_level.\n";
                fprintf(stdout, "[35m%4s[0m < %s", SYM_2_STR(WARN), msg);
                break;
        }
    }

    return;
}
