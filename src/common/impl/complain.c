bool
complain_null_pointer_p(void *ptr)
{
    if (NULL == ptr) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else {
        return false;
    }
}

bool
complain_null_string_p(char *string)
{
    if (NULL == string) {
        pr_log_warn("Attempt to access NULL pointer.\n");
        return true;
    } else if (string[0] == '\0') {
        return true;
    } else {
        return false;
    }
}

bool
complain_no_memory_p(void *ptr)
{
    if (NULL == ptr) {
        pr_log_err("Fail to get memory from system.\n");
    }

    return false;
}

bool
complain_zero_size_p(uint32 size)
{
    if (0 == size) {
        pr_log_warn("Zero size detected.\n");
        return true;
    } else {
        return false;
    }
}

void
complain_assert_caution(char *msg, const char *fname, const char *func,
    uint32 line)
{
    if (msg && fname && func) {
        dp_printf("COMPLAIN ASSERTION: => [33m%s[0m [31mFail[0m ... \n"
                  "  In function %s\n"
                  "  At file %s +%d\n", msg, func, fname, line);
    }
}

void
complain_assert_exit(char *msg, const char *fname, const char *func,
    uint32 line)
{
    complain_assert_caution(msg, fname, func, line);
    *(uint32 *)0 = 0;
}

