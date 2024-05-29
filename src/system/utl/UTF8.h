#ifndef UTL_UTF8_H
#define UTL_UTF8_H
#include "utl/Str.h"

unsigned int DecodeUTF8(unsigned short&, const char*);
unsigned int EncodeUTF8(String&, unsigned int);
void UTF8toASCIIs(char*, int, const char*, char);
void ASCIItoUTF8(char*, int, const char*);
int UTF8StrLen(const char*);
const char* UTF8strchr(const char*, unsigned short);
void UTF8ToLower(unsigned short, char*);
void UTF8ToUpper(unsigned short, char*);
void UTF8FilterString(char*, int, const char*, const char*, char);

void UTF8FilterKeyboardString(char*, int, const char*); // defined in os/PlatformMgr.cpp for some reason

#endif
