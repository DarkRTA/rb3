#ifndef META_PROFILE_H
#define META_PROFILE_H
#include "meta/FixedSizeSaveable.h"
#include "obj/Object.h"

enum ProfileSaveState {
    kMetaProfileUnloaded = 0,
    kMetaProfileLoaded = 1,
    kMetaProfileError = 2,
    kMetaProfileDelete = 3,
    kMetaProfileUnchanged = -1
};

class Profile : public FixedSizeSaveable, virtual Hmx::Object {
public:
    Profile(int);
    virtual ~Profile();
    virtual void SaveFixed(FixedSizeSaveableStream&) const = 0;
    virtual void LoadFixed(FixedSizeSaveableStream&, int) = 0;
    virtual DataNode Handle(DataArray*, bool);
    virtual bool HasCheated() const;
    virtual bool IsUnsaved() const;
    virtual void SaveLoadComplete(ProfileSaveState);
    virtual bool HasSomethingToUpload();
    virtual void DeleteAll();
    virtual void PreLoad(){}

    bool IsAutosaveEnabled() const;
    bool HasValidSaveData() const;
    int GetPadNum() const;
    ProfileSaveState GetSaveState() const;
    void SetSaveState(ProfileSaveState);
    void MakeDirty();

    bool mDirty;
    int mPadNum;
    ProfileSaveState mState;
};

#endif
