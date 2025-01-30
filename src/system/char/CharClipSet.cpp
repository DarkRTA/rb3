#include "char/CharClipSet.h"
#include "char/CharBoneDir.h"
#include "char/CharBonesMeshes.h"
#include "char/CharClip.h"
#include "char/CharClipGroup.h"
#include "char/CharForeTwist.h"
#include "char/CharNeckTwist.h"
#include "char/CharPollable.h"
#include "char/CharUpperTwist.h"
#include "char/CharUtl.h"
#include "char/Character.h"
#include "math/Rand.h"
#include "math/Rot.h"
#include "math/Vec.h"
#include "obj/Data.h"
#include "obj/DataUtl.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/ObjVersion.h"
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "rndobj/Trans.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

INIT_REVS(CharClipSet)
const char* kHighThresholdGroups[] = { "close" };
const char* kLowThresholdGroups[] = {
    "fail", "revive", "ending", "lose", "win"
};

CharClipSet::CharClipSet() : mCharFilePath(), mPreviewChar(this), mPreviewClip(this), mStillClip(this) {
    ResetPreviewState();
    SetRate(k1_fpb);
}

void CharClipSet::ResetPreviewState(){
    delete mPreviewChar;
    mPreviewClip = 0;
    mStillClip = 0;
    mCharFilePath.SetRoot("");
    mFilterFlags = 0;
    mBpm = 90;
    mPreviewWalk = false;
}

CharClipSet::~CharClipSet(){
    
}

void CharClipSet::ResetEditorState(){
    ResetPreviewState();
    ObjectDir::ResetEditorState();
}

void CharClipSet::RandomizeGroups(){
    for(ObjDirItr<CharClipGroup> it(this, false); it != 0; ++it){
        it->Randomize();
    }
}

void CharClipSet::SortGroups(){
    for(ObjDirItr<CharClipGroup> it(this, false); it != 0; ++it){
        it->Sort();
    }
}

void CharClipSet::PreSave(BinStream& bs){
    if(mPreviewChar) mPreviewChar->SetName("", 0);
    if(bs.Cached()){
        ResetPreviewState();
        ResetEditorState();
    }
}

void CharClipSet::PostSave(BinStream& bs){
    ObjectDir::PostSave(bs);
    if(mPreviewChar){
        mPreviewChar->SetName("preview_character", this);
        mPreviewChar->Enter();
        Hmx::Object* obj = ObjectDir::Main()->FindObject("milo", false);
        if(obj) obj->Handle(Message("update_objects"), true);
    }
}

void CharClipSet::RecenterAll(){
    MILO_WARN("You can only recenter clips from PC");
}

void CharClipSet::Load(BinStream& bs){ ObjectDir::Load(bs); }
SAVE_OBJ(CharClipSet, 0x8E)

void CharClipSet::PreLoad(BinStream& bs){
    LOAD_REVS(bs)
    ASSERT_REVS(0x18, 0)
    MILO_ASSERT(gRev > 3, 0xA2);
    PushRev(packRevs(gAltRev, gRev), this);
    ObjectDir::PreLoad(bs);
}

void CharClipSet::PostLoad(BinStream& bs){
    ObjectDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(IsProxy()) return;
    if(gRev < 0x11){
        int x, y;
        bs >> x;
        bs >> y;
    }
    if(gRev == 0xF || gRev == 0x10){
        int x; bs >> x;
    }
    if(gRev < 9){
        FilePath fp;
        bs >> fp;
        if(!fp.empty()) MILO_WARN("Set the type and resave %s, graph_path was \"%s\"", PathName(this), fp.c_str());
    }
    if(gRev < 6){
        String str; bs >> str;
        MILO_WARN("You'll need to reexport some clips into this clipset");
    }
    if(gRev < 7){
        int x; bs >> x;
    }
    if(gRev < 0x18){
        int count = 0;
        for(ObjDirItr<CharClip> it(this, true); it != 0; ++it){
            count++;
        }
        for(int i = 0; i < count; i++){
            ObjPtr<CharClip> clipPtr(this);
            bs >> clipPtr;
            int x, y;
            bs >> x;
            bs >> y;
        }
    }
    if(gRev > 0xD){
        if(gRev < 0x18){
            bool b1, b2;
            bs >> b1;
            if(gRev > 0x12) bs >> b2;
        }
    }
    else {
        int count; bs >> count;
        for(int i = 0; i < count; i++){
            Symbol s; bs >> s;
        }
    }
    if(gRev >= 5 && gRev <= 0x17){
        int count; bs >> count;
        char buf[0x100];
        for(int i = 0; i < count; i++){
            bs.ReadString(buf, 0x100);
        }
        bs >> count;
        for(int i = 0; i < count; i++){
            bs.ReadString(buf, 0x100);
        }
        bool b; bs >> b;
    }
    if(gRev >= 10 && gRev <= 23){
        Symbol s;
        bs >> s;
        int x; bs >> x;
    }
    if(gRev == 0xB){
        bool b; bs >> b;
    }
#ifdef MILO_DEBUG
    bool bugged = false;
    if(gRev < 0xC){
        if(!Type().Null()) bugged = true;
    }
    if(bugged) MILO_WARN("%s may have a bug in the transition graph, need to resave from milo", PathName(this));
#else
    if(gRev < 0xC && !Type().Null()){
        MILO_WARN("%s may have a bug in the transition graph, need to resave from milo", PathName(this));
    }
#endif
    if(gRev < 0xD) Handle(filter_clips_msg, false);
    if(gRev > 0x11){
        bs >> mCharFilePath;
        bs >> mPreviewClip;
    }
    if(gRev > 0x13) bs >> mFilterFlags;
    if(gRev > 0x14) bs >> mBpm;
    if(gRev > 0x15) bs >> mPreviewWalk;
    if(gRev > 0x16) bs >> mStillClip;
}

