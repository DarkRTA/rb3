#ifndef UTL_FILEPATH_H
#define UTL_FILEPATH_H
#include "utl/Str.h"

class FilePath : public String {
public:
    static FilePath sRoot;
    static FilePath sNull;

    FilePath(const String & str) : String(str) { }
    FilePath(const char* str){
        Set(sRoot.c_str(), str);
    }
    FilePath(){ }
    virtual ~FilePath(){ }

    void Set(const char *, const char *); // fn_8034C91C - the only not-weak method here

    // FilePath *operator=(const FilePath &);
    char* FilePathRelativeToRoot();
    void SetRoot(const char*);
};

#endif
