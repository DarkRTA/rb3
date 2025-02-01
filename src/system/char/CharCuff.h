#pragma once
#include "rndobj/Trans.h"
#include "rndobj/Mesh.h"
#include "char/FileMerger.h"
#include "obj/ObjPtr_p.h"

struct Shape {
    float offset;
    float radius;
};

/** "A cuff used to constrain colliding outfits against each other.\n      for example
 * boots against pants.  The widest cuff wins" */
class CharCuff : public RndTransformable {
public:
    CharCuff();
    OBJ_CLASSNAME(CharCuff)
    OBJ_SET_TYPE(CharCuff)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual ~CharCuff();
    virtual void Highlight();

    void Deform(SyncMeshCB *, FileMerger *);
    float Eccentricity(const Vector2 &) const;
    void DeformMesh(RndMesh *, int, SyncMeshCB *);

    DECLARE_REVS;
    NEW_OBJ(CharCuff)
    static void Init() { REGISTER_OBJ_FACTORY(CharCuff) }

    // offset0, radius0, offset1, radius1, offset2, radius2, outer_radius
    // offset0: "Inner offset, usually negative, the inside of the cuff"
    // radius0: "Inner radius, usually the smallest, the inside of the cuff"
    // offset1: "middle offset, usually zero, the center of the cuff"
    // radius1: "middle radius for the center of the cuff, should be at the cuff line"
    // offset2: "Outer offset, usually positive, the outside of the cuff"
    // radius2: "Outer radius, usually the largest, the outside of the cuff"
    Shape mShape[3]; // 0x90, 0x98, 0xa0
    /** "Outside radius, should encompass the biggest thing on the outside, biggest one
     * wins. For incompressible things like big boots should be the biggest part. For soft
     * things like cloth should just be radius1" */
    float mOuterRadius; // 0xa8
    /** "Is the inside open or closed, open is good for things like gauntlets" */
    bool mOpenEnd; // 0xac
    /** "meshes to never deform" */
    ObjPtrList<RndMesh> mIgnore; // 0xb0
    /** "The bone of interest, like bone_R-knee for boot and pant cuffs" */
    ObjPtr<RndTransformable> mBone; // 0xc0
    /** "How much smaller to make the radius along Y, must be < 1" */
    float mEccentricity; // 0xcc
    /** "The outfit category to cuff against, must be set to work" */
    Symbol mCategory; // 0xd0
};
