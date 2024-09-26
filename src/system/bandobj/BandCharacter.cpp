#include "bandobj/BandCharacter.h"
#include "bandobj/BandHeadShaper.h"
#include "bandobj/BandWardrobe.h"
#include "char/CharServoBone.h"
#include "char/CharClipDriver.h"
#include "char/CharFaceServo.h"
#include "char/CharMeshCacheMgr.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(BandCharacter)

const char* BandIntensityString(int num){
    if(num != 0){
        int intensity = num & 0x7F000;
        switch(intensity){
            case 0x1000: return "realtime_idle";
            case 0x2000: return "idle";
            case 0x4000: return "idle_intense";
            case 0x8000: return "play_mellow";
            case 0x10000: return "play_normal";
            case 0x20000: return "play_intense";
            case 0x40000: return "play_solo";
            default:
                MILO_FAIL("Bad intensity %d!", intensity);
                break;
        }
    }
    return "";
}

void BandCharacter::Init(){ Register(); }
void BandCharacter::Terminate(){}

BandCharacter::BandCharacter() : mPlayFlags(0), unk454(this, 0), mAddDriver(0), mFaceDriver(0), mForceNextGroup(0), mForceVertical(1), mOutfitDir(this, 0), mInstDir(this, 0), mTempo("medium"), mFileMerger(0),
    mHeadLookAt(this, 0), mNeckLookAt(this, 0), mEyes(this, 0), unk574(0), mTestPrefab(this, 0), mGenre("rocker"), mDrumVenue("small_club"), mTestTourEndingVenue(0), mInstrumentType("none"), unk594(this, 0),
    mInCloset(0), unk5a1(0), unk5a2(0), unk5a3(0), mSingalongWeight(this, 0), unk5b0(this, kObjListNoNull), unk5c0(this, kObjListNoNull), unk5d0(this, kObjListNoNull),
    unk5e0(this, kObjListNoNull), unk5f0(this, kObjListNoNull), unk600(this, kObjListNoNull), unk610(this, kObjListNoNull), unk620(this, kObjListNoNull),
    unk630(this, kObjListNoNull), unk640(this, kObjListNoNull), unk650(this, kObjListNoNull), unk660(this, kObjListNoNull), unk670(this, kObjListNoNull),
    unk680(this, 0), unk68c(this, 0), unk698(this, 0), unk6a4(this, 0), unk6b0(this, 0), mUseMicStandClips(0), unk6bd(1), unk6c0(this, 0), mInTourEnding(0), unk6d8(0), unk6ec(0),
    unk738(0), unk73c(this, kObjListNoNull), unk74c(this, kObjListNoNull) {
    mGroupName[0] = 0;
    mOverrideGroup[0] = 0;
    mFaceGroupName[0] = 0;
    mOverlay = RndOverlay::Find("char_status", true);
    unk734 = Hmx::Object::New<Waypoint>();
    unk734->SetRadius(2.0f);
    unk734->SetStrictRadiusDelta(5.0f);
    unk734->SetAngRadius(0.17453292f);
    unk734->SetStrictAngDelta(0.2617994f);
}

#pragma push
#pragma dont_inline on
BandCharacter::~BandCharacter(){
    TheRnd->CompressTextureCancel(this);
    delete unk734;
}
#pragma pop

void BandCharacter::AddedObject(Hmx::Object* o){
    Character::AddedObject(o);
    if(streq(o->Name(), "main_add.drv")) mAddDriver = dynamic_cast<CharDriver*>(o);
    if(streq(o->Name(), "expression.drv")) mFaceDriver = dynamic_cast<CharDriver*>(o);
    else if(streq(o->Name(), "head.lookat")) mHeadLookAt = dynamic_cast<CharLookAt*>(o);
    else if(streq(o->Name(), "neck.lookat")) mNeckLookAt = dynamic_cast<CharLookAt*>(o);
    else if(streq(o->Name(), "FileMerger.fm")) mFileMerger = dynamic_cast<FileMerger*>(o);
    else if(streq(o->Name(), "outfit")) mOutfitDir = dynamic_cast<Character*>(o);
    else if(streq(o->Name(), "instrument")) mInstDir = dynamic_cast<Character*>(o);
    else if(streq(o->Name(), "CharEyes.eyes")) mEyes = dynamic_cast<CharEyes*>(o);
    else if(streq(o->Name(), "singalong.weight")) mSingalongWeight = dynamic_cast<CharWeightSetter*>(o);
    else AddObject(o);
}

