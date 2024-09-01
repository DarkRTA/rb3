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
    TrackWidgetImpBase(){}
    virtual ~TrackWidgetImpBase(){} // 0x8
    virtual bool Empty() = 0; // 0xC
    virtual int Size() = 0; // 0x10
    virtual float GetFirstInstanceY() = 0; // 0x14
    virtual float GetLastInstanceY() = 0; // 0x18
    virtual void Sort() = 0; // 0x1C
    virtual void Clear() = 0; // 0x20
    virtual void RemoveAt(float, float, float) = 0; // 0x24
    virtual void RemoveUntil(float, float) = 0; // 0x28
    virtual int AddInstance(Transform, float) {MILO_ASSERT(0, 38); return 0;} // 0x2C
    virtual int AddTextInstance(Transform, String, bool) {MILO_ASSERT(0, 40); return 0;} // 0x30
    virtual int AddMeshInstance(Transform, RndMesh*, float) {MILO_ASSERT(0, 42); return 0;} // 0x34
    virtual void DrawInstances(const ObjPtrList<RndMesh, ObjectDir>&, int) = 0; // 0x38
    virtual void SetDirty(bool) {} // 0x3C
    virtual void Poll() {} // 0x40
    virtual void Init() {} // 0x44
    virtual void SetScale(float) {} // 0x48
    virtual void CheckValid(const char*) const {} // 0x4C

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

template <typename T>
class TrackWidgetImp : public TrackWidgetImpBase {
public:
    TrackWidgetImp(){}
    virtual ~TrackWidgetImp(){}
    virtual bool Empty(){ return Instances().empty(); }
    virtual int Size(){ return Instances().size(); }
    virtual float GetFirstInstanceY();
    virtual float GetLastInstanceY();
    virtual void Sort();
    virtual void Clear(){ DoClear(Instances()); }
    virtual void RemoveAt(float, float, float);
    virtual void RemoveUntil(float, float);
    virtual int AddInstance(Transform, float);
    virtual void DrawInstances(const ObjPtrList<RndMesh, ObjectDir>&, int);
    virtual std::list<T>& Instances();
    virtual void RemoveInstances(std::list<T>&, std::list<T>::iterator, std::list<T>::iterator);
    virtual int PushInstance(T&);

    void DoClear(std::list<T>& insts){
        insts.clear();
        SetDirty(true);
    }
};

class TextInstance {
    public:
    TextInstance(Transform t, String s) : mXfm(t) {}
    Transform mXfm;
}; // ????

class CharWidgetImp : public TrackWidgetImp<TextInstance> {
    public:
    CharWidgetImp(RndFont*, RndText*, int, int, RndText::Alignment, Hmx::Color32, Hmx::Color32, bool);
    virtual void Clear();
    virtual int AddTextInstance(Transform, String, bool);
    virtual void SetDirty(bool);
    virtual std::list<TextInstance>& Instances();
    virtual void RemoveInstances(std::list<TextInstance>&, std::list<TextInstance>::iterator, std::list<TextInstance>::iterator);
    virtual int PushInstance(TextInstance&);

    void SetScale(float);

    bool mDirty; // 0x4
    bool unk_0x5; 
    int unk_0x8, unk_0xC;
    RndText* unk_0x10;
    std::list<TextInstance> mInstances; // 0x14
    RndFont* unk_0x1C;
    std::vector<int, u16> unk_0x20;
};

class MeshInstance {
    public:
};

class MatWidgetImp : public TrackWidgetImp<MeshInstance> {
public:
    virtual std::list<MeshInstance>& Instances();

    std::list<MeshInstance> mInstances;
};

class MultiMeshWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> { 
public:
    MultiMeshWidgetImp(const ObjPtrList<RndMesh, ObjectDir>&, bool);
    virtual ~MultiMeshWidgetImp();
    virtual bool Empty();
    virtual int Size();
    virtual void Clear();
    virtual float GetLastInstanceY();
    virtual int AddInstance(Transform, float);
    virtual void Init();
    virtual std::list<RndMultiMesh::Instance>& Instances();
    virtual int PushInstance(RndMultiMesh::Instance&);

    std::vector<RndMultiMesh*> mMultiMeshes; // 0x4
    const ObjPtrList<RndMesh,ObjectDir>& mMeshes; // 0xc
    bool unk10; // 0x10
};

class ImmediateWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> {
public:

    std::list<RndMultiMesh::Instance> mInstances;
    bool unk_0xC;

    ImmediateWidgetImp(bool b) : unk_0xC(b) {} 
    virtual int AddInstance(Transform, float);
    virtual std::list<RndMultiMesh::Instance>& Instances();
    virtual void DrawInstances(const ObjPtrList<RndMesh, ObjectDir>&, int);
    virtual int PushInstance(RndMultiMesh::Instance&);
};

#endif // TRACK_TRACKWIDGETIMP_H
