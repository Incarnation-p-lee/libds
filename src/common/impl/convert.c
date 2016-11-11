/*
 * convert_string_to_uint32_array has a output argv 'uint32 *len'.
 */
uint32 *
convert_string_to_uint32_array(char *string, uint32 *len)
{
    uint32 *converted;
    uint32 i, string_len;

    if (!string || !len) {
        return PTR_INVALID;
    } else {
        string_len = dp_strlen(string);
        converted = dp_malloc(sizeof(*converted) * string_len);

        i = 0;
        while (i < string_len) {
            converted[i] = (uint32)string[i];
            i++;
        }

        *len = string_len;
        return converted;
    }
}

