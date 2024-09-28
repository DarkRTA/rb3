#include "bandobj/BandCharDesc.h"
#include "bandobj/BandHeadShaper.h"
#include "obj/DataFunc.h"
#include "utl/Symbols.h"

INIT_REVS(BandCharDesc)
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
        for(ObjDirItr<BandCharDesc> from(old, true); from != 0; ++from){
            BandCharDesc* to = gPrefabs->Find<BandCharDesc>(from->Name(), false); // this should actually be FindPrefab but inlined
            MILO_ASSERT(from != to, 0x4E);
            const std::vector<ObjRef*>& refs = from->Refs();
            while(!refs.empty()){
                refs.back()->Replace(from, to);
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
    int size = 8;
    size += Head::SaveSize(i);
    size += Outfit::SaveSize(i);
    size += 12;
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
    for(int i = 0; i < 3; i++){
        if(mColors[i] != piece.mColors[i]) return false;
    }
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

void BandCharDesc::Outfit::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mEyebrows;
    stream << mEarrings;
    stream << mFaceHair;
    stream << mGlasses;
    stream << mHair;
    stream << mPiercings;
    stream << mFeet;
    stream << mHands;
    stream << mLegs;
    stream << mRings;
    stream << mTorso;
    stream << mWrist;
}

int BandCharDesc::Outfit::SaveSize(int i){
    int size = OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "BandCharDesc::Outfit", size);
    }
    return size;
}

void BandCharDesc::Outfit::LoadFixed(FixedSizeSaveableStream& stream, int i){
    stream >> mEyebrows;
    stream >> mEarrings;
    stream >> mFaceHair;
    stream >> mGlasses;
    stream >> mHair;
    stream >> mPiercings;
    stream >> mFeet;
    stream >> mHands;
    stream >> mLegs;
    stream >> mRings;
    stream >> mTorso;
    stream >> mWrist;
}

BandCharDesc::InstrumentOutfit::InstrumentOutfit(){
    mSaveSizeMethod = &SaveSize;
}

void BandCharDesc::InstrumentOutfit::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mGuitar;
    stream << mBass;
    stream << mDrum;
    stream << mMic;
    stream << mKeyboard;
}

int BandCharDesc::InstrumentOutfit::SaveSize(int i){
    int size = OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    size += OutfitPiece::SaveSize(i);
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "BandCharDesc::InstrumentOutfit", size);
    }
    return size;
}

void BandCharDesc::InstrumentOutfit::LoadFixed(FixedSizeSaveableStream& stream, int){
    stream >> mGuitar;
    stream >> mBass;
    stream >> mDrum;
    stream >> mMic;
    stream >> mKeyboard;
}

BandCharDesc::Patch::Patch() : mTexture(0), mCategory(0), mUV(0.5f, 0.5f), mRotation(0), mScale(1.0f, 1.0f) {
    mSaveSizeMethod = &SaveSize;
}

void BandCharDesc::Patch::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mTexture;
    stream << mCategory;
    FixedSizeSaveable::SaveFixedString(stream, mMeshName);
    stream << mUV;
    stream << mRotation;
    stream << mScale;
}

int BandCharDesc::Patch::SaveSize(int i){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "BandCharDesc::Patch", 0x9C);
    }
    return 0x9C;
}

DECOMP_FORCEACTIVE(BandCharDesc, "tattoo_head")

void BandCharDesc::Patch::LoadFixed(FixedSizeSaveableStream& stream, int){
    stream >> mTexture;
    stream >> mCategory;
    FixedSizeSaveable::LoadFixedString(stream, mMeshName);
    stream >> mUV;
    stream >> mRotation;
    stream >> mScale;
}

BandCharDesc::BandCharDesc() : mGender("male"), mSkinColor(3), mHeight(0.5f), mWeight(0.5f), mMuscle(0.5f), unk224(0) {
    mSaveSizeMethod = &SaveSize;
}

BandCharDesc::Head::Head() : mHide(0), mEyeColor(0), mShape(0), mChin(0), mChinWidth(0.5f), mChinHeight(0.5f), mJawWidth(0.5f), mJawHeight(0.5f),
    mNose(0), mNoseWidth(0.5f), mNoseHeight(0.5f), mEye(0), mEyeSeparation(0.5f), mEyeHeight(0.5f), mEyeRotation(0.5f), mMouth(0),
    mMouthWidth(0.5f), mMouthHeight(0.5f), mBrowSeparation(0.5f), mBrowHeight(0.5f) {
    mSaveSizeMethod = &SaveSize;
}

