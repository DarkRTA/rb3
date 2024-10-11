#include "bandobj/BandCharacter.h"
#include "bandobj/BandHeadShaper.h"
#include "bandobj/BandWardrobe.h"
#include "char/CharServoBone.h"
#include "char/CharClipDriver.h"
#include "char/CharClipGroup.h"
#include "char/CharFaceServo.h"
#include "char/CharInterest.h"
#include "char/CharMeshCacheMgr.h"
#include "char/CharUtl.h"
#include "math/Rand.h"
#include "obj/Utl.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(BandCharacter)

ObjectDir* sBoneMergeDir;
ObjectDir* sOutfitDir;
ObjectDir* sResourceDir;
ObjectDir* sCharSharedDir;
ObjectDir* sInstrumentDir;
ObjectDir* sInstResourceDir;
ObjectDir* sToDir;

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
            unk6c0 = handled.Obj<BandCharacter>();
            if(unk6c0){
                unk6c0->unk6c0 = this;
                CharClip* clip = unk6c0->GetDriver()->FirstPlayingClip();
                if(clip) MakeMRU(this, clip);
            }
        }
    }
}

void BandCharacter::Exit(){ Character::Exit(); }

bool BandCharacter::InVignetteOrCloset() const {
    Symbol cliptype = mDriver->ClipType();
    bool ret = false;
    if(cliptype == shell || cliptype == vignette) ret = true;
    return ret;
}

DECOMP_FORCEACTIVE(BandCharacter, "BandCharacter.no_anim")

CharClipDriver* BandCharacter::PlayMainClip(int i, bool b){
    if(mGroupName[0] == 0 || !unk454) return 0;
    else {
        ObjectDir* clipdir = unk454->ClipDir();
        if(!clipdir) return 0;
        else {
            CharClipGroup* grp = clipdir->Find<CharClipGroup>(mGroupName, false);
            if(!grp){
                MILO_NOTIFY_ONCE("%s could not find group %s in %s\n", PathName(this), mGroupName, PathName(clipdir));
                return 0;
            }
            else {
                bool invorc = InVignetteOrCloset();
                int mask = mPlayFlags;
                if(invorc){
                    mask = mGender == "male" ? 0x20 : 0x40;
                }
                else if(streq(mGroupName, "realtime_idle")){
                    mask = mask & 0xFFF80FFF | 0x1000;
                }
                CharClip* clp = 0;
                if(mUseMicStandClips || mInstrumentType == keyboard && ((i & 0xF) != 2) && !b){
                    CharClip* firstclip = unk454->FirstClip();
                    if(firstclip){
                        if(firstclip->InGroup(grp)){
                            i = i & 0xfffffff0U | 4;
                            clp = firstclip;
                        }
                    }
                }
                if(!clp) clp = grp->GetClip(mask);
                if(!clp && invorc && mask == 0x40){
                    MILO_NOTIFY_ONCE("%s no female vignette clip in %s, using male", PathName(this), PathName(grp));
                    mask = 0x20;
                    clp = grp->GetClip(0x20);
                }
                if(!clp){
                    MILO_NOTIFY_ONCE("%s no clip w. flags %s in %s", PathName(this), FlagString(mask), PathName(grp));
                    invorc = 0;
                }
                else {
                    if(invorc) clp->SetFlags(clp->Flags() | 0xF);
                    else {
                        if(IsLoading()){
                            int imask = (mask & 0xF) ? 2 : 1;
                            CharDriver* drv = mDriver;
                            if(unk454 == drv) drv = mAddDriver;
                            CharClip* stillclip = drv->ClipDir()->Find<CharClip>("still", false);
                            if(stillclip) drv->Play(stillclip, imask, -1.0f, 1e+30f, 0.0f);
                            else MILO_NOTIFY_ONCE("%s could not find still clip", PathName(drv));
                        }
                    }
                    CharClipDriver* played = unk454->Play(clp, mask, -1.0f, 1e+30f, 0.0f);
                    if((mask & 0xF) == 2) mTeleported = true;
                    if(played){
                        MakeMRU(unk6c0, clp);
                    }
                    return played;
                }
            }
        }
    }
}

