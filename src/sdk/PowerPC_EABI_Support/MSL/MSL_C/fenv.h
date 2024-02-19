#ifndef _FENV_H
#define _FENV_H

#ifdef __cplusplus
extern "C" {
#endif

struct fenv_t;
struct fexcept_t;

int fegetround(void);
int fesetround(int round);

int fegetenv(struct fenv_t *envp);
int fesetenv(const struct fenv_t *envp);
int feupdateenv(const struct fenv_t *envp);

int feclearexcept(int excepts);
int feholdexcept(struct fenv_t *envp);
int feraiseexcept(int excepts);
int fetestexcept(int excepts);

int fegetexceptflag(struct fexcept_t *flagp, int excepts);
int fesetexceptflag(const struct fexcept_t *flagp, int excepts);

#ifdef __cplusplus
}
#endif

#endif
