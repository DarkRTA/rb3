#include "bandobj/PatchDir.h"
#include "rndobj/Mat.h"
#include "utl/Symbols.h"

std::vector<Symbol> PatchLayer::sCategoryNames;
PatchDir* PatchLayer::sStickerOwner;
RndDir* PatchLayer::sResource;
RndMat* PatchLayer::sMat;
RndGroup* PatchLayer::sGrpAnim;
RndTransAnim* PatchLayer::sTransAnim;
ColorPalette* PatchLayer::sColorPalette;

INIT_REVS(PatchDir);

BinStream& operator<<(BinStream& bs, const PatchDescriptor& d){
    bs << d.patchType;
    bs << d.patchIndex;
    return bs;
}

BinStream& operator>>(BinStream& bs, PatchDescriptor& d){
    int i; bs >> i;
    d.patchType = i;
    bs >> d.patchIndex;
    return bs;
}

PatchSticker::PatchSticker() : unk18(1.0f), unk1c(1.0f), unk20(0), unk24(1), mLoader(0), mTex(0), unk30(0) {

}

PatchSticker::~PatchSticker(){
    Unload();
}

void PatchSticker::MakeLoader(){
    MILO_ASSERT(!mLoader, 0x52);
    mLoader = dynamic_cast<FileLoader*>(TheLoadMgr.AddLoader(unkc, kLoadFront));
}

void PatchSticker::FinishLoad(){
    MILO_ASSERT(mLoader, 0x5B);
    MILO_ASSERT(!mTex, 0x5C);
    mTex = Hmx::Object::New<RndTex>();
    unk30 = Hmx::Object::New<RndTex>();
    RndBitmap bmap;
    const char* buf = mLoader->GetBuffer(0);
    RELEASE(mLoader);
    if(buf){
        RndBitmap other;
        other.Create((void*)buf);
    }
}

void PatchSticker::Unload(){
    RELEASE(mLoader);
    RELEASE(mTex);
    RELEASE(unk30);
}

void PatchLayer::Init(){
    DataArray* cfg = SystemConfig("art_maker", "stickers");
    for(int i = 1; i < cfg->Size(); i++){
        sCategoryNames.push_back(cfg->Array(i)->ForceSym(0));
    }
    InitResources();
}

void PatchLayer::InitResources(){
    DataArray* cfg = SystemConfig();
    DataArray* artMakerArr = cfg->FindArray("art_maker", false);
    if(artMakerArr){
        DataArray* patchLayerArr = artMakerArr->FindArray("patch_layer", false);
        if(patchLayerArr){
            sResource = dynamic_cast<RndDir*>(DirLoader::LoadObjects(FilePath(FileGetPath(patchLayerArr->File(), 0), patchLayerArr->Str(1)), 0, 0));
            MILO_ASSERT(sResource, 0xBA);
            sMat = sResource->Find<RndMat>("patch.mat", true);
            sTransAnim = sResource->Find<RndTransAnim>("root.tnm", true);
            sGrpAnim = sResource->Find<RndGroup>("warp.grp", true);
            sColorPalette = sResource->Find<ColorPalette>("sticker.pal", true);
        }
    }
}

void PatchLayer::Terminate(){
    RELEASE(sResource);
    sMat = 0;
}

PatchLayer::PatchLayer() : mStickerCategory(gNullStr), mStickerIdx(0), unk28(0) {
    Reset();
}

BEGIN_COPYS(PatchLayer)
    CREATE_COPY(PatchLayer)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mColorIdx)
        COPY_MEMBER(mDeformFrame)
        COPY_MEMBER(mPosX)
        COPY_MEMBER(mPosZ)
        COPY_MEMBER(mRot)
        COPY_MEMBER(mScaleX)
        COPY_MEMBER(mScaleY)
        COPY_MEMBER(mStickerCategory)
        COPY_MEMBER(mStickerIdx)
    END_COPYING_MEMBERS
END_COPYS

void PatchLayer::Reset(){
    mColorIdx = 0;
    SetPosition(Vector3(0,0,0));
    SetRotation(0);
    SetScaleX(1.0f);
    SetScaleY(1.0f);
    SetDeformFrame(0);
    unk28 = 0;
}

PatchSticker* PatchLayer::GetSticker(bool b) const {
    if(mStickerCategory.Null()) return 0;
    else return sStickerOwner->GetSticker(mStickerCategory, mStickerIdx, b);
}

bool PatchLayer::HasSticker() const { return !mStickerCategory.Null(); }

void PatchLayer::SelectFX(){
    unk28 = TheTaskMgr.UISeconds() + 0.5f;
}

