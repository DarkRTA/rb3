#ifndef RUNTIME_GECKO_SETJMP_H
#define RUNTIME_GECKO_SETJMP_H

#ifdef __cplusplus
extern "C" {
#endif

struct __jmp_buf {
    unsigned long lr;
    unsigned long cr;
    unsigned long sp;
    unsigned long toc;
    unsigned long _padding1;
    unsigned long gprs[32 - 13];
    double fprs[(32 - 14) * 2];
    double fpscr;
    double _padding2;
};

int __setjmp(struct __jmp_buf* env);
void longjmp(struct __jmp_buf* env, int status);

#ifdef __cplusplus
}
#endif

#endif
