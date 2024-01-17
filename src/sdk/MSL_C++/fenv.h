#ifndef _FENV_H
#define _FENV_H

#ifdef __cplusplus
extern "C" {
#endif

struct fenv_t;
struct fexcept_t;

int fegetround(void);
int fesetround(int round);

int fegetenv(fenv_t *envp);
int fesetenv(const fenv_t *envp);
int feupdateenv(const fenv_t *envp);

int feclearexcept(int excepts);
int feholdexcept(fenv_t *envp);
int feraiseexcept(int excepts);
int fetestexcept(int excepts);

int fegetexceptflag(fexcept_t *flagp, int excepts);
int fesetexceptflag(const fexcept_t *flagp, int excepts);

#ifdef __cplusplus
}
#endif

#endif
