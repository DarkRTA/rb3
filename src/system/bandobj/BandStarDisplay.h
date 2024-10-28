#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "synth/Sequence.h"

class BandStarDisplay : public RndDir {
public:
    BandStarDisplay();
    OBJ_CLASSNAME(BandStarDisplay)
    OBJ_SET_TYPE(BandStarDisplay)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~BandStarDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();

    void SetNumStars(float, bool);
    void SetStarType(Symbol, bool);
    void Reset();
    void SetupStars();
    void ResetStars();

    float GetNumStars() const { return mNumStars; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(BandStarDisplay)
    static void Init() {
        Register();
    }
    REGISTER_OBJ_FACTORY_FUNC(BandStarDisplay)

    float mNumStars; // 0x18c
    ObjVector<ObjPtr<RndDir, ObjectDir> > mStars; // 0x190
    ObjVector<ObjPtr<RndAnimatable, ObjectDir> > mStarSweepAnims; // 0x19c
    ObjVector<ObjPtr<EventTrigger, ObjectDir> > mStarFullTriggers; // 0x1a8
    ObjVector<ObjPtr<EventTrigger, ObjectDir> > mStarGoldTriggers; // 0x1b4
    ObjPtr<RndAnimatable, ObjectDir> mStarOffsetAnim; // 0x1c0
    ObjPtr<Sequence, ObjectDir> mEarnStarSfx; // 0x1cc
    ObjPtr<Sequence, ObjectDir> mEarnSpadeSfx; // 0x1d8
    Symbol mStarType; // 0x1e4
};