void BandCharacter::RemovingObject(Hmx::Object* o){
    Character::RemovingObject(o);
    if(o == mAddDriver) mAddDriver = 0;
    else if(o == mFileMerger) mFileMerger = 0;
}

void BandCharacter::Replace(Hmx::Object* from, Hmx::Object* to){
    BandCharDesc::Replace(from, to);
    Character::Replace(from, to);
    if(from == mTestPrefab){
        mTestPrefab = dynamic_cast<BandCharDesc*>(to);
        if(mTestPrefab) CopyCharDesc(mTestPrefab);
    }
}

void BandCharacter::Enter(){
    OnRestoreCategories(0);
    mForceVertical = true;
    mForceNextGroup = false;
    unk574 = false;
    unk5a2 = false;
    unk5a3 = false;
    unk594 = 0;
    mGroupName[0] = 0;
    mPlayFlags &= 0x300000;
    mOverrideGroup[0] = 0;
    mFaceGroupName[0] = 0;
    mFrozen = false;
    Character::Enter();
    SetState("", mPlayFlags, 2, false, false);
    SetHeadLookatWeight(0);
    unk6c0 = 0;
    if(mDriver){
        Message msg("get_matching_dude");
        DataNode handled = HandleType(msg);
        if(handled.Type() == kDataObject){
            unk6c0 = handled.Obj<BandCharacter>(0);
            if(unk6c0){
                unk6c0->unk6c0 = this;
                CharClip* clip = unk6c0->mDriver->FirstPlayingClip();
                if(clip) MakeMRU(this, clip);
            }
        }
    }
}

void BandCharacter::Exit(){ Character::Exit(); }

bool BandCharacter::InVignetteOrCloset() const {
    bool ret = false;
    if(mDriver->mClipType == shell || mDriver->mClipType == vignette) ret = true;
    return ret;
}

void BandCharacter::RemoveDrawAndPoll(Character* c){
    if(c){
        c->SyncObjects();
        VectorRemove(mDraws, c);
        VectorRemove(mPolls, c);
    }
}

void BandCharacter::SetClipTypes(Symbol s1, Symbol s2){
    if(mDriver){
        mDriver->SetClipType(s2);
        if(BoneServo()){
            BoneServo()->SetClipType(s1);
        }
    }
}

SAVE_OBJ(BandCharacter, 0x3EB)

BEGIN_LOADS(BandCharacter)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandCharacter::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(8, 0);
    Character::PreLoad(bs);
    int hashsize = (mHashTable.mNumEntries + 20) * 2;
    int strsize = mStringTable.UsedSize();
    Reserve(hashsize, strsize + 440);
}

void BandCharacter::PostLoad(BinStream& bs){
    Character::PostLoad(bs);
    if(gLoadingProxyFromDisk){
        BandCharDescTest test;
        test.Load(bs);
    }
    else BandCharDesc::Load(bs);
}

BEGIN_COPYS(BandCharacter)
    COPY_SUPERCLASS(Character)
    COPY_SUPERCLASS(BandCharDesc)
    CREATE_COPY(BandCharacter)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPlayFlags)
        COPY_MEMBER(mTempo)
        COPY_MEMBER(mDrumVenue)
        COPY_MEMBER(mTestPrefab)
        COPY_MEMBER(mInstrumentType)
    END_COPYING_MEMBERS
END_COPYS

void BandCharacter::CollideList(const Segment& seg, std::list<Collision>& colls){
    if(CollideSphere(seg)){
        if(IsProxy()) RndDrawable::CollideList(seg, colls);
        else {
            if(mOutfitDir) mOutfitDir->CollideListSubParts(seg, colls);
            if(mInstDir) mInstDir->CollideListSubParts(seg, colls);
            RndDir::CollideList(seg, colls);
        }
    }
}

