#include "utl/FilePath.h"

extern "C" const char* FileMakePath(const char*, const char*, char*);

FilePath FilePath::sRoot;
FilePath FilePath::sNull("");

void FilePath::Set(const char* c1, const char* c2){
    if(c2 != 0 && *c2 != '\0'){
        *(String*)this = FileMakePath(c1, c2, 0);
    }
    else *(String*)this = "";
}
