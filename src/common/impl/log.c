void
libds_log_print(enum log_level lvl, const char *msg)
{
    assert_exit(NULL != logfile);

    if (msg) {
        switch (lvl) {
            case INFO:
                dp_fprintf(logfile, " >> %4s: %s", SYM_2_STR(INFO), msg);
                break;
            case WARN:
                dp_fprintf(logfile, " >> %4s: %s", SYM_2_STR(WARN), msg);
                break;
            case DBUG:
                dp_fprintf(logfile, " >> %4s: %s", SYM_2_STR(DBUG), msg);
                break;
            case ERRR:
                dp_fprintf(stdout,  " >> %4s: %s", SYM_2_STR(ERRR), msg);
                break;
            default:
                msg = "Unknown enum value of enum log_level.\n";
                dp_fprintf(logfile, " >> %4s: %s", SYM_2_STR(WARN), msg);
                break;
        }
    }
}

void
libds_log_file_create(void)
{
    logfile = dp_fopen(LOG_FNAME, "w");

    if (!logfile) {
        pr_log_err("Failed to create logfile.\n");
    }
}

void
libds_log_file_close(void)
{
    if (logfile) {
        dp_fclose(logfile);
        libds_log_memory_stat_print();
    }
}

static inline void
libds_log_memory_stat_print(void)
{
    dp_printf("  >> LIBDS Memory Usage Summary <<\n");
    dp_printf("    . Malloc  %10"U64_MDF_U"\n", malloc_cnt);
    dp_printf("    . Realloc %10"U64_MDF_U"\n", realloc_cnt);
    dp_printf("    . Free    %10"U64_MDF_U"\n", free_cnt);
    dp_printf("  >> Memory End <<\n\n");

    if (free_cnt != malloc_cnt) {
        dp_printf("Memory leak at dp_malloc %10"U64_MDF_U" <=> dp_free %10"U64_MDF_U"\n",
            malloc_cnt, free_cnt);
        dp_exit(1);
    }
}


