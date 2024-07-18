#ifndef _MSL_VA_LIST_DEF_H
#define _MSL_VA_LIST_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _va_arg_type {
    arg_ARGPOINTER,
    arg_WORD,
    arg_DOUBLEWORD,
    arg_ARGREAL
} _va_arg_type;

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];
typedef __va_list va_list;

void *__va_arg(va_list v_list, int type);

/* clang-format off */
#define va_start(ap, fmt)   ((void)fmt, __builtin_va_info(&ap))
#define va_arg(ap, t)       (*((t*)__va_arg(ap, _var_arg_typeof(t))))
/* #define va_copy(dest, src) TODO */
#define va_end(ap)          (void)0
/* clang-format on */

#ifdef __cplusplus
}
#endif

#endif
