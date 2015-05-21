struct option_set *
option_process(uint32 argc, char **argv)
{
    uint32 iter;

    iter = 1;
    if (!*argv || !argv) {
        pr_log_warn("Attempt to access NULL pointer.\n");
    } else {
        while (iter < argc) {
            option_one_parameter_process(&opt_set, argv[iter++]);
        }

        /* if content of opt_set has not been set */
        if ('\0' == opt_set.content[0]) {
            strcpy(opt_set.content, "*.*.*");
        }
    }

    return &opt_set;
}

static inline void
option_one_parameter_process(struct option_set *opt, char *arg)
{
    uint32 len;
    assert(NULL != arg);

    if ('-' == arg[0]) {
        if (!strncmp("-l", arg, strlen(arg))
            || !strncmp("-list", arg, strlen(arg))
            || !strncmp("--list", arg, strlen(arg))) {
            opt->list = true;
        } else {
            opt->list = false;
        }
    } else {
        len = strlen(arg);
        assert(len < CONTENT_LEN);
        strncpy(opt->content, arg, len);
        opt->content[len] = '\0';
    }

    return;
}
