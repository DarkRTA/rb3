#include "TrackWidgetImp.h"
#include "rndobj/MultiMesh.h"

void ImmediateWidgetImp::DrawInstances(const ObjPtrList<RndMesh, ObjectDir>& l, int i) {

}

MultiMeshWidgetImp::MultiMeshWidgetImp(const ObjPtrList<RndMesh, ObjectDir>&, bool) {

}

bool MultiMeshWidgetImp::Empty() {
    if (mMeshes.size() == 0) return true;
    return mMeshes[0]->mInstances.empty();
}

int MultiMeshWidgetImp::Size() {
    if (mMeshes.size() == 0) return 0;
    return mMeshes[0]->mInstances.size();
}

void MultiMeshWidgetImp::Clear() {
    for (int i = 0; i < mMeshes.size(); i++) {
        mMeshes[i]->mInstances.clear();
        SetDirty(true);
    }
}

CharWidgetImp::CharWidgetImp(RndFont* f, RndText* t, int i1, int i2, RndText::Alignment, Hmx::Color32, Hmx::Color32, bool) 
    : mDirty(false), unk_0x5(true), unk_0x8(i1), unk_0xC(i2), unk_0x10(t), unk_0x1C(f) {}

int CharWidgetImp::AddTextInstance(Transform t, String s, bool b) {
    int x = 0;
    if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
    TextInstance i(t, s);
    PushInstance(i); 
    if (x) Sort(); 
    return x;
}

int MultiMeshWidgetImp::AddInstance(Transform t, float) {
    int x = 0;
    if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
    RndMultiMesh::Instance i(t);
    PushInstance(i); 
    if (x) Sort(); 
    return x;
}


int ImmediateWidgetImp::Instances() { 
    return mInstances.size(); // this is wrong, but it's returning `addi r3,r3,4` which is. odd
} 

int ImmediateWidgetImp::AddInstance(Transform t, float) {
    int x = 0;
    if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
    RndMultiMesh::Instance i(t);
    PushInstance(i); 
    if (x) Sort(); 
    return x;
}