void BandCharacter::MakeMRU(BandCharacter* bchar, CharClip* clip){
    MILO_ASSERT(clip, 0x1A1);
    if(bchar && bchar->GetDriver()->ClipDir()){
        CharClip* clip2 = bchar->GetDriver()->ClipDir()->Find<CharClip>(clip->Name(), false);
        if(clip2) clip2->MakeMRU();
    }
}

void BandCharacter::PlayFaceClip(){
    if(mFaceDriver){
        CharClipGroup* grp = mFaceDriver->ClipDir()->Find<CharClipGroup>(mFaceGroupName, false);
        if(!grp){
            MILO_WARN("Could not find CharClipGroup %s in %s\n", mFaceGroupName, PathName(mDriver->ClipDir()));
        }
        else mFaceDriver->Play(grp->GetClip(), 4, -1.0f, 1e+30f, 0.0f);
    }
}

bool BandCharacter::AllowOverride(const char* cc){
    if(mInstrumentType == "mic"){
        if(!streq(cc, "stand") && !streq(cc, "closeup") && !streq(cc, "extreme_closeup") && !streq(cc, "")){
            return false;
        }
    }
    return true;
}

void BandCharacter::Poll(){
    START_AUTO_TIMER("cc_poll");
    if(unk5a2){
        Teleport(unk594);
        unk5a2 = false;
    }
    if(unk5a3){
        const char* name;
        if(mOverrideGroup[0] != 0) name = mOverrideGroup;
        else name = mInstrumentType == drum ? "sit" : "stand";
        SetState(name, mPlayFlags, 2, false, true);
        unk5a3 = false;
    }
}

void BandCharacter::CalcBoundingSphere(){
    mBounding.Zero();
    Sphere s48(Vector3(0,0,5.0f), 45.0f);
    Multiply(s48, mSphereBase->WorldXfm(), s48);
    mBounding.GrowToContain(s48);
    if(mInstDir){
        Sphere s58;
        mInstDir->MakeWorldSphere(s58, false);
        mBounding.GrowToContain(s58);
    }
    Transform tf38;
    FastInvert(mSphereBase->WorldXfm(), tf38);
    Multiply(mBounding, tf38, s48);
    SetSphere(s48);
}

bool BandCharacter::ValidateInterest(CharInterest* ci, ObjectDir* dir){
    if(!ci) return false;
    if(dir){
        if(dir == this || ci->Dir() == this){
            if(ci->CategoryFlags() & 0x200) return false;
        }
        DataNode* prop = dir->Property("lookat_cameras", false);
        if(prop && (ci->CategoryFlags() & 1) && !prop->Int()) return false;
    }
    return true;
}

bool BandCharacter::SetFocusInterest(CharInterest* ci, int i){
    if(mEyes) return mEyes->SetFocusInterest(ci, i);
    else return Character::SetFocusInterest(ci, i);
}

void BandCharacter::SetInterestFilterFlags(int i){
    if(mEyes) mEyes->SetInterestFilterFlags(i);
    else Character::SetInterestFilterFlags(i);
}

void BandCharacter::ClearInterestFilterFlags(){
    if(mEyes) mEyes->ClearInterestFilterFlags();
    else Character::ClearInterestFilterFlags();
}

DataNode BandCharacter::OnToggleInterestDebugOverlay(DataArray* da){
    if(mEyes) mEyes->ToggleInterestsDebugOverlay();
    return DataNode(0);
}

struct FlagPair {
    int flag;
    const char* str;
};

const char* BandCharacter::FlagString(int flags){
    static FlagPair pairs[7] = {
        {0x1000, "IR|"},
        {0x2000, "I|"},
        {0x4000, "II|"},
        {0x8000, "PM|"},
        {0x10000, "P|"},
        {0x20000, "PI|"},
        {0x40000, "PS|"},
    };
    char buf[256];
    buf[0] = 0;
    for(unsigned int i = 0; i < 7; i++){
        if(flags & pairs[i].flag){
            strcat(buf, pairs[i].str);
            flags &= ~(pairs[i].flag);
        }
    }
    if(flags != 0 || buf[0] == 0) strcat(buf, MakeString("0x%x", flags));
    else buf[strlen(buf) - 1] = 0;
    return MakeString(buf);
}

