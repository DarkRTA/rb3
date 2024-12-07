#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Mesh.h"
#include "rndobj/Env.h"
#include "rndobj/MultiMesh.h"
#include "char/Character.h"
#include "utl/BinStream.h"

/**
 * @brief The crowd of characters you would see in a loaded venue.
 * Original _objects description:
 * "A quickly-rendered bunch of instanced characters within an area"
 */
class WorldCrowd : public RndDrawable, public RndPollable {
public:

    /** "Character archetypes for the crowd" */
    class CharDef {
    public:
        CharDef(Hmx::Object*);
        void Load(BinStream&);

        /** "The character to use as the archetype" */
        ObjPtr<Character> mChar; // 0x0
        /** "The height at which to render the character" */
        float mHeight; // 0xc
        /** "Density to place this character" */
        float mDensity; // 0x10
        /** "Collision radius of the character - characters won't be placed within this range" */
        float mRadius; // 0x14
        bool mUseRandomColor; // 0x18
        ObjPtrList<RndMat> mMats; // 0x1c
    };

    class CharData {
    public:
        class Char3D {
        public:
            Char3D(const Transform& tf, int i) : unk0(tf), unk30(i) {}
            Transform unk0; // 0x0
            int unk30; // 0x30
            std::vector<Hmx::Color> mRandomColors; // 0x34
        };

        CharData(Hmx::Object*);
        void Load(BinStream&);

        // the RB3 dump says mDef is a member - would it be easier to make CharDef a superclass of CharData?
        CharDef mDef; // 0x0
        RndMultiMesh* mMMesh; // 0x2c
        std::list<RndMultiMesh::Instance> mBackup; // 0x30
        std::vector<Char3D> m3DChars; // 0x38
        std::vector<Char3D> m3DCharsCreated; // 0x40
    };

    WorldCrowd();
    OBJ_CLASSNAME(WorldCrowd);
    OBJ_SET_TYPE(WorldCrowd);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual ~WorldCrowd();
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();

    void CleanUpCrowdFloor();
    int GetModifyStamp() const { return mModifyStamp; }
    void Set3DCharList(const std::vector<std::pair<int, int> >&, Hmx::Object*);
    /** "Reassigns the random crowd colors" */
    void AssignRandomColors();
    void SetFullness(float, float);
    void SetMatAndCameraLod();
    void CreateMeshes();
    RndMesh* BuildBillboard(Character*, float);
    void SetLod(int);
    void Force3DCrowd(bool);
    void Reset3DCrowd();
    void Sort3DCharList();
    void Set3DCharAll();
    bool Crowd3DExists();
    void Draw3DChars();
    bool IsForced3DCrowd() const { return mForce3DCrowd; }

    DataNode OnRebuild(DataArray*);
    DataNode OnIterateFrac(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(WorldCrowd)
    static void Init(){
        REGISTER_OBJ_FACTORY(WorldCrowd)
    }

    /** "The placement mesh" */
    ObjPtr<RndMesh> mPlacementMesh; // 0x28
    /** The list of characters that will be in the crowd. */
    ObjList<CharData> mCharacters; // 0x34
    /** "Number of characters to place" */
    int mNum; // 0x40
    int unk44; // 0x44
    Vector3 mCenter; // 0x48
    /** "Makes crowd be 3D regardless of the CamShot" */
    bool mForce3DCrowd; // 0x54
    /** "Shows only the 3D crowd, but ONLY in Milo so you can more easily distinguish them from the 2d crowd" */
    bool mShow3DOnly; // 0x55
    float mCharFullness; // 0x58
    float mFlatFullness; // 0x5c
    int mLod; // 0x60
    /** "The environ to render the imposter billboards with" */
    ObjPtr<RndEnviron> mEnviron; // 0x64
    /** "The environ used when rendering the 3D crowd set by a cam shot" */
    ObjPtr<RndEnviron> mEnviron3D; // 0x70
    /** "Optional crowd facing focus when rotate is set to kCrowdRotateNone" */
    ObjPtr<RndTransformable> mFocus; // 0x7c
    int mModifyStamp; // 0x88
};

inline BinStream& operator>>(BinStream& bs, WorldCrowd::CharData& cd){
    cd.Load(bs);
    return bs;
}

inline BinStream& operator>>(BinStream& bs, WorldCrowd::CharDef& cd){
    cd.Load(bs);
    return bs;
}

struct Sort3DChars {
    bool operator()(const WorldCrowd::CharData::Char3D& char1, const WorldCrowd::CharData::Char3D& char2) const {
        return char1.unk30 < char2.unk30;
    }
};