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

%%
[0-9]+          { printf("asdf"); }
\n              { gDataLine++; }
%%
