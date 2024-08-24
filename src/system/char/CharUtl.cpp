#include "char/CharUtl.h"
#include "char/Character.h"
#include "char/CharClip.h"
#include "obj/DirLoader.h"
#include "obj/DataFunc.h"
#include "rndobj/Mesh.h"
#include "rndobj/Cam.h"
#include "rndobj/Dir.h"
#include "char/CharCollide.h"
#include "char/CharCuff.h"
#include "char/CharBone.h"
#include "char/CharBones.h"
#include "char/CharHair.h"

static DataNode OnResetHair(DataArray* da){
    CharUtlResetHair(da->Obj<Character>(1));
    return DataNode(0);
}

static DataNode OnCharMergeBones(DataArray* da){
    FilePath fp(da->Str(1));
    ObjectDir* dir = DirLoader::LoadObjects(fp, 0, 0);
    ObjectDir* dir2 = da->Obj<ObjectDir>(2);
    CharUtlMergeBones(dir, dir2, da->Int(3));
    delete dir;
    return DataNode(0);
}

bool CharUtlIsAnimatable(RndTransformable* trans){
    RndMesh* mesh = dynamic_cast<RndMesh*>(trans);
    if(mesh && mesh->NumBones() != 0) return false;
    if(dynamic_cast<RndCam*>(trans)) return false;
    if(dynamic_cast<CharCollide*>(trans)) return false;
    if(dynamic_cast<CharCuff*>(trans)) return false;
    if(dynamic_cast<RndDir*>(trans)) return false;
    return strncmp(trans->Name(), "spot_", 5) != 0;
}

void CharUtlInit(){
    DataRegisterFunc("reset_hair", OnResetHair);
    DataRegisterFunc("char_merge_bones", OnCharMergeBones);
}

CharUtlBoneSaver::CharUtlBoneSaver(ObjectDir* dir) : mDir(dir) {
    for(ObjDirItr<RndTransformable> it(mDir, true); it != 0; ++it){
        if(strncmp("bone_", it->Name(), 5) == 0){
            mXfms.push_back(it->LocalXfm());
        }
    }
}

CharUtlBoneSaver::~CharUtlBoneSaver(){
    int idx = 0;
    for(ObjDirItr<RndTransformable> it(mDir, true); it != 0; ++it){
        if(strncmp("bone_", it->Name(), 5) == 0){
            it->SetLocalXfm(mXfms[idx++]);
        }
    }
}

CharBone* GrabBone(CharBone* bone, ObjectDir* dir){
    CharBone* found = CharUtlFindBone(bone->Name(), dir);
    if(!found) MILO_WARN("Could not find %s must hand merge", bone->Name());
    return found;
}

// fn_804FB9C4
void CharUtlMergeBones(ObjectDir* dir1, ObjectDir* dir2, int i){
    for(ObjDirItr<CharBone> it(dir1, true); it != 0; ++it){
        if(it->Target()){
            CharBone* bone = GrabBone(it, dir2);
            if(bone){
                if(!bone->Target()){
                    const char* name = it->Target()->Name();
                    CharBone* findbone = CharUtlFindBone(name, dir2);
                    if(!findbone) MILO_WARN("could not find target %s in dest, must merge", name);
                    bone->SetTarget(findbone);
                }
                else {
                    if(!streq(it->Target()->Name(), bone->Target()->Name())){
                        MILO_WARN("%s has different targets %s v %s, must resolve", it->Name(), it->Target()->Name(), bone->Target()->Name());
                    }
                }
            }
        }
        if(it->PositionContext() != 0){
            CharBone* bone = GrabBone(it, dir2);
            if(bone) bone->SetPositionContext(bone->PositionContext() | i);
        }
        if(it->ScaleContext() != 0){
            CharBone* bone = GrabBone(it, dir2);
            if(bone) bone->SetPositionContext(bone->ScaleContext() | i);
        }
        if(it->RotationContext() != 0 && it->RotationType() != CharBones::TYPE_END){
            CharBone* bone = GrabBone(it, dir2);
            if(bone){
                if(bone->RotationType() != CharBones::TYPE_END && bone->RotationType() != it->RotationType()){
                    MILO_WARN("bones %s have different rotations, must hand resolve", it->Name());
                }                    
                else {
                    bone->SetRotationType(it->RotationType());
                    bone->SetRotationContext(bone->RotationContext() | i);
                }
            }
        }
    }
}

void CharUtlResetTransform(ObjectDir* dir){
    for(ObjDirItr<RndTransformable> it(dir, true); it != 0; ++it){
        if(!it->TransParent()){
            it->ResetLocalXfm();
        }
    }
}

ClipPredict::ClipPredict(CharClip* clip, const Vector3& pos, float ang) : mClip(0) {
    SetClip(clip);
    mPos = pos;
    mAng = ang;
    MILO_ASSERT(mAngChannel, 0x239);
}

void ClipPredict::SetClip(CharClip* clip){
    if(clip != mClip){
        mClip = clip;
        mAngChannel = clip->GetChannel("bone_facing.rotz");
        mPosChannel = clip->GetChannel("bone_facing.pos");
        MILO_ASSERT(mAngChannel, 0x245);
    }
}

DECOMP_FORCEACTIVE(CharUtl, "tmp_bones")

CharBone* CharUtlFindBone(const char* cc, ObjectDir* dir){
    if(!dir) return 0;
    else {
        char buf[256];
        strcpy(buf, cc);
        char* dst = strrchr(buf, 0x2E);
        if(!dst) dst = buf + strlen(buf);
        strcpy(dst, ".cb");
        return dir->Find<CharBone>(buf, false);
    }
}

RndTransformable* CharUtlFindBoneTrans(const char* cc, ObjectDir* dir){
    if(!dir) return 0;
    else {
        char buf[256];
        strcpy(buf, cc);
        char* dst = strrchr(buf, 0x2E);
        if(!dst) dst = buf + strlen(buf);
        strcpy(dst, ".cb");
        CharBone* bone = dir->Find<CharBone>(buf, false);
        if(bone) return bone->mTrans;
        else {
            strcpy(dst, ".trans");
            RndTransformable* trans = dir->Find<RndTransformable>(buf, false);
            if(trans) return trans;
            else {
                strcpy(dst, ".mesh");
                RndTransformable* mesh = dir->Find<RndTransformable>(buf, false);
                return mesh;
            }
        }
    }
}

DECOMP_FORCEACTIVE(CharUtl, "vector")

void CharUtlResetHair(Character* c){
    for(ObjDirItr<CharHair> it(c, true); it != 0; ++it){
        it->Enter();
    }
}