void BandCharDesc::Head::SetShape(BandHeadShaper& shaper){
    shaper.AddDegrees("nose", mNose, &mNoseWidth, 2);
    shaper.AddDegrees("mouth", mMouth, &mMouthWidth, 2);
    shaper.AddDegrees("eye", mEye, &mEyeSeparation, 3);
    shaper.AddFrame("shape", mShape, 1.0f);
    shaper.AddDegrees("jaw", 0, &mJawWidth, 2);
    shaper.AddDegrees("chin", mChin, &mChinWidth, 2);
    shaper.AddDegrees("brow", 0, &mBrowSeparation, 2);
    shaper.End();
}

void BandCharDesc::Head::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mEyeColor;
    stream << mShape;
    stream << mChin;
    stream << mChinWidth;
    stream << mChinHeight;
    stream << mJawWidth;
    stream << mJawHeight;
    stream << mNose;
    stream << mNoseWidth;
    stream << mNoseHeight;
    stream << mEye;
    stream << mEyeSeparation;
    stream << mEyeHeight;
    stream << mEyeRotation;
    stream << mMouth;
    stream << mMouthWidth;
    stream << mMouthHeight;
    stream << mBrowSeparation;
    stream << mBrowHeight;
}

int BandCharDesc::Head::SaveSize(int i){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "BandCharDesc::Head", 0x4C);
    }
    return 0x4C;
}

void BandCharDesc::Head::LoadFixed(FixedSizeSaveableStream& stream, int){
    stream >> mEyeColor;
    stream >> mShape;
    stream >> mChin;
    stream >> mChinWidth;
    stream >> mChinHeight;
    stream >> mJawWidth;
    stream >> mJawHeight;
    stream >> mNose;
    stream >> mNoseWidth;
    stream >> mNoseHeight;
    stream >> mEye;
    stream >> mEyeSeparation;
    stream >> mEyeHeight;
    stream >> mEyeRotation;
    stream >> mMouth;
    stream >> mMouthWidth;
    stream >> mMouthHeight;
    stream >> mBrowSeparation;
    stream >> mBrowHeight;
}

BandCharDesc::~BandCharDesc(){

}

BandCharDesc::OutfitPiece* BandCharDesc::Outfit::GetPiece(Symbol s){
    if(s == "torso") return &mTorso;
    else if(s == "legs") return &mLegs;
    else if(s == "hands") return &mHands;
    else if(s == "feet") return &mFeet;
    else if(s == "hair") return &mHair;
    else if(s == "wrist") return &mWrist;
    else if(s == "facehair") return &mFaceHair;
    else if(s == "rings") return &mRings;
    else if(s == "piercings") return &mPiercings;
    else if(s == "earrings") return &mEarrings;
    else if(s == "glasses") return &mGlasses;
    else if(s == "eyebrows") return &mEyebrows;
    else return 0;
}

BandCharDesc::OutfitPiece* BandCharDesc::InstrumentOutfit::GetPiece(Symbol s){
    if(s == "guitar") return &mGuitar;
    else if(s == "bass") return &mBass;
    else if(s == "drum") return &mDrum;
    else if(s == "mic") return &mMic;
    else if(s == "keyboard") return &mKeyboard;
    else return 0;
}

void BandCharDesc::MakeOutfitPath(Symbol s, FilePath& fp){
    Symbol piecename;
    if(s == "head"){
        if(!mHead.mHide) piecename = s;
    }
    else {
        OutfitPiece* piece = mOutfit.GetPiece(s);
        if(piece) piecename = piece->mName;
        else MILO_WARN("unknown body part %s", s);
    }
    if(piecename.Null()) fp.SetRoot("");
    else {
        fp.SetRoot(MakeString("char/main/%s/%s/%s.milo", s, mGender, piecename));
    }
}

void BandCharDesc::MakeInstrumentPath(Symbol s1, Symbol s2, FilePath& fp){
    Symbol piecename;
    OutfitPiece* piece = mInstruments.GetPiece(s1);
    if(piece) piecename = piece->mName;
    else MILO_WARN("unknown instrument %s", s1);
    if(piecename.Null()) fp.SetRoot("");
    else if(s1 != "drum"){
        fp.SetRoot(MakeString("char/main/%s/%s.milo", s1, piecename));
    }
    else {
        fp.SetRoot(MakeString("char/main/%s/%s_%s.milo", s1, piecename, s2));
    }
}

void BandCharDesc::SetChanged(int i){
    unk224 |= i;
}

void BandCharDesc::SetGender(Symbol s){
    if(s != mGender){
        mGender = s;
        SetChanged(1);
    }
}

