struct option_set *
option_process(uint32 argc, char **argv)
{
    uint32 iter;

    iter = 1;
    if (!*argv || !argv) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        opt_set.list = false;
        opt_set.iteration = DEFAULT_ITERATION_CNT;

        while (iter < argc) {
            option_one_parameter_process(&opt_set, argv[iter++]);
        }

        /*
         * if content of opt_set has not been set
         */
        if ('\0' == opt_set.content[0]) {
            strcpy(opt_set.content, "*.*.*");
        }
    }

    return &opt_set;
}

static inline void
option_one_parameter_process(struct option_set *opt, char *arg)
{
    char *tmp;
    uint32 len;
    uint32 iter;
    assert(NULL != arg);

    if ('-' == arg[0]) {
        if (!strcmp("-l", arg) || !strcmp("-list", arg)
            || !strcmp("--list", arg)) {
            opt->list = true;
        } else if (!strncmp("-i=", arg, strlen("-i="))
            || !strncmp("-iter=", arg, strlen("-iter="))
            || !strncmp("--iter=", arg, strlen("--iter="))) {
            tmp = strchr(arg, '=');
            tmp++;
            iter = atoi(tmp);

            if (!iter) {
                pr_log_info("Invalid iteration count, use default.\n");
                opt->iteration = DEFAULT_ITERATION_CNT;
            } else {
                opt->iteration = iter;
            }
        } else {
            pr_log_err("Invalid arguments specified.\n");
        }
    } else {
        len = strlen(arg);
        assert(len < CONTENT_LEN);

        strncpy(opt->content, arg, len);
        opt->content[len] = '\0';
    }
}
