#pragma once
#include "math/Mtx.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Mesh.h"
#include "utl/BinStream.h"
#include "utl/Std.h"
#include "utl/TextStream.h"
#include <list>
#include <utility>

class OldMMInst {
public:
    Transform mOldXfm; // 0x0
    Hmx::Color mOldColor; // 0x30
};

inline BinStream& operator>>(BinStream& bs, OldMMInst& inst){
    bs >> inst.mOldXfm >> inst.mOldColor;
    return bs;
}

/**
 * @brief An object that instances \ref RndMesh "RndMeshes".
 * Original _objects description:
 * "A MultiMesh object draws a simple Mesh in many places
 * quickly. Create a multimesh by instancing the base mesh lots of
 * times in Max, then using the multiobject wizard."
 */
class RndMultiMesh : public RndDrawable {
public:
    /** A struct representing a location where a Mesh should be drawn. */
    struct Instance {
        Instance();
        Instance(const Transform& t) : mXfm(t) {}
        void LoadRev(BinStream&, int);
        void Load(BinStream&);

        Transform mXfm; // 0x0
    };
    RndMultiMesh();
    OBJ_CLASSNAME(MultiMesh);
    OBJ_SET_TYPE(MultiMesh);
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
    virtual ~RndMultiMesh() {InvalidateProxies();}
    virtual void Print();
    virtual void UpdateMesh(){}

    /** Invalidates all proxies in the proxy pool. */
    void InvalidateProxies();

    /** Handler to retrieve a specific Mesh instance's pos.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the Instance list to get the pos of.
     *     Nodes 3-5: vars to house the Instance pos's X/Y/Z coordinates.
     * Example usage: {$this get_pos $x $y $z}
     */
    DataNode OnGetPos(const DataArray* arr);
    /** Handler to set a specific Mesh instance's pos.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the Instance list to set the pos of.
     *     Nodes 3-5: The Instance pos's desired X/Y/Z coordinates.
     * Example usage: {$this set_pos 0.0 69.0 420.0}
     */
    DataNode OnSetPos(const DataArray* arr);
    /** Handler to retrieve a specific Mesh instance's rot.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the Instance list to get the rot of.
     *     Nodes 3-5: vars to house the Instance rot's X/Y/Z coordinates.
     * Example usage: {$this get_rot $x $y $z}
     */
    DataNode OnGetRot(const DataArray* arr);
    /** Handler to set a specific Mesh instance's rot.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the Instance list to set the rot of.
     *     Nodes 3-5: The Instance rot's desired X/Y/Z coordinates.
     * Example usage: {$this set_rot 0.0 69.0 420.0}
     */
    DataNode OnSetRot(const DataArray* arr);
    /** Handler to retrieve a specific Mesh instance's scale.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the Instance list to get the scale of.
     *     Nodes 3-5: vars to house the Instance scale's X/Y/Z coordinates.
     * Example usage: {$this get_scale $x $y $z}
     */
    DataNode OnGetScale(const DataArray* arr);
    /** Handler to set a specific Mesh instance's scale.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the Instance list to set the scale of.
     *     Nodes 3-5: The Instance scale's desired X/Y/Z coordinates.
     * Example usage: {$this set_scale 0.0 69.0 420.0}
     */
    DataNode OnSetScale(const DataArray* arr);
    /** Handler to add another MultiMesh's instance to this MultiMesh's instance list.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the other RndMultiMesh.
     *     Node 3: the index of the other RndMultiMesh's instance list.
     * Example usage: {$this add_xfm the_other_multimesh 3}
     */
    DataNode OnAddXfm(const DataArray* arr);
    /** Handler to add some number of empty instances to the instance list.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the number of instances to add.
     * Example usage: {$this add_xfms 69}
     */
    DataNode OnAddXfms(const DataArray* arr);
    /** Handler to remove a specific instance from the instance list.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the index of the instance list to remove.
     * Example usage: {$this remove_xfm 69}
     */
    DataNode OnRemoveXfm(const DataArray* arr);
    /** Handler to get the number of instances of this MultiMesh.
     * @returns The number of instances.
     * Example usage: {$this num_xfms}
     */
    DataNode OnNumXfms(const DataArray*);
    /** Handler to get the Mesh associated with this MultiMesh.
     * @returns The mesh.
     * Example usage: {$this mesh}
     */
    DataNode OnMesh(const DataArray*);
    /** Handler to move all instances according to supplied X/Y/Z coordinates.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2-4: the desired X/Y/Z coordinates.
     * Example usage: {$this move_xfms 1.0 2.0 3.0}
     */
    DataNode OnMoveXfms(const DataArray* arr);
    /** Handler to scale all instances according to supplied X/Y/Z coordinates.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2-4: the desired X/Y/Z coordinates.
     * Example usage: {$this scale_xfms 1.0 2.0 3.0}
     */
    DataNode OnScaleXfms(const DataArray* arr);
    /** Handler to (presumably) sort all instances according to supplied X/Y/Z coordinates.
     * I say "presumably" because this handler actually will fail in debug and return 0 in retail.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2-4: the desired X/Y/Z coordinates.
     * Example usage: {$this sort_xfms 1.0 2.0 3.0}
     */
    DataNode OnSortXfms(const DataArray* arr);
    /** Handler to (presumably) randomize all instances.
     * I say "presumably" because this handler actually will fail in debug and return 0 in retail.
     * Example usage: {$this random_xfms}
     */
    DataNode OnRandomXfms(const DataArray*);
    /** Handler to scramble all instances.
     * Example usage: {$this scramble_xfms}
     */
    DataNode OnScrambleXfms(const DataArray*);
    // not documented yet because idk how exactly the "distribution" is happening lol
    DataNode OnDistribute(const DataArray* arr);

    /** Remove the Instance at the specified index.
     * @param [in] idx The desired index.
     */
    void RemoveInstance(int idx){
        mInstances.erase(NextItr(mInstances.begin(), idx));
    }
    /** Get the Instance at the specified index.
     * @param [in] idx The desired index.
     * @returns The aforementioned Instance.
     */
    Instance& Instances(int idx){
        return *NextItr(mInstances.begin(), idx);
    }

    // getters/setters
    void SetMesh(RndMesh*);
    RndMesh* GetMesh() const { return mMesh; }

    /** The simple mesh to draw. */
    ObjPtr<RndMesh> mMesh; // 0x20
    /** The locations at which the mesh should be drawn. */
    std::list<RndMultiMesh::Instance> mInstances; // 0x2C

    static void Terminate();
    static std::list<std::pair<class RndMultiMeshProxy*, int> > sProxyPool;

    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS
    NEW_OBJ(RndMultiMesh)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMultiMesh)
    }
};

inline BinStream& operator>>(BinStream& bs, RndMultiMesh::Instance& i) {
    i.Load(bs);
    return bs;
}

TextStream& operator<<(TextStream& ts, const RndMultiMesh::Instance& i);
