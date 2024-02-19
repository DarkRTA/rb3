#ifndef _WCTYPE_H
#define _WCTYPE_H

#include "MSL_Common/locale_def.h"
#include "MSL_Common/wctype_api.h"
#include "MSL_Common/wint_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */
/* Don't move ternary results to their own lines */
static inline int iswalnum(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_alnum);
}

static inline int iswalpha(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_alpha);
}

static inline int iswblank(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_blank);
}

static inline int iswcntrl(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_cntrl);
}

static inline int iswdigit(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_digit);
}

static inline int iswgraph(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_graph);
}

static inline int iswlower(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_lower);
}

static inline int iswprint(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_print);
}

static inline int iswpunct(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_punct);
}

static inline int iswspace(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_space);
}

static inline int iswupper(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_upper);
}

static inline int iswxdigit(wint_t c) {
    return (c < 0 || c >= 256) ? 0 : (int)(_current_locale.ctype_cmpt_ptr->wctype_map_ptr[c] & wctype_xdigit);
}

static inline wint_t towlower(wint_t c) {
    return (c < 0 || c >= 256) ? c : (int)(&_current_locale)->ctype_cmpt_ptr->wlower_map_ptr[c];
}

static inline wint_t towupper(wint_t c) {
    return (c < 0 || c >= 256) ? c : (int)(&_current_locale)->ctype_cmpt_ptr->wupper_map_ptr[c];
}
/* clang-format on */

int iswctype(wint_t c);
wint_t towctrans(wint_t c, wctrans_t desc);
wctrans_t wctrans(const char *name);
wctype_t wctype(const char *name);

#ifdef __cplusplus
}
#endif
#endif
