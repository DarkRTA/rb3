#ifndef UTL_STR_H
#define UTL_STR_H
#include "utl/TextStream.h"
#include "utl/Symbol.h"

class String : public TextStream {
public:
    unsigned int mCap;
    const char* mStr;

    String();
    String(const char *);
    String(Symbol);
    String(const String &);
    String(unsigned int, char);

    virtual ~String();
    virtual void Print(const char *);
};

#endif
