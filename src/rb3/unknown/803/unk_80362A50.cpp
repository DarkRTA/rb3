#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "common.hpp"

// fn_80362A50
// searches for occurrences of substring substr_old within string src, and replaces each
// occurrence with substr_new. the result goes in dest. if a change was made, this fn
// returns true. if no changes to the original string were made, return false
bool SearchReplace(
    const char *src, const char *substr_old, const char *substr_new, char *dest
) {
    bool changed;
    int temp_r31;
    char *temp_r3;

    *dest = 0;
    changed = false;

    while (true) {
        temp_r3 = strstr(src, substr_old);
        if (temp_r3 == 0)
            break;
        temp_r31 = temp_r3 - src;
        strncat(dest, src, temp_r31);
        strcat(dest, substr_new);
        src = strlen(substr_old) + (src + temp_r31);
        changed = true;
    }

    strcat(dest, src);
    return changed;
}

// fn_80362AF4
// sorta like strncpy, except for the return value
// returns true if the copy operation was terminated because of reaching the maximum
// length or encountering the end of src, and 0 otherwise.
bool StrNCopy(char *dest, const char *src, int cnt) {
    int var_r5_2;
    char temp_r0;
    bool max_len_reached;
    char *var_r3;
    char *var_r4;

    var_r3 = dest;
    var_r4 = (char *)src;
    var_r5_2 = cnt - 1;

    while (*var_r4 != 0 && (var_r5_2 != 0)) {
        temp_r0 = *var_r4++;
        *var_r3++ = temp_r0;
        var_r5_2--;
    }

    max_len_reached = false;
    *var_r3 = 0;
    if ((var_r5_2 != 0) || (*var_r4 == 0)) {
        max_len_reached = true;
    }
    return max_len_reached;
}

// fn_80362D14 - a destructor for some derived class from TextStream

// fn_80362C94 - a destructor for some derived class from fn_80362D14?