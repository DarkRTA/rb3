#ifndef OBJ_DATAFLEX_TARGET_H
#define OBJ_DATAFLEX_TARGET_H

#include <stdio.h>

#include "DataFile_Flex.h"
#include "DataFlex.h"

namespace yytarget {
    extern void yyrestart(FILE*);
    extern int yylex();

    extern void yy_actually_restart();

    extern FILE *yyin, *yyout;

    extern char *yytext;
    extern int yyleng;
}

#endif
