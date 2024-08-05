#include "char/CharClipSet.h"
#include "char/CharClipGroup.h"
#include "char/Character.h"
#include "obj/Msg.h"
#include "obj/ObjVersion.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

INIT_REVS(CharClipSet)

CharClipSet::CharClipSet() : mCharFilePath(), mPreviewChar(this, 0), mPreviewClip(this, 0), mStillClip(this, 0) {
    ResetPreviewState();
    mRate = k1_fpb;
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
        bs.ReadInt();
        bs.ReadInt();
    }
    if(gRev == 0xF || gRev == 0x10) bs.ReadInt();
    if(gRev < 9){
        FilePath fp;
        bs >> fp;
        if(!fp.empty()) MILO_WARN("Set the type and resave %s, graph_path was \"%s\"", PathName(this), fp.c_str());
    }
    if(gRev < 6){
        String str; bs >> str;
        MILO_WARN("You'll need to reexport some clips into this clipset");
    }
    if(gRev < 7) bs.ReadInt();
    if(gRev < 0x18){
        int count = 0;
        for(ObjDirItr<CharClip> it(this, true); it != 0; ++it){
            count++;
        }
        for(int i = 0; i < count; i++){
            ObjPtr<CharClip, ObjectDir> clipPtr(this, 0);
            bs >> clipPtr;
            bs.ReadInt();
            bs.ReadInt();
        }
    }
    if(gRev > 0xD){
        if(gRev < 0x18){
            bs.ReadBool();
            if(gRev > 0x12) bs.ReadBool();
        }
    }
    else {
        int count; bs >> count;
        for(int i = 0; i < count; i++){
            Symbol s; bs >> s;
        }
    }
    if(gRev == 5 || gRev == 6 || gRev == 7 || gRev == 8 || gRev == 9 || gRev == 0xA || gRev == 0xB ||
        gRev == 0xC || gRev == 0xD || gRev == 0xE || gRev == 0xF || gRev == 0x10 || gRev == 0x11 ||
        gRev == 0x12 || gRev == 0x13 || gRev == 0x14 || gRev == 0x15 || gRev == 0x16 || gRev == 0x17){
        int count; bs >> count;
        char buf[0x100];
        for(int i = 0; i < count; i++){
            bs.ReadString(buf, 0x100);
        }
        bs >> count;
        for(int i = 0; i < count; i++){
            bs.ReadString(buf, 0x100);
        }
        bs.ReadBool();
    }
    if(gRev == 10 || gRev == 11 || gRev == 12 || gRev == 13 || gRev == 14 || gRev == 15 || gRev == 16 ||
        gRev == 17 || gRev == 18 || gRev == 19 || gRev == 20 || gRev == 21 || gRev == 22 || gRev == 23){
        Symbol s;
        bs >> s;
        bs.ReadInt();
    }
    if(gRev == 0xB) bs.ReadBool();
    bool bugged = false;
    if(gRev < 0xC){
        if(!Type().Null()) bugged = true;
    }
    if(bugged) MILO_WARN("%s may have a bug in the transition graph, need to resave from milo", PathName(this));
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
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x156);
    delete mPreviewChar;
    ObjectDir* loadedobj = DirLoader::LoadObjects(mCharFilePath, 0, 0);
    ObjectDir* dummy = dynamic_cast<RndDir*>(loadedobj);
    RndDir* newchar = dynamic_cast<RndDir*>(dummy);
    mPreviewChar = newchar;
    Character* theChar = dynamic_cast<Character*>(dummy);
    if(mPreviewChar && !theChar){
        ObjDirItr<Character> it(mPreviewChar, true);
        if(it) mPreviewChar = it;
    }
    if(mPreviewChar){
        mPreviewChar->Enter();
        mPreviewChar->SetName("preview_character", this);
        Hmx::Object* foundobj = ObjectDir::Main()->FindObject("milo", false);
        if(foundobj) foundobj->Handle(Message("update_objects"), true);
    }
}

void CharClipSet::DrawShowing(){
    if(!mPreviewChar) return;
    mPreviewChar->DrawShowing();
}

float CharClipSet::StartFrame(){
    if(mPreviewClip) return mPreviewClip->StartBeat();
    else return 0;
}

float CharClipSet::EndFrame(){
    if(mPreviewClip) return mPreviewClip->EndBeat();
    else return 0;
}

void CharClipSet::SetBpm(int bpm){
    static Symbol sBpm("bpm");
    Hmx::Object* obj = ObjectDir::Main()->FindObject("milo", false);
    if(obj) obj->SetProperty(sBpm, bpm);
    mBpm = bpm;
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