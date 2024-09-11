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

SEPARATOR_CHARS [ \t\n\r\(\)\[\]\{\}]
IDENTIFIER [^ \t\n\r\(\)\[\]\{\}]+

INT_LITERAL [+-]?[0-9]+
HEX_LITERAL 0x[A-Fa-f0-9]+
FLOAT_LITERAL [+-]?[0-9]*\.[0-9]*
FLOAT_PRECISION {FLOAT_LITERAL}-?[Ee][0-9]+
STRING_LITERAL ".*?"
SYMBOL_LITERAL '[^\n]*?'

%x state_comment

%%
\r                                                  { /* skip carriage returns */ }
\n                                                  { gDataLine++; }
{STRING_LITERAL}                                    { return kDataTokenString; }
{SYMBOL_LITERAL}                                    { return kDataTokenQuotedSymbol; }
\/\*\n                                              { BEGIN(state_comment); }
_6                                                  { /* do nothing */ }
_7                                                  { /* do nothing */ }
_8                                                  { gDataLine++; }
<state_comment>\*\/                                 { BEGIN(INITIAL); }
\;.*\n                                              { /* comment */ }
kUnhandled                                          { return kDataTokenUnhandled; }

{HEX_LITERAL}                                       { return kDataTokenHex; }
{INT_LITERAL}                                       { return kDataTokenInt; }
{FLOAT_LITERAL}                                     { return kDataTokenFloat; }
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
