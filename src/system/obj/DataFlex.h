#ifndef OBJ_DATAFLEX_H
#define OBJ_DATAFLEX_H

#include <stdio.h>

extern "C" void yyrestart(FILE*);
extern "C" int yylex();
extern char *yytext;
extern int yyleng;

#endif // OBJ_DATAFLEX_H
