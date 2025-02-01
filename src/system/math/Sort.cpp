#include "math/Sort.h"

int HashString(const char *str, int i) {
    int ret = 0;
    for (unsigned char *u = (unsigned char *)str; *u != 0; u++) {
        ret = (*u + ret * 0x7F) % i;
    }
    return ret;
}
