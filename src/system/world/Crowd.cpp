#include "world/Crowd.h"
#include "utl/Symbols.h"

RndCam* gImpostorCamera;
RndMat* gImpostorMat;
int gNumCrowd;

INIT_REVS(WorldCrowd)

WorldCrowd::WorldCrowd() : mPlacementMesh(this), mCharacters(this), mEnviron(this), mEnviron3D(this), mFocus(this) {
    gImpostorMat = Hmx::Object::New<RndMat>();
    gImpostorMat->SetUseEnv(true);
    gImpostorMat->SetPreLit(false);
    gImpostorMat->SetBlend(kSrc);
    gImpostorMat->SetZMode(kNormal);
    gImpostorMat->SetAlphaCut(true);
    gImpostorMat->SetAlphaThreshold(0x80);
    gImpostorMat->SetTexWrap(kClamp);
    gImpostorMat->SetPerPixelLit(false);
    gImpostorMat->SetPointLights(true);
}

WorldCrowd::CharData::CharData(Hmx::Object* o) : mDef(o), mMMesh(0) {

}

void WorldCrowd::CharData::Load(BinStream& bs){ mDef.Load(bs); }

WorldCrowd::CharDef::CharDef(Hmx::Object* o) : mChar(o, 0), mHeight(75.0f), mDensity(1.0f), mRadius(10.0f), unk18(0), unk1c(o, kObjListNoNull) {}

void WorldCrowd::CharDef::Load(BinStream& bs){
    bs >> mChar;
    bs >> mHeight;
    bs >> mDensity;
    if(WorldCrowd::gRev > 1) bs >> mRadius;
    if(WorldCrowd::gRev > 8) bs >> unk18;
}

BEGIN_HANDLERS(WorldCrowd)
    HANDLE(rebuild, OnRebuild)
    HANDLE_ACTION(assign_random_colors, AssignRandomColors())
    HANDLE(iterate_frac, OnIterateFrac)
    HANDLE_ACTION(set_fullness, SetFullness(_msg->Float(2), _msg->Float(3)))
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x6FF)
END_HANDLERS