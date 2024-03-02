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

    void InitSongMetadata();
    void operator delete(void* v){
        _MemFree(v);
    }
    int ID() const;
    bool IsOnDisc() const;
    Symbol GameOrigin() const;
    void PreviewTimes(float&, float&) const;
    DataArraySongInfo* SongBlock() const;
    int NumVocalParts() const;

    static int sSaveVer;

    short mVersion;
    Symbol mShortName;
    int mID;
    bool mIsOnDisc;
    Symbol mGameOrigin;
    float mPreviewStartTime;
    float mPreviewEndTime;
    DataArraySongInfo* mSongInfo;
    DataArray* mSongVocalsBlock;
};

#endif
