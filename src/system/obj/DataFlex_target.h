#ifndef OBJ_DATAFLEX_TARGET_H
#define OBJ_DATAFLEX_TARGET_H

#include <stdio.h>

#include "DataFile_Flex.h"
#include "DataFlex.h"

namespace yytarget {

#ifdef YY_REENTRANT

    extern int yylex_init(void **out_globals);
    extern int yylex_destroy(void *yy_globals);

#ifndef YY_LAST_ARG
#define YY_LAST_ARG , void *yy_globals
#define YY_ONLY_ARG void *yy_globals
#endif

#else

    extern FILE *yyin, *yyout;

    extern char *yytext;
    extern int yyleng;

#ifndef YY_LAST_ARG
#define YY_LAST_ARG
#define YY_ONLY_ARG void
#endif

#endif

    extern int yylex(YY_ONLY_ARG);
    extern void yyrestart(FILE *file YY_LAST_ARG);

    extern char *yyget_text(YY_ONLY_ARG);
    extern int yyget_leng(YY_ONLY_ARG);

#ifdef DATAFLEX_TESTER
    extern void yy_actually_restart(YY_ONLY_ARG);
#endif

}

#endif
