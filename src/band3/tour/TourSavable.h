#pragma once
#include "meta/Profile.h"
#include "os/DateTime.h"
#include "obj/Object.h"

class TourSavable : public virtual Hmx::Object {
public:
    TourSavable();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~TourSavable();
    virtual bool IsDirtySave() const;
    virtual bool IsUploadNeeded() const;
    virtual int SecBetweenUploads() const = 0;
    virtual void SetDirty(bool, int);
    virtual void UploadComplete();

    bool IsDirtyUpload() const;
    bool IsNameUnchecked() const;
    void SaveLoadComplete(ProfileSaveState);
    void UploadAttempted();

    bool mDirtySave; // 0x8
    bool mDirtyUpload; // 0x9
    bool unka; // 0xa
    DateTime unkb; // 0xb
    bool mNameUnchecked; // 0x11
    bool unk12; // 0x12
};
