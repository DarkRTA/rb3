#include "tour/TourSavable.h"
#include "meta/Profile.h"
#include "obj/ObjMacros.h"
#include "os/DateTime.h"
#include "utl/Symbols4.h"

TourSavable::TourSavable() : mDirtySave(1), mDirtyUpload(1), unka(0), mNameUnchecked(1), unk12(1) {
    DateTime dt;
    GetDateAndTime(dt);
    unsigned int diff = dt.ToCode() - 0xe10;
    unkb = diff;
}

TourSavable::~TourSavable(){

}

bool TourSavable::IsDirtySave() const { return mDirtySave; }
bool TourSavable::IsDirtyUpload() const { return mDirtyUpload; }
bool TourSavable::IsNameUnchecked() const { return mNameUnchecked; }

bool TourSavable::IsUploadNeeded() const {
    DateTime dt;
    GetDateAndTime(dt);
    unsigned int comp = dt.ToCode() - unkb.ToCode();
    return mDirtyUpload && comp >= SecBetweenUploads();
}

void TourSavable::SetDirty(bool dirty, int mask){
    if(mask & 1) mDirtySave = dirty;
    if(mask & 2) mDirtyUpload = dirty;
    if(mask & 0x10) unka = dirty;
    if(mask & 4) mNameUnchecked = dirty;
    if(mask & 8) unk12 = dirty;
}

void TourSavable::SaveLoadComplete(ProfileSaveState state){
    if(state == kMetaProfileLoaded) mDirtySave = false;
}

void TourSavable::UploadAttempted(){
    GetDateAndTime(unkb);
}

void TourSavable::UploadComplete(){
    mDirtyUpload = false;
    mDirtySave = true;
    GetDateAndTime(unkb);
}

BEGIN_HANDLERS(TourSavable)
    HANDLE_ACTION(set_dirty, SetDirty(_msg->Int(2), _msg->Int(3)))
    HANDLE_CHECK(0x89)
END_HANDLERS