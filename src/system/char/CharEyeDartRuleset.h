#ifndef CHAR_CHAREYEDARTRULESET_H
#define CHAR_CHAREYEDARTRULESET_H
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"

class CharEyeDartRuleset : public Hmx::Object {
public:
    struct EyeDartRulesetData {
        EyeDartRulesetData(){ ClearToDefaults(); }
        float mMinRadius;
        float mMaxRadius;
        float mOnTargetAngleThresh;
        int mMinDartsPerSequence;
        int mMaxDartsPerSequence;
        float mMinSecsBetweenDarts;
        float mMaxSecsBetweenDarts;
        float mMinSecsBetweenSequences;
        float mMaxSecsBetweenSequences;
        bool mScaleWithDistance;
        float mReferenceDistance;

        void ClearToDefaults();
    };

    CharEyeDartRuleset();
    virtual ~CharEyeDartRuleset();
    OBJ_CLASSNAME(CharEyeDartRuleset);
    OBJ_SET_TYPE(CharEyeDartRuleset);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(CharEyeDartRuleset)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharEyeDartRuleset)
    }

    EyeDartRulesetData mData;
};

#endif
