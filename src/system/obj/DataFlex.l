/*
 * requires the following commit of flex:
 * https://github.com/westes/flex/commit/fe84af1738b78edeca58752c5a549a175236420a
 *
 * run with the following command-line args in the root of the repo:
 * -L "-osrc/system/obj/DataFlex.c" "src/system/obj/DataFlex.l"
 */

/* %option nounistd - not supported on the version of flex used */
%option never-interactive
%option noyywrap

%{
/* This version of Flex is stupid and doesn't include this under C mode for malloc/realloc */
#include <stdlib.h>

#include "DataFlex.h"

#define YY_INPUT(buf, result, max_size) \
    (result) = (DataInput((buf), 1) != 0)

#ifdef DATAFLEX_TESTER
#define TESTER_TERMINATE() yyterminate()
#define TESTER_RETURN(value) return value
#else
#define TESTER_TERMINATE()
#define TESTER_RETURN(value)
#endif

#define ECHO TESTER_RETURN(kDataTokenNotRecognized) /* don't echo unmatched characters */
%}

/* TODO: '-' has a significant usage outside of SIGN */

DIGIT               [0-9]
HEX_DIGIT           [A-Fa-f0-9]
SIGN                [+-]

HEX_NUMBER          0x{HEX_DIGIT}+
INTEGER             {SIGN}?{DIGIT}+
FLOAT               {SIGN}?{DIGIT}*\.{DIGIT}*
FLOAT_EXPONENT      {SIGN}?{DIGIT}*\.{DIGIT}*[Ee]{SIGN}?{DIGIT}+

IDENTIFIER          [^ \t\n\r\(\)\[\]\{\}]+

SYMBOL              {IDENTIFIER}
VARIABLE            \${IDENTIFIER}
QUOTED_SYMBOL       \'[^\']*\'
STRING              \"[^\"]*\"

COMMENT             ;[^\n]*

%x BLOCK_COMMENT
/* BUG: /** won't start a block */
BCOMMENT_START      (\/\*)+[^\n\*]*
BCOMMENT_TEXT       [^\n\*]*
BCOMMENT_SKIP       \*+[^\n\/\*]*
BCOMMENT_END        \*+\/

%%
\r                                                  { /* skip carriage returns */ TESTER_RETURN(kDataTokenCarriageReturn); }
\n                                                  { gDataLine++; TESTER_RETURN(kDataTokenNewline); }
{STRING}                                            { return kDataTokenString; }
{QUOTED_SYMBOL}                                     { return kDataTokenQuotedSymbol; }
{BCOMMENT_START}                                    { BEGIN(BLOCK_COMMENT); TESTER_RETURN(kDataTokenBlockCommentStart); }
<BLOCK_COMMENT>{BCOMMENT_TEXT}                      { /* ignore text in block comments */ TESTER_RETURN(kDataTokenBlockCommentText); }
<BLOCK_COMMENT>{BCOMMENT_SKIP}                      { /* ignore *s in block comments */ TESTER_RETURN(kDataTokenBlockCommentSkip); }
<BLOCK_COMMENT>\n                                   { gDataLine++; TESTER_RETURN(kDataTokenBlockCommentNewline); }
<BLOCK_COMMENT>{BCOMMENT_END}                       { BEGIN(INITIAL); TESTER_RETURN(kDataTokenBlockCommentEnd); }
{COMMENT}                                           { /* skip comments */ TESTER_RETURN(kDataTokenComment); }
kDataUnhandled                                      { return kDataTokenUnhandled; }

{HEX_NUMBER}                                        { return kDataTokenHex; }
{INTEGER}                                           { return kDataTokenInt; }
{FLOAT}                                             { return kDataTokenFloat; }
{FLOAT_EXPONENT}                                    { TESTER_RETURN(kDataTokenFloatExp); return kDataTokenFloat; }

#include_opt                                        { return kDataTokenIncludeOptional; }
#include                                            { return kDataTokenInclude; }
#merge                                              { return kDataTokenMerge; }
#ifdef                                              { return kDataTokenIfdef; }
#undef                                              { return kDataTokenUndef; }
#ifndef                                             { return kDataTokenIfndef; }
#else                                               { return kDataTokenElse; }
#endif                                              { return kDataTokenEndif; }
#define                                             { return kDataTokenDefine; }
#autorun                                            { return kDataTokenAutorun; }
#{IDENTIFIER}                                       { DataFail("bad # directive"); TESTER_TERMINATE(); }

{VARIABLE}                                          { return kDataTokenVar; }
{SYMBOL}                                            { return kDataTokenSymbol; }

\(                                                  { return kDataTokenArrayOpen; }
\)                                                  { return kDataTokenArrayClose; }
\{                                                  { return kDataTokenCommandOpen; }
\}                                                  { return kDataTokenCommandClose; }
\[                                                  { return kDataTokenPropertyOpen; }
\]                                                  { return kDataTokenPropertyClose; }
%%

#ifdef DATAFLEX_TESTER
/* This version of Flex is even more stupid and doesn't reset the lexing state when restarting */
void yy_actually_restart(YY_ONLY_ARG) {
    BEGIN(INITIAL);
    yyrestart(NULL YY_CALL_LAST_ARG);
}
#endif
