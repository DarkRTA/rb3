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

#ifdef __cplusplus
}
#endif

#endif // OBJ_DATAFLEX_H