BEGIN_COPYS(CharClipSet)
    COPY_SUPERCLASS(ObjectDir)
    CREATE_COPY(CharClipSet)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mCharFilePath)
        COPY_MEMBER(mPreviewClip)
        COPY_MEMBER(mFilterFlags)
        COPY_MEMBER(mBpm)
        COPY_MEMBER(mPreviewWalk)
        COPY_MEMBER(mStillClip)
    END_COPYING_MEMBERS
END_COPYS

void CharClipSet::LoadCharacter(){
#ifdef MILO_DEBUG
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x156);
#endif
    delete mPreviewChar;
    ObjectDir* loadedobj = DirLoader::LoadObjects(mCharFilePath, 0, 0);
    ObjectDir* dummy = dynamic_cast<RndDir*>(loadedobj);
    mPreviewChar = dynamic_cast<RndDir*>(dummy);
    Character* theChar = dynamic_cast<Character*>(dummy);
    if(mPreviewChar && !theChar){
        for(ObjDirItr<Character> it(mPreviewChar, true); it != nullptr; ++it){
            mPreviewChar = it;
            break;
        }
    }
    if(mPreviewChar){
        mPreviewChar->Enter();
        mPreviewChar->SetName("preview_character", this);
        Hmx::Object* foundobj = ObjectDir::sMainDir->FindObject("milo", false);
        if(foundobj) foundobj->Handle(Message("update_objects"), true);
    }
}

DataNode CharClipSet::OnListClips(DataArray*){
    std::list<CharClip*> clips;
    for(ObjDirItr<CharClip> it(this, true); it != nullptr; ++it){
        int myFilterFlags = mFilterFlags;
        if(myFilterFlags == (myFilterFlags & it->Flags())){
            clips.push_back(it);
        }
    }
    clips.sort(AlphaSort());
    DataArray* arr = new DataArray(clips.size() + 1);
    arr->Node(0) = NULL_OBJ;
    int idx = 1;
    for(std::list<CharClip*>::iterator it = clips.begin(); it != clips.end(); ++it){
        arr->Node(idx++) = *it;
    }
    DataNode ret(arr, kDataArray);
    arr->Release();
    return ret;
}

void CharClipSet::DrawShowing(){
    if(mPreviewChar) mPreviewChar->DrawShowing();
}

float CharClipSet::StartFrame(){
    if(mPreviewClip) return mPreviewClip->StartBeat();
    else return 0;
}

float CharClipSet::EndFrame(){
    if(mPreviewClip) return mPreviewClip->EndBeat();
    else return 0;
}

// matches in retail
void CharClipSet::SetFrame(float frame, float blend){
    if(mPreviewClip && mPreviewChar){
        RndAnimatable::SetFrame(frame, 1);
        CharBonesMeshes mesh1;
        CharBonesMeshes mesh2;
        mesh1.SetName("preview_anim", mPreviewChar);
        mPreviewClip->StuffBones(mesh1);
        mesh2.SetName("preview", this);
        mPreviewClip->StuffBones(mesh2);
        mesh2.Zero();
        mesh1.Zero();
        CharClip* relative = mPreviewClip->Relative();
        if(relative){
            CharClip* theClip = mStillClip ? mStillClip : mPreviewClip;
            theClip->ScaleAdd(mesh1, 1, frame, 0);
            mPreviewClip->RotateTo(mesh1, 1, frame);
            theClip->ScaleAdd(mesh2, 1, frame, 0);
            mPreviewClip->RotateTo(mesh2, 1, frame);
        }
        else {
            mPreviewClip->ScaleAdd(mesh1, 1, frame, 0);
            mPreviewClip->ScaleAdd(mesh2, 1, frame, 0);
        }
        mesh1.PoseMeshes();
        mesh2.PoseMeshes();
        if(mPreviewWalk){
            RndTransformable* pelvisTrans = CharUtlFindBoneTrans("bone_pelvis", mesh1.Dir());
            float* rotZPtr = (float*)mesh1.FindPtr("bone_facing.rotz");
            Vector3* posPtr = (Vector3*)mesh1.FindPtr("bone_facing.pos");
            if(pelvisTrans && posPtr && rotZPtr){
                Transform& pelvisXfm = pelvisTrans->DirtyLocalXfm();
                if(rotZPtr){
                    RotateAboutZ(pelvisXfm.m, *rotZPtr, pelvisXfm.m);
                    RotateAboutZ(pelvisXfm.v, *rotZPtr, pelvisXfm.v);
                    Normalize(pelvisXfm.m, pelvisXfm.m);
                }
                pelvisXfm.v += *posPtr;
            }
            for(ObjDirItr<CharBone> it(mPreviewClip->GetResource(), false); it != nullptr; ++it){
                if(it->BakeOutAsTopLevel()){
                    String str(it->Name());
                    if(str.find(".cb") != String::npos){
                        str = str.substr(0, str.length() - 3);
                    }
                    RndTransformable* t = CharUtlFindBoneTrans(str.c_str(), mesh1.Dir());
                    if(t && posPtr && rotZPtr){
                        Transform& xfm = t->DirtyLocalXfm();
                        if(rotZPtr){
                            RotateAboutZ(xfm.m, *rotZPtr, xfm.m);
                            RotateAboutZ(xfm.v, *rotZPtr, xfm.v);
                            Normalize(xfm.m, xfm.m);
                        }
                        xfm.v += *posPtr;
                    }                    
                }
            }
        }

        for(ObjDirItr<CharPollable> it(mPreviewChar, true); it != nullptr; ++it){
            if(dynamic_cast<CharForeTwist*>(&*it) || dynamic_cast<CharUpperTwist*>(&*it) || dynamic_cast<CharNeckTwist*>(&*it)){
                it->Poll();
            }
        }
    }
}

