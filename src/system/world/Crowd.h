#ifndef WORLD_CROWD_H
#define WORLD_CROWD_H
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Mesh.h"
#include "rndobj/Env.h"
#include "rndobj/MultiMesh.h"
#include "char/Character.h"

class WorldCrowd : public RndDrawable, public RndPollable {
public:

    class CharDef {
    public:
        CharDef(Hmx::Object*);
        void Load(BinStream&);

        ObjPtr<Character, ObjectDir> mChar; // 0x0
        float mHeight; // 0xc
        float mDensity; // 0x10
        float mRadius; // 0x14
        bool unk18; // 0x18 - use random color?
        ObjPtrList<RndMat, ObjectDir> unk1c; // 0x1c
    };

    class CharData {
    public:
        class Char3D {
        public:
        };

        CharData(Hmx::Object*);
        void Load(BinStream&);

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
    int GetModifyStamp() const { return unk88; }
    void Set3DCharList(const std::vector<std::pair<int, int> >&, Hmx::Object*);
    void AssignRandomColors();
    void SetFullness(float, float);
    void SetMatAndCameraLod();
    void CreateMeshes();
    RndMesh* BuildBillboard(Character*, float);
    void SetLod(int);
    void Force3DCrowd(bool);

    DataNode OnRebuild(DataArray*);
    DataNode OnIterateFrac(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(WorldCrowd)
    static void Init(){
        REGISTER_OBJ_FACTORY(WorldCrowd)
    }

    ObjPtr<RndMesh, ObjectDir> mPlacementMesh; // 0x28
    ObjList<CharData> mCharacters; // 0x34
    int mNum; // 0x40
    int unk44; // 0x44
    Vector3 unk48; // 0x48
    bool mForce3DCrowd; // 0x54
    bool mShow3DOnly; // 0x55
    float unk58; // 0x58
    float unk5c; // 0x5c
    int mLod; // 0x60
    ObjPtr<RndEnviron, ObjectDir> mEnviron; // 0x64
    ObjPtr<RndEnviron, ObjectDir> mEnviron3D; // 0x70
    ObjPtr<RndTransformable, ObjectDir> mFocus; // 0x7c
    int unk88; // 0x88
};

inline BinStream& operator>>(BinStream& bs, WorldCrowd::CharData& cd){
    cd.Load(bs);
    return bs;
}

#endif
