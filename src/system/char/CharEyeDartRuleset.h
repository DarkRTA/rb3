#pragma once
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"

/** "Defines a procedural ruleset that can be used to generate a variety of realistic eye darting behavior" */
class CharEyeDartRuleset : public Hmx::Object {
public:
    struct EyeDartRulesetData {
        EyeDartRulesetData(){ ClearToDefaults(); }
        /** "Dart locations will be at least this distance from target". Ranges from 0 to 1000. */
        float mMinRadius; // 0x0
        /** "Dart locations will be at most this distance from target". Ranges from 0 to 1000. */
        float mMaxRadius; // 0x4
        float mOnTargetAngleThresh; // 0x8
        /** "Each sequence of darts will have at least this many locations before returning to target". Ranges from 0 to 50. */
        int mMinDartsPerSequence; // 0xc
        /** "Each sequence of darts will have at most this many locations before returning to target". Ranges from 0 to 50. */
        int mMaxDartsPerSequence; // 0x10
        /** "In seconds, the minimum time between each dart in a sequence.  should be very small". Ranges from 0 to 2. */
        float mMinSecsBetweenDarts; // 0x14
        /** "In seconds, the maximum time between each dart in a sequence.  should be very small". Ranges from 0 to 2. */
        float mMaxSecsBetweenDarts; // 0x18
        /** "In seconds, the minimum time to wait to start another dart sequence after the previous one finishes". Ranges from 0 to 100. */
        float mMinSecsBetweenSequences; // 0x1c
        /** "In seconds, the maximum time to wait to start another dart sequence after the previous one finishes". Ranges from 0 to 100. */
        float mMaxSecsBetweenSequences; // 0x20
        /** "Sets whether the dart radius scales with the distance to the character - meaning this dart sequence looks the same regardless of distance" */
        bool mScaleWithDistance; // 0x24
        /** "When scale_with_distance is true, this distance is used as a reference to scale up the radius." */
        float mReferenceDistance; // 0x28

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

    EyeDartRulesetData mData; // 0x1c
};
