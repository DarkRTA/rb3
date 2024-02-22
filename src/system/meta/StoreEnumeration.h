#ifndef META_STOREENUMERATION_H
#define META_STOREENUMERATION_H

#include "stlport/list"

struct EnumProduct {int ihavenoclue;};

class StoreEnumeration {
public:
    enum State {
        kEnumWaiting = 0,
        kEnumProcessing = 1,
        kPreSuccess = 2,
        kPreFail = 3,
        kSuccess = 4,
        kFail = 5,
    };
    ~StoreEnumeration();
};

class WiiEnumeration : public StoreEnumeration { // 0x1c
public:
    WiiEnumeration(int);
    virtual ~WiiEnumeration() {
            mContentList.clear();
    }
    virtual void Start();
    virtual bool IsSuccess() const;
    virtual int IsEnumerating() const;
    virtual void Poll();

    std::list<EnumProduct> mContentList;
    bool mLoading;
    StoreEnumeration::State mState;
};

#endif // META_STOREENUMERATION_H
