#ifndef TRACK_TRACKWIDGETIMP_H
#define TRACK_TRACKWIDGETIMP_H

#include "math/Mtx.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"

class TrackWidgetImpBase {
    public:
    virtual ~TrackWidgetImpBase() = 0;
    virtual bool Empty() = 0;
    virtual int Size() = 0;
    virtual float GetFirstInstanceY() = 0;
    virtual float GetLastInstanceY() = 0;
    virtual void Sort() = 0;
    virtual void Clear() = 0;
    virtual void RemoveAt() = 0;
    virtual void RemoveUntil() = 0;
    virtual int AddInstance(Transform, float) {MILO_ASSERT(0, 38); return 0;}
    virtual int AddTextInstance(Transform, String, bool) {MILO_ASSERT(0, 40); return 0;}
    virtual int AddMeshInstance(Transform, RndMesh*, float) {MILO_ASSERT(0, 42); return 0;}
    virtual void DrawInstances() = 0;
    virtual void SetDirty(bool) {}
    virtual void Poll() {}
    virtual void Init() {}
    virtual void SetScale(float) {}
    virtual void CheckValid(const char*) const {}
    virtual void Instances() = 0;
    virtual void RemoveInstances() = 0;
    virtual void PushInstance() = 0;

    NEW_OVERLOAD
};

template <typename T>
class TrackWidgetImp : public TrackWidgetImpBase {
    public:
    virtual ~TrackWidgetImp();
    virtual bool Empty();
    virtual int Size();
    virtual float GetFirstInstanceY();
    virtual float GetLastInstanceY();
    virtual void Sort();
    virtual void Clear();
    virtual void RemoveAt();
    virtual void RemoveUntil();
    virtual void AddInstance();
    virtual void AddTextInstance();
    virtual void AddMeshInstance();
    virtual void DrawInstances();
    virtual void SetDirty(bool) {}
    virtual void Poll() {}
    virtual void Init() {}
    virtual void SetScale(float) {}
    virtual void CheckValid(const char*) const {}
    virtual void Instances();
    virtual void RemoveInstances();
    virtual void PushInstance();
};

class MultiMeshWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> { 
public:
    MultiMeshWidgetImp(const ObjPtrList<RndMesh, ObjectDir>&, bool);
};

class ImmediateWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> {
    virtual ~ImmediateWidgetImp();
};

#endif // TRACK_TRACKWIDGETIMP_H