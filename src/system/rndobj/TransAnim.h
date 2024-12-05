#pragma once
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Key.h"

/**
 * @brief A class for animating Transes.
 * Original _objects description:
 * "TransAnim objects animate the position, rotation, and
 * scale of transformable objects."
 */
class RndTransAnim : public RndAnimatable {
public:
    RndTransAnim();
    OBJ_CLASSNAME(TransAnim);
    OBJ_SET_TYPE(TransAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndTransAnim(){}
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget() { return mTrans; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void MakeTransform(float frame, Transform& tf, bool whole, float blend);

    // getters and setters
    void SetTrans(RndTransformable*);
    void SetKeysOwner(RndTransAnim*);
    RndTransformable* Trans() const { return mTrans; }
    Keys<Vector3, Vector3>& TransKeys(){ return mKeysOwner->mTransKeys; }
    Keys<Hmx::Quat, Hmx::Quat>& RotKeys(){ return mKeysOwner->mRotKeys; }
    Keys<Vector3, Vector3>& ScaleKeys(){ return mKeysOwner->mScaleKeys; }
    bool TransSpline() const { return mKeysOwner->mTransSpline; }
    bool ScaleSpline() const { return mKeysOwner->mScaleSpline; }
    void SetTransSpline(bool b){ mKeysOwner->mTransSpline = b; }
    void SetScaleSpline(bool b){ mKeysOwner->mScaleSpline = b; }
    void SetRotSlerp(bool b){ mKeysOwner->mRotSlerp = b; }
    RndTransAnim* KeysOwner() const { return mKeysOwner; }

    /** Handler to set this TransAnim's trans spline toggle.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2: the boolean to set the trans spline to.
     * Example usage: {$this set_trans_spline TRUE}
     */
    DataNode OnSetTransSpline(const DataArray* arr);
    /** Handler to set this TransAnim's scale spline toggle.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2: the boolean to set the scale spline to.
     * Example usage: {$this set_scale_spline TRUE}
     */
    DataNode OnSetScaleSpline(const DataArray* arr);
    /** Handler to set this TransAnim's rot slerp toggle.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2: the boolean to set the rot slerp to.
     * Example usage: {$this set_rot_slerp TRUE}
     */
    DataNode OnSetRotSlerp(const DataArray* arr);
    /** Handler to get the Trans Object that this TransAnim will animate.
     * Example usage: {$this trans}
     */
    DataNode OnTrans(const DataArray*);
    /** Handler to get the number of position keys in this TransAnim.
     * Example usage: {$this num_trans_keys}
     */
    DataNode OnNumTransKeys(const DataArray*);
    /** Handler to get the number of rotation keys in this TransAnim.
     * Example usage: {$this num_rot_keys}
     */
    DataNode OnNumRotKeys(const DataArray*);
    /** Handler to get the number of scale keys in this TransAnim.
     * Example usage: {$this num_scale_keys}
     */
    DataNode OnNumScaleKeys(const DataArray*);
    /** Handler to add a positional key to this TransAnim.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2-4: the positional X/Y/Z coordinates of the key to add.
     *     Node 5: the frame that this new key will be associated with.
     * Example usage: {$this add_trans_key 1.0 2.0 3.0 69.0}
     */
    DataNode OnAddTransKey(const DataArray* arr);
    /** Handler to add a rotational key to this TransAnim.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2-4: the rotational X/Y/Z coordinates of the key to add.
     *     Node 5: the frame that this new key will be associated with.
     * Example usage: {$this add_rot_key 1.0 2.0 3.0 69.0}
     */
    DataNode OnAddRotKey(const DataArray* arr);
    /** Handler to add a scale key to this TransAnim.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Nodes 2-4: the scale X/Y/Z coordinates of the key to add.
     *     Node 5: the frame that this new key will be associated with.
     * Example usage: {$this add_scale_key 1.0 2.0 3.0 69.0}
     */
    DataNode OnAddScaleKey(const DataArray* arr);
    /** Handler to splice keys from another TransAnim at a certain frame range.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the other RndTransAnim.
     *     Node 3: the first frame in the range of frames to splice.
     *     Node 4: the last frame in the range of frames to splice.
     * Example usage: {$this splice other_trans_anim 69.0 420.0}
     */
    DataNode OnSplice(const DataArray* arr);
    /** Handler to remove a range of rotational keys from this RndTransAnim.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents:
     *     Node 2: the first frame in the range of frames to remove.
     *     Node 3: the last frame in the range of frames to remove.
     * Example usage: {$this remove_rot_keys 69.0 420.0}
     */
    DataNode OnRemoveRotKeys(const DataArray* arr);
    /** Handler to remove a range of positional keys from this RndTransAnim.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents:
     *     Node 2: the first frame in the range of frames to remove.
     *     Node 3: the last frame in the range of frames to remove.
     * Example usage: {$this remove_trans_keys 69.0 420.0}
     */
    DataNode OnRemoveTransKeys(const DataArray* arr);
    DataNode OnLinearize(const DataArray*);
    /** Handler to set the Trans Object that this TransAnim should animate.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents:
     *     Node 2: the Trans object.
     * Example usage: {$this set_trans the_trans_object}
     */
    DataNode OnSetTrans(const DataArray* arr);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTransAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTransAnim)
    }

    /** The Trans to animate. */
    ObjPtr<RndTransformable> mTrans; // 0x10
    /** Whether or not to use spline interpolation for the trans keys. */
    bool mTransSpline; // 0x1C
    /** Whether or not to use spline interpolation for the scale keys. */
    bool mScaleSpline; // 0x1D
    /** Whether or not to use slerp interpolation for the rot keys. */
    bool mRotSlerp; // 0x1E
    /** Whether or not to use spline interpolation for the rot keys. */
    bool mRotSpline; // 0x1F
    /** The collection of rotation keys. */
    Keys<Hmx::Quat, Hmx::Quat> mRotKeys; // 0x20
    /** The collection of position keys. */
    Keys<Vector3, Vector3> mTransKeys; // 0x28
    /** The collection of scale keys. */
    Keys<Vector3, Vector3> mScaleKeys; // 0x30
    /** The TransAnim that owns all of these keys. */
    ObjOwnerPtr<RndTransAnim> mKeysOwner; // 0x38
    bool mRepeatTrans; // 0x44
    bool mFollowPath; // 0x45
};
