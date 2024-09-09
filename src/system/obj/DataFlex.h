#ifndef OBJ_DATAFLEX_H
#define OBJ_DATAFLEX_H

#include <stdio.h>

#include "DataFile_Flex.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void yyrestart(FILE*);
extern int yylex();

extern char *yytext;
extern int yyleng;

#ifdef __cplusplus
}
#endif

#endif // OBJ_DATAFLEX_H
