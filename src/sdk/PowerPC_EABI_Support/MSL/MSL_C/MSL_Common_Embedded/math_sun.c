
#include <math.h>
double scalbn(double arg, int exp) {
    int exp_2;
    double f = frexp(arg, &exp_2);
    exp_2 += exp;
    return ldexp(f, exp_2);
}
