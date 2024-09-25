/*
 * requires the following commit of flex:
 * https://github.com/westes/flex/commit/fe84af1738b78edeca58752c5a549a175236420a
 */

/* %option nounistd - not supported on the version of flex used */
%option never-interactive
%option noyywrap

%{
#include "DataFlex.h"

#define YY_INPUT(buf, result, max_size) \
    (result) = (DataInput((buf), 1) != 0)

#define ECHO /* don't echo unmatched characters */
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
BCOMMENT_START      \/\*[^\n\*]*
BCOMMENT_TEXT       [^\n\*]*
BCOMMENT_SKIP       \*+
BCOMMENT_END        \*+\/

%%
\r                                                  { /* skip carriage returns */ }
\n                                                  { gDataLine++; }
{STRING}                                            { return kDataTokenString; }
{QUOTED_SYMBOL}                                     { return kDataTokenQuotedSymbol; }
{BCOMMENT_START}                                    { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>{BCOMMENT_TEXT}                      { /* ignore text in block comments */ }
<BLOCK_COMMENT>{BCOMMENT_SKIP}                      { /* ignore *s in block comments */ }
<BLOCK_COMMENT>\n                                   { gDataLine++; }
<BLOCK_COMMENT>{BCOMMENT_END}                       { BEGIN(INITIAL); }
{COMMENT}                                           { /* skip comments */ }
kDataUnhandled                                      { return kDataTokenUnhandled; }

{HEX_NUMBER}                                        { return kDataTokenHex; }
{INTEGER}                                           { return kDataTokenInt; }
{FLOAT}                                             { return kDataTokenFloat; }
{FLOAT_EXPONENT}                                    { return kDataTokenFloat; }

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
#{IDENTIFIER}                                       { DataFail("bad # directive"); }

{VARIABLE}                                          { return kDataTokenVar; }
{SYMBOL}                                            { return kDataTokenSymbol; }

\(                                                  { return kDataTokenArrayOpen; }
\)                                                  { return kDataTokenArrayClose; }
\{                                                  { return kDataTokenCommandOpen; }
\}                                                  { return kDataTokenCommandClose; }
\[                                                  { return kDataTokenPropertyOpen; }
\]                                                  { return kDataTokenPropertyClose; }
%%
