#ifndef META_PROFILE_H
#define META_PROFILE_H
#include "meta/FixedSizeSaveable.h"
#include "obj/Object.h"
#include "os/UserMgr.h"

enum ProfileSaveState {
    kMetaProfileUnloaded = 0,
    kMetaProfileLoaded = 1,
    kMetaProfileError = 2,
    kMetaProfileDelete = 3,
    kMetaProfileUnchanged = -1
};

class Profile : public FixedSizeSaveable, public virtual Hmx::Object {
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
    ProfileSaveState GetSaveState() const;
    void SetSaveState(ProfileSaveState);
    void MakeDirty();

    int GetPadNum() const;
    // const char* GetName() const;
    const char* GetName() const {
        LocalUser* u = TheUserMgr->GetLocalUserFromPadNum(mPadNum);
        return u->UserName();
    }

    // int GetPadNum() const {
    //     return mPadNum;
    // }

    // int GetPadNum() const { return mPadNum; }
    // const char* GetName() const {
    //     LocalUser* u = TheUserMgr->GetLocalUserFromPadNum(mPadNum);
    //     return u->UserName();
    // }

    bool mDirty;
    mutable int mPadNum;
    ProfileSaveState mState;
};

#endif