void BandCharDesc::SetPrefab(Symbol s){
    if(s != mPrefab){
        mPrefab = s;
        SetChanged(1);
    }
}

void BandCharDesc::SetHeight(float f){
    if(f != mHeight){
        mHeight = f;
        SetChanged(2);
    }
}

void BandCharDesc::SetWeight(float f){
    if(f != mWeight){
        mWeight = f;
        SetChanged(2);
    }
}

void BandCharDesc::SetMuscle(float f){
    if(f != mMuscle){
        mMuscle = f;
        SetChanged(2);
    }
}

void BandCharDesc::SetSkinColor(int i){
    if(i != mSkinColor){
        mSkinColor = i;
        SetChanged(1);
    }
}

BinStream& operator<<(BinStream& bs, const BandCharDesc::Patch& patch){
    bs << patch.mTexture;
    bs << patch.mCategory;
    bs << patch.mMeshName;
    bs << patch.mUV;
    bs << patch.mRotation;
    bs << patch.mScale;
    return bs;
}

BinStream& operator>>(BinStream& bs, BandCharDesc::Patch& patch){
    bs >> patch.mTexture;
    bs >> patch.mCategory;
    bs >> patch.mMeshName;
    bs >> patch.mUV;
    bs >> patch.mRotation;
    bs >> patch.mScale;
    return bs;
}

BinStream& operator<<(BinStream& bs, BandCharDesc::OutfitPiece& piece){
    bs << piece.mName;
    for(int i = 0; i < 3; i++){
        unsigned char col = piece.mColors[i];
        bs << col;
    }
    return bs;
}

BinStream& operator>>(BinStream& bs, BandCharDesc::OutfitPiece& piece){
    bs >> piece.mName;
    unsigned char col;
    bs >> col;
    piece.mColors[0] = col;
    bs >> col;
    piece.mColors[1] = col;
    if(BandCharDesc::gRev > 0xB){
        bs >> col;
        piece.mColors[2] = col;
    }
    return bs;
}

BinStream& operator<<(BinStream& bs, BandCharDesc::Outfit& outfit){
    bs << outfit.mEyebrows;
    bs << outfit.mEarrings;
    bs << outfit.mFaceHair;
    bs << outfit.mGlasses;
    bs << outfit.mHair;
    bs << outfit.mPiercings;
    bs << outfit.mFeet;
    bs << outfit.mHands;
    bs << outfit.mLegs;
    bs << outfit.mRings;
    bs << outfit.mTorso;
    bs << outfit.mWrist;
    return bs;
}

BinStream& operator>>(BinStream& bs, BandCharDesc::Outfit& outfit){
    if(BandCharDesc::gRev < 5){
        BandCharDesc::OutfitPiece piece;
        bs >> piece;
    }
    else bs >> outfit.mEyebrows;
    bs >> outfit.mEarrings;
    if(BandCharDesc::gRev < 5){
        BandCharDesc::OutfitPiece piece;
        bs >> piece;
    }
    bs >> outfit.mFaceHair;
    bs >> outfit.mGlasses;
    bs >> outfit.mHair;
    if(BandCharDesc::gRev < 5){
        BandCharDesc::OutfitPiece piece;
        bs >> piece;
    }
    bs >> outfit.mPiercings;
    bs >> outfit.mFeet;
    bs >> outfit.mHands;
    bs >> outfit.mLegs;
    bs >> outfit.mRings;
    bs >> outfit.mTorso;
    bs >> outfit.mWrist;
    return bs;
}

BinStream& operator<<(BinStream& bs, BandCharDesc::InstrumentOutfit& outfit){
    bs << outfit.mGuitar;
    bs << outfit.mBass;
    bs << outfit.mDrum;
    bs << outfit.mMic;
    bs << outfit.mKeyboard;
    return bs;
}

BinStream& operator>>(BinStream& bs, BandCharDesc::InstrumentOutfit& outfit){
    bs >> outfit.mGuitar;
    bs >> outfit.mBass;
    bs >> outfit.mDrum;
    bs >> outfit.mMic;
    bs >> outfit.mKeyboard;
    return bs;
}

BinStream& operator<<(BinStream& bs, BandCharDesc::Head& head){
    bs << head.mHide;
    bs << head.mEyeColor;
    bs << head.mShape;
    bs << head.mChin;
    bs << head.mChinWidth;
    bs << head.mChinHeight;
    bs << head.mJawWidth;
    bs << head.mJawHeight;
    bs << head.mNose;
    bs << head.mNoseWidth;
    bs << head.mNoseHeight;
    bs << head.mEye;
    bs << head.mEyeSeparation;
    bs << head.mEyeHeight;
    bs << head.mEyeRotation;
    bs << head.mMouth;
    bs << head.mMouthWidth;
    bs << head.mMouthHeight;
    bs << head.mBrowSeparation;
    bs << head.mBrowHeight;
    return bs;
}

