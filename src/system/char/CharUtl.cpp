#include "char/CharUtl.h"
#include "char/Character.h"
#include "obj/DirLoader.h"
#include "obj/DataFunc.h"
#include "rndobj/Mesh.h"
#include "rndobj/Cam.h"
#include "rndobj/Dir.h"
#include "char/CharCollide.h"
#include "char/CharCuff.h"

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
    if(mesh && !mesh->mBones.empty()) return false;
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