void BandCharacter::UpdateOverlay(){
    if(mOverlay->Showing()){
        *mOverlay << Name() << "- " << mInstrumentType << ": " << mGroupName << " " << FlagString(mPlayFlags & 0x7F000);
        CharClipDriver* firstplaying = mDriver->FirstPlaying();
        if(firstplaying){
            if(AddDriverClipDir()){
                *mOverlay << " " << SafeName(firstplaying->GetClip());
                CharClipDriver* firstaddplaying = mAddDriver->FirstPlaying();
                if(firstaddplaying){
                    *mOverlay << "/" << SafeName(firstaddplaying->GetClip()) << " " << FlagString(firstaddplaying->GetClip()->Flags() & 0x7F000) << " ";
                    *mOverlay << " " << CharClip::BeatAlignString(firstaddplaying->mPlayFlags);
                    *mOverlay << MakeString(" %.2f %.2f", std::fmod(TheTaskMgr.Beat(), 1.0f), std::fmod(firstaddplaying->mBeat, 1.0f));
                }
                else {
                    *mOverlay << " " << FlagString(firstplaying->GetClip()->Flags() & 0x7F000);
                    *mOverlay << " " << CharClip::BeatAlignString(firstplaying->mPlayFlags);
                    *mOverlay << MakeString(" %.2f %.2f", std::fmod(TheTaskMgr.Beat(), 1.0f), std::fmod(firstplaying->mBeat, 1.0f));
                }
            }
            else {
                *mOverlay << " " << SafeName(firstplaying->GetClip()) << " " << FlagString(firstplaying->GetClip()->Flags() & 0x7F000);
                *mOverlay << " " << CharClip::BeatAlignString(firstplaying->mPlayFlags);
                *mOverlay << MakeString(" %.2f %.2f", std::fmod(TheTaskMgr.Beat(), 1.0f), std::fmod(firstplaying->mBeat, 1.0f));
            }
        }
        *mOverlay << "\n";
    }
}

void BandCharacter::RemoveDrawAndPoll(Character* c){
    if(c){
        c->SyncObjects();
        VectorRemove(mDraws, c);
        VectorRemove(mPolls, c);
    }
}

#pragma push
#pragma pool_data off
void BandCharacter::SyncObjects(){
    unk6b0 = Find<CharWeightable>("lod0.weight", false);
    static const char* bones[8] = {
        "bone_pelvis.mesh", "bone_prop0.mesh", "bone_prop1.mesh", "bone_prop2.mesh",
        "bone_prop3.mesh", "spot_neck.mesh", "spot_navel.mesh", "bone_mic_stand_bottom.mesh"
    };
    for(const char** ptr = bones; *ptr != 0; ptr++){
        RndTransformable* t = Find<RndTransformable>(*ptr, false);
        if(t) t->SetTransParent(this, false);
    }
    SetDeformation();
    RndMat* feetmat = Find<RndMat>("feet_socks_skin.mat", false);
    if(feetmat){
        RndMat* legmat = mOutfitDir->Find<RndMat>("legs_socks_swap.mat", false);
        if(legmat) feetmat->Copy(legmat, kCopyDeep);
        else {
            RndMat* skinmat = Find<RndMat>("feet_skin.mat", false);
            if(skinmat) feetmat->Copy(skinmat, kCopyDeep);
        }
    }

//   iVar4 = *(int *)(this + 0x5e4);
//   if ((iVar4 != 0) && (*(int *)(iVar4 + 4) != 0)) {
//     piVar12 = *(int **)(iVar4 + 8);
//     for (piVar3 = (int *)piVar12[2]; piVar11 = piVar3, piVar3 != piVar12; piVar3 = (int *)piVar3[2 ])
//     {
//       for (; piVar11 != piVar12; piVar11 = (int *)piVar11[1]) {
//         iVar4 = *piVar11;
//         iVar5 = *(int *)piVar11[1];
//         if (*(float *)(iVar5 + 0x178) <= *(float *)(iVar4 + 0x178)) break;
//         *piVar11 = iVar5;
//         *(int *)piVar11[1] = iVar4;
//       }
//     }
//   }

    for(ObjPtrList<CharHair, ObjectDir>::iterator it = unk5f0.begin(); it != unk5f0.end(); ++it){
        (*it)->Hookup(unk5e0);
    }
    Character::SyncObjects();
    for(ObjPtrList<CharBoneOffset, ObjectDir>::iterator it = unk640.begin(); it != unk640.end(); ++it){
        (*it)->ApplyToLocal();
        mOutfitDir->RemoveFromPoll(*it);
    }
    RemoveDrawAndPoll(mOutfitDir);
    RemoveDrawAndPoll(mInstDir);
    if(!mInCloset){
        for(ObjPtrList<OutfitConfig, ObjectDir>::iterator it = unk620.begin(); it != unk620.end(); ++it){
            (*it)->CompressTextures();
        }
        while(!unk610.empty()){
            RndMeshDeform* df = unk610.front();
            if(!df->Mesh()) MILO_FAIL("BandCharacter::SyncObjects() - character missing mesh data.");
            df->Mesh()->SetKeepMeshData(false);
            delete df;
        }
        while(!unk600.empty()){
            delete unk600.front();
        }
        for(ObjPtrList<CharCollide, ObjectDir>::iterator it = unk5e0.begin(); it != unk5e0.end(); ++it){
            (*it)->ClearMesh();
        }
    }
    CharMeshHide::HideAll(unk5b0, -(mDriver->ClipType() == "vignette") & 0x2000);
    if(InVignetteOrCloset()){
        CharClipDriver* first = mDriver->FirstPlaying();
        if(first && mGroupName[0] != 0){
            int mask = mGender == "male" ? 0x20 : 0x40;
        }
    }
    const char* eyedfname = mGender == "male" ? "eyesdeform_male.anim" : "eyesdeform_female.anim";
    RndPropAnim* panim = Find<RndPropAnim>(eyedfname, false);
    if(panim){
        int numeyeshapes = BandHeadShaper::sEyeNum;
        if((int)panim->EndFrame() != numeyeshapes)
            MILO_NOTIFY_ONCE("%s must have a frame for each eye shape.  It currently has %d frames, but there are %d eye shapes",
                eyedfname, (int)panim->EndFrame(), BandHeadShaper::sEyeNum);
        if(!DataVariable("eyetweaker.loadedsettings").Int()){
            panim->SetFrame(mHead.mEye, 1.0f);
        }
    }
    else MILO_NOTIFY_ONCE("Can't find eye settings prop anim %s. This is required to set range of motion and lid tracking for each eye shape.", eyedfname);
}
#pragma pop

