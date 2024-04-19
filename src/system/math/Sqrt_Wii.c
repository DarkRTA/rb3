#include "macros.h"
double sqrt(register double f1) {
    register float f0 = f1;
    register float f2 = 0.5f, f3 = 3.0f, f4;
    ASM_BLOCK (
        frsqrte f1, f0 // f1 = 1/sqrt(f0)
        fmuls f4, f1, f1 // f4 = f1 * f1
        fmuls f1, f1, f2 // f1 *= f2
        fnmsubs f4, f4, f0, f3 // f4 = -((f4 * f0) - f3)
        fmuls f1, f4, f1 // f1 *= f4
        fsel f1, f1, f1, f0 // f1 = f0 > 0 ? f1 : f1
        fmuls f1, f0, f1 // f1 *= f0
    )
    return f1;
}
