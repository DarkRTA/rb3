#include "arith.h"

int abs(int n) {
    return ((n >> 31) ^ n) - (n >> 31);
}
