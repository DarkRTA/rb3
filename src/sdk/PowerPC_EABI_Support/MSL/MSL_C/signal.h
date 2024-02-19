#ifndef _SIGNAL_H
#define _SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* TODO
#define SIGABRT
#define SIGFPE
#define SIGILL
#define SIGINT
#define SIGSEGV
#define SIGTERM
*/

typedef int sig_atomic_t;

typedef void (*sig_func)(int sig);

/*
#define SIG_DFL
#define SIG_IGN
#define SIG_ERR
*/

sig_func signal(int sig, sig_func handler);
int raise(int sig);

#ifdef __cplusplus
}
#endif

#endif
