/* NOTE : this header has no guards and is MEANT for multiple inclusion!
 * If you are using "header protection" option with your compiler,
 * please also find #pragma which disables it and put it here, to
 * allow reentrancy of this header.
 */

#ifndef _STLP_PROLOG_HEADER_INCLUDED
#  error STLport epilog header can not be included as long as prolog has not be included.
#endif

#if !defined (_STLP_DONT_REDEFINE_STD)
#  define std _STLP_STD
#endif

#undef _STLP_PROLOG_HEADER_INCLUDED /* defined in _prolog.h */
