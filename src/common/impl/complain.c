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
complain_no_memory_p(void *ptr)
{
    if (NULL == ptr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        return false;
    }
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

