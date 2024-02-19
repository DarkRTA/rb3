#ifndef _MSL_SECURE_ERROR_H
#define _MSL_SECURE_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*msl_constraint_handler)(int,int,int);

void __msl_runtime_constraint_violation_s(int param1, int param2, int param3);

#ifdef __cplusplus
}
#endif

#endif
