#include "common.hpp"

// fn_8022FE48
int Modulo(int i1, int i2) {
    if (i2 == 0)
        return 0;
    int tmp = i1 % i2;
    if (tmp < 0)
        return tmp + i2;
    else
        return tmp;
}