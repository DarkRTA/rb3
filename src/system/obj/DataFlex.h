#ifndef OBJ_DATAFLEX_H
#define OBJ_DATAFLEX_H

#include <stdio.h>

#include "DataFile_Flex.h"

#ifdef __cplusplus
extern "C" {
#endif

enum DataToken {
    kDataTokenFinished,
    kDataTokenHex,
    kDataTokenFloat,
    kDataTokenInt,
    kDataTokenString,
    kDataTokenSymbol,
    kDataTokenQuotedSymbol,
    kDataTokenArrayOpen,
    kDataTokenArrayClose,
    kDataTokenPropertyOpen,
    kDataTokenPropertyClose,
    kDataTokenCommandOpen,
    kDataTokenCommandClose,
    kDataTokenDefine,
    kDataTokenAutorun,
    kDataTokenInclude,
    kDataTokenIncludeOptional,
    kDataTokenMerge,
    kDataTokenVar,
    kDataTokenUnhandled,
    kDataTokenIfdef,
    kDataTokenIfndef,
    kDataTokenUndef,
    kDataTokenElse,
    kDataTokenEndif,
};

extern void yyrestart(FILE*);
extern int yylex();

extern char *yytext;
extern int yyleng;

#ifdef __cplusplus
}
#endif

#endif // OBJ_DATAFLEX_H