RndDrawable* BandCharacter::CollideShowing(const Segment& s, float& f, Plane& pl){
    if(mOutfitDir->CollideShowing(s, f, pl)) return this;
    else return RndDir::CollideShowing(s, f, pl);
}

void BandCharacter::Teleport(Waypoint* way){
    Character::Teleport(way);
    unk594 = way;
    if(mOutfitDir) mOutfitDir->mTeleported = true;
}

void BandCharacter::SetTempoGenreVenue(Symbol s1, Symbol s2, const char* cc){
    mTempo = s1;
    mGenre = s2;
    mDrumVenue = NameToDrumVenue(cc);
    if(strstr(cc, "big_club")) mTestTourEndingVenue = "big_club";
    else if(strstr(cc, "arena")) mTestTourEndingVenue = "arena";
    else if(strstr(cc, "festival")) mTestTourEndingVenue = "festival";
}

void BandCharacter::DrawLodOrShadowMode(int i, DrawMode mode){
    Character::DrawLodOrShadow(i, mode);
    if(mode == kCharDrawTranslucent){
        mOutfitDir->DrawLodOrShadow(i, mode);
        if(!unk574) mInstDir->DrawLodOrShadow(i, mode);
    }
    else {
        if(!unk574) mInstDir->DrawLodOrShadow(i, mode);
        mOutfitDir->DrawLodOrShadow(i, mode);
    }
}

float BandCharacter::ComputeScreenSize(RndCam* cam){
    if(mOutfitDir) return mOutfitDir->ComputeScreenSize(cam);
    else return 0;
}

#pragma push
#pragma pool_data off
#pragma dont_inline on
void BandCharacter::AddObject(Hmx::Object* o){
    static Symbol ikScale("CharIKScale");
    static Symbol ikHand("CharIKHand");
    static Symbol collide("CharCollide");
    static Symbol charCuff("CharCuff");
    static Symbol charHair("CharHair");
    static Symbol meshDeform("MeshDeform");
    static Symbol charBoneOffset("CharBoneOffset");
    static Symbol outfitConfig("OutfitConfig");
    static Symbol charMeshHide("CharMeshHide");
    static Symbol ikMidi("CharIKMidi");
    static Symbol cdMidi("CharDriverMidi");
    static Symbol khMidi("CharKeyHandMidi");
    Symbol name = o->ClassName();
    if(name == ikScale) unk5c0.push_back(dynamic_cast<CharIKScale*>(o));
    else if(name == ikHand) unk5d0.push_back(dynamic_cast<CharIKHand*>(o));
    else if(name == collide) unk5e0.push_back(dynamic_cast<CharCollide*>(o));
    else if(name == charHair){
        CharHair* h = dynamic_cast<CharHair*>(o);
        h->SetManagedHookup(true);
        unk5f0.push_back(h);
    }
    else if(name == charCuff) unk600.push_back(dynamic_cast<CharCuff*>(o));
    else if(name == meshDeform){
        RndMeshDeform* md = dynamic_cast<RndMeshDeform*>(o);
        if(!md->Mesh()) MILO_FAIL("RndMeshDeform(%s) has no deform mesh.", md->Name());
        unk610.push_back(md);
    }
    else if(name == outfitConfig){
        OutfitConfig* cfg = dynamic_cast<OutfitConfig*>(o);
        unk738 |= cfg->OverlayFlags();
        unk620.push_back(cfg);
    }
    else if(name == charBoneOffset) unk640.push_back(dynamic_cast<CharBoneOffset*>(o));
    else if(name == charMeshHide) unk5b0.push_back(dynamic_cast<CharMeshHide*>(o));
    else if(name == ikMidi) unk650.push_back(dynamic_cast<CharIKMidi*>(o));
    else if(name == cdMidi) unk660.push_back(dynamic_cast<CharDriverMidi*>(o));
    else if(name == khMidi) unk670.push_back(dynamic_cast<CharKeyHandMidi*>(o));
}
#pragma pop

