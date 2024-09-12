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

IDENTIFIER          [^ \t\n\r\(\)\[\]\{\}]+

DIGIT               [0-9]
HEX_DIGIT           [A-Fa-f0-9]
SIGN                [+-]

HEX_NUMBER          0x{HEX_DIGIT}+
INTEGER             {SIGN}?{DIGIT}+
FLOAT               {SIGN}?{DIGIT}*\.{DIGIT}*
FLOAT_PRECISION     {SIGN}?{DIGIT}*\.{DIGIT}*[Ee]{SIGN}?{DIGIT}+

STRING_LITERAL      \"[^\"]*\"
SYMBOL_LITERAL      \'[^\']*\'

%x BLOCK_COMMENT

%%
\r                                                  { /* skip carriage returns */ }
\n                                                  { gDataLine++; }
{STRING_LITERAL}                                    { return kDataTokenString; }
{SYMBOL_LITERAL}                                    { return kDataTokenQuotedSymbol; }
\/\* /* BUG: /** won't start a block */             { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>[^\n\*]*                             { /* ignore text in block comments */ }
<BLOCK_COMMENT>\*+                                  { /* ignore *s in block comments */ }
<BLOCK_COMMENT>\n                                   { gDataLine++; }
<BLOCK_COMMENT>\*\/                                 { BEGIN(INITIAL); }
;.*\n                                               { /* comment */ }
kUnhandled                                          { return kDataTokenUnhandled; }

{HEX_NUMBER}                                        { return kDataTokenHex; }
{INTEGER}                                           { return kDataTokenInt; }
{FLOAT}                                             { return kDataTokenFloat; }
{FLOAT_PRECISION}                                   { return kDataTokenFloat; }

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

\${IDENTIFIER}                                      { return kDataTokenVar; }
{IDENTIFIER}                                        { return kDataTokenSymbol; }

\(                                                  { return kDataTokenArrayOpen; }
\)                                                  { return kDataTokenArrayClose; }
\{                                                  { return kDataTokenCommandOpen; }
\}                                                  { return kDataTokenCommandClose; }
\[                                                  { return kDataTokenPropertyOpen; }
\]                                                  { return kDataTokenPropertyClose; }
%%
