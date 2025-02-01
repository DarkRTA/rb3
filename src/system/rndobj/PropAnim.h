#pragma once
#include "obj/Data.h"
#include "rndobj/Anim.h"
#include "obj/Object.h"
#include <vector>
#include "rndobj/PropKeys.h"

/**
 * @brief: A property animator.
 * Original _objects description:
 * "Animate any properties on target object"
 */
class RndPropAnim : public RndAnimatable {
public:
    RndPropAnim();
    OBJ_CLASSNAME(PropAnim);
    OBJ_SET_TYPE(PropAnim);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~RndPropAnim();
    virtual bool Loop() { return mLoop; }
    virtual void StartAnim();
    virtual void EndAnim() {}
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Print();

    /** Loads this Object from a BinStream. Only called if gRev < 7. */
    void LoadPre7(BinStream &);
    void AdvanceFrame(float);
    /** Delete all PropKeys from this RndPropAnim. */
    void RemoveKeys();
    /** Get the PropKeys from our collection that has the supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @returns The PropKeys with the above target and prop, if it exists.
     */
    PropKeys *GetKeys(const Hmx::Object *obj, DataArray *prop);
    /** Add a new set of keys to our collection.
     * @param [in] obj The target object for the new keys.
     * @param [in] prop The property of the target object the new keys should animate.
     * @param [in] keysType The new keys' type.
     * @returns The newly created and added keys.
     */
    PropKeys *AddKeys(Hmx::Object *obj, DataArray *prop, PropKeys::AnimKeysType keysType);
    bool ChangePropPath(Hmx::Object *, DataArray *, DataArray *);
    /** Remove the PropKeys that has the supplied target object and property.
     * @param [in] obj The target object for the keys.
     * @param [in] prop The property of the target object the keys should animate.
     * @returns True if the keys existed and have been removed, false otherwise.
     */
    bool RemoveKeys(Hmx::Object *obj, DataArray *prop);
    /** Determine whether or not we have a PropKeys with the supplied target object and
     * property.
     * @param [in] obj The target object for the keys.
     * @param [in] prop The property of the target object the keys should animate.
     * @returns True if such PropKeys exists in our collection, false if not.
     */
    bool HasKeys(Hmx::Object *obj, DataArray *prop);
    /** Get the position of the PropKeys collection containing a PropKeys with the
     * supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @returns An iterator of the PropKeys collection with the corresponding PropKeys.
     */
    std::vector<PropKeys *>::iterator FindKeys(Hmx::Object *obj, DataArray *prop);
    void SetKey(Hmx::Object *, DataArray *, float);
    /** Get the PropKeys with the supplied target and prop, and add a new keyframe with
     * the supplied value/frame pair.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @param [in] frame The frame of the keyframe we want to modify.
     * @param [in] val The value of the keyframe we want to modify.
     * @param [in] unique If true, and a keyframe at the supplied frame exists, modify the
     * value. Else, create a new keyframe.
     * @returns An iterator of the PropKeys collection with the corresponding PropKeys.
     */
    void SetKeyVal(
        Hmx::Object *obj, DataArray *prop, float frame, const DataNode &val, bool unique
    );
    /** Get the animation keys type of the PropKeys with the supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @returns The found PropKeys' animation type. If the PropKeys doesn't exist, return
     * kFloat.
     */
    PropKeys::AnimKeysType AnimKeysType(Hmx::Object *obj, DataArray *prop);
    /** Get the interpolation type of the PropKeys with the supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @returns The found PropKeys' interpolation type. If the PropKeys doesn't exist,
     * return kStep.
     */
    PropKeys::Interpolation InterpType(Hmx::Object *obj, DataArray *prop);
    /** Set the interpolation type of the PropKeys with the supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @param [in] interp The interpolation type to set.
     */
    void SetInterpType(Hmx::Object *obj, DataArray *prop, PropKeys::Interpolation interp);
    /** Get the handler of the PropKeys with the supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @returns The found PropKeys' handler. If the PropKeys doesn't exist, return a null
     * Symbol.
     */
    Symbol InterpHandler(Hmx::Object *obj, DataArray *prop);
    /** Set the handler of the PropKeys with the supplied target and prop.
     * @param [in] obj The target object the PropKeys must have.
     * @param [in] prop The property that the PropKeys must be animating.
     * @param [in] handler The handler to set.
     */
    void SetInterpHandler(Hmx::Object *obj, DataArray *prop, Symbol handler);
    /** Get the value at the given frame of the given keys.
     * @param [in] keys The PropKeys to search in.
     * @param [in] frame The frame to get the value from.
     * @param [out] var The DataNode that will store the corresponding value.
     * @returns The index of the PropKeys in which this frame resides.
     */
    int ValueFromFrame(PropKeys *keys, float frame, DataNode *var);
    /** Get the value at the given index of the given keys.
     * @param [in] keys The PropKeys to search in.
     * @param [in] index The index to get the value from.
     * @param [out] var The DataNode that will store the corresponding value.
     * @returns True if a value was successfully retrieved, false otherwise.
     */
    bool ValueFromIndex(PropKeys *keys, int index, DataNode *var);

