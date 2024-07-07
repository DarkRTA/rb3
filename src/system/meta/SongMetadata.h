#ifndef META_SONGMETADATA_H
#define META_SONGMETADATA_H
#include "utl/Symbol.h"
#include "obj/Object.h"
#include "obj/Data.h"
#include "meta/DataArraySongInfo.h"

class SongMetadata : public Hmx::Object {
public:
    SongMetadata();
    SongMetadata(DataArray*, DataArray*, bool);
    virtual ~SongMetadata();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual bool IsVersionOK() const = 0;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    void InitSongMetadata();
    int ID() const;
    bool IsOnDisc() const;
    Symbol GameOrigin() const;
    void PreviewTimes(float&, float&) const;
    DataArraySongInfo* SongBlock() const;
    int NumVocalParts() const;
    Symbol ShortName() const { return mShortName; }
    int Age() const { return mAge; }

    static int sSaveVer;

    short mVersion; // 0x1c
    Symbol mShortName; // 0x20
    int mID; // 0x24
    bool mIsOnDisc; // 0x28
    Symbol mGameOrigin; // 0x2c
    float mPreviewStartTime; // 0x30
    float mPreviewEndTime; // 0x34
    DataArraySongInfo* mSongInfo; // 0x38
    // DataArray* mSongVocalsBlock; // 0x3c - maybe this went unused?
    int mAge; // 0x3c
};

#endif
