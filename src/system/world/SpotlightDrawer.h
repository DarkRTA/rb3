#ifndef WORLD_SPOTLIGHTDRAWER_H
#define WORLD_SPOTLIGHTDRAWER_H
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/PostProc.h"

class RndTex;
class SpotlightDrawer;

class SpotDrawParams {
public:
    SpotDrawParams(SpotlightDrawer*);
    SpotDrawParams& operator=(const SpotDrawParams&);
    void Load(BinStream&, int);

    float mIntensity;
    Hmx::Color mColor;
    float mBaseIntensity;
    float mSmokeIntensity;
    float mHalfDistance;
    float mLightingInfluence;
    ObjPtr<RndTex, ObjectDir> mTexture;
    ObjPtr<RndDrawable, ObjectDir> mProxy;
    SpotlightDrawer* mOwner;
};

class SpotlightDrawer : public RndDrawable, public PostProcessor {
public:

    // size: 0x40
    class SpotMeshEntry {
    public:
    };

    // size: 0x8
    class SpotlightEntry {
    public:
    };

    SpotlightDrawer();
    OBJ_CLASSNAME(SpotlightDrawer);
    OBJ_SET_TYPE(SpotlightDrawer);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual ~SpotlightDrawer();
    virtual void EndWorld();
    virtual void DoPost(){}
    virtual void OnGPHangRecover(){}
    virtual float Priority(){ return 0.1f; }
    virtual void SetAmbientColor(const Hmx::Color&);
    virtual void SortLights();
    virtual void DrawWorld();
    virtual void DrawShadow();
    virtual void DrawMeshVec(std::vector<SpotMeshEntry>&); // change return type
    virtual void DrawAdditional(SpotlightEntry*, const SpotlightEntry*&);
    virtual void DrawLenses(SpotlightEntry*, const SpotlightEntry*&);
    virtual void DrawBeams(SpotlightEntry*, const SpotlightEntry*&);
    virtual void DrawFlares(SpotlightEntry*, const SpotlightEntry*&);
    virtual void ClearPostDraw(){}
    virtual void ClearPostProc(){}

    void UpdateBoxMap();
    void ClearLights();

    static SpotlightDrawer* sCurrent;
    static std::vector<SpotlightEntry> sLights;
    static std::vector<SpotMeshEntry> sCans;
    static std::vector<class Spotlight*> sShadowSpots;

    static void Init();
    static void RemoveFromLists(Spotlight*);

    SpotDrawParams mParams;
};

#endif