void BandCharacter::AddOverlays(BandPatchMesh& mesh){
    for(ObjPtrList<OutfitConfig, ObjectDir>::iterator it = unk620.begin(); it != unk620.end(); ++it){
        for(ObjVector<OutfitConfig::Overlay>::iterator oit = (*it)->mOverlays.begin(); oit != (*it)->mOverlays.end(); ++oit){
            if((*oit).mCategory & mesh.mCategory){
                mesh.ConstructQuad((*oit).mTexture);
            }
        }
    }
}

void BandCharacter::DeformHead(SyncMeshCB* cb){
    if(mOutfitDir){
        RndMesh* mesh = mOutfitDir->Find<RndMesh>("head.mesh", false);
        if(mesh){
            BandHeadShaper shaper;
            if(!shaper.Start(this, mGender, mesh, cb, false)) return;
            else mHead.SetShape(shaper);
        }
    }
}

void BandCharacter::SyncOutfitConfig(OutfitConfig* cfg){
    char buf[256];
    strcpy(buf, cfg->Name());
    char* dot = strchr(buf, '.');
    MILO_ASSERT(dot, 0x5EA);
    *dot = 0;
    Symbol sym(buf);
    int colors[6];
    if(sym == eyes){
        colors[3] = 0;
        colors[4] = 0;
        colors[5] = 0;
        colors[3] = mHead.mEyeColor;
        cfg->SetColors(&colors[3]);
    }
    else if(sym == skin || sym == heads){
        colors[0] = 0;
        colors[1] = 0;
        colors[2] = 0;
        colors[0] = mSkinColor;
        cfg->SetColors(colors);
    }
    else {
        BandCharDesc::OutfitPiece* piece = mOutfit.GetPiece(sym);
        if(piece) cfg->SetColors(piece->mColors);
        else {
            BandCharDesc::OutfitPiece* instpiece = mInstruments.GetPiece(sym);
            if(instpiece) cfg->SetColors(instpiece->mColors);
            else cfg->Recompose();
        }
    }
    if(sym == skin){
        OutfitConfig::SetSkinTextures(this, mOutfitDir, this);
        if(unk738){
            cfg->RecomposePatches(unk738);
            unk738 = 0;
        }
    }
}

void BandCharacter::SetDeformation(){
    CharClip* clip = BandCharDesc::GetDeformClip(mGender);
    if(clip){
        CharBonesMeshes meshes;
        meshes.SetName("tmp_bones", this);
        clip->StuffBones(meshes);
        clip->ScaleDown(meshes, 0);
        clip->ScaleAdd(meshes, 1, 0, 0);
        meshes.PoseMeshes();
        if(TheLoadMgr.EditMode() && BoneServo()){
            BoneServo()->AcquirePose();
        }
        for(ObjPtrList<CharIKScale, ObjectDir>::iterator it = unk5c0.begin(); it != unk5c0.end(); ++it){
            (*it)->CaptureBefore();
        }
        CharMeshCacheMgr* mgr = new CharMeshCacheMgr();
        mgr->Disable(!mInCloset);
        for(ObjPtrList<RndMesh, ObjectDir>::iterator it = unk73c.begin(); it != unk73c.end(); ++it){
            mgr->SyncMesh(*it, 0xBF);
        }
        DeformHead(mgr);
        for(ObjPtrList<CharCuff, ObjectDir>::iterator it = unk600.begin(); it != unk600.end(); ++it){
            (*it)->Deform(mgr, mFileMerger);
        }
        unk73c.clear();
        mgr->StuffMeshes(unk73c);
        clip->ScaleDown(meshes, 0);
        float weights[18];
        ComputeDeformWeights(weights);
        for(int i = 0; i < 18; i++){
            clip->ScaleAdd(meshes, weights[i], i, 0);
        }
        meshes.PoseMeshes();
        for(ObjPtrList<RndMeshDeform, ObjectDir>::iterator it = unk610.begin(); it != unk610.end(); ++it){
            (*it)->Reskin(mgr, (unk224 >> 1) & 1);
        }
        for(ObjPtrList<CharCollide, ObjectDir>::iterator it = unk5e0.begin(); it != unk5e0.end(); ++it){
            CharCollide* col = *it;
            RndMesh* colmesh = col->mMesh;
            if(colmesh && mgr->HasMesh(colmesh)){
                col->Deform();
            }
        }
        for(ObjPtrList<CharIKScale, ObjectDir>::iterator it = unk5c0.begin(); it != unk5c0.end(); ++it){
            (*it)->CaptureAfter();
        }
        for(ObjPtrList<CharIKHand, ObjectDir>::iterator it = unk5d0.begin(); it != unk5d0.end(); ++it){
            (*it)->MeasureLengths();
        }
        for(ObjPtrList<OutfitConfig, ObjectDir>::iterator it = unk620.begin(); it != unk620.end(); ++it){
            SyncOutfitConfig(*it);
            (*it)->ApplyAO(mgr);
        }
        delete mgr;
        unk224 &= 0xfffffffd; // i think this might be a bitfield
    }
}