    DataNode OnReplaceKeyframe(DataArray *);
    DataNode OnReplaceFrame(DataArray *);

    /** Handler to get the index of a PropKeys' frame.
     * @param [in] arr The supplied DataArray.
     * @returns The index of the supplied PropKeys frame, or -1 if the PropKeys doesn't
     * exist. Expected DataArray contents: Node 2: The target object of the PropKeys. Node
     * 3: The property associated with the PropKeys (as a DataArray). Node 4: The frame of
     * the PropKeys to search. Example usage: {$this index_from_frame targetObj
     * (targetPropKey targetPropVal) 69.0}
     */
    DataNode OnGetIndexFromFrame(const DataArray *arr);
    /** Handler to get the frame at a PropKeys' index.
     * @param [in] arr The supplied DataArray.
     * @returns The frame of the supplied PropKeys index, or -1.0 if the PropKeys doesn't
     * exist. Expected DataArray contents: Node 2: The target object of the PropKeys. Node
     * 3: The property associated with the PropKeys (as a DataArray). Node 4: The index of
     * the PropKeys to get. Example usage: {$this frame_from_index targetObj
     * (targetPropKey targetPropVal) 420}
     */
    DataNode OnGetFrameFromIndex(const DataArray *arr);
    /** Handler to get the value at a PropKeys' index.
     * @param [in] arr The supplied DataArray.
     * @returns True if a value was successfully retrieved, false otherwise.
     * Expected DataArray contents:
     *     Node 2: The target object of the PropKeys.
     *     Node 3: The property associated with the PropKeys (as a DataArray).
     *     Node 4: The index of the PropKeys to get.
     *     Node 5: The DataNode var to store the resulting value in.
     * Example usage: {$this value_from_index targetObj (targetPropKey targetPropVal) 420
     * $valueVar}
     */
    DataNode OnGetValueFromIndex(const DataArray *arr);
    /** Handler to get the value at a PropKeys' frame.
     * @param [in] arr The supplied DataArray.
     * @returns The value from the PropKey's frame, or -1 if the PropKeys doesn't exist.
     * Expected DataArray contents:
     *     Node 2: The target object of the PropKeys.
     *     Node 3: The property associated with the PropKeys (as a DataArray).
     *     Node 4: The frame of the PropKeys to search.
     * Example usage: {$this value_from_frame targetObj (targetPropKey
     * targetPropVal) 69.0}
     */
    DataNode OnGetValueFromFrame(const DataArray *arr);
    DataNode ForEachTarget(const DataArray *);
    DataNode ForAllKeyframes(const DataArray *);
    DataNode ForeachKeyframe(const DataArray *);
    DataNode ForeachFrame(const DataArray *);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndPropAnim)
    static void Init() { REGISTER_OBJ_FACTORY(RndPropAnim) }

    /** A collection of PropKeys. */
    std::vector<PropKeys *> mPropKeys; // 0x10
    float mLastFrame; // 0x18
    bool mInSetFrame; // 0x1c
    /** "Do I self loop on SetFrame" */
    bool mLoop; // 0x1d
};

struct ForAllKeyframesSorter {
    bool operator()(const DataArrayPtr &ptr1, const DataArrayPtr &ptr2) const {
        DataArray *arr2 = ptr2;
        DataArray *arr1 = ptr1;
        return arr1->Float(2) < arr2->Float(2) ? true : false;
    }
};