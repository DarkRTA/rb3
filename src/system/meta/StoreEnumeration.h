#ifndef META_STOREENUMERATION_H
#define META_STOREENUMERATION_H
#include "utl/Str.h"
#include <list>

struct EnumProduct {
    String mName;
    String mGameCode;
    unsigned short mContentId;
    unsigned short mWiiPoints;
    bool mPurchased;
    bool mDownloaded;
};

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
    StoreEnumeration(){}
    ~StoreEnumeration(){}
    virtual void Start() = 0;
    virtual bool IsSuccess() const = 0;
    virtual int IsEnumerating() const = 0;
    virtual void Poll() = 0;

    std::list<EnumProduct> mContentList;
};

class WiiEnumeration : public StoreEnumeration { // 0x1c
public:
    WiiEnumeration(int);
    virtual ~WiiEnumeration(){}
    virtual void Start();
    virtual bool IsSuccess() const;
    virtual int IsEnumerating() const;
    virtual void Poll();

    bool mLoading;
    StoreEnumeration::State mState;
};

#endif // META_STOREENUMERATION_H