void BandCharacter::PlayGroup(const char* cc, bool b, int i, float f, TaskUnits u, Symbol s){
    if(mOverrideGroup[0] != 0 && AllowOverride(cc)){
        cc = mOverrideGroup;
        f = 0;
    }
    if(*cc){
        bool b528 = mForceNextGroup;
        bool b3 = false;
        unk5a3 = false;
        mForceNextGroup = false;
        if((b | b528) || f != 0){
            b3 = true;
        }
        CharClipDriver* driver = SetState(cc, mPlayFlags, i, b3, true);
        if(driver){
            mFrozen = false;
            driver->SetBeatOffset(f, u, s);
        }
        if(BoneServo()->mRegulate && !mTeleported){
            Teleport(BoneServo()->mRegulate);
        }
    }
}

CharLipSyncDriver* BandCharacter::GetLipSyncDriver(){
    return Find<CharLipSyncDriver>("song.lipdrv", false);
}

DECOMP_FORCEACTIVE(BandCharacter, "BandCharacter::SetFaceOverrideClip couldn't find clip named %s for %s\n",
    "BandCharacter::SetFaceOverrideClip couldnt find  lip sync driver for %s\n", 
    "!mFileMerger->IsLoading()", "head")

void BandCharacter::SetHeadLookatWeight(float f){
    if(mHeadLookAt){
        mHeadLookAt->SetWeight(f);
        if(mNeckLookAt) mNeckLookAt->SetWeight(f * 0.5f);
    }
}

bool BandCharacter::SetPrefab(BandCharDesc* desc){
    mTestPrefab = desc;
    if(mTestPrefab) CopyCharDesc(mTestPrefab);
    return unk224;
}

void BandCharacter::ClearDircuts(){ mDircuts.clear(); }

bool BandCharacter::AddDircut(Symbol s1, Symbol s2, int i){
    Symbol animinst = BandCharDesc::GetAnimInstrument(mInstrumentType);
    FilePath fp;
    bool ismale = mGender != "female";
    int mask = 0x8000;
    if(!ismale) mask = 0x4000;
    if(i & mask){
        fp.Set(FileRoot(), MakeString("char/main/anim/%s/dircut/%s/%s_%s.milo", animinst, mGender, s1, s2));
    }
    else {
        fp.Set(FileRoot(), MakeString("char/main/anim/%s/dircut/%s/%s.milo", animinst, mGender, s1));
    }
    return AddDircut(fp);
}

int BandCharacter::GetShotFlags(Symbol s){
    BandCharDesc::CharInstrumentType ty = BandCharDesc::GetInstrumentFromSym(mInstrumentType);
    if(ty >= BandCharDesc::kNumInstruments) return 0;
    else {
        DataArray* arr = BandWardrobe::GetGroupArray(ty);
        for(int i = 0; i < arr->Size(); i++){
            if(arr->Array(i)->Sym(0) == s){
                return arr->Array(i)->Int(1);
            }
        }
    }
    return 0;
}

