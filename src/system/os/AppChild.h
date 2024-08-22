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
    void Poll();
    void SetEnabled(bool b) { mEnabled = b; }

    static void Init();
    static void Terminate();
};

extern AppChild* TheAppChild;

#endif
