#ifndef OBJ_DATAFLEX_TARGET_H
#define OBJ_DATAFLEX_TARGET_H

#include <stdio.h>

#include "DataFile_Flex.h"
#include "DataFlex.h"

namespace yytarget {
    extern void yyrestart(FILE*);
    extern int yylex();

    extern FILE *yyin, *yyout;

    extern char *yytext;
    extern int yyleng;
}

#endif
