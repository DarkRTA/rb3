#ifndef _SETJMP_H
#define _SETJMP_H

#ifdef __cplusplus
extern "C" {
#endif

struct jmp_buf; /* TODO */
#define setjmp(env)
void longjmp(struct jmp_buf env, int status);

#ifdef __cplusplus
}
#endif

#endif
