#include "TrackWidgetImp.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Utl.h"

void ImmediateWidgetImp::DrawInstances(const ObjPtrList<RndMesh, ObjectDir>& l, int i) {

}

MultiMeshWidgetImp::MultiMeshWidgetImp(const ObjPtrList<RndMesh, ObjectDir>& meshlist, bool b) : mMeshes(meshlist), unk10(b) {
    for(int i = 0; i < mMeshes.size(); i++){
        mMultiMeshes.push_back(Hmx::Object::New<RndMultiMesh>());
    }
}

MultiMeshWidgetImp::~MultiMeshWidgetImp() {
    for (int i = 0; i < mMultiMeshes.size(); i++) delete mMultiMeshes[i];
}

void MultiMeshWidgetImp::Init(){
    int idx = 0;
    for(ObjPtrList<RndMesh, ObjectDir>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it){
        RndMesh* cur = *it;
        mMultiMeshes[idx]->SetMesh(cur);
        idx++;
    }
}

std::list<RndMultiMesh::Instance>& MultiMeshWidgetImp::Instances(){
    MILO_FAIL("MultiMeshWidgetImp::Instances() called; not implemented");
    return mMultiMeshes.front()->mInstances;
}

void MultiMeshWidgetImp::PushInstance(RndMultiMesh::Instance& inst){
    for(int i = 0; i < mMultiMeshes.size(); i++){
        mMultiMeshes[i]->mInstances.push_back(inst);
    }
}

bool MultiMeshWidgetImp::Empty(){
    if(mMultiMeshes.empty()) return true;
    else return mMultiMeshes.front()->mInstances.empty();
}

int MultiMeshWidgetImp::Size(){
    if(mMultiMeshes.empty()) return 0;
    else return mMultiMeshes.front()->mInstances.size();
}

void MultiMeshWidgetImp::Clear(){
    for(int i = 0; i < mMultiMeshes.size(); i++){
        DoClear(mMultiMeshes[i]->mInstances);
    }
}

float MultiMeshWidgetImp::GetFirstInstanceY(){
    if(mMultiMeshes.empty()) return 0;
    else return DoGetFirstInstanceY(mMultiMeshes.front()->mInstances);
}

float MultiMeshWidgetImp::GetLastInstanceY(){
    if(mMultiMeshes.empty()) return 0;
    else return DoGetLastInstanceY(mMultiMeshes.front()->mInstances);
}

// CharWidgetImp::CharWidgetImp(RndFont* f, RndText* t, int i1, int i2, RndText::Alignment, Hmx::Color32, Hmx::Color32, bool) 
//     : mDirty(false), unk_0x5(true), unk_0x8(i1), unk_0xC(i2), unk_0x10(t), unk_0x1C(f) {}

// std::list<TextInstance>* CharWidgetImp::Instances() { return &mInstances; }

// void CharWidgetImp::SetScale(float f) {
//     SetLocalScale(unk_0x10, Vector3(f,1,f));
// }

// void CharWidgetImp::Clear() {
//     Instances()->clear();
//     SetDirty(true);
// }

// std::list<MeshInstance>* MatWidgetImp::Instances() { return &mInstances; }

// void CharWidgetImp::SetDirty(bool b) { mDirty = b; }

// int CharWidgetImp::AddTextInstance(Transform t, String s, bool b) {
//     int x = 0;
//     if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
//     TextInstance i(t, s);
//     PushInstance(i); 
//     if (x) Sort(); 
//     return x;
// }

// int MultiMeshWidgetImp::AddInstance(Transform t, float) {
//     int x = 0;
//     if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
//     RndMultiMesh::Instance i(t);
//     PushInstance(i); 
//     if (x) Sort(); 
//     return x;
// }


// std::list<RndMultiMesh::Instance>* ImmediateWidgetImp::Instances() { return &mInstances; } 

// int ImmediateWidgetImp::AddInstance(Transform t, float) {
//     int x = 0;
//     if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
//     RndMultiMesh::Instance i(t);
//     PushInstance(i); 
//     if (x) Sort(); 
//     return x;
// }
