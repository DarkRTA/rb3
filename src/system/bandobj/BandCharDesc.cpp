#include "bandobj/BandCharDesc.h"
#include "bandobj/BandHeadShaper.h"
#include "obj/DataFunc.h"
#include "utl/Symbols.h"

ObjectDir* gPrefabs;
ObjectDir* gDeforms;
Symbol gInstNames[6];
BandCharDesc* gBandCharDescMe;

ObjectDir* BandCharDesc::GetPrefabs(){ return gPrefabs; }

BandCharDesc* BandCharDesc::FindPrefab(const char* cc, bool b){
    return gPrefabs->Find<BandCharDesc>(cc, false);
}

void BandCharDesc::ReloadPrefabs(){
    ObjectDir* old = gPrefabs;
    const char* prefabpath = "";
    gPrefabs = 0;
    DataArray* cfg = SystemConfig("objects", "BandCharDesc");
    if(cfg->FindData("prefabs_path", prefabpath, false) && prefabpath[0] != 0){
        static int _x = MemFindHeap("char");
        MemPushHeap(_x);
        gPrefabs = DirLoader::LoadObjects(FilePath(prefabpath), 0, 0);
        MemPopHeap();
    }
    if(gPrefabs && old){
        MILO_ASSERT(gPrefabs != old, 0x49);
        for(ObjDirItr<BandCharDesc> it(old, true); it != 0; ++it){
            BandCharDesc* from = it;
            BandCharDesc* to = FindPrefab(from->Name(), false); // this should be inlined
            MILO_ASSERT(from != to, 0x4E);
            const std::vector<ObjRef*>& refs = it->Refs();
            while(!refs.empty()){
                refs.back()->Replace(it, to);
            }
        }
    }
    delete old;
}

DECOMP_FORCEACTIVE(BandCharDesc, "from != to")

CharClip* BandCharDesc::GetDeformClip(Symbol s){
    if(!gDeforms) return 0;
    else return gDeforms->Find<CharClip>(s.Str(), false);
}

DataNode OnBandCharDescPrefabs(DataArray*){
    return DataNode(gPrefabs);
}

DataNode OnBandCharDescReloadPrefabs(DataArray*){
    BandCharDesc::ReloadPrefabs();
    return DataNode(0);
}

#pragma push
#pragma pool_data off
void BandCharDesc::Init(){
    gInstNames[0] = "guitar";
    gInstNames[1] = "bass";
    gInstNames[2] = "drum";
    gInstNames[3] = "mic";
    gInstNames[4] = "keyboard";
    gInstNames[5] = "none";
    FilePathTracker tracker(FileRoot());
    Register();
    DataRegisterFunc("bandchardesc_prefabs", OnBandCharDescPrefabs);
    DataRegisterFunc("bandchardesc_reload_prefabs", OnBandCharDescReloadPrefabs);
    ReloadPrefabs();
    const char* dfpath = "";
    DataArray* cfg = SystemConfig("objects", "BandCharDesc");
    if(cfg->FindData("deform_path", dfpath, false)){
        if(dfpath[0] != 0){
            static int _x = MemFindHeap("char");
            MemPushHeap(_x);
            gDeforms = DirLoader::LoadObjects(FilePath(dfpath), 0, 0);
            MemPopHeap();
        }
    }
}
#pragma pop

Symbol BandCharDesc::GetInstrumentSym(int inst){
    MILO_ASSERT(inst <= kNumInstruments && inst >= 0, 0xD7);
    return gInstNames[inst];
}

BandCharDesc::CharInstrumentType BandCharDesc::GetInstrumentFromSym(Symbol sym){
    for(int i = 0; i < 5; i++){
        if(GetInstrumentSym(i) == sym) return (CharInstrumentType)i;
    }
    return kNumInstruments;
}

Symbol BandCharDesc::GetAnimInstrument(Symbol s){
    if(s == "bass") return "guitar";
    else return s;
}

void BandCharDesc::SaveFixed(FixedSizeSaveableStream& stream) const {
    FixedSizeSaveable::SaveSymbolID(stream, mGender);
    stream << mSkinColor;
    stream << mHead;
    stream << mOutfit;
    stream << mHeight;
    stream << mWeight;
    stream << mMuscle;
    stream << mInstruments;
    FixedSizeSaveable::SaveStdFixed(stream, mPatches, 0x10);
}

