#ifndef RNDOBJ_DRAW_H
#define RNDOBJ_DRAW_H
#include "rndobj/Highlightable.h"
#include "obj/Object.h"
#include "math/Sphere.h"
#include "math/Mtx.h"
#include "math/Geo.h"
#include <list>

enum HighlightStyle {
    kHighlightWireframe,
    kHighlightSphere,
    kHighlightNone,
    kHighlightWireframeWithNormals,
    kNumHighlightStyles
};

class RndDrawable : public virtual RndHighlightable {
public:
    struct Collision {
        RndDrawable* object; // offset 0x0, size 0x4
        float distance; // offset 0x4, size 0x4
        Plane plane; // offset 0x10, size 0x10
    };

    RndDrawable();
    OBJ_CLASSNAME(Draw);
    OBJ_SET_TYPE(Draw);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&){ return 0.0f; }
    virtual bool MakeWorldSphere(Sphere&, bool){ return 0; }
    virtual int CamOverride(){ return 0; }
    virtual void Mats(std::list<class RndMat*>&, bool){}
    virtual void Draw();
    virtual void DrawShowing(){}
    virtual bool DrawShowingBudget(float);
    virtual void ListDrawChildren(std::list<RndDrawable*>&){}
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&){ return 0; }
    virtual int CollidePlane(const Plane&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual void DrawPreClear(){}
    virtual void UpdatePreClearState(){}
    virtual void Highlight();
    virtual ~RndDrawable(){}

    bool DrawBudget(float);
    static void DumpLoad(BinStream&);
    static HighlightStyle sHighlightStyle;
    static float sNormalDisplayLength;
    static bool sForceSubpartSelection;

    static HighlightStyle GetHighlightStyle(){ return sHighlightStyle; }
    static void SetHighlightStyle(HighlightStyle hs){ sHighlightStyle = hs; }
    static float GetNormalDisplayLength(){ return sNormalDisplayLength; }
    static void SetNormalDisplayLength(float f){ sNormalDisplayLength = f; }
    static bool GetForceSubpartSelection(){ return sForceSubpartSelection; }
    static void SetForceSubpartSelection(bool b){ sForceSubpartSelection = b; }

    DataNode OnCopySphere(const DataArray*);
    DataNode OnGetSphere(const DataArray*);
    DataNode OnSetShowing(const DataArray*);
    DataNode OnShowing(const DataArray*);
    DataNode OnZeroSphere(const DataArray*);
    
    bool mShowing : 1;
    bool unk8p1 : 1; // used in RndGroup
    bool mSynthEmitterEnabled : 1; // used in SynthEmitter
    bool mTestDone : 1; // used in RndFlare
    bool mLastDone : 1; // used in RndFlare
    bool unk8p5 : 1;
    bool unk8p6 : 1;
    bool unk8p7 : 1;

    bool unk9p0 : 1;
    bool unk9p1 : 1;
    bool unk9p2 : 1;
    bool unk9p3 : 1;
    bool unk9p4 : 1; // used in RndMultiMesh
    bool mUseCurrentRect : 1; // used in RndScreenMask
    bool unk9p6 : 1; // used in RndTexBlender
    bool unk9p7 : 1;

    Sphere mSphere;
    float mOrder;
};

#endif
