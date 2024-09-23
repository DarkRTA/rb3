#pragma once
#include "rndobj/Dir.h"
#include "rndobj/Mesh.h"
#include "bandobj/BandStarDisplay.h"

class BandScoreboard : public RndDir {
public:
    BandScoreboard();
    OBJ_CLASSNAME(BandScoreboard)
    OBJ_SET_TYPE(BandScoreboard)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~BandScoreboard();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    void SetScore(int);
    void SetNumStars(float, bool);
    float GetNumStars() const;
    void Reset();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int mScore; // 0x18c
    ObjPtr<RndMesh, ObjectDir> unk190; // 0x190
    ObjPtr<RndMesh, ObjectDir> unk19c; // 0x19c
    ObjVector<int> unk1a8; // 0x1a8
    ObjVector<int> unk1b4; // 0x1b4
    ObjPtr<BandStarDisplay, ObjectDir> mStarDisplay; // 0x1c0
};