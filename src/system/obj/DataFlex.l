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

IDENTIFIER [^\s\(\)\[\]\{\}]+

INT_LITERAL [0-9]+
HEX_LITERAL 0x[0-9]+
DECIMAL_LITERAL \.[0-9]+
FLOAT_LITERAL [0-9]+\.[0-9]+
STRING_LITERAL "[^\n]"
SYMBOL_LITERAL '{IDENTIFIER}'

%s state1

%%
_1                  { /* do nothing */ }
\n                  { gDataLine++; }
{STRING_LITERAL}    { return kDataTokenString; }
{SYMBOL_LITERAL}    { return kDataTokenQuotedSymbol; }
_5                  { BEGIN(state1); }
_6                  { /* do nothing */ }
_7                  { /* do nothing */ }
\r\n                { gDataLine++; }
_9                  { BEGIN(INITIAL); }
\s                  { /* do nothing */ }
kUnhandled          { return kDataTokenUnhandled; }

{HEX_LITERAL}       { return kDataTokenHex; }
{INT_LITERAL}       { return kDataTokenInt; }
{FLOAT_LITERAL}     { return kDataTokenFloat; }
{DECIMAL_LITERAL}   { return kDataTokenFloat; }

#include            { return kDataTokenInclude; }
_17                 { return kDataTokenIncludeOptional; }
#merge              { return kDataTokenMerge; }
#ifdef              { return kDataTokenIfdef; }
#ifndef             { return kDataTokenIfndef; }
#undef              { return kDataTokenUndef; }
#else               { return kDataTokenElse; }
#endif              { return kDataTokenEndif; }
#define             { return kDataTokenDefine; }
#autorun            { return kDataTokenAutorun; }
#                   { DataFail("bad # directive"); }

\${IDENTIFIER}      { return kDataTokenVar; }
{IDENTIFIER}        { return kDataTokenSymbol; }

\(                  { return kDataTokenArrayOpen; }
\)                  { return kDataTokenArrayClose; }
\{                  { return kDataTokenPropertyOpen; }
\}                  { return kDataTokenPropertyClose; }
\[                  { return kDataTokenCommandOpen; }
\]                  { return kDataTokenCommandClose; }
%%
