#pragma once
#include "utl/Str.h"
#include <list>

enum StoreError {
    kStoreErrorSuccess = 0,
    kStoreErrorNoContent = 1,
    kStoreErrorCacheNoSpace = 2,
    kStoreErrorCacheRemoved = 3,
    kStoreErrorLiveServer = 4,
    kStoreErrorStoreServer = 5,
    kStoreErrorSignedOut = 6,
    kStoreErrorNoMetadata = 7,
    kStoreErrorEcommerce = 8,
    kStoreErrorNoEula = 9
};

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
    virtual ~StoreEnumeration(){}
    virtual void Start() = 0;
    virtual bool IsEnumerating() const = 0;
    virtual bool IsSuccess() const = 0;
    virtual void Poll() = 0;

    std::list<EnumProduct> mContentList;
};

class WiiEnumeration : public StoreEnumeration { // 0x1c
public:
    WiiEnumeration(int);
    virtual ~WiiEnumeration(){}
    virtual void Start();
    virtual bool IsEnumerating() const;
    virtual bool IsSuccess() const;
    virtual void Poll();

    bool mLoading;
    StoreEnumeration::State mState;
};
