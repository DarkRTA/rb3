#include "bandobj/PatchDir.h"
#include "rndobj/Mat.h"
#include "rndwii/Rnd.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

std::vector<Symbol> PatchLayer::sCategoryNames;
PatchDir* PatchLayer::sStickerOwner;
RndDir* PatchLayer::sResource;
RndMat* PatchLayer::sMat;
RndGroup* PatchLayer::sGrpAnim;
RndTransAnim* PatchLayer::sTransAnim;
ColorPalette* PatchLayer::sColorPalette;
INIT_REVS(PatchDir);

float hackyScaleValue = 1.0f;

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

void PatchSticker::SetOnMat(RndMat* mat) const {
    mat->SetDiffuseTex(mTex);
    mat->SetAlpha(mTex ? 1.0f : 0.0f);
    mat->SetBlend(kPreMultAlpha);
}

void PatchSticker::SetIconOnMat(RndMat* mat) const {
    mat->SetDiffuseTex(unk30);
    mat->SetAlpha(unk30 ? 1.0f : 0.0f);
    mat->SetBlend(kPreMultAlpha);
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

void PatchLayer::FlipX(){
    SetScaleX(ScaleX() * -1.0f);
    SetRotation(Modulo(360.0f - Rotation(), 360.0f));
}

void PatchLayer::FlipY(){
    SetScaleX(ScaleX() * -1.0f);
    SetRotation(Modulo(360.0f - (Rotation() - 90.0f) + 90.0f, 360.0f));
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

void PatchLayer::Draw(){
    PatchSticker* sticker = GetSticker(TheLoadMgr.EditMode());
    if(sticker){
        sticker->SetOnMat(sMat);
        sMat->SetColor(sColorPalette->GetColor(mColorIdx));
        Transform tf50;
        tf50.Reset();
        tf50.v = Position();
        Hmx::Matrix3 m78;
        Vector3 vb4(0, Rotation() * DEG2RAD, 0);
        MakeRotMatrix(vb4, tf50.m, true);
        float scale = ScaleX();
        hackyScaleValue = scale;
        if(scale < 0){
            scale = ScaleX();
            scale = scale * -1.0f;
        }
        Vector3 vc0(sticker->unk18 * scale * 7.5f, 1.0f, sticker->unk1c * ScaleY() * 7.5f);
        Scale(vc0, tf50.m, tf50.m);
        Transform tfa8;
        tfa8.Reset();
        if(scale != ScaleX()){
            Vector3 vcc(-1.0f, 1.0f, 1.0f);
            Scale(vcc, tfa8.m, tfa8.m);
            sMat->SetTexXfm(tfa8);
        }
        else sMat->SetTexXfm(tfa8);
        float uisec = TheTaskMgr.UISeconds();
        if(unk28 >= uisec) sTransAnim->SetFrame((unk28 - uisec) * 40.0f + 100.0f, 1.0f);
        else sTransAnim->SetFrame(0, 1.0f);
        float deform = DeformFrame();
        if(deform != sGrpAnim->GetFrame()){
            sGrpAnim->SetFrame(deform, 1.0f);
        }
        sResource->SetLocalXfm(tf50);
        sResource->DrawShowing();
        RndGxDrawDone();
    }
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
        COPY_MEMBER(mLayers)
        if(ty == kCopyDeep && c->HasLayers()){
            CacheRenderedTex(c->mTex, false);
        }
    END_COPYING_MEMBERS
    unk1c0 = true;
END_COPYS

PatchDir::PatchDir() : unk1c0(0) {
    mSaveSizeMethod = &SaveSize;
    mLayers.resize(50);
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

float PatchLayer::Rotation() const { return (mRot * 360.0f) / 511.0f; }

void PatchLayer::SetRotation(float r){
    for(; r > 360.0f; r -= 360.0f);
    for(; r < -360.0f; r += 360.0f);
    MILO_ASSERT(r >= -360.0f, 0x302);
    MILO_ASSERT(r <= 360.0f, 0x303);
    if(r < 0) r += 360.0f;
    mRot = r * 1.4194444f;
}

float PatchLayer::ScaleX() const {
    return mScaleX * (1/1638.3f) - 5.0f;
}

void PatchLayer::SetScaleX(float scaleX){
    MILO_ASSERT(scaleX >= -5.0f, 0x314);
    MILO_ASSERT(scaleX <= 5.0f, 0x315);
    mScaleX = (scaleX + 5.0f) * 1638.3f;
}

float PatchLayer::ScaleY() const {
    return mScaleY * (1/1638.3f) - 5.0f;
}

void PatchLayer::SetScaleY(float scaleY){
    MILO_ASSERT(scaleY >= -5.0f, 0x321);
    MILO_ASSERT(scaleY <= 5.0f, 0x322);
    mScaleY = (scaleY + 5.0f) * 1638.3f;
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
    if(gRev == 0) bs >> mLayers;
    else LoadRemote(bs);
END_LOADS

#define kPatchBufSize 0x830

void PatchDir::SaveRemote(BinStream& bs){
    char buf[0x830];
    IntPacker packer(buf, 0x830);
    packer.AddU(0, 0x10);
    SaveRemote(packer);
    unsigned int size = packer.mPos >> 3 & 0xFFFF;
    if(packer.mPos & 7) size = size + 1 & 0xFFFF;
    packer.SetPos(0);
    packer.AddU(size, 0x10);
    MILO_ASSERT(size < kPatchBufSize, 0x37B);
    bs.Write(buf, size);
}

void PatchDir::LoadRemote(BinStream& bs){
    gRev = 5;
    char buf[2];
    IntPacker packer(buf, 2);
    int read;
    if(gRev < 3){
        bs.Read(buf, 1);
        read = 1;
    }
    else {
        bs.Read(buf, 2);
        read = 2;
    }
    unsigned int size = packer.ExtractU(read << 3);
    size &= 0xFFFF;
    MILO_ASSERT(size < kPatchBufSize, 0x394);
    char buf2[0x830];
    IntPacker packer2(buf2, size);
    bs.Read(buf2, size - read);
    LoadRemote(packer2);
}

void PatchDir::SaveRemote(IntPacker& packer){
    unsigned char size = mLayers.size();
    packer.AddU(size, 8);
    for(unsigned int i = 0; i < size; i++){
        packer.AddBool(!mLayers[i].mStickerCategory.Null());
        if(!mLayers[i].mStickerCategory.Null()){
            mLayers[i].SavePacked(packer);
        }
    }
}

void PatchDir::DrawShowing(){
    TheUI->unk34->Select();
    for(std::vector<PatchLayer>::iterator it = mLayers.begin(); it != mLayers.end(); ++it){
        (*it).Draw();
    }
}

RndCam* PatchDir::CamOverride(){ return TheUI->unk34; }

bool PatchDir::HasLayers() const {
    for(std::vector<PatchLayer>::const_iterator it = mLayers.begin(); it != mLayers.end(); ++it){
        if(!(*it).mStickerCategory.Null()) return true;
    }
    return false;
}

int PatchDir::NumLayers() const { return mLayers.size(); }

int PatchDir::NumLayersUsed() const {
    int count = 0;
    for(std::vector<PatchLayer>::const_iterator it = mLayers.begin(); it != mLayers.end(); ++it){
        if(!(*it).mStickerCategory.Null()) count++;
    }
    return count;
}

bool PatchDir::UsesSticker(const PatchSticker* sticker) const {
    for(std::vector<PatchLayer>::const_iterator it = mLayers.begin(); it != mLayers.end(); ++it){
        if((*it).GetSticker(false) == sticker) return true;
    }
    return false;
}

bool PatchDir::IsLoadingStickers() const { return mStickersLoading.size() > 0; }
int PatchDir::NumStickersLoading() const { return mStickersLoading.size(); }
PatchLayer& PatchDir::Layer(int idx){ return mLayers[idx]; }

int PatchDir::FindEmptyLayer(){
    int idx = 0;
    for(std::vector<PatchLayer>::iterator it = mLayers.begin(); it != mLayers.end(); ++it){
        if((*it).mStickerCategory.Null()){
            return idx;
        }
        else idx++;
    }
    return -1;
}

void PatchDir::LoadStickerTex(PatchSticker* sticker, bool push){
    if(!sticker->mTex && !sticker->mLoader){
        sticker->MakeLoader();
        MILO_ASSERT(sticker->GetLoader(), 0x4EE);
        if(push) mStickersLoading.push_back(sticker);
        else {
            TheLoadMgr.PollUntilLoaded(sticker->mLoader, 0);
            sticker->FinishLoad();
        }
    }
}

void PatchDir::UnloadStickerTex(PatchSticker* sticker){
    if(UsesSticker(sticker)) return;
    if(sticker->mLoader){
        std::vector<PatchSticker*>::iterator it = std::find(mStickersLoading.begin(), mStickersLoading.end(), sticker);
        MILO_ASSERT(it != mStickersLoading.end(), 0x504);
        mStickersLoading.erase(it);
    }
    sticker->Unload();
}

BEGIN_HANDLERS(PatchDir)
    HANDLE_EXPR(has_layers, HasLayers())
    HANDLE_ACTION(clear, Clear())
    HANDLE_EXPR(is_loading_stickers, !mStickersLoading.empty())
    HANDLE_EXPR(get_tex, mTex)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x544)
END_HANDLERS