#pragma once
#include "math/Mtx.h"
#include "math/Utl.h"
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
    TrackWidgetImpBase() {}
    virtual ~TrackWidgetImpBase() {} // 0x8
    virtual bool Empty() = 0; // 0xC
    virtual int Size() = 0; // 0x10
    virtual float GetFirstInstanceY() = 0; // 0x14
    virtual float GetLastInstanceY() = 0; // 0x18
    virtual void Sort() = 0; // 0x1C
    virtual void Clear() = 0; // 0x20
    virtual void RemoveAt(float, float, float) = 0; // 0x24
    virtual void RemoveUntil(float, float) = 0; // 0x28
    virtual int AddInstance(Transform, float) {
        MILO_ASSERT(0, 38);
        return 0;
    } // 0x2C
    virtual int AddTextInstance(Transform, String, bool) {
        MILO_ASSERT(0, 40);
        return 0;
    } // 0x30
    virtual int AddMeshInstance(Transform, RndMesh *, float) {
        MILO_ASSERT(0, 42);
        return 0;
    } // 0x34
    virtual void DrawInstances(const ObjPtrList<RndMesh> &, int) = 0; // 0x38
    virtual void SetDirty(bool) {} // 0x3C
    virtual void Poll() {} // 0x40
    virtual void Init() {} // 0x44
    virtual void SetScale(float) {} // 0x48
#ifdef MILO_DEBUG
    virtual void CheckValid(const char *) const {} // 0x4C
#endif

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

class WidgetInstance {
public:
    WidgetInstance(const Transform &t) : mXfm(t) {}

    Transform mXfm;
};

template <typename T>
class WidgetInstanceCmp {
public:
    bool operator()(const T &t1, const T &t2) const {
        return t1.mXfm.v.y < t2.mXfm.v.y ? true : false;
    }
};

template <typename T>
class TrackWidgetImp : public TrackWidgetImpBase {
public:
    TrackWidgetImp() {}
    virtual ~TrackWidgetImp() {}
    virtual bool Empty() { return Instances().empty(); }
    virtual int Size() { return Instances().size(); }
    virtual float GetFirstInstanceY() { return DoGetFirstInstanceY(Instances()); }
    virtual float GetLastInstanceY() { return DoGetLastInstanceY(Instances()); }
    virtual void Sort() { DoSort(Instances()); }
    virtual void Clear() { DoClear(Instances()); }
    virtual void RemoveAt(float f1, float f2, float f3) {
        DoRemoveAt(Instances(), f1, f2, f3);
    }
    virtual void RemoveUntil(float f1, float f2) { DoRemoveUntil(Instances(), f1, f2); }
    virtual std::list<T> &Instances() = 0;
    virtual void RemoveInstances(
        std::list<T> &list, typename std::list<T>::iterator start, typename std::list<T>::iterator end
    ) {
        list.erase(start, end);
        SetDirty(true);
    }
    virtual void PushInstance(T &inst) { DoPushInstance(Instances(), inst); }

    void DoClear(std::list<T> &insts) {
        insts.clear();
        SetDirty(true);
    }

    float DoGetFirstInstanceY(std::list<T> &list) {
        MILO_ASSERT(!list.empty(), 0x8F);
        return list.front().mXfm.v.y;
    }

    float DoGetLastInstanceY(std::list<T> &list) {
        MILO_ASSERT(!list.empty(), 0x95);
        return list.back().mXfm.v.y;
    }

    void DoRemoveAt(std::list<T> &insts, float f1, float f2, float f3) {
        if (!insts.empty()) {
            typename std::list<T>::iterator it5c = insts.end();
            typename std::list<T>::iterator it = insts.begin();
            for (; it != insts.end(); ++it) {
                if (IsFabsZero(it->mXfm.v.y - f1)) {
                    if (f3 < 0 || Abs<float>(it->mXfm.v.x - f2) <= f3) {
                        if (it5c == insts.end()) {
                            it5c = it;
                        }
                    } else if (it5c != insts.end()) {
                        RemoveInstances(insts, it5c, it);
                        it5c = insts.end();
                    }
                } else if (it->mXfm.v.y > f1) {
                    if (it5c != insts.end()) {
                        RemoveInstances(insts, it5c, it);
                        it5c = insts.end();
                    }
                    break;
                }
            }
            if (it5c != insts.end()) {
                RemoveInstances(insts, it5c, it);
            }
        }
    }

    void DoRemoveUntil(std::list<T> &insts, float f1, float f2) {
        if (!insts.empty()) {
            typename std::list<T>::iterator it = insts.begin();
            for (; it != insts.end() && f2 * it->mXfm.m.y.y + it->mXfm.v.y < f1; ++it) {
            }
            if (it != insts.end()) {
                RemoveInstances(insts, insts.begin(), it);
            }
        }
    }

    void DoSort(std::list<T> &insts) { insts.sort(WidgetInstanceCmp<T>()); }

    void DoPushInstance(std::list<T> &insts, T &instance) {
        insts.push_back(instance);
        SetDirty(true);
    }

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

class TextInstance : public WidgetInstance {
public:
    TextInstance(const Transform &t, const String &s, bool alt)
        : WidgetInstance(t), mText(s), mLineId(-1), mUseAltStyle(alt) {}

