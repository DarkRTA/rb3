#include "decomp.h"
double sqrt(register double value) {
    register float fValue = value; // f0
    register float f_1, half = 0.5f, three = 3.0f, f_4;

    ASM_BLOCK (
        frsqrte  f_1, fValue              // f_1 = 1/sqrt(fValue)
        fmuls    f_4, f_1, f_1            // f_4 = f_1 * f_1
        fmuls    f_1, f_1, half           // f_1 *= half
        fnmsubs  f_4, f_4, fValue, three  // f_4 = -((f_4 * fValue) - three)
        fmuls    f_1, f_4, f_1            // f_1 *= f_4
        fsel     f_1, f_1, f_1, fValue    // f_1 = fValue > 0 ? f_1 : f_1
        fmuls    value, fValue, f_1       // f_1 *= fValue
    )

    return value;
}
