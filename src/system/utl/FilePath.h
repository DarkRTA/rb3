#ifndef UTL_FILEPATH_H
#define UTL_FILEPATH_H
#include "Str.h"

class FilePath : public String {
public:
    FilePath(const String &); // fn_8000EC00
    FilePath(const char *); // fn_8000EC5C
    FilePath(); // found in RB2
    virtual ~FilePath(); // fn_8000EA28

    void Set(const char *, const char *); // fn_8034C91C
    FilePath *operator=(const FilePath &);
    char* FilePathRelativeToRoot();
    void SetRoot(const char*);
};

#endif
