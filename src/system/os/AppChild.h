#ifndef OS_APPCHILD_H
#define OS_APPCHILD_H
#include "utl/BinStream.h"

class AppChild {
public:
    bool mEnabled;
    BinStream* mStream;
    bool mSync;

    AppChild(const char*);
    ~AppChild();
    void Sync();
    void Sync(unsigned short);

    static void Terminate();
};

#endif