float sDrawOrder = -1.0f;

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
    bs >> mPlayFlags;
    bs >> mTempo;
    if(gRev < 6){
        if(gRev < 4){
            int i; bs >> i;
            if(gRev < 3){
                Symbol s; bs >> s;
            }
        }
        Symbol s; bs >> s;
    }
    if(gRev > 6) bs >> mDrumVenue;
    if(gRev != 0) mTestPrefab.Load(bs, true, BandCharDesc::GetPrefabs());
    if(gRev == 2 || gRev == 3 || gRev == 4){ bool b; bs >> b; }
    if(gRev > 7){
        if(gLoadingProxyFromDisk){ Symbol s; bs >> s; }
        else bs >> mInstrumentType;
    }
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

void BandCharacter::DrawShowing(){
    if(!unk6bd || !IsLoading()){
        if(DataVariable("bandcharacter.show_spheres").Int()){

        }
        Character::DrawShowing();
        static DataNode& n = DataVariable("bandcharacter.show_slot");
        if(n.Int()){
            Transform& headxfm = CharUtlFindBoneTrans("bone_head", this)->WorldXfm();
            MakeString("slot%d pos%d");
        }
    }
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

void BandCharacter::StartLoad(bool b1, bool b2, bool b3){
    bool b4 = false;
    if(!mInCloset){
        if(b2 || (unk224 & 7)) b4 = true;
    }
    bool bvar1 = mInCloset;
    unk5a1 = b4;
    mInCloset = b2;
    if(bvar1 && !b2) b3 = true;
    if(!IsLoading() || !unk6bd || b3){
        b4 = false;
        if(unk5a1 || b3) b4 = true;
        unk6bd = b4;
    }

    if(!mFileMerger->StartLoad(b1) && (mInCloset || (bvar1 && !mInCloset))){
        mFileMerger->Select("blank", FilePath(""), true);
        mFileMerger->StartLoad(b1);
    }
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
    int colors[7];
    *dot = 0;
    Symbol sym(buf);
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

bool BandCharacter::AddDircut(const FilePath& f){
    MILO_ASSERT(!f.empty(), 0x794);
    // more
}

void BandCharacter::SetDircuts(){
    int maxNum = mFileMerger->FindMergerIndex("directed_cut_0", true);
    MILO_ASSERT(maxNum < 32, 0x7AE);
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

void ReplaceSubdir(ObjectDir* d1, ObjectDir* d2){
    for(int i = 0; i < d1->mSubDirs.size(); i++){
        ObjDirPtr<ObjectDir> dPtr(d1->mSubDirs[i].Ptr());
        d1->RemoveSubDir(dPtr);
    }
    ObjDirPtr<ObjectDir> dPtr(d2);
    d1->AppendSubDir(dPtr);
}

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
        ObjectDir* viseme = BandHeadShaper::GetViseme(mGender, true);
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
    const DataNode& handled = HandleType(get_patch_tex);
    if(handled.Type() == kDataUnhandled || !handled.Obj<RndTex>()){
        if(!mPrefab.Null()){
            return Find<RndTex>(MakeString("prefab_art%02d.tex", patch.mTexture), false);
        }
        else if(TheLoadMgr.EditMode()) return Find<RndTex>("patchtest.tex", false);
        else return 0;
    }
    return handled.Obj<RndTex>();
}

RndMesh* BandCharacter::GetPatchMesh(Patch& patch){
    ObjectDir* dir = this;
    if(patch.mCategory & 0x2E00){
        dir = mInstDir;
    }
    return dir->Find<RndMesh>(patch.mMeshName.c_str(), false);
}

RndTex* BandCharacter::GetBandLogo(){
    if(TheLoadMgr.EditMode()){
        return TheRnd->GetNullTexture();
    }
    else {
        RndTex* ret;
        DataNode handled = HandleType(get_band_logo_msg);
        if(handled.Type() == kDataObject){
            ret = handled.Obj<RndTex>();
        }
        else ret = 0;
        return ret;
    }
}

void BandCharacter::Compress(RndTex* tex, bool b){
    tex->Compress(b);
}

void BandCharacter::TextureCompressed(int i){
    std::list<int>::iterator it;
    for(it = mCompressedTextureIDs.begin(); it != mCompressedTextureIDs.end() && *it != i; ++it);
    if(it == mCompressedTextureIDs.end()) MILO_WARN("%s Could not find compress texture id %d\n", PathName(this), i);
    else mCompressedTextureIDs.erase(it);
}

void BandCharacter::RecomposePatches(BandCharDesc* desc, int i){
    CopyCharDesc(desc);
    if(!mInCloset){
        unk224 |= 1;
        StartLoad(true, mInCloset, true);
    }
    else {
        for(ObjPtrList<OutfitConfig, ObjectDir>::iterator it = unk620.begin(); it != unk620.end(); ++it){
            (*it)->RecomposePatches(i);
        }
    }
}

void BandCharacter::SetInstrumentType(Symbol s){
    if(s != mInstrumentType){
        mInstrumentType = s;
        SetChanged(8);
    }
}

void BandCharacter::ClearGroup(){
    SetState("", mPlayFlags, 1, false, false);
    mGroupName[0] = 0;
    if(mDriver) mDriver->Clear();
    if(mAddDriver) mAddDriver->Clear();
}

void BandCharacter::MiloReload(){
    StartLoad(false, mInCloset, false);
}

void BandCharacter::SetLipSync(CharLipSync* sync){
    CharLipSyncDriver* driver = Find<CharLipSyncDriver>("song.lipdrv", false);
    if(driver){
        driver->mSongOwner = 0;
        driver->SetLipSync(sync);
    }
}

void BandCharacter::SetSongOwner(CharLipSyncDriver* driver){
    CharLipSyncDriver* drvr = Find<CharLipSyncDriver>("song.lipdrv", false);
    if(drvr){
        drvr->mSongOwner = driver;
        drvr->SetLipSync(Find<CharLipSync>("blinktrack.lipsync", false));
        drvr->mSongOffset = RandomFloat(0, 1000.0f);
    }
}

void BandCharacter::SetSingalong(float f){
    if(mSingalongWeight) mSingalongWeight->SetWeight(f);
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
#ifdef MILO_DEBUG
    HANDLE(toggle_interests_overlay, OnToggleInterestDebugOverlay)
#endif
    HANDLE(list_drum_venues, OnListDrumVenues)
    HANDLE(portrait_begin, OnPortraitBegin)
    HANDLE(portrait_end, OnPortraitEnd)
    HANDLE_SUPERCLASS(BandCharDesc)
    HANDLE_SUPERCLASS(Character)
    HANDLE_CHECK(0x9A6)
END_HANDLERS
#pragma pop

void BandCharacter::GameOver(){
    for(ObjPtrList<CharIKMidi, ObjectDir>::iterator it = unk650.begin(); it != unk650.end(); ++it){
        CharIKMidi* cur = *it;
        cur->Handle(Message("game_over"), true);
    }
    for(ObjPtrList<CharDriverMidi, ObjectDir>::iterator it = unk660.begin(); it != unk660.end(); ++it){
        CharDriverMidi* cur = *it;
        cur->Handle(Message("game_over"), true);
    }
    for(ObjPtrList<CharKeyHandMidi, ObjectDir>::iterator it = unk670.begin(); it != unk670.end(); ++it){
        CharKeyHandMidi* cur = *it;
        cur->Handle(Message("game_over"), true);
    }
}

DataNode BandCharacter::OnListDircuts(){
    int mask = 0x3E00;
    if(mGender == "female"){
        if(mGenre == "banger") mask |= 0x4;
        else if(mGenre == "dramatic") mask |= 0x2;
        else if(mGenre == "rocker") mask |= 0x1;
        else if(mGenre == "spazz") mask |= 8;
    }
    else {
        if(mGenre == "banger") mask |= 0x40;
        else if(mGenre == "dramatic") mask |= 0x20;
        else if(mGenre == "rocker") mask |= 0x10;
        else if(mGenre == "spazz") mask |= 0x80;
    }
    return ListAnimGroups(mask);
}

DataNode BandCharacter::OnLoadDircut(DataArray* da){
    Symbol sym = da->Sym(2);
    if(sym == ""){
        return DataNode(0);
    }
    else {
        ClearDircuts();
        return DataNode(AddDircut(sym, mGenre, GetShotFlags(sym)));
    }
}

DataNode BandCharacter::OnPlayGroup(DataArray* da){
    bool b6 = false;
    if(da->Size() > 3) b6 = da->Int(3);
    bool b1 = false;
    if(da->Size() > 4) b1 = da->Int(4);
    float f7 = 0;
    int i5 = 0;
    Symbol s;
    if(da->Size() > 5){
        f7 = da->Float(5);
        i5 = da->Int(6);
        s = da->Sym(7);
    }
    int i3 = 2;
    if(b1) i3 = 1;
    PlayGroup(da->Str(2), b6, i3, f7, (TaskUnits)i5, s);
    return DataNode(0);
}

DataNode BandCharacter::OnGroupOverride(DataArray* da){
    strcpy(mOverrideGroup, da->Str(2));
    mForceNextGroup = true;
    return DataNode(0);
}

DataNode BandCharacter::OnSetPlay(DataArray* da){
    SetState(mGroupName, mPlayFlags & 0xFFF80FFF | da->Int(2), 3, false, false);
    return DataNode(0);
}

DataNode BandCharacter::OnClosetTeleport(DataArray* da){
    unk734->DirtyLocalXfm() = LocalXfm();
    Teleport(unk734);
    unk5a2 = false;
    return DataNode(0);
}

DataNode BandCharacter::OnCamTeleport(DataArray* da){
    if(da->Int(2)){
        Teleport(unk594);
    }
    else {
        Waypoint* w = unk594;
        Teleport(0);
        unk594 = w;
        unk5a2 = false;
    }
    return DataNode(0);
}

DataNode BandCharacter::OnChangeFaceGroup(DataArray* da){
    if(!mFaceDriver || !mFaceDriver->ClipDir()) return DataNode(0);
    else if(strcmp(mFaceGroupName, da->Str(2)) != 0){
        strcpy(mFaceGroupName, da->Str(2));
        PlayFaceClip();
    }
    return DataNode(0);
}

void ReplaceRefs(Hmx::Object*, Hmx::Object* mine){
    MILO_ASSERT(mine, 0xA72);
}

MergeFilter::Action BandCharacter::FilterSubdir(ObjectDir* o1, ObjectDir*){
    return DefaultSubdirAction(o1, mFileMerger->mSubdirs);
}

DataNode BandCharacter::OnInstallFilter(DataArray* da){
    sBoneMergeDir = 0;
    sOutfitDir = da->Obj<ObjectDir>(2);
    sToDir = da->Obj<ObjectDir>(3);
    sInstrumentDir = da->Obj<ObjectDir>(4);
    const char* bodyparts[] = {
        "hair", "glasses", "facehair", "earrings", "piercings", "eyebrows", "wrist", "torso", "head", "legs", "feet", "rings", "hands"
    };
    return DataNode(0);
}

DataNode BandCharacter::OnPreClear(DataArray* da){
    Symbol sym = da->Sym(2);
    FileMerger* fm = da->Obj<FileMerger>(3);
    static Symbol ocn("OutfitConfig");
    return DataNode(0);
}

void BandCharacter::SavePrefabFromCloset(){
    MILO_ASSERT(0, 0xB95);
}

DataNode BandCharacter::OnSavePrefab(DataArray* da){
    if(mTestPrefab) mTestPrefab->CopyCharDesc(this);
    return DataNode(0);
}

DataNode BandCharacter::OnCopyPrefab(DataArray* da){
    if(mTestPrefab) CopyCharDesc(mTestPrefab);
    return DataNode(0);
}

// just here temporarily until we match the corresponding funcs these strings belong to
DECOMP_FORCEACTIVE(BandCharacter, "Mesh", "%s is being merged into", "mine->Dir() == this", "bone_", "exo_", "world.wind",
    "instruments can only have one subdir, which is the resource or colorpalettes.milo", "bone_pelvis.mesh",
    "outfits can only have one subdir, which is the resource")

DataNode BandCharacter::OnSetFileMerger(DataArray* da){
    FilePathTracker tracker(FileRoot());
    SetVisemes();
    unk224 &= 0xfffffff2;
    if(!mFileMerger) return DataNode(0);
    FilePath fp70;
    if(!mPrefab.Null()) fp70.SetRoot(MakeString("char/main/prefab/%s.milo", mPrefab));
    mFileMerger->Select("prefab", fp70, unk5a1);
    const char* bodyparts[14] = {
        "head", "eyebrows", "torso", "legs", "hands", "wrist", "rings", "feet", "hair", "facehair", "earrings", "glasses", "piercings", 0
    };
    for(int i = 0; bodyparts[i] != 0; i++){
        FilePath fp7c;
        MakeOutfitPath(bodyparts[i], fp7c);
        mFileMerger->Select(bodyparts[i], fp7c, unk5a1);
    }
    for(int i = 0; i < 5; i++){
        mFileMerger->Select(BandCharDesc::GetInstrumentSym(i), FilePath(0), false);
    }
    FilePath fp88("");
    FilePath fp94("");
    FilePath fpa0("");
    FilePath fpac("");
    FilePath fpb8("");
    FilePath fpc4("");
    FilePath fpd0("");
    FilePath fpdc("");
    FilePath fpe8("");
    FilePath fpf4("");
    mPlayFlags &= 0xffcfffff;
    Symbol animinst = BandCharDesc::GetAnimInstrument(mInstrumentType);
    BandCharDesc::CharInstrumentType ty = BandCharDesc::GetInstrumentFromSym(mInstrumentType);
    if(ty == BandCharDesc::kGuitar) mPlayFlags |= 0x100000;
    else if(ty == BandCharDesc::kBass) mPlayFlags |= 0x200000;
    if(ty != BandCharDesc::kNumInstruments){
        if(!mGenre.Null() && !mTempo.Null()){
            if(ty == BandCharacter::kMic){
                mUseMicStandClips = mGenre != "banger";
            }
            fp94.SetRoot(MakeString("char/main/anim/%s/body/%s/realtime_%s.milo", animinst, mGender, mGenre));
            fpa0.SetRoot(MakeString("char/main/anim/%s/body/%s/%s_%s.milo", animinst, mGender, mTempo, mGenre));
            if(ty == BandCharDesc::kDrum){
                fpac.SetRoot(MakeString("char/main/anim/%s/body_add/%s/%s_%s.milo", animinst, mGender, mTempo, mGenre));
                fpb8.SetRoot(MakeString("char/main/anim/%s/body_add/%s/body_add_base.milo", animinst, mGender));
            }
        }
        switch(ty){
            case BandCharDesc::kGuitar:
            case BandCharDesc::kBass:
                fp88.SetRoot("char/main/rigging/guitar_rh.milo");
                if(mGender == "female") fpf4.SetRoot("char/main/anim/rigging/guitar/fret_left_female.milo");
                else fpf4.SetRoot("char/main/anim/rigging/guitar/fret_left.milo");
                break;
            case BandCharDesc::kDrum:
                fp88.SetRoot("char/main/rigging/drum.milo");
                fpc4.SetRoot(MakeString("char/main/anim/rigging/drum/stick_left_%s.milo", mGender));
                fpd0.SetRoot(MakeString("char/main/anim/rigging/drum/stick_right_%s.milo", mGender));
                if(mGender == "female"){
                    fpdc.SetRoot("char/main/anim/rigging/drum/pedal_right_female.milo");
                    fpe8.SetRoot("char/main/anim/rigging/drum/pedal_left_female.milo");
                }
                else {
                    fpdc.SetRoot("char/main/anim/rigging/drum/pedal_right.milo");
                    fpe8.SetRoot("char/main/anim/rigging/drum/pedal_left.milo");
                }
                break;
            case BandCharDesc::kMic:
                fp88.SetRoot("char/main/rigging/vocal.milo");
                break;
            case BandCharDesc::kKeyboard:
                fp88.SetRoot("char/main/rigging/keyboard.milo");
                break;
            default:
                MILO_FAIL("new instrument type added but not supported");
                break;
        }
        if(ty != BandCharDesc::kDrum || !mDrumVenue.Null()){
            FilePath fp100("");
            MakeInstrumentPath(mInstrumentType, mDrumVenue, fp100);
            mFileMerger->Select(mInstrumentType, fp100, unk5a1);
        }
    }
    if(mInTourEnding && !mTestTourEndingVenue.Null()){
        FilePath fp10c(MakeString("char/main/anim/%s/finale/%s/%s/tour_endings.milo", animinst, mGender, mTestTourEndingVenue));
        mFileMerger->Select("tour_ending_clips", fp10c, false);
    }
    else {
        if(TheLoadMgr.EditMode() && !mTestTourEndingVenue.Null()){
            FilePath fp118(MakeString("char/main/anim/%s/finale/%s/%s/tour_endings.milo", animinst, mGender, mTestTourEndingVenue));
            mFileMerger->Select("tour_ending_clips", fp118, false);
        }
        else {
            mFileMerger->Select("tour_ending_clips", FilePath(""), false);
        }
    }
    mFileMerger->Select("rigging", fp88, false);
    mFileMerger->Select("body_realtime_clips", fp94, false);
    mFileMerger->Select("body_tempo_clips", fpa0, false);
    mFileMerger->Select("body_add_clips", fpac, false);
    mFileMerger->Select("body_add_base", fpb8, false);
    mFileMerger->Select("stick_left", fpc4, false);
    mFileMerger->Select("stick_right", fpd0, false);
    mFileMerger->Select("drum_pedal_right", fpdc, false);
    mFileMerger->Select("drum_pedal_left", fpe8, false);
    mFileMerger->Select("guitar_fret", fpf4, false);
    SetDircuts();
    unk5a1 = false;
    return DataNode(0);
}

BEGIN_PROPSYNCS(BandCharacter)
    SYNC_PROP(tempo, mTempo)
    SYNC_PROP(genre, mGenre)
    SYNC_PROP(drum_venue, mDrumVenue)
    SYNC_PROP(force_vertical, mForceVertical)
    SYNC_PROP_SET(instrument_type, mInstrumentType, SetInstrumentType(_val.Sym()))
    SYNC_PROP_SET(group_name, mGroupName, SetGroupName(_val.Str()))
    SYNC_PROP_SET(head_lookat_weight, mHeadLookAt ? mHeadLookAt->Weight() : 0, SetHeadLookatWeight(_val.Float()))
    SYNC_PROP_SET(in_closet, mInCloset, StartLoad(false, _val.Int(), false))
    SYNC_PROP(test_prefab, mTestPrefab)
    SYNC_PROP(use_mic_stand_clips, mUseMicStandClips)
    SYNC_PROP(in_tour_ending, mInTourEnding)
    SYNC_PROP(test_tour_ending_venue, mTestTourEndingVenue)
    SYNC_SUPERCLASS(BandCharDesc)
    SYNC_SUPERCLASS(Character)
END_PROPSYNCS
