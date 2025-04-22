#pragma once
#include "obj/ObjMacros.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/PostProc.h"
#include "world/Spotlight.h"

class RndEnviron;
class RndTex;
class SpotlightDrawer;

class SpotDrawParams {
public:
    SpotDrawParams(SpotlightDrawer *);
    SpotDrawParams &operator=(const SpotDrawParams &);
    void Load(BinStream &, int);

    float mIntensity; // 0x0
    Hmx::Color mColor; // 0x4
    float mBaseIntensity; // 0x14
    float mSmokeIntensity; // 0x18
    float mHalfDistance; // 0x1c
    float mLightingInfluence; // 0x20
    ObjPtr<RndTex> mTexture; // 0x24
    ObjPtr<RndDrawable> mProxy; // 0x30
    SpotlightDrawer *mOwner; // 0x3c
};

class SpotlightDrawer : public RndDrawable, public PostProcessor {
public:
    // size: 0x40
    class SpotMeshEntry {
    public:
        SpotMeshEntry() : unk0(0), unk4(0), unk8(0) {}
        RndMesh *unk0;
        RndMesh *unk4;
        Spotlight *unk8;
        int unkc;
        Transform unk10;
    };

    // size: 0x8
    class SpotlightEntry {
    public:
        SpotlightEntry() : unk0(0), unk4(0) {}
        unsigned int unk0; // 0x0 - id?
        Spotlight *unk4; // 0x4 - the spotlight
    };

    SpotlightDrawer();
    OBJ_CLASSNAME(SpotlightDrawer);
    OBJ_SET_TYPE(SpotlightDrawer);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable *> &);
    virtual ~SpotlightDrawer();
    virtual void EndWorld();
    virtual void DoPost() {}
    virtual void OnGPHangRecover();
    virtual float Priority() { return 0.1f; }
    virtual void SetAmbientColor(const Hmx::Color &);
    virtual void SortLights();
    virtual void DrawWorld();
    virtual void DrawShadow();
    virtual void DrawMeshVec(std::vector<SpotMeshEntry> &);
    virtual void DrawAdditional(SpotlightEntry *, SpotlightEntry *const &);
    virtual void DrawLenses(SpotlightEntry *, SpotlightEntry *const &);
    virtual void DrawBeams(SpotlightEntry *, SpotlightEntry *const &);
    virtual void DrawFlares(SpotlightEntry *, SpotlightEntry *const &);
    virtual void ClearPostDraw();
    virtual void ClearPostProc() {}

    void UpdateBoxMap();
    void ClearLights();
    void Select();
    void DeSelect();
    void ApplyLightingApprox(BoxMapLighting &, float) const;

    static SpotlightDrawer *sCurrent;
    static SpotlightDrawer *sDefault;
    static RndEnviron *sEnviron;
    static RndMat *sEditorMat;
    static int sNeedBoxMap;
    static std::vector<SpotlightEntry> sLights;
    static std::vector<SpotMeshEntry> sCans;
    static std::vector<class Spotlight *> sShadowSpots;
    static bool sNeedDraw;
    static bool sHaveAdditionals;
    static bool sHaveLenses;
    static bool sHaveFlares;
    static bool sNoBeams;

    static void Init();
    static void RemoveFromLists(Spotlight *);
    static void DrawLight(Spotlight *);
    static void Register() { REGISTER_OBJ_FACTORY(SpotlightDrawer); }
    NEW_OBJ(SpotlightDrawer);

    SpotDrawParams mParams; // 0x24
};

struct ByColor {
    bool operator()(
        const SpotlightDrawer::SpotlightEntry &e1,
        const SpotlightDrawer::SpotlightEntry &e2
    ) const {
        return e1.unk0 < e2.unk0;
    }
};

struct ByEnvMesh {
    bool operator()(
        const SpotlightDrawer::SpotMeshEntry &e1, const SpotlightDrawer::SpotMeshEntry &e2
    ) const {
        if (e1.unk4 < e2.unk4)
            return true;
        else if (e1.unk4 > e2.unk4)
            return false;
        else
            return e1.unk0 < e2.unk0;
    }
};