    String mText;
    int mLineId;
    bool mUseAltStyle;
};

class CharWidgetImp : public TrackWidgetImp<TextInstance> {
public:
    CharWidgetImp(
        RndFont *, RndText *, int, int, RndText::Alignment, Hmx::Color32, Hmx::Color32, bool
    );
    virtual ~CharWidgetImp() {}
    virtual void Clear();
    virtual int AddTextInstance(Transform tf, String s, bool alt) {
        bool b2 = false;
        if (!Empty() && tf.v.y < GetLastInstanceY()) {
            b2 = true;
        }
        TextInstance inst(tf, s, alt);
        PushInstance(inst);
        if (b2)
            Sort();
        return b2;
    }
    virtual void DrawInstances(const ObjPtrList<RndMesh> &, int);
    virtual void SetDirty(bool dirty) { mNeedRebuild = dirty; }
    virtual void Poll();
    virtual void SetScale(float);
#ifdef MILO_DEBUG
    virtual void CheckValid(const char *name) const {
        if (!Valid()) {
            MILO_WARN(
                "WARNING: Text widget \"%s\" won't be drawn under the current parameters.  It needs a valid text obj, valid font, max instances > 0 , and chars per instance > 0.",
                name
            );
        }
    }
#endif
    virtual std::list<TextInstance> &Instances();
    virtual void RemoveInstances(
        std::list<TextInstance> &,
        std::list<TextInstance>::iterator,
        std::list<TextInstance>::iterator
    );
    virtual void PushInstance(TextInstance &);

    bool Valid() const {
        return mText && mFont && mCharsPerInst > 0 && mMaxInstances > 0;
    }

    NEW_OVERLOAD
    DELETE_OVERLOAD

    bool mNeedRebuild; // 0x4
    bool mNeedSync; // 0x5
    int mCharsPerInst; // 0x8
    int mMaxInstances; // 0xc
    RndText *mText; // 0x10
    std::list<TextInstance> mInstances; // 0x14
    RndFont *mFont; // 0x1c
    std::vector<int> mReusableLines; // 0x20
};

class MeshInstance : public WidgetInstance {
public:
    MeshInstance(const Transform &t, RndMesh *mesh) : WidgetInstance(t), mMesh(mesh) {}

    RndMesh *mMesh;
};

class MatWidgetImp : public TrackWidgetImp<MeshInstance> {
public:
    MatWidgetImp(RndMat *m) : mMat(m) {}
    virtual ~MatWidgetImp() {}
    virtual int AddMeshInstance(Transform, RndMesh *, float);
    virtual void DrawInstances(const ObjPtrList<RndMesh> &, int);
    virtual std::list<MeshInstance> &Instances() { return mInstances; }

    NEW_OVERLOAD
    DELETE_OVERLOAD

    std::list<MeshInstance> mInstances; // 0x4
    RndMat *mMat; // 0xc
};

class MultiMeshWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> {
public:
    MultiMeshWidgetImp(const ObjPtrList<RndMesh> &, bool);
    virtual ~MultiMeshWidgetImp();
    virtual bool Empty();
    virtual int Size();
    virtual float GetFirstInstanceY();
    virtual float GetLastInstanceY();
    virtual void Sort();
    virtual void Clear();
    virtual void RemoveAt(float, float, float);
    virtual void RemoveUntil(float, float);
    virtual int AddInstance(Transform tf, float) {
        bool b2 = false;
        if (!Empty() && tf.v.y < GetLastInstanceY()) {
            b2 = true;
        }
        RndMultiMesh::Instance inst(tf);
        PushInstance(inst);
        if (b2)
            Sort();
        return b2;
    }
    virtual void DrawInstances(const ObjPtrList<RndMesh> &, int);
    virtual void Init();
    virtual std::list<RndMultiMesh::Instance> &Instances();
    virtual void PushInstance(RndMultiMesh::Instance &);

    NEW_OVERLOAD
    DELETE_OVERLOAD

    std::vector<RndMultiMesh *> mMultiMeshes; // 0x4
    const ObjPtrList<RndMesh> &mMeshes; // 0xc
    bool unk10; // 0x10
};

class ImmediateWidgetImp : public TrackWidgetImp<RndMultiMesh::Instance> {
public:
    ImmediateWidgetImp(bool b) : mAllowRotation(b) {}
    virtual ~ImmediateWidgetImp() {}
    virtual int AddInstance(Transform tf, float) {
        bool b2 = false;
        if (!Empty() && tf.v.y < GetLastInstanceY()) {
            b2 = true;
        }
        RndMultiMesh::Instance inst(tf);
        PushInstance(inst);
        if (b2)
            Sort();
        return b2;
    }
    virtual void DrawInstances(const ObjPtrList<RndMesh> &, int);
    virtual std::list<RndMultiMesh::Instance> &Instances() { return mInstances; }

    NEW_OVERLOAD
    DELETE_OVERLOAD

    std::list<RndMultiMesh::Instance> mInstances; // 0x4
    bool mAllowRotation; // 0xc
};
