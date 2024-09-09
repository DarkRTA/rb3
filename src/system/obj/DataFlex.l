/*
 * requires the following commit of flex:
 * https://github.com/westes/flex/commit/fe84af1738b78edeca58752c5a549a175236420a
 */

/* %option nounistd - not supported on the version of flex used */
%option never-interactive

%{
#include "DataFile.h"
%}

%%
[0-9]+          { printf("asdf"); }
\n              { gDataLine++; }
%%
