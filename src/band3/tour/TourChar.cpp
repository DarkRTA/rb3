#include "tour/TourChar.h"
#include "bandobj/BandCharDesc.h"
#include "decomp.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Bitmap.h"
#include "tour/TourSavable.h"
#include "utl/HxGuid.h"
#include "game/Defines.h"

TourChar::TourChar() : mIsFinalized(0), unk41(0), mPortraitTex(Hmx::Object::New<RndTex>()) {
    mSaveSizeMethod = &SaveSize;
    mPortraitTex->SetMipMapK(666.0f);
    mBandCharDesc = dynamic_cast<BandCharDesc*>(BandCharDesc::NewObject());
}

TourChar::~TourChar(){
    delete mBandCharDesc;
    delete mPortraitTex;
}

const char* TourChar::GetCharacterName() const { return mName.c_str(); }
BandCharDesc* TourChar::GetBandCharDesc() const { return mBandCharDesc; }

void TourChar::SaveFixed(FixedSizeSaveableStream& stream) const {
    MILO_ASSERT(mIsFinalized, 0x51);
    MILO_ASSERT(mBandCharDesc, 0x52);
    FixedSizeSaveable::SaveFixedString(stream, mName);
    stream << mGuid;
    stream << *mBandCharDesc;
    RndBitmap bmap;
    mPortraitTex->LockBitmap(bmap, 1);
    bmap.Save(stream);
    mPortraitTex->UnlockBitmap();
}

int TourChar::SaveSize(int i){
    int size = HxGuid::SaveSize() + 0x80;
    size += BandCharDesc::SaveSize(i);
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "TourChar", size + 0x4020);
    }
    return size + 0x4020;
}

void TourChar::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    MILO_ASSERT(mBandCharDesc, 0x76);
    FixedSizeSaveable::LoadFixedString(stream, mName);
    stream >> mGuid;
    stream >> *mBandCharDesc;
    RndBitmap bmap;
    bmap.Load(stream);
    mPortraitTex->SetBitmap(bmap, 0, true);
    mIsFinalized = true;
}

void TourChar::SyncSave(BinStream& bs) const {
    if(unk41) bs << mName;
    else {
        String censor(mName);
        CensorString(censor);
        bs << censor;
    }
    bs << mGuid;
    mBandCharDesc->Save(bs);
}

void TourChar::CachePortraitTex(RndTex* tex){
    MILO_ASSERT(tex->Width() > 0 && tex->Height() > 0, 0xCE);
    RndBitmap bmap;
    tex->LockBitmap(bmap, 1);
    mPortraitTex->SetBitmap(bmap, 0, true);
    tex->UnlockBitmap();
    mPortraitTex->Compress(true);
}

bool TourChar::IsFinalized() const { return mIsFinalized; }
bool TourChar::IsCustomizable() const { return true; }

BEGIN_HANDLERS(TourChar)
    HANDLE_SUPERCLASS(TourSavable)
    HANDLE_CHECK(0xE2)
END_HANDLERS

DECOMP_FORCEACTIVE(TourChar, "pair.mTex")