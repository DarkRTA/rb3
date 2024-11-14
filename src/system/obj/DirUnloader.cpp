#include "obj/DirUnloader.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Rnd.h"
#include "rndwii/Rnd.h"
#include "utl/Loader.h"

DirUnloader::DirUnloader(ObjectDir* dir) : Loader(FilePath(dir->GetPathName()), kLoadFront), mObjects() {
    mObjects.reserve(dir->mHashTable.Size() / 2);
    for(ObjDirItr<Hmx::Object> it(dir, false); it != 0; ++it){
        Hmx::Object* cur = it;
        if(cur != dir){
            cur->SetName(0, 0);
            mObjects.push_back(ObjPtr<Hmx::Object, ObjectDir>(this, cur));
        }
    }
}

DirUnloader::~DirUnloader(){
    MILO_ASSERT(mObjects.empty(), 0x20);
}

bool DirUnloader::IsLoaded() const { return false; }

void DirUnloader::PollLoading(){
    gSuppressPointTest++;
    TheLoadMgr.StartAsyncUnload();
    while(true){

    }
    TheLoadMgr.FinishAsyncUnload();
    MILO_ASSERT(gSuppressPointTest>0, 0x47);
    gSuppressPointTest--;

//       gSuppressPointTest = gSuppressPointTest + 1;
//   LoadMgr::StartAsyncUnload(TheLoadMgr);
//   while( true ) {
//     iVar2 = fn_8031A7A0(TheLoadMgr);
//     if ((iVar2 != 0) || (piVar3 = fn_8031A6E8(TheLoadMgr), piVar3 != param_1)) goto LAB_803317c0;
//     iVar2 = stlpmtx_std::vector<><>::empty(param_1 + 0xd);
//     if (iVar2 != 0) break;
//     pvVar1 = fn_80331864(param_1 + 0xd);
//     piVar3 = MergedGet0x8(pvVar1);
//     if ((piVar3 != 0x0) && (piVar3 != 0x0)) {
//       (**(*piVar3 + 8))(piVar3,1);
//     }
//     fn_803317F8(param_1 + 0xd);
//   }
//   if (param_1 != 0x0) {
//     (**(*param_1 + 8))(param_1,1);
//   }
// LAB_803317c0:
//   LoadMgr::FinishAsyncUnload(TheLoadMgr);
//   gSuppressPointTest = gSuppressPointTest + -1;
//   return;
}

const char* DirUnloader::DebugText(){ return MakeString("UnLoader: %s", mFile.c_str()); }