#ifndef UTL_STR_H
#define UTL_STR_H
#include "utl/TextStream.h"
#include "utl/Symbol.h"

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

    const char* c_str();
};

#endif