void CharClipSet::SetBpm(int bpm){
    static Symbol sBpm("bpm");
    Hmx::Object* obj = ObjectDir::Main()->FindObject("milo", false);
    if(obj) obj->SetProperty(sBpm, bpm);
    mBpm = bpm;
}

int GroupDeleteThreshold(const char* cc){
    for(int i = 0; i < 1; i++) {
        if(strstr(cc, kHighThresholdGroups[i]) != nullptr) {
            return 2;
        }
    }    
    for(int i = 0; i < 5; i++) {
        if(strstr(cc, kLowThresholdGroups[i]) != nullptr) {
            return 1;
        }
    }    
    return 2;
}

void StuffGroups(CharClip* clip, ObjectDir* dir, std::vector<CharClipGroup*>& groups){
    FOREACH_OBJREF(it, clip){
        CharClipGroup* grp = dynamic_cast<CharClipGroup*>((*it)->RefOwner());
        if(grp && grp->Dir() == dir){
            groups.push_back(grp);
        }
    }
}

void CharClipSet::SyncObjects(){
#ifdef MILO_DEBUG
    if(!DataGetMacro("HX_SYSTEST")){
#endif
        std::vector<CharClip*> clips;
        for(ObjDirItr<CharClip> it(this, false); it != nullptr; ++it){
            if(it->Flags()){
                clips.push_back(it);
            }
        }
        if(clips.size() != 0){
            std::vector<CharClipGroup*> groups;
            groups.reserve(100);
#ifdef MILO_DEBUG
            if(!DataGetMacro("OVERRIDE_RANDOM_ANIM_DELETION")){
#endif
                for(int i = 0; i < clips.size(); i++){
                    std::swap(clips[i], clips[RandomInt(i, clips.size())]);
                }
#ifdef MILO_DEBUG
            }
#endif
            for(int i = 0; i < clips.size(); i++){
                CharClip* curClip = clips[i];
                groups.clear();
                StuffGroups(curClip, this, groups);
                bool b1 = true;
                if(groups.size() != 0){
                    curClip->Flags();
                    for(int j = 0; j < groups.size(); j++){
                        int thresh = GroupDeleteThreshold(groups[j]->Name());
                        if(groups[j]->NumFlagDuplicates(curClip, 0x7F060) < thresh){
                            b1 = false;
                            break;
                        }
                    }
                    if(b1){
                        for(int j = 0; j < groups.size(); j++){
                            groups[j]->RemoveClip(curClip);
                        }
                        delete curClip;
                    }
                }
            }
        }
#ifdef MILO_DEBUG
    }
#endif
    ObjectDir::SyncObjects();
}

BEGIN_HANDLERS(CharClipSet)
    HANDLE_ACTION(randomize_groups, RandomizeGroups())
    HANDLE_ACTION(sort_groups, SortGroups())
    HANDLE_ACTION(recenter_all, RecenterAll())
    HANDLE_ACTION(load_character, LoadCharacter())
    HANDLE(list_clips, OnListClips)
    HANDLE_SUPERCLASS(ObjectDir)
    HANDLE_CHECK(0x2F0)
END_HANDLERS

BEGIN_PROPSYNCS(CharClipSet)
    SYNC_PROP(char_file_path, mCharFilePath)
    SYNC_PROP(preview_clip, mPreviewClip)
    SYNC_PROP(still_clip, mStillClip)
    SYNC_PROP(filter_flags, mFilterFlags)
    SYNC_PROP_SET(bpm, mBpm, SetBpm(_val.Int()))
    SYNC_PROP(preview_walk, mPreviewWalk)
    SYNC_SUPERCLASS(ObjectDir)
END_PROPSYNCS