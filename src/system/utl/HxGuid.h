#ifndef UTL_HXGUID_H
#define UTL_HXGUID_H
#include "utl/BinStream.h"

class HxGuid {
public:
    HxGuid();

    void Generate();
    void Clear();
    bool IsNull() const;
    bool IsNull() { return (mData[0] == 0 && mData[1] == 0 && mData[2] == 0 && mData[3] == 0); }
    bool operator==(const HxGuid&) const;
    bool operator<(const HxGuid&) const;
    int Chunk32(int) const;
    const char* ToString() const;
    static int SaveSize();

    int mData[4];
};

BinStream& operator<<(BinStream&, const HxGuid&);
BinStream& operator>>(BinStream&, HxGuid&);

class UserGuid : public HxGuid {
public:
    UserGuid(){}
    UserGuid& operator=(const UserGuid& u){
        mData[0] = u.mData[0];
        mData[1] = u.mData[1];
        mData[2] = u.mData[2];
        mData[3] = u.mData[3];
        return *this;
    }
};

extern UserGuid gNullUserGuid;

#endif
