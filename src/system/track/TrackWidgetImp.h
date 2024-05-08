#ifndef TRACK_TRACKWIDGETIMP_H
#define TRACK_TRACKWIDGETIMP_H

#include "math/Mtx.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Font.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Text.h"
#include <list>
#include <vector>

class TrackWidgetImpBase {
    public:
    virtual ~TrackWidgetImpBase() = 0; // 0x8
    virtual bool Empty() = 0; // 0xC
    virtual int Size() = 0; // 0x10
    virtual float GetFirstInstanceY() = 0; // 0x14
    virtual float GetLastInstanceY() = 0; // 0x18
    virtual void Sort() = 0; // 0x1C
    virtual void Clear() = 0; // 0x20
    virtual void RemoveAt() = 0; // 0x24
    virtual void RemoveUntil() = 0; // 0x28
    virtual int AddInstance(Transform, float) {MILO_ASSERT(0, 38); return 0;} // 0x2C
    virtual int AddTextInstance(Transform, String, bool) {MILO_ASSERT(0, 40); return 0;} // 0x30
    virtual int AddMeshInstance(Transform, RndMesh*, float) {MILO_ASSERT(0, 42); return 0;} // 0x34
    virtual void DrawInstances(const ObjPtrList<RndMesh, ObjectDir>&, int) = 0; // 0x38
    virtual void SetDirty(bool) {} // 0x3C
    virtual void Poll() {} // 0x40
    virtual void Init() {} // 0x44
    virtual void SetScale(float) {} // 0x48
    virtual void CheckValid(const char*) const {} // 0x4C
    virtual int Instances() = 0; // 0x50
    virtual void RemoveInstances() = 0; // 0x54
    //virtual int PushInstance() = 0; // 0x58

    NEW_OVERLOAD
};

template <typename T>
class TrackWidgetImp : public TrackWidgetImpBase {
    public:
    virtual bool Empty();
    virtual int Size();
    virtual float GetFirstInstanceY();
    virtual float GetLastInstanceY();
    virtual void Sort();
    virtual void Clear();
    virtual void RemoveAt();
    virtual void RemoveUntil();
    virtual int AddInstance(Transform, float);
    virtual void DrawInstances(const ObjPtrList<RndMesh, ObjectDir>&, int);
    virtual int Instances();
    virtual void RemoveInstances();
    virtual int PushInstance(T&);
};

class TextInstance {
    public:
    TextInstance(Transform t, String s) : mXfm(t) {}
    Transform mXfm;
}; // ????

class CharWidgetImp : public TrackWidgetImp<TextInstance> {
    public:
    CharWidgetImp(RndFont*, RndText*, int, int, RndText::Alignment, Hmx::Color32, Hmx::Color32, bool);
    virtual int AddTextInstance(Transform, String, bool);
    virtual void SetDirty(bool);
    virtual int PushInstance(TextInstance&);

    bool mDirty; // 0x4
    bool unk_0x5; 
    int unk_0x8, unk_0xC;
    RndText* unk_0x10;
    std::list<TextInstance> unk_0x14;
    RndFont* unk_0x1C;
    std::vector<int, u16> unk_0x20;
};

class MultiMeshWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> { 
public:

    std::vector<RndMultiMesh*> mMeshes;

    MultiMeshWidgetImp(const ObjPtrList<RndMesh, ObjectDir>&, bool);
    virtual bool Empty();
    virtual int Size();
    virtual void Clear();
    virtual float GetLastInstanceY();
    virtual int AddInstance(Transform, float);
    virtual int PushInstance(RndMultiMesh::Instance&);
};

class ImmediateWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> {
public:

    std::list<RndMultiMesh::Instance> mInstances;
    bool unk_0xC;

    ImmediateWidgetImp(bool b) : unk_0xC(b) {} 
    virtual int AddInstance(Transform, float);
    virtual int Instances();
    virtual void DrawInstances(const ObjPtrList<RndMesh, ObjectDir>&, int);
    virtual int PushInstance(RndMultiMesh::Instance&);

    DELETE_OVERLOAD
};

#endif // TRACK_TRACKWIDGETIMP_H
