#ifndef UTL_STR_H
#define UTL_STR_H
#include "utl/TextStream.h"
#include "utl/Symbol.h"
#include <string.h>

class String : public TextStream {
public:
    unsigned int mCap;
    const char* mStr;

    virtual ~String();
    virtual void Print(const char *);

    String();
    String(const char *);
    String(Symbol);
    String(const String &);
    String(unsigned int, char);

    unsigned int length() const { return strlen(mStr); }
    const char* c_str() const { return mStr; }
    bool empty() const { return mStr != 0; }
};

#endif
