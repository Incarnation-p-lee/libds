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