BinStream& operator>>(BinStream& bs, BandCharDesc::Head& head){
    if(BandCharDesc::gRev > 7) bs >> head.mHide;
    bs >> head.mEyeColor;
    bs >> head.mShape;
    bs >> head.mChin;
    if(BandCharDesc::gRev > 6){
        bs >> head.mChinWidth;
        bs >> head.mChinHeight;
    }
    bs >> head.mJawWidth;
    bs >> head.mJawHeight;
    bs >> head.mNose;
    if(BandCharDesc::gRev > 5) bs >> head.mNoseWidth;
    bs >> head.mNoseHeight;
    bs >> head.mEye;
    bs >> head.mEyeSeparation;
    bs >> head.mEyeHeight;
    if(BandCharDesc::gRev > 10) bs >> head.mEyeRotation;
    bs >> head.mMouth;
    bs >> head.mMouthWidth;
    bs >> head.mMouthHeight;
    if(BandCharDesc::gRev > 8) bs >> head.mBrowSeparation;
    bs >> head.mBrowHeight;
    return bs;
}

void BandCharDesc::Save(BinStream& bs){
    bs << packRevs(0, 0x11);
    if(ClassName() == StaticClassName()) Hmx::Object::Save(bs);
    bs << mPrefab;
    bs << mGender;
    bs << mSkinColor;
    bs << mHead;
    bs << mOutfit;
    bs << mHeight;
    bs << mWeight;
    bs << mMuscle;
    bs << mInstruments;
    bs << mPatches;
}

BEGIN_LOADS(BandCharDesc)
    LOAD_REVS(bs);
    ASSERT_REVS(0x11, 0);
    if(ClassName() == StaticClassName()) LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 0x10) bs >> mPrefab;
    bs >> mGender;
    if(gRev != 0){
        bs >> mSkinColor;
        if(gRev < 5){
            int i, j;
            bs >> i; bs >> j;
        }
        else bs >> mHead;
    }
    bs >> mOutfit;
    if(gRev < 10){
        Outfit o;
        bs >> o;
    }
    if(gRev > 1){
        int i88 = 0;
        if(gRev < 0xF) bs >> i88;
        if(gRev > 0xD) bs >> mHeight;
        else {
            float f17c[3] = { 0.5f, 1.0f, 0.0f };
            mHeight = f17c[Mod(i88, 3)];
            i88 /= 3;
        }
        if(gRev > 0xE){
            bs >> mWeight;
            bs >> mMuscle;
        }
        else {
            float farr1[5] = { 0.5f, 1.0f, 0.5f, 0.0f, 0.5f };
            mWeight = farr1[i88];
            float farr2[5] = { 0.5f, 0.5f, 1.0f, 0.5f, 0.0f };
            mMuscle = farr2[i88];
        }
        if(gRev < 3){ bool b; bs >> b; }
    }
    if(gRev > 3){
        if(gRev < 0x10){ Symbol s; bs >> s; }
        bs >> mInstruments;
    }
    if(gRev > 0xC) bs >> mPatches;
END_LOADS

BEGIN_COPYS(BandCharDesc)
    if(ClassName() == StaticClassName()) COPY_SUPERCLASS(Hmx::Object);
    CREATE_COPY(BandCharDesc)
    if(c) CopyCharDesc(c);
END_COPYS

void BandCharDesc::CopyCharDesc(const BandCharDesc* desc){

}

    // Symbol mPrefab; // 0xc
    // Symbol mGender; // 0x10
    // int mSkinColor; // 0x14
    // Head mHead; // 0x18
    // Outfit mOutfit; // 0x70
    // InstrumentOutfit mInstruments; // 0x198
    // float mHeight; // 0x218
    // float mWeight; // 0x21c
    // float mMuscle; // 0x220
    // int unk224; // 0x224 - likely a bitfield as seen in BandCharacter methods
    // std::vector<Patch> mPatches; // 0x228

bool BandCharDesc::IsSameCharDesc(const BandCharDesc& desc) const {
    BandCharDesc bdesc;
    bdesc.CopyCharDesc(this);
    bool ret = false;
    bdesc.CopyCharDesc(&desc);
    ret = ret == 0;
    return ret;
}

void BandCharDesc::Compress(RndTex* tex, bool b){
    tex->Compress(b);
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