int BandCharDesc::SaveSize(int i){
    int size = Head::SaveSize(i);
    size += Outfit::SaveSize(i);
    size += InstrumentOutfit::SaveSize(i);
    size += Patch::SaveSize(i) * 0x10 + 0x4;
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "BandCharDesc", size);
    }
    return size;
}

void BandCharDesc::LoadFixed(FixedSizeSaveableStream& stream, int i){
    mPrefab = Symbol("");
    FixedSizeSaveable::LoadSymbolFromID(stream, mGender);
    stream >> mSkinColor;
    stream >> mHead;
    stream >> mOutfit;
    stream >> mHeight;
    stream >> mWeight;
    stream >> mMuscle;
    stream >> mInstruments;
    FixedSizeSaveable::LoadStdFixed(stream, mPatches, 0x10, i);
}

BandCharDesc::OutfitPiece::OutfitPiece(){
    mName = Symbol();
    for(int i = 0; i < 3; i++) mColors[i] = 0;
    mSaveSizeMethod = &SaveSize;
}

bool BandCharDesc::OutfitPiece::operator==(const BandCharDesc::OutfitPiece& piece) const {
    if(mName != piece.mName) return false;
    if(mColors[0] != piece.mColors[0]) return false;
    if(mColors[1] != piece.mColors[1]) return false;
    if(mColors[2] != piece.mColors[2]) return false;
    return true;
}

void BandCharDesc::OutfitPiece::SaveFixed(FixedSizeSaveableStream& stream) const {
    FixedSizeSaveable::SaveFixedSymbol(stream, mName);
    for(int i = 0; i < 3; i++){
        stream << mColors[i];
    }
}

int BandCharDesc::OutfitPiece::SaveSize(int i){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "BandCharDesc::OutfitPiece", 0x3E);
    }
    return 0x3E;
}

void BandCharDesc::OutfitPiece::LoadFixed(FixedSizeSaveableStream& stream, int){
    FixedSizeSaveable::LoadFixedSymbol(stream, mName);
    for(int i = 0; i < 3; i++){
        stream >> mColors[i];
    }
}

BandCharDesc::Outfit::Outfit(){
    mSaveSizeMethod = &SaveSize;
}

BandCharDesc::InstrumentOutfit::InstrumentOutfit(){
    mSaveSizeMethod = &SaveSize;
}

BandCharDesc::Patch::Patch() : mTexture(0), mCategory(0), mUV(0.5f, 0.5f), mRotation(0), mScale(1.0f, 1.0f) {
    mSaveSizeMethod = &SaveSize;
}

BandCharDesc::BandCharDesc() : mGender("male"), mSkinColor(3), mHeight(0.5f), mWeight(0.5f), mMuscle(0.5f), unk224(0) {
    mSaveSizeMethod = &SaveSize;
}

BandCharDesc::Head::Head() : mHide(0), mEyeColor(0), mShape(0), mChin(0), mChinWidth(0.5f), mChinHeight(0.5f), mJawWidth(0.5f), mJawHeight(0.5f),
    mNose(0), mNoseWidth(0.5f), mNoseHeight(0.5f), mEye(0), mEyeSeparation(0.5f), mEyeHeight(0.5f), mEyeRotation(0.5f), mMouth(0),
    mMouthWidth(0.5f), mMouthHeight(0.5f), mBrowSeparation(0.5f), mBrowHeight(0.5f) {
    mSaveSizeMethod = &SaveSize;
}

BEGIN_HANDLERS(BandCharDesc)
    if(sym == list_outfits) return ListOutfits(_msg->Sym(2));
    HANDLE_EXPR(nose_num, BandHeadShaper::sNoseNum)
    HANDLE_EXPR(mouth_num, BandHeadShaper::sMouthNum)
    HANDLE_EXPR(eye_num, BandHeadShaper::sEyeNum)
    HANDLE_EXPR(shape_num, BandHeadShaper::sShapeNum)
    HANDLE_EXPR(chin_num, BandHeadShaper::sChinNum)
    HANDLE_ACTION(milo_reload, MiloReload())
    if(ClassName() == StaticClassName()) HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x604)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(BandCharDesc::Patch)
    SYNC_PROP_MODIFY(category, o.mCategory, gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY(texture, o.mTexture, gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY_ALT(mesh_name, o.mMeshName, gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY(rotation, o.mRotation, gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY_ALT(uv, o.mUV, gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY_ALT(scale, o.mScale, gBandCharDescMe->SetChanged(1))
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandCharDesc::OutfitPiece)
    SYNC_PROP_MODIFY(name, o.mName, gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY(color0, o.mColors[0], gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY(color1, o.mColors[1], gBandCharDescMe->SetChanged(1))
    SYNC_PROP_MODIFY(color2, o.mColors[2], gBandCharDescMe->SetChanged(1))
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandCharDesc::Outfit)
    SYNC_PROP(eyebrows, o.mEyebrows)
    SYNC_PROP(earrings, o.mEarrings)
    SYNC_PROP(facehair, o.mFaceHair)
    SYNC_PROP(glasses, o.mGlasses)
    SYNC_PROP(hair, o.mHair)
    SYNC_PROP(piercings, o.mPiercings)
    SYNC_PROP(feet, o.mFeet)
    SYNC_PROP(hands, o.mHands)
    SYNC_PROP(legs, o.mLegs)
    SYNC_PROP(rings, o.mRings)
    SYNC_PROP(torso, o.mTorso)
    SYNC_PROP(wrist, o.mWrist)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandCharDesc::InstrumentOutfit)
    SYNC_PROP(guitar, o.mGuitar)
    SYNC_PROP(bass, o.mBass)
    SYNC_PROP(drum, o.mDrum)
    SYNC_PROP(mic, o.mMic)
    SYNC_PROP(keyboard, o.mKeyboard)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandCharDesc::Head)
    SYNC_PROP(eye_color, o.mEyeColor)
    SYNC_PROP(shape, o.mShape)
    SYNC_PROP(chin, o.mChin)
    SYNC_PROP(chin_width, o.mChinWidth)
    SYNC_PROP(chin_height, o.mChinHeight)
    SYNC_PROP(jaw_width, o.mJawWidth)
    SYNC_PROP(jaw_height, o.mJawHeight)
    SYNC_PROP(nose, o.mNose)
    SYNC_PROP(nose_width, o.mNoseWidth)
    SYNC_PROP(nose_height, o.mNoseHeight)
    SYNC_PROP(eye, o.mEye)
    SYNC_PROP(eye_separation, o.mEyeSeparation)
    SYNC_PROP(eye_height, o.mEyeHeight)
    SYNC_PROP(eye_rotation, o.mEyeRotation)
    SYNC_PROP(mouth, o.mMouth)
    SYNC_PROP(mouth_width, o.mMouthWidth)
    SYNC_PROP(mouth_height, o.mMouthHeight)
    SYNC_PROP_MODIFY(brow_separation, o.mBrowSeparation, gBandCharDescMe->SetChanged(2))
    SYNC_PROP_MODIFY(brow_height, o.mBrowHeight, gBandCharDescMe->SetChanged(2))
    SYNC_PROP(hide, o.mHide)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandCharDesc)
    gBandCharDescMe = this;
    SYNC_PROP_SET(prefab, mPrefab, SetPrefab(_val.Sym(0)))
    SYNC_PROP_SET(gender, mGender, SetGender(_val.Sym(0)))
    SYNC_PROP_SET(height, mHeight, SetHeight(_val.Float(0)))
    SYNC_PROP_SET(weight, mWeight, SetWeight(_val.Float(0)))
    SYNC_PROP_SET(muscle, mMuscle, SetMuscle(_val.Float(0)))
    SYNC_PROP_SET(skin_color, mSkinColor, SetSkinColor(_val.Int(0)))
    SYNC_PROP_MODIFY_ALT(head, mHead, SetChanged(1))
    SYNC_PROP(instruments, mInstruments)
    SYNC_PROP(outfit, mOutfit)
    SYNC_PROP(patches, mPatches)
END_PROPSYNCS