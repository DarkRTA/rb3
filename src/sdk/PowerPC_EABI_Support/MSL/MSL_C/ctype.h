#ifndef _CTYPE_H
#define _CTYPE_H

#include "MSL_Common/locale_def.h"
#include "MSL_Common/ctype_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */
/* Don't move ternary results to their own lines */
inline int isalnum(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_alnum);
}

inline int isalpha(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_alpha);
}

inline int isblank(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_blank);
}

inline int iscntrl(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_cntrl);
}

inline int isdigit(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_digit);
}

inline int isgraph(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_graph);
}

inline int islower(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_lower);
}

inline int isprint(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_print);
}

inline int ispunct(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_punct);
}

inline int isspace(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_space);
}

inline int isupper(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_upper);
}

inline int isxdigit(int c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->ctype_map_ptr[c] & ctype_xdigit);
}

inline int tolower(int c) {
    return (c < 0 || c >= 256) ? c : (int)(&_current_locale)->ctype_cmpt_ptr->lower_map_ptr[c];
}

inline int toupper(int c) {
    return (c < 0 || c >= 256) ? c : (int)(&_current_locale)->ctype_cmpt_ptr->upper_map_ptr[c];
}
/* clang-format on */

#ifdef __cplusplus
}
#endif

#endif
