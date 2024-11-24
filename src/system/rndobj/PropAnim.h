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
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndPropAnim();
    virtual bool Loop(){ return mLoop; }
    virtual void StartAnim();
    virtual void EndAnim(){}
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void LoadPre7(BinStream&);
    void AdvanceFrame(float);
    void RemoveKeys();
    PropKeys* GetKeys(const Hmx::Object*, DataArray*);
    PropKeys* AddKeys(Hmx::Object*, DataArray*, PropKeys::AnimKeysType);
    bool ChangePropPath(Hmx::Object*, DataArray*, DataArray*);
    bool RemoveKeys(Hmx::Object*, DataArray*);
    bool HasKeys(Hmx::Object*, DataArray*);
    std::vector<PropKeys*>::iterator FindKeys(Hmx::Object*, DataArray*);
    void SetKey(Hmx::Object*, DataArray*, float);
    void SetKeyVal(Hmx::Object*, DataArray*, float, const DataNode&, bool);
    PropKeys::AnimKeysType AnimKeysType(Hmx::Object*, DataArray*);
    PropKeys::Interpolation InterpType(Hmx::Object*, DataArray*);
    void SetInterpType(Hmx::Object*, DataArray*, PropKeys::Interpolation);
    Symbol InterpHandler(Hmx::Object*, DataArray*);
    void SetInterpHandler(Hmx::Object*, DataArray*, Symbol);
    int ValueFromFrame(PropKeys*, float, DataNode*);
    bool ValueFromIndex(PropKeys*, int, DataNode*);

    DataNode OnReplaceKeyframe(DataArray*);
    DataNode OnReplaceFrame(DataArray*);
    DataNode OnGetIndexFromFrame(const DataArray*);
    DataNode OnGetFrameFromIndex(const DataArray*);
    DataNode OnGetValueFromIndex(const DataArray*);
    DataNode OnGetValueFromFrame(const DataArray*);
    DataNode ForEachTarget(const DataArray*);
    DataNode ForAllKeyframes(const DataArray*);
    DataNode ForeachKeyframe(const DataArray*);
    DataNode ForeachFrame(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndPropAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndPropAnim)
    }
    
    std::vector<PropKeys*> mPropKeys; // 0x10
    float mLastFrame; // 0x18
    bool mInSetFrame; // 0x1c
    bool mLoop; // 0x1d
};

struct ForAllKeyframesSorter {
    bool operator()(const DataArrayPtr& ptr1, const DataArrayPtr& ptr2) const {
        DataArray* arr2 = ptr2;
        DataArray* arr1 = ptr1;
        return arr1->Float(2) < arr2->Float(2) ? true : false;
    }
};