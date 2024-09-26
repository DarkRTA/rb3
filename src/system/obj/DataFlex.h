#ifndef OBJ_DATAFLEX_H
#define OBJ_DATAFLEX_H

#include <stdio.h>

#include "DataFile_Flex.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DATAFLEX_TESTER
enum DataToken {
    kDataTokenFinished,
    kDataTokenNotRecognized,

    kDataTokenNewline,
    kDataTokenCarriageReturn,

    kDataTokenComment,
    kDataTokenBlockCommentStart,
    kDataTokenBlockCommentText,
    kDataTokenBlockCommentSkip,
    kDataTokenBlockCommentNewline,
    kDataTokenBlockCommentEnd,

    kDataTokenHex,
    kDataTokenFloat,
    kDataTokenFloatExp,
    kDataTokenInt,

    kDataTokenString,
    kDataTokenSymbol,
    kDataTokenQuotedSymbol,
    kDataTokenVar,
    kDataTokenUnhandled,

    kDataTokenArrayOpen,
    kDataTokenArrayClose,
    kDataTokenPropertyOpen,
    kDataTokenPropertyClose,
    kDataTokenCommandOpen,
    kDataTokenCommandClose,

    kDataTokenDefine,
    kDataTokenUndef,
    kDataTokenInclude,
    kDataTokenIncludeOptional,
    kDataTokenMerge,
    kDataTokenAutorun,

    kDataTokenIfdef,
    kDataTokenIfndef,
    kDataTokenElse,
    kDataTokenEndif,
};
#else
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
    kDataTokenUndef,
    kDataTokenIfndef,
    kDataTokenElse,
    kDataTokenEndif,
};
#endif

extern void yyrestart(FILE*);
extern int yylex();

extern void yy_actually_restart();

extern FILE *yyin, *yyout;

extern char *yytext;
extern int yyleng;

#ifdef __cplusplus
}
#endif

#endif // OBJ_DATAFLEX_H
