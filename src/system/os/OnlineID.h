#ifndef OS_ONLINEID_H
#define OS_ONLINEID_H
#include "utl/BinStream.h"

class OnlineID {
public:
    int mPrincipalID;
    bool mValid;

    OnlineID();
    void SetPrincipalID(int);
    int GetPrincipalID() const;
    const char* ToString() const;
    bool operator==(const OnlineID&) const;
};

BinStream& operator<<(BinStream&, const OnlineID&);
BinStream& operator>>(BinStream&, OnlineID&);

#endif
