#include "common.hpp"

// fn_80259250
float Modulo(float f1, float f2) {
    if (f2 == 0.0f)
        return 0.0f;
    float tmp = FMod(f1, f2);
    if (tmp < 0.0f)
        tmp += f2;
    return tmp;
}