void BandCharacter::SetContext(Symbol s){
    CharWeightable* w = Find<CharWeightable>("venue.weight", false);
    if(w) w->SetWeight(s == "venue");
    CharWeightable* cw = Find<CharWeightable>("closet.weight", false);
    if(cw) cw->SetWeight(s == "closet");
    mOverrideGroup[0] = 0;
    int hideallint = 0;
    if(s == "vignette"){
        SetClipTypes(s, s);
        hideallint = 0x2000;
        mDriver->SetBlendWidth(1.0f);
    }
    else if(s == "closet"){
        SetClipTypes("shell", "shell");
        mDriver->SetBlendWidth(2.0f);
    }
    else if(s == "venue"){
        ObjectDir* clipsdir = Find<ObjectDir>("body_clips", true);
        mDriver->SetClips(clipsdir);
        mDriver->SetBlendWidth(1.0f);
        switch(BandCharDesc::GetInstrumentFromSym(mInstrumentType)){
            case kGuitar:
            case kBass:
                SetClipTypes("guitar_all", "guitar_body");
                break;
            case kDrum:
                SetClipTypes("drum_all", "drum_body");
                break;
            case kMic:
                SetClipTypes("mic_body", "mic_body");
                break;
            case kKeyboard:
                SetClipTypes("keyboard_all", "keyboard_body");
                break;
            default:
                break;
        }
        HandleType(on_set_instrument_clip_types_msg);
    }
    else {
        MILO_WARN("%s illegal context %s", PathName(this), s);
    }
    CharMeshHide::HideAll(unk5b0, hideallint);
}

void ReplaceSubdir(ObjectDir*, ObjectDir*);

void BandCharacter::SetVisemes(){
    ObjectDir* visemedir = Find<ObjectDir>("visemes", false);
    if(visemedir){
        ObjectDir* viseme = BandHeadShaper::GetViseme(mGender, false);
        if(viseme) ReplaceSubdir(visemedir, viseme);
        CharLipSyncDriver* lsdriver = Find<CharLipSyncDriver>("song.lipdrv", false);
        if(lsdriver) lsdriver->SetClips(visemedir);
        CharFaceServo* servo = Find<CharFaceServo>("face.faceservo", false);
        if(servo) servo->SetClips(visemedir);
    }
    ObjectDir* vignettedir = Find<ObjectDir>("vignette_visemes", false);
    if(vignettedir){
        ObjectDir* viseme = BandHeadShaper::GetViseme(mGender, false);
        if(viseme) ReplaceSubdir(vignettedir, viseme);
        CharLipSyncDriver* lsdriver = Find<CharLipSyncDriver>("vignette.lipdrv", false);
        if(lsdriver) lsdriver->SetClips(vignettedir);
    }
}

void BandCharacter::SetGroupName(const char* name){ strcpy(mGroupName, name); }

OutfitConfig* BandCharacter::GetOutfitConfig(const char* cc){
    ObjectDir* pObjectDir;
    if(strcmp(cc, "guitar.cfg") == 0 || strcmp(cc, "bass.cfg") == 0 || strcmp(cc, "drum.cfg") == 0 || strcmp(cc, "mic.cfg") == 0 || strcmp(cc, "keyboard.cfg") == 0){
        pObjectDir = mInstDir;
    }
    else pObjectDir = mOutfitDir;
    MILO_ASSERT(pObjectDir, 0x8AD);
    return pObjectDir->Find<OutfitConfig>(cc, false);
}

RndTex* BandCharacter::GetPatchTex(Patch& patch){
    static Message get_patch_tex("get_patch_tex", DataNode(0), DataNode(0));
    get_patch_tex[0] = DataNode(patch.mTexture);
    get_patch_tex[1] = DataNode(patch.mMeshName);
    DataNode handled = HandleType(get_patch_tex);
    if(handled.Type() != kDataUnhandled){
        if(handled.Obj<RndTex>(0)){
            goto ret;
        }
    }
    if(!mPrefab.Null()){
        return Find<RndTex>(MakeString("prefab_art%02d.tex", patch.mTexture), false);
    }
    else if(TheLoadMgr.EditMode()) return Find<RndTex>("patchtest.tex", false);
    else return 0;
ret:
    return handled.Obj<RndTex>(0);
}

RndMesh* BandCharacter::GetPatchMesh(Patch& patch){
    ObjectDir* dir = this;
    if(patch.mCategory & 0x2E00){
        dir = mInstDir;
    }
    return dir->Find<RndMesh>(patch.mMeshName.c_str(), false);
}

// void __thiscall BandCharacter::GetPatchMesh(BandCharacter *this,Patch *param_1)

// {
//   undefined4 uVar1;
  
//   if ((*(uint *)(param_1 + 0xc) & 0x2e00) != 0) {
//     this = *(BandCharacter **)(this + 0x540);
//   }
//   uVar1 = ObjectDir::FindObject((ObjectDir *)this,*(char **)(param_1 + 0x18),false);
//   __dynamic_cast(uVar1,0,&RndMesh::__RTTI,&Hmx::Object::__RTTI,0);
//   return;
// }

void BandCharacter::TextureCompressed(int i){
    std::list<int>::iterator it;
    for(it = mCompressedTextureIDs.begin(); it != mCompressedTextureIDs.end() && *it != i; ++it);
    if(it == mCompressedTextureIDs.end()) MILO_WARN("%s Could not find compress texture id %d\n", PathName(this), i);
    else mCompressedTextureIDs.erase(it);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandCharacter)
    HANDLE_EXPR(get_play_flags, mPlayFlags)
    HANDLE(play_group, OnPlayGroup)
    HANDLE(group_override, OnGroupOverride)
    HANDLE(change_face_group, OnChangeFaceGroup)
    HANDLE_ACTION(clear_group, ClearGroup())
    HANDLE(set_play, OnSetPlay)
    HANDLE_ACTION(start_load, StartLoad(_msg->Int(2), _msg->Size() > 3 ? _msg->Int(3) : mInCloset, false))
    HANDLE_EXPR(is_loading, IsLoading())
    HANDLE_EXPR(flag_string, FlagString(_msg->Int(2)))
    HANDLE(cam_teleport, OnCamTeleport)
    HANDLE(closet_teleport, OnClosetTeleport)
    HANDLE(install_filter, OnInstallFilter)
    HANDLE(pre_clear, OnPreClear)
    HANDLE(copy_prefab, OnCopyPrefab)
    HANDLE(save_prefab, OnSavePrefab)
    HANDLE(set_file_merger, OnSetFileMerger)
    if(sym == list_dircuts) return OnListDircuts();
    HANDLE(load_dircut, OnLoadDircut)
    HANDLE_ACTION(set_context, SetContext(_msg->Sym(2)))
    HANDLE_ACTION(save_from_closet, SavePrefabFromCloset())
    HANDLE_ACTION(set_singalong, SetSingalong(_msg->Float(2)))
    HANDLE(on_post_merge, OnPostMerge)
    HANDLE(hide_categories, OnHideCategories)
    HANDLE(restore_categories, OnRestoreCategories)
    HANDLE_ACTION(game_over, GameOver())
    HANDLE(toggle_interests_overlay, OnToggleInterestDebugOverlay)
    HANDLE(list_drum_venues, OnListDrumVenues)
    HANDLE(portrait_begin, OnPortraitBegin)
    HANDLE(portrait_end, OnPortraitEnd)
    HANDLE_SUPERCLASS(BandCharDesc)
    HANDLE_SUPERCLASS(Character)
    HANDLE_CHECK(0x9A6)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(BandCharacter)
    SYNC_PROP(tempo, mTempo)
    SYNC_PROP(genre, mGenre)
    SYNC_PROP(drum_venue, mDrumVenue)
    SYNC_PROP(force_vertical, mForceVertical)
    SYNC_PROP_SET(instrument_type, mInstrumentType, SetInstrumentType(_val.Sym(0)))
    SYNC_PROP_SET(group_name, mGroupName, SetGroupName(_val.Str(0)))
    SYNC_PROP_SET(head_lookat_weight, mHeadLookAt ? mHeadLookAt->Weight() : 0, SetHeadLookatWeight(_val.Float(0)))
    SYNC_PROP_SET(in_closet, mInCloset, StartLoad(false, _val.Int(0), false))
    SYNC_PROP(test_prefab, mTestPrefab)
    SYNC_PROP(use_mic_stand_clips, mUseMicStandClips)
    SYNC_PROP(in_tour_ending, mInTourEnding)
    SYNC_PROP(test_tour_ending_venue, mTestTourEndingVenue)
    SYNC_SUPERCLASS(BandCharDesc)
    SYNC_SUPERCLASS(Character)
END_PROPSYNCS