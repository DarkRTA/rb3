/* Code submitted by Svante Seleborg, cleaned up by Tom St Denis */

#include "mycrypt.h"
#include <stdarg.h>

#ifdef MPI

mp_err mp_init_multi(mp_int *mp, ...) 
{
    mp_err res = MP_OKAY;      /* Assume ok until proven otherwise */
    int n = 0;                 /* Number of ok inits */
    mp_int* cur_arg = mp;
    va_list args;

    va_start(args, mp);        /* init args to next argument from caller */
    while (cur_arg != NULL) {
        if (mp_init(cur_arg) != MP_OKAY) {
            /* Oops - error! Back-track and mp_clear what we already
               succeeded in init-ing, then return error.
            */
            va_list clean_args;
            cur_arg = mp;
            va_start(clean_args, mp);
            while (n--) {
                mp_clear(cur_arg);
                cur_arg = va_arg(clean_args, mp_int*);
            }
            va_end(clean_args);
            res = MP_MEM;
            break;
        }
        n++;
        cur_arg = va_arg(args, mp_int*);
    }
    va_end(args);
    return res;                /* Assumed ok, if error flagged above. */
}

/*
    Clear all arguments given, ended by a NULL marker.
*/
void mp_clear_multi(mp_int *mp, ...) 
{
    mp_int* next_mp = mp;
    va_list args;
    va_start(args, mp);
    while (next_mp != NULL) {
        mp_clear(next_mp);
        next_mp = va_arg(args, mp_int*);
    }
    va_end(args);
}

#endif

