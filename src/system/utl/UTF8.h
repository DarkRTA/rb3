#pragma once
#include "utl/Str.h"

unsigned int DecodeUTF8(unsigned short &, const char *);
unsigned int EncodeUTF8(String &, unsigned int);
void UTF8toASCIIs(char *, int, const char *, char);
void ASCIItoUTF8(char *, int, const char *);
int UTF8StrLen(const char *);
const char *UTF8strchr(const char *, unsigned short);
void UTF8ToLower(unsigned short, char *);
void UTF8ToUpper(unsigned short, char *);
void UTF8FilterString(char *, int, const char *, const char *, char);
void ASCIItoWideVector(std::vector<unsigned short> &vec, const char *cc);
int WideVectorToUTF8(std::vector<unsigned short> &vec, String &str);
void UTF8FilterKeyboardString(char *, int, const char *); // defined in os/PlatformMgr.cpp
                                                          // for some reason
String WideVectorToASCII(std::vector<unsigned short> &);
char *WideCharToChar(const unsigned short *us);
void UTF8RemoveSpaces(char *, int, const char *);
void UTF8toUTF16(unsigned short *us, const char *c);