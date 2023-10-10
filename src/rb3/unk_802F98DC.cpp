#include "std/string.h"
#include "unknown.hpp"
#include "string.hpp"

// fn_802FA190
void FileQualifiedFilename(String& s, const char* c, int i){
    char lol[256];
    FileQualifiedFilename(lol, 0x100, c, i);
    s = lol;
}