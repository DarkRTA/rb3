#ifndef CHAR_CHAREYEDARTRULESET_H
#define CHAR_CHAREYEDARTRULESET_H
#include "obj/Object.h"

class CharEyeDartRuleset : public Hmx::Object {
public:
    struct EyeDartRulesetData {
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

    void operator delete(void* v){
        _MemFree(v);
    }

    static unsigned short gRev;
    static unsigned short gAltRev;

    EyeDartRulesetData mData;
};

#endif
