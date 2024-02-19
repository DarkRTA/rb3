#ifndef _MSL_ARITH_H
#define _MSL_ARITH_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

int abs(int n);
long labs(long n);
long long llabs(long long n);

div_t div(int x, int y);
ldiv_t ldiv(long x, long y);
lldiv_t lldiv(long long x, long long y);

#ifdef __cplusplus
}
#endif

#endif