void PatchLayer::ClearSticker(){
    Reset();
    mStickerCategory = Symbol(0);
}

void PatchLayer::SetScale(float x, float y){
    SetScaleX(1.0f / x);
    SetScaleY(1.0f / y);
}

void PatchLayer::SetDefaultColor(){
    PatchSticker* sticker = GetSticker(false);
    if(sticker) mColorIdx = sticker->unk20;
}

bool PatchLayer::AllowColor(){
    PatchSticker* sticker = GetSticker(false);
    MILO_ASSERT(sticker, 0x127);
    return sticker->unk24;
}

BEGIN_HANDLERS(PatchLayer)
    HANDLE_EXPR(color_palette, sColorPalette)
    HANDLE_EXPR(has_sticker, !mStickerCategory.Null())
    HANDLE_ACTION(set_scale, SetScale(_msg->Float(2), _msg->Float(3)))
    HANDLE_EXPR(allow_color, AllowColor())
    HANDLE_ACTION(set_default_color, SetDefaultColor())
    HANDLE_ACTION(select_fx, SelectFX())
    HANDLE_ACTION(flip_x, FlipX())
    HANDLE_ACTION(flip_y, FlipY())
    HANDLE_ACTION(clear_sticker, ClearSticker())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x185)
END_HANDLERS

BEGIN_PROPSYNCS(PatchLayer)
    SYNC_PROP_MODIFY(sticker_category, mStickerCategory, mStickerIdx = 0)
    SYNC_PROP(sticker_idx, mStickerIdx)
    SYNC_PROP(color_idx, mColorIdx)
END_PROPSYNCS

void PatchDir::Init(){
    PatchLayer::Init();
    TheDebug.AddExitCallback(Terminate);
}

void PatchDir::Terminate(){ PatchLayer::Terminate(); }

BEGIN_COPYS(PatchDir)
    CREATE_COPY(PatchDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(unk194)
        if(ty == kCopyDeep && c->HasLayers()){
            CacheRenderedTex(c->mTex, false);
        }
    END_COPYING_MEMBERS
    unk1c0 = true;
END_COPYS

PatchDir::PatchDir() : unk1c0(0) {
    mSaveSizeMethod = &SaveSize;
    unk194.resize(50);
    mTex = Hmx::Object::New<RndTex>();
    mTex->SetMipMapK(666.0f);
    if(TheLoadMgr.EditMode()) LoadStickerData();
}

PatchDir::~PatchDir(){

}

void PatchDir::CacheRenderedTex(RndTex* tex, bool b){
    MILO_ASSERT(tex->Width() > 0 && tex->Height() > 0, 0x1EF);
    RndBitmap bmap;
    tex->LockBitmap(bmap, true);
    mTex->SetBitmap(bmap, 0, true);
    tex->UnlockBitmap();
    if(b) mTex->Compress(true);
}

Vector3 PatchLayer::Position() const {
    return Vector3(mPosX, 0, mPosZ);
}

void PatchLayer::SetPosition(const Vector3& v){
    mPosX = v.x;
    mPosZ = v.z;
}

float PatchLayer::DeformFrame() const {
    return mDeformFrame * (1 / 20.46f);
}

void PatchLayer::SetDeformFrame(float df){
    MILO_ASSERT(df >= 0.0f, 0x32E);
    MILO_ASSERT(df <= 50.0f, 0x32F);
    mDeformFrame = df * 20.46f;
}

BinStream& operator>>(BinStream& bs, PatchLayer& layer){
    MILO_ASSERT(PatchDir::GetCurrentRev() == 0, 0x337);
    bs >> layer.mStickerCategory;
    bs >> layer.mStickerIdx;
    bs >> layer.mColorIdx;
    Vector3 v; bs >> v;
    layer.SetPosition(v);
    float rot; bs >> rot;
    layer.SetRotation(rot);
    float x; bs >> x;
    layer.SetScaleX(x);
    float y; bs >> y;
    layer.SetScaleY(y);
    float frame; bs >> frame;
    layer.SetDeformFrame(frame);
    return bs;
}

void PatchDir::Save(BinStream& bs){
    bs << 5;
    SaveRemote(bs);
}

BEGIN_LOADS(PatchDir)
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    if(gRev == 0) bs >> unk194;
    else LoadRemote(bs);
END_LOADS

BEGIN_HANDLERS(PatchDir)
    HANDLE_EXPR(has_layers, HasLayers())
    HANDLE_ACTION(clear, Clear())
    HANDLE_EXPR(is_loading_stickers, !unk1b4.empty())
    HANDLE_EXPR(get_tex, mTex)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x544)
END_HANDLERS