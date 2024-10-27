#include "tour/TourBand.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/SessionMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "tour/TourSavable.h"

TourBand::TourBand(BandProfile* pf) : unk1c(pf), unk30(0) {
    mSaveSizeMethod = &SaveSize;
    unk2c = new PatchDescriptor();
    SetDirty(false, 0xFF);
}

TourBand::~TourBand(){
    RELEASE(unk2c);
}

void TourBand::SetBandName(const char* cc){
    if(unk20 != cc){
        unk20 = cc;
        SetDirty(true, 7);
        BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
        MILO_ASSERT(pMachineMgr, 0x38);
        pMachineMgr->RefreshPrimaryProfileInfo();
    }
}

void TourBand::ChooseBandLogo(int i, int j){
    if(unk2c->patchIndex == j && unk2c->patchType == i) return;
    unk2c->patchIndex = j;
    unk2c->patchType = i;
    SetDirty(true, 3);
}

bool TourBand::IsUploadNeeded() const {
    if(unk20.length() == 0) return false;
    else return TourSavable::IsUploadNeeded();
}

int TourBand::SaveSize(int size){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "TourBand", 0x8A);
    }
    return 0x8A;
}

void TourBand::SaveFixed(FixedSizeSaveableStream& stream) const {
    FixedSizeSaveable::SaveFixedString(stream, unk20);
    stream << *unk2c;
    stream << IsDirtyUpload();
    stream << IsNameUnchecked();
}

void TourBand::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    FixedSizeSaveable::LoadFixedString(stream, unk20);
    stream >> *unk2c;
    bool b1; stream >> b1;
    SetDirty(b1, 2);
    bool b2; stream >> b2;
    SetDirty(b2, 4);
}

BEGIN_HANDLERS(TourBand)
    HANDLE_SUPERCLASS(TourSavable)
    HANDLE_CHECK(0x99)
END_